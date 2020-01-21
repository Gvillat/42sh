/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 17:07:08 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/21 21:52:55 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		display_subprompt(t_read *term, char *prompt)
{
	ft_strcpy(term->prompt, prompt);
	term->prompt_len = ft_strlen(term->prompt);
	term->x = term->prompt_len;
	term->y = 0;
	term->width = term->x;
	term->x_index = term->x;
	term->sub_prompt = 1;
	ft_printf(term->prompt);
}

uint8_t		read_multiline(t_read *term, char sb)
{
	char	buff[READ_SIZE + 1];

	ft_bzero(buff, READ_SIZE);
	while (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		if (check_caps(buff, term) == TRUE)
		{
			ft_bzero(buff, READ_SIZE);
			continue ;
		}
		else
		{
			if (sb == BACKSLASH && check_backslash(term, &sb) == FALSE)
				return (FALSE);
			else if (sb == FALSE)
				return (FALSE);
			else if (sb != BACKSLASH && ft_strchr(term->buffer, sb))
				return (FALSE);
			else if (sb != BACKSLASH)
				term->buffer = ft_strjoinf(term->buffer, "\n", 1);
			break ;
		}
	}
	return (TRUE);
}

int8_t		check_sb_read(t_read *term, char sb)
{
	if (read_multiline(term, sb) == FALSE)
	{
		term->sub_prompt = FALSE;
		term->buffer = ft_strjoinf(term->tmp_buff, term->buffer, 2);
		if (quotes_is_matching(term, &sb) == FALSE)
		{
			term->buffer = ft_strjoinf(term->buffer, "\n", 1);
			ft_strdel(&term->tmp_buff);
			term->tmp_buff = ft_strdup(term->buffer);
			return (TRUE);
		}
		else
			return (FALSE);
	}
	return (TRUE);
}

void		load_subprompt(char sb, t_read *term)
{
	if (sb != BACKSLASH)
		term->buffer = ft_strjoinf(term->buffer, "\n", 1);
	term->tmp_buff = ft_strdup(term->buffer);
	term->status = CMD_SUBPROMPT;
	while (TRUE)
	{
		ft_strdel(&term->buffer);
		term->buffer = ft_memalloc(BUFF_SIZE);
		display_subprompt(term, PS2);
		if (check_sb_read(term, sb) == FALSE)
			break ;
		if (term->status == CMD_PROMPT)
			return ;
		term->tmp_buff = ft_strjoinf(term->tmp_buff, term->buffer, 1);
	}
	ft_strdel(&term->tmp_buff);
	term->status = CMD_DONE;
}
