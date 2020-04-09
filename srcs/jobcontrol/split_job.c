//HEADER

#include "sh42.h"

static void	erase_process(t_process *process)
{
	process->tok_list = NULL;
	process->assign_list = NULL;
	process->redir_list = NULL;
	process->envp = NULL;
	process->av = NULL;
	process->bin = NULL;
	process->command = NULL;
}

static void	copy_process_list(t_job *job, t_job *new_job)
{
	t_process	process;
	t_lst		*process_list;
	t_lst		*ptr;
	
	ptr = job->process_list;
	process_list = NULL;
	if (((t_process*)ptr->content)->type == P_PIPE)
	{
		while (((t_process*)ptr->content)->type == P_PIPE)
		{
			ft_memcpy(&process, ptr->content, sizeof(t_process));
			ft_lstappend(&process_list, ft_lstnew(&process, sizeof(t_process)));
			erase_process(ptr->content);
			ptr = ptr->next;
		}
		ptr = ptr->next;
	}
	ft_memcpy(&process, ptr->content, sizeof(t_process));
	ft_lstappend(&process_list, ft_lstnew(&process, sizeof(t_process)));
	erase_process(ptr->content);
	new_job->process_list = process_list;
}

void	split_job(t_core *shell, t_job *job)
{
	t_lst	*ptr;
	t_job	new_job;

	ptr = job->process_list;
	ft_bzero(&new_job, sizeof(t_job));
	copy_process_list(job, &new_job);
	job->pgid = -1;
	new_job.pgid = job->pgid;
	new_job.type = P_SEMICOLON;
	new_job.process_list = job->process_list;
	//rebuild_job_command(&new_job);
	ft_lstappend(&(shell->launched_jobs), ft_lstnew(&new_job, sizeof(t_job)));
}
