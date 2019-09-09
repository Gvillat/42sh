/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 18:53:26 by fcatusse          #+#    #+#             */
/*   Updated: 2019/09/09 19:43:19 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*walking_history(char buff_tmp[BUFF_SIZE], t_read *line)
{
	t_lst	*history;

	history = line->history;
	while (history)
	{
		if (ft_strcmp(buff_tmp, "") && ft_strstr(history->data, buff_tmp) != 0)
		{
			xtputs(xtgetstr("cr", NULL), 1, my_outc);
			xtputs(xtgetstr("ce", NULL), 1, my_outc);
			dprintf(STDIN_FILENO, "(reverse-i-search)`%s':", buff_tmp);
			dprintf(STDIN_FILENO, " %s", history->data);
			ft_strcpy(line->buffer, history->data);
			return (history->data);
		}
		history = history->next;
	}
	return (NULL);
}

void		search_in_history(t_read *line)
{
	char	buff[READ_SIZE + 1];
	char	buff_tmp[BUFF_SIZE];
	int		i;

	i = -1;
	ft_bzero(buff_tmp, BUFF_SIZE);
	while (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		if (!is_print(*buff) && *buff != CTRL_R)
			return ;
		buff_tmp[++i] = *buff;
		walking_history(buff_tmp, line);
	}
}

void		research_mode(t_read **line)
{
	goto_prompt(*line);
	xtputs(xtgetstr("cr", NULL), 1, my_outc);
	xtputs(xtgetstr("ce", NULL), 1, my_outc);
	dprintf(STDIN_FILENO, "(reverse-i-search)`':");
	search_in_history(*line);
	xtputs(xtgetstr("cr", NULL), 1, my_outc);
	xtputs(xtgetstr("ce", NULL), 1, my_outc);
	display_prompt(*line);
	dprintf(STDIN_FILENO, "%s", (*line)->buffer);
	(*line)->x += ft_strlen((*line)->buffer);
	(*line)->width = (*line)->x;
	(*line)->x_index = (*line)->x;
}
