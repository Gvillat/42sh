/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_updates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:56:37 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/10/04 08:31:28 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include "sh42.h"

/*
 **	Create IFS set variable (Input Field Separator)
 */

int8_t	update_ifs(t_core *shell)
{
	char	*value;
	t_db	*db;

	db = NULL;
	value = NULL;
	if (shell != NULL && (db = get_or_create_db(shell, "IFS", INTERNAL_VAR)) != NULL)
	{
		value = ft_strdup("' \t\n'");
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}

/*
**	Create TERM set variable if not existing (default value = dumb)
**		- should only be executed at shell startup
*/

int8_t	create_term(t_core *shell)
{
	if (shell != NULL && search_db(shell->env, "TERM") == NULL)
	{
		if (ft_lstappend(&(shell->env), ft_lstnew(
				fetch_db(&(shell->db), "TERM=dumb", INTERNAL_VAR)
				, sizeof(t_db))) != NULL)
			return (SUCCESS);
	}
	return (FAILURE);
}

/*
 **	Create LINES and COLUMNS (set variables) with the terminal width and height
 **		- Should be updated each time SIGWINCH is captured
 */

int8_t	update_termsize(t_core *shell)
{
	struct winsize	ws;
	t_db			*db;
	char			*value;

	db = NULL;
	value = NULL;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	if (shell && (db = get_or_create_db(shell, "LINES", INTERNAL_VAR)) != NULL)
	{
		if (!(value = ft_itoa(ws.ws_row)) || modify_db(db, value, 0) == NULL)
		{
			ft_strdel(&value);
			return (FAILURE);
		}
	}
	if (shell && (db = get_or_create_db(shell, "COLUMNS", INTERNAL_VAR)))
	{
		if (!(value = ft_itoa(ws.ws_col)) || modify_db(db, value, 0) == NULL)
		{
			ft_strdel(&value);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
