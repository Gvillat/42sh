/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_analyzer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:51:01 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/03 17:59:04 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		ft_freejoblist(t_lst **lst)
{
	t_lst	*tmp;
	t_lst	*node;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		node = tmp;
		if (tmp->content)
		{
			free_process_list(&((t_job*)tmp->content)->process_list);
			free(((t_job*)tmp->content)->command);
			free((t_job*)tmp->content);
		}
		if (!tmp->next)
		{
			free(tmp);
			break ;
		}
		tmp = tmp->next;
		free(node);
	}
	*lst = NULL;
}

void		ft_freetokenlist(t_lst **lst)
{
	t_lst	*tmp;
	t_lst	*node;

	if (!*lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		node = tmp;
		if (tmp->content)
		{
			ft_strdel(&((t_token*)tmp->content)->data);
			free(tmp->content);
		}
		if (!tmp->next)
		{
			free(tmp);
			break ;
		}
		tmp = tmp->next;
		if (node)
			free(node);
	}
}

/*
static void	ft_freedblist(t_lst **lst)
{
	t_lst	*tmp;
	t_lst	*node;

	if (!*lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		node = tmp;
		if (tmp->content)
		{
			free(((t_db*)tmp->content)->key);
			free(((t_db*)tmp->content)->value);
			free((t_db*)tmp->content);
		}
		if (!tmp->next)
		{
			free(tmp);
			break ;
		}
		tmp = tmp->next;
		free(node);
	}
}*/

void		lexer_parser_analyzer(t_core *shell)
{
	t_lst	*lxr_tok;

	lxr_tok = lexer(shell->term.buffer);
	if (lxr_tok == NULL)
		return ;
	if (parser(lxr_tok) == TRUE)
	{
		analyzer(shell, lxr_tok);
		//ft_printjoblst(shell->job_list);
	}
	ft_freetokenlist(&lxr_tok);
}
