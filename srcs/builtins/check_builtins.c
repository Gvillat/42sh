/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:35:43 by fcatusse          #+#    #+#             */
/*   Updated: 2019/07/31 11:49:51 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "twenty_one.h"

int	check_builtins(char **cmd, char **env, t_read *term)
{
	(void)env;
	if (!ft_strcmp(term->buffer, "exit"))
		return (exit_sh(term));
	else if (!ft_strcmp(cmd[0], "history"))
		return (history(term, cmd));
	return (0);
}
