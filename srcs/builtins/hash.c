/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 14:50:10 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/27 12:36:32 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>

void	print_hash_map(t_core *shell, u_int8_t format)
{
	t_lst	**map;
	t_lst	*cur_map;
	size_t	i;

	i = -1;
	if ((map = shell->hash.map) == NULL)
		return ;
	if (format & HASH_DEFAULT)
		dprintf(STDOUT_FILENO, "hits    command\n");
	while (++i < shell->hash.size)
	{
		cur_map = map[i];
		while (cur_map)
		{
			if (format & HASH_DEFAULT)
				dprintf(STDOUT_FILENO, "%4d    %s\n",
						((t_db *)cur_map->content)->hit,
						((t_db *)cur_map->content)->value);
			if (format & HASH_LISTED)
				dprintf(STDOUT_FILENO, "builtin hash -p %s %s\n",
						((t_db *)cur_map->content)->value,
						((t_db *)cur_map->content)->key);
			cur_map = cur_map->next;
		}
	}
}

void	free_hash_key(t_hash *hash, t_lst *map)
{
	ft_strdel(&((t_db *)map->content)->key);
	ft_strdel(&((t_db *)map->content)->value);
	free(map->content);
	free(map);
	map = NULL;
	hash->lenght--;
	if (hash->lenght == 0)
		reset_hash(hash);
}

void	hash_key_remover(t_core *shell, char *process)
{
	t_lst		*map;
	t_lst		*prev;
	u_int32_t	hash_value;

	if (shell->hash.map == NULL || process == NULL)
		return ;
	hash_value = get_hash(process, shell->hash.size);
	map = shell->hash.map[hash_value];
	if (map && ft_strequ(((t_db *)map->content)->key, process) == TRUE)
	{
		shell->hash.map[hash_value] = map->next;
		return (free_hash_key(&shell->hash, map));
	}
	while (map && ft_strequ(((t_db *)map->content)->key, process) == FALSE)
	{
		prev = map;
		if ((map = map->next) == NULL)
		{
			dprintf(STDERR_FILENO, "42sh: hash: %s: not found\n", process);
			return ;
		}
	}
	prev->next = map->next;
	free_hash_key(&shell->hash, map);
}

int		get_hash_t_pad(char *key)
{
	int	pad;

	pad = ft_strlen(key);
	if (pad > 8)
		pad += 7;
	else if (pad == 8)
		pad += 8;
	else
		pad = 8;
	return (pad);
}

void	find_hash_sub_map(t_process *process, t_lst *map, size_t i, int ac)
{
	t_lst	*sub_map;

	sub_map = map;
	while (sub_map)
	{
		if (ft_strequ(process->av[i], ((t_db *)sub_map->content)->key))
		{
			if (ac > 3)
				dprintf(STDOUT_FILENO, "%-*s%s\n",
					get_hash_t_pad(((t_db *)sub_map->content)->key),
					((t_db *)sub_map->content)->key,
					((t_db *)sub_map->content)->value);
			else
				dprintf(STDOUT_FILENO, "%s\n",
					((t_db *)sub_map->content)->value);
				((t_db *)sub_map->content)->hit += 1;
			break ;
		}
		sub_map = sub_map->next;
	}
	if (sub_map == NULL)
		dprintf(STDERR_FILENO,
			"42sh: hash: %s: not found\n", process->av[i]);
}

void	find_hash(t_core *shell, t_process *process, int ac)
{
	t_lst	**map;
	size_t	i;

	i = 2;
	map = NULL;
	if (shell->hash.map)
		map = shell->hash.map;
	while (process->av[i])
	{
		shell->hash.value = get_hash(process->av[i], shell->hash.size);
		if (map == NULL || map[shell->hash.value] == NULL)
		{
			dprintf(STDERR_FILENO,
				"42sh: hash: %s: not found\n", process->av[i]);
			i++;
			continue ;
		}
		find_hash_sub_map(process, map[shell->hash.value], i, ac);
		i++;
	}
}

int8_t	parse_hash(t_core *shell, int ac, t_process *process)
{
	u_int64_t	options;
	size_t		i;

	options = get_options(ac, process->av, "rlpdt");
	if (options & (1ULL << 63))
	{
		print_usage("hash", options % 128, "[-rl] [-p pathname] [-dt] [name ...]");
		return (FAILURE);
	}
	if (options & (1ULL << 11))
	{
		print_hash_map(shell, HASH_LISTED);
		return (FAILURE);
	}
	if (options & (1ULL << 3))
	{
		if (ac == 2)
			return (SUCCESS);
		i = 2;
		while (process->av[i])
			hash_key_remover(shell, process->av[i++]);
		return (FAILURE);
	}
	if (options & (1ULL << 17))
	{
		free_hash_map(&shell->hash);
		return (FAILURE);
	}
	if (options & (1ULL << 19))
	{
		if (ac == 2)
		{
			dprintf(STDERR_FILENO, "42sh: hash: -t: option requires an argument\n");
			return (FAILURE);
		}
		find_hash(shell, process, ac);
		return (FAILURE);
	}
	if (options & (1ULL << 15))
	{
		if (ac == 2)
		{
			dprintf(STDERR_FILENO, "42sh: hash: -p: option requires an argument\n");
			print_usage("hash", 0, "[-rl] [-p pathname] [-dt] [name ...]");
			return (FAILURE);
		}
		if (ac == 3)
			return (SUCCESS);
		if (is_a_dir(process->av[2]) == EISDIR)
		{
			i = 3;
			while (process->av[i])
			{
				dprintf(STDERR_FILENO, "42sh: hash: %s: Is a directoy\n", process->av[2]);
				i++;
			}
			return (FAILURE);
		}
		hash_map_dispatcher(shell, process, HASH_PATH);
		return (FAILURE);
	}
	return (SUCCESS);
}

int8_t	builtin_hash(t_core *shell, t_process *process)
{
	int	ac;

	ac = ft_tablen(process->av);
	if (parse_hash(shell, ac, process) != SUCCESS)
		return (FAILURE);
	print_hash_map(shell, HASH_DEFAULT);
	return (SUCCESS);
}
