/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 19:32:26 by guvillat          #+#    #+#             */
/*   Updated: 2020/01/25 13:53:41 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t is_expansion(enum e_pstate id)
{
	if (id == P_TILDEP || id == P_TILDEM || id == P_TILDE
			|| id == P_DBPARENT || id == P_PARENT || id == P_DBQUOTE
			|| id == P_BRACKET || id == P_HOOK ||id == P_DOLLAR)
		return (TRUE);
	return (FALSE);
}

char *exp_error(char *data, t_core *shell)
{
	(void)shell;
	printf("EXP_ERROR [%s]\n", data);
	return (data);
}

int8_t add_assign_env(t_lst *lst, t_core *shell)
{
	char	*value;
	t_lst	*tmp;

	if (!lst || !shell->env)
		return (FAILURE);
	value = NULL;
	tmp = NULL;
	while (lst)
	{
		value = ft_strdup(((t_db*)lst->content)->value);
		if (edit_var(shell, ((t_db*)lst->content)->key, value, INTERNAL_VAR) != SUCCESS)
		{
			// free(value);
			return (FAILURE);
		}
		tmp = lst;
		lst = lst->next;
		ft_strdel(&((t_db*)tmp->content)->key);
		ft_strdel(&((t_db*)tmp->content)->value);
		free(tmp);
	}
	return (TRUE);
}

char *start_expansion(t_core *shell, char *data)
{
	int 	i;
	t_expan expan[] = 	{
		{exp_tilde, P_TILDE, 1, "~"},
		{exp_tilde, P_TILDEP, 2, "~+"},
		{exp_tilde, P_TILDEM, 2, "~-"},
		{exp_math, P_DBPARENT, 3, "$(("},
		{exp_cmd_subs, P_PARENT, 2, "$("},
		{exp_param, P_BRACKET, 2, "${"},
		{exp_math, P_HOOK, 2, "$["},
		{exp_param, P_DOLLAR, 1, "$"},
	};
	i = 0;
	if (!data || !shell->env)
		return (data);
	while (i < NB_OF_EXP)
	{
		if (!(ft_strncmp(data, expan[i].data, expan[i].len)))
			data = expan[i].machine(data, shell);
		i++;
	}
	return (data);
}

// char *do_exp_in_dbquote(char *str, t_cre *shell)
// {
// 	va parcourir la str et check a chaque ~ ou $ lexpansion si ya pas dexpansion go next et join
// }

void		find_expansion(char **tablo, t_core *shell)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (tablo[++i])
	{
		tmp = ft_strdup(tablo[i]);
		if (tablo[i][0] == '$' || tablo[i][0] == '~')
		{
			//LEAKS
			tmp = start_expansion(shell, tmp);
			free(tablo[i]);
			tablo[i] = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		// else if (tablo[i][0] == '\"')
		// {
		// 	tmp = do_exp_in_dbquote(tmp, shell)
		// 	free(tablo[i]);
		// 	tablo[i] = ft_strdup(tmp);
		// 	ft_strdel(&tmp);
		// }
	}
}

void		expansion(t_core *shell, t_process *process)
{
	char	**tablo;

	tablo = NULL;
	if (!process->av)
		return ;
	tablo = ft_tabcopy(tablo, process->av);
	find_expansion(tablo, shell);
	ft_tabfree(process->av);
	process->av = ft_tabcopy(process->av, tablo);
	ft_tabfree(tablo);
}
