/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_nbr_nwl_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:55:48 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/03 17:54:18 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static t_lst	*isvalid_ionumber(t_lexer *lexer, t_lst *lexer_token, int i)
{
	char	*str;

	str = NULL;
	if ((lexer->buff[i] == '<' || lexer->buff[i] == '>'))
	{
		if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, i - lexer->buf_pos)))
			return (NULL);
		if (!(ft_lstappend(&lexer_token, ft_lstnew(
			fetch_token(&lexer->token, P_IONUMBER, str), sizeof(t_token)))))
			return (NULL);
		free(str);
		lexer->buf_pos = i;
		lexer->ntok++;
	}
	else
		return (lexer_token = name_lexer(lexer, lexer_token));
	return (lexer_token);
}

t_lst		*number_lexer(t_lexer *lx, t_lst *lexer_token)
{
	int		i;

	i = lx->buf_pos;
	if (!lx->buff[lx->buf_pos] || !ft_isdigit(lx->buff[lx->buf_pos]))
	{
		lx->status = L_END;
		return (lexer_token);
	}
	while (ft_isdigit(lx->buff[i]) && lx->buff[i])
		i++;
	lexer_token = isvalid_ionumber(lx, lexer_token, i);
	lx->status = L_START;
	return (lexer_token);
}

t_lst			*newline_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	char	*str;

	str = NULL;
	if (!lexer->buff[lexer->buf_pos])
	{
		lexer->status = L_END;
		return (lexer_token);
	}
	if (lexer->buff[lexer->buf_pos] == '\n')
	{
		if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, 1)))
			return (NULL);
		if (!(ft_lstappend(&lexer_token, ft_lstnew(
			fetch_token(&lexer->token, P_NEWLINE, str), sizeof(t_token)))))
			return (NULL);
		free(str);
		lexer->ntok++;
		lexer->buf_pos++;
	}
	lexer->status = L_START;
	return (lexer_token);
}
