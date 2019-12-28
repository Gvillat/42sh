/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:42:37 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/26 15:58:54 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_process	*find_process(t_lst *job, pid_t pid)
{
	t_lst *process;
	while (job != NULL)
	{
		process = ((t_job*)job->content)->process_list;
		while (process)
		{
			if (((t_process*)process->content)->pid == pid)
				return (((t_process*)process->content));
			process = process->next;
		}
		job = job->next;
	}
	return (NULL);
}

t_job	*find_job(t_lst *job, pid_t pgid)
{
	while (job != NULL)
	{
		if (((t_job*)job->content)->pgid == pgid)
			return (((t_job*)job->content));
		job = job->next;
	}
	return (NULL);
}

int8_t	job_is_stopped(t_job *job)
{
	t_lst	*ptr;

	ptr = job->process_list;
	while (ptr != NULL)
	{
		if (((t_process*)ptr->content)->completed != TRUE
				&& ((t_process*)ptr->content)->stopped != TRUE)
			return (FAILURE);
		ptr = ptr->next;
	}
	return (SUCCESS);
}

int8_t	job_is_completed(t_job *job)
{
	t_lst	*ptr;

	ptr = job->process_list;
	while (ptr != NULL)
	{
		if (((t_process*)ptr->content)->completed != TRUE)
			return (FAILURE);
		ptr = ptr->next;
	}
	return (SUCCESS);
}
