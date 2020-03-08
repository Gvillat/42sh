/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 18:59:53 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/08 21:17:09 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sh42.h"

static void	sig_handler(int signum)
{
	t_core	*shell;
	pid_t	pid;

	shell = get_core(NULL);
	if (signum == SIGTSTP)
		return ;
	reset_config(shell);
	pid = getpid();
	signal(signum, SIG_DFL);
	kill(pid, signum);
}

static void	sig_exit(int signum)
{
	t_core	*shell;

	shell = get_core(NULL);
	quit_shell(shell, 141, (signum == SIGPIPE) ? FALSE : TRUE);
}

static void	sigh_winch(int signum)
{
	t_core	*shell;

	(void)signum;
	fflush(stdout);
	shell = get_core(NULL);
	if (get_size(&(shell->term)) != SUCCESS || update_termsize(shell))
		quit_shell(shell, EXIT_SUCCESS, FALSE);
}

/*
**	HUP INT
**	QUIT ILL TRAP ABRT EMT
**	FPE KILL(NULL)BUS SEGV SYS PIPE
**	ALRM TERM URG STOP(NL) TSTP CONT
**	CHLD TTIN TTOU IO XCPU XFSZ
**	VTALRM PROF WINCH INFO USR1
**	USR2
*/

void		init_signals(void)
{
	static int	signals[27] = {SIGHUP, SIGINT, SIGQUIT, SIGILL, SIGTRAP
			, SIGABRT, SIGFPE, SIGBUS, SIGSEGV, SIGSYS, SIGPIPE, SIGALRM
			, SIGTERM, SIGURG, SIGTSTP, SIGCONT, SIGCHLD, SIGTTIN, SIGTTOU
			, SIGIO, SIGXCPU, SIGXFSZ, SIGVTALRM, SIGPROF, SIGWINCH, SIGUSR1
			, SIGUSR2};
	static void	(*sighandler[27])(int) = {sig_handler, sigint_handler
		, sig_handler, sig_handler, sig_handler, sig_handler, sig_handler
		, sig_handler, sig_handler, sig_handler, sig_exit, sig_handler
		, sig_handler, sig_handler, sig_handler, sig_exit, SIG_DFL, SIG_IGN
		, SIG_IGN, SIG_DFL, sig_handler, sig_handler, sig_handler, sig_handler
		, sigh_winch, sig_handler, sig_handler};
	size_t		i;

	i = 0;
	while (i < 27)
	{
		if (sighandler[i] != NULL)
			signal(signals[i], sighandler[i]);
		i++;
	}
}
