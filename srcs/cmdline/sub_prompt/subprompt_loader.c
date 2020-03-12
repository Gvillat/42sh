/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subprompt_loader.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:55:33 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/12 16:55:57 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	subprompt_loader(t_core *shell)
{
	while (TRUE)
	{
		ft_strdel(&shell->term.buffer);
		shell->term.buffer = ft_memalloc(BUFF_SIZE);
		display_subprompt(&shell->term);
		if (read_multiline(&shell->term) == FALSE)
			break ;
	}
}
