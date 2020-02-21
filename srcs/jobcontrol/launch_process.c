/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 12:55:51 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/21 02:43:02 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <signal.h>

void		reset_signals(void)
{
	int		i;

	i = 0;
	while (i++ < SIGUSR2)
		signal(i, SIG_DFL);
}

static void	put_process_in_grp(t_core *shell, t_process *process)
{
	(void)shell;
	process->pid = getpid();
	if (process->pgid == -1)
		process->pgid = process->pid;
	if (setpgid(process->pid, process->pgid) != SUCCESS)
	{
		dprintf(STDERR_FILENO, "42sh: setpgid error\n");
		exit(EXIT_FAILURE);
	}
}

static void	redir_pipes(t_process *process)
{
	if (process->pipe[0] != STDIN_FILENO)
	{
		dup2(process->pipe[0], STDIN_FILENO);
		close(process->pipe[0]);
	}
	if (process->pipe[1] != STDOUT_FILENO)
	{
		dup2(process->pipe[1], STDOUT_FILENO);
		close(process->pipe[1]);
	}
	if (process->close[0] != -1)
		close(process->close[0]);
	if (process->close[1] != -1)
		close(process->close[1]);
}

int8_t		launch_blt(t_core *shell, t_process *process)
{
	int		blt;

	if (process->pipe[0] == STDIN_FILENO && process->pipe[1] == STDOUT_FILENO
		&& process->av && (blt = is_a_blt(process->av[0])) != FAILURE)
	{
		process->status = 1;
		if (exec_redirs(shell, process, process->redir_list) == SUCCESS)
			process->status = call_builtin(shell, process, blt);
		process->completed = TRUE;
		shell->status = process->status;
		close_fds(process->redir_list);
		return (SUCCESS);
	}
	return (FAILURE);
}

void		launch_process(t_core *shell, t_process *process)
{
	int		blt;

	if (shell->is_interactive)
	{
		reset_signals();
		put_process_in_grp(shell, process);
	}
	redir_pipes(process);
	if (process->av)
	{
		if ((blt = is_a_blt(process->av[0])) != FAILURE)
			exit(call_builtin(shell, process, blt));
	}
	call_bin(shell, process);
}
