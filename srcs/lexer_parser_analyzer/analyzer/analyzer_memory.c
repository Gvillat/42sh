/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:40:31 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/28 17:54:54 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		get_token(t_analyzer *analyzer)
{
	t_token	*tmp;

	if (!analyzer->lexer)
		return ;
	tmp = analyzer->lexer->content;
	free(tmp->data);
	free(tmp);
	analyzer->lexer = analyzer->lexer->next;
}

void		ft_free_redir(t_redir *redir)
{
	free(redir->op[0]);
	free(redir->op[1]);
	free(redir);
}

void		ft_free_redirlist(t_lst **head)
{
	t_lst	*curr;
	t_lst	*next;

	if (!*head)
		return ;
	curr = *head;
	next = NULL;
	while (curr)
	{
		if (curr->content)
			ft_free_redir((t_redir*)curr->content);
		next = curr;
		curr = curr->next;
		free(next);
	}
}

void		free_process_list(t_lst **head)
{
	t_lst		*tmp;
	t_lst		*process;
	t_process	*pro;

	process = NULL;
	pro = NULL;
	tmp = NULL;
	if (!head || !*head)
		return ;
	process = *head;
	*head = NULL;
	while (process)
	{
		if (process->content)
		{
			pro = (t_process*)process->content;
			ft_free_redirlist(&pro->redir_list);
			if (pro->av)
				ft_tabfree(pro->av);
		}
		free(process->content);
		tmp = process;
		process = process->next;
		free(tmp);
	}
}
