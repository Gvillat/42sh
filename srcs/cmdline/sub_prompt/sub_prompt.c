/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 17:07:08 by fcatusse          #+#    #+#             */
/*   Updated: 2020/03/06 23:00:33 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

ssize_t		check_quote_priority(char *str, t_subprompt *sub)
{
	if (!str || str[sub->index] != '\'')
		return (1);
	sub->index++;
	while (str[sub->index])
	{
		if (str[sub->index] == '\'')
		{
			sub->index++;
			return (0);
		}
		sub->index++;
	}
	return (1);
}

enum e_subp	quote_subprompt(t_core *shell, t_subprompt *sub)
{
	if (check_quote_priority(shell->term.buffer, sub))
	{
		if (!sub->keys)
		{
			sub->keys = add_keys_subprompt('\'', sub->keys);
			sub->quoted = 1;
		}
		else if (sub->keys[0] == '\'')
		{
			sub->keys = del_keys_subprompt('\'', sub->keys);
			sub->quoted = 0;
		}
	}
	return (sub->state = SP_START);
}

ssize_t		check_dbquote_priority(t_core *shell, t_subprompt *sub)
{
	while (shell->term.buffer[++sub->index])
	{
		if (shell->term.buffer[sub->index] == '\\')
		{
			sub->index++;
			continue;
		}
		if (shell->term.buffer[sub->index] == '\"')
		{
			sub->index++;
			return (0);
		}
		if (shell->term.buffer[sub->index] == '$'
			&& shell->term.buffer[sub->index + 1] == '{')
			return (1);
	}
	return (1);
}

enum e_subp	dbquote_subprompt(t_core *shell, t_subprompt *sub)
{
	if (check_dbquote_priority(shell, sub))
	{
		if (!sub->keys)
		{
			sub->keys = add_keys_subprompt('\"', sub->keys);
			sub->dbquoted = 1;
		}
		else if (sub->keys[0] == '\"')
		{
			sub->keys = del_keys_subprompt('\"', sub->keys);
			sub->dbquoted = 0;
		}
		else
		{
			sub->keys = add_keys_subprompt('\"', sub->keys);
			sub->dbquoted = 1;
		}
	}
	return (sub->state = SP_START);
}

enum e_subp	braceparam_subprompt(t_core *shell, t_subprompt *sub)
{
	if (shell->term.buffer[sub->index] == '$'
		&& shell->term.buffer[sub->index + 1] == '{')
		sub->keys = add_keys_subprompt('}', sub->keys);
	sub->index++;
	return (sub->state = SP_START);
}
