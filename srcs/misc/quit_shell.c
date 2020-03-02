/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 23:52:50 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/02 14:45:49 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	quit_shell(t_core *shell, int exit_value, int8_t v)
{
	write_history(shell);
	if (shell->is_interactive)
    {
        reset_config(shell);
	    save_history(&shell->term);
	    write_history(shell);
    }
	free_shell(shell);
	if (shell->is_interactive && v == TRUE)
		write(STDERR_FILENO, "exit\n", 5);
	longjmp(g_exit_leaks, 42);
	exit(exit_value);
}
