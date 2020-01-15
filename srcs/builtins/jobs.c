/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:22:47 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/15 21:18:35 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	print_longjob(t_job *job)
{
	t_process	*process;
	t_lst		*ptr;

	ptr = job->process_list;
	while (ptr != NULL)
	{
		process = ((t_process *)ptr->content);
		if (ptr == job->process_list)
			printf("[%d]%c %d %-24s %s\n", job->jobc_id, job->jobc_last
			, process->pid, signal_msg(process->status), "process->cmd");
		else
			printf("     %d %24s%s\n", process->pid
			, signal_msg(process->status), "process->command");
		ptr = ptr->next;
	}
}

static void	print_job(t_job *job, uint64_t opt)
{
	if (opt & (1ULL << 15))
		printf("%d\n", job->pgid);
	else if (opt & (1ULL << 11))
		print_longjob(job);
	else
		printf("[%d]%c  %s\t\t%s\n", job->jobc_id, job->jobc_last
		, (job_is_stopped(job)) ? "Stopped" : "Done", job->command);
}

int8_t		builtin_jobs(t_core *shell, t_process *process)
{
	uint64_t	opt;
	t_lst		*job;
	int			argc;
	int			i;

	argc = ft_tablen(process->av);
	job = shell->launched_jobs;
	i = (process->av[1] && ft_strcmp(process->av[1], "--") == 0) ? 2 : 1;
	if (shell->launched_jobs)
		update_status(shell);
	if ((opt = get_options(argc, process->av, "lp")) & OPT_ERROR)
		print_usage("42sh: jobs", opt & 0xFF, "jobs [-lp] [jobspec ...]");
	if (i == argc)
		while (job)
		{
			print_job(job->content, opt);
			job = job->next;
		}
	else
		while (i < argc)
		{
			job->content = get_job(shell->launched_jobs, process->av[i++]);
			print_job(job->content, opt);
		}
	return (SUCCESS);
}
