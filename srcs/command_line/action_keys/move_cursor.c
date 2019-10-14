/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:36:52 by fcatusse          #+#    #+#             */
/*   Updated: 2019/10/14 15:47:53 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Arrow down print the prev saved in history from history index
*/

void			move_key_down(t_read *line)
{
	t_lst	 	*w;
	int		i;

	i = -1;
	if (line->history && line->history_index)
	{
		goto_prompt(line);
		memset(line->buffer, 0, strlen(line->buffer));
		if (line->history_index && line->history_index->prev)
		{
			w = line->history_index->prev;
			line->history_index = w;
		}
		else
		{
			line->history_index = line->history->prev;
			return ;
		}
		while (w->content && ((char*)w->content)[++i])
			insert_char_in_buffer(((char*)w->content)[i], line, i);
	}
}

/*
**	Arrow up print the next saved in history from history index
*/

void			move_key_up(t_read *line)
{
	t_lst	 	*w;
	int		i;

	i = -1;
	if (line->history)
	{
		if (line->history_index && !line->history_index->next)
			return ;
		if (line->history_index && line->history_index->next)
		{
			w = line->history_index->next;
			line->history_index = w;
		}
		else
		{
			line->history_index = line->history;
			w = line->history;
		}
		goto_prompt(line);
		memset(line->buffer, 0, strlen(line->buffer));
		while (w->content && ((char *)w->content)[++i])
			insert_char_in_buffer(((char *)w->content)[i], line, i);
	}
}

/*
**	Arrow right to move the cursor one char on the right
*/

void			move_right(char *buff, t_read *input)
{
	int		width;
	int		buff_index;

	(void)buff;
	width = get_width_current_line(input);
	buff_index = input->x_index - input->prompt_len;
	if (input->x < width)
	{
		xtputs(input->tcaps[KEY_RIGHT], 1, my_outc);
		input->x_index++;
		input->x++;
	}
	else if (input->x == input->ws_col || *buff == NEW_LINE
			|| input->buffer[buff_index] == NEW_LINE)
	{
		xtputs(input->tcaps[LEFT_MARGIN], 1, my_outc);
		xtputs(input->tcaps[KEY_DOWN], 1, my_outc);
		input->x_index++;
		input->x = 0;
		input->y++;
	}
}

/*
**	Arrow left to move the cursor one char on the left
*/

void		move_left(char *buff, t_read *input)
{
	int		width;

	(void)buff;
	if ((input->x > input->prompt_len && input->y == 0)
		|| (input->x > 0 && input->y > 0))
	{
		xtputs(input->tcaps[KEY_LEFT], 1, my_outc);
		input->x_index--;
		input->x--;
	}
	else if (input->y > 0 && input->x == 0)
	{
		width = get_width_last_line(input);
		input->x = width;
		xtputs(input->tcaps[KEY_LEFT], 1, my_outc);
		if (width < input->prompt_len)
		{
			while (width--)
				xtputs(input->tcaps[KEY_RIGHT], 1, my_outc);
			xtputs(input->tcaps[KEY_UP], 1, my_outc);
		}
		input->x_index--;
		input->y--;
	}
}
