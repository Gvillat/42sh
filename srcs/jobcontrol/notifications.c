/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 13:17:48 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/17 06:18:29 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t		mark_process_status(t_core *shell
		, t_lst *jobs, pid_t pid, int status)
{
	t_process	*process;

	if (pid > 0)
	{
		if ((process = find_process(jobs, pid)) && process->pid == pid)
		{
			if (WIFSTOPPED(status))
			{
				printf("\n");
				process->status = 18;
				process->stopped = TRUE;
			}
			else
			{
				process->completed = TRUE;
				process->status = (WIFEXITED(status))
					? WTERMSIG(status) : WEXITSTATUS(status);
				status_handler(shell, status);
			}
		}
		return (SUCCESS);
	}
	else if (pid != 0)
		dprintf(STDERR_FILENO, "42sh: waitpid error (mark_process_status)\n");
	return (FAILURE);
}

void		update_status(t_core *shell)
{
	pid_t	pid;
	int		status;

	if (!shell->launched_jobs)
		return ;
	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (pid > 0
		&& !mark_process_status(shell, shell->launched_jobs, pid, status))
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	}
}

void		format_job_info(t_job *job)
{
	static char	*str[2] = {"Stopped", "Done"};
	int			status;

	if (job_is_completed(job))
		status = 1;
	else if (job_is_stopped(job) && job->notified == FALSE)
		status = 0;
	else
		return ;
	dprintf(STDERR_FILENO, "[%i]%c  %s\t\t%s\n", job->jobc_id
		, job->jobc_last, str[status], job->command);
}

static void	free_job(t_core *shell, t_lst *job)
{
	t_lst	*ptr;

	ptr = shell->launched_jobs;
	if (shell->launched_jobs != job)
	{
		while (ptr && ptr->next != job)
			ptr = ptr->next;
		ptr->next = job->next;
	}
	else
		shell->launched_jobs = job->next;
	free_process_list(job->content);
	ft_strdel(&(((t_job*)job->content)->command));
	free(job);
}

static void	attr_jobc_id(t_core *shell, t_job *job)
{
	t_lst	*jobs;
	t_job	*ptr;
	int		c;

	c = 0;
	jobs = shell->launched_jobs;
	while (jobs)
	{
		ptr = ((t_job*)jobs->content);
		if (ptr != job && ptr->jobc_id > c)
			c = ptr->jobc_id;
		ptr->jobc_last = (ptr->jobc_last == '+') ? '-' : ' ';
		jobs = jobs->next;
	}
	job->jobc_id = c + 1;
	job->jobc_last = '+';
}

int8_t		do_job_notification(t_core *shell)
{
	t_lst *job;
	t_lst *jnext;
	t_job *ptr;

	update_status(shell);
	job = shell->launched_jobs;
	while (job)
	{
		ptr = ((t_job*)job->content);
		jnext = job->next;
		format_job_info(ptr);
		if (job_is_completed(ptr))
		{
			free_job(shell, job);
			job = shell->launched_jobs;
			ptr = NULL;
		}
		else if (job_is_stopped(ptr) && ptr->notified != TRUE)
		{
			attr_jobc_id(shell, ptr);
			ptr->notified = TRUE;
		}
		job = jnext;
	}
	return (SUCCESS);
}
