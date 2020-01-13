/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_io_nwln_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:23:16 by guvillat          #+#    #+#             */
/*   Updated: 2019/11/03 14:56:27 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int 	get_word_size_ntype(int i, char *str, e_pstate *state)
{
	int index;
	e_pstate stat;

	if (!str || !str[i])
		return (0);
	index = i;
	stat = *state;
	while (str[index] && (!ft_strchr(CHAR_INTERRUPT, str[index]) && !ft_strchr(EXPANSION, str[index])))
	{
		if (str[index] == '\'')
			while (str[index++] && str[index] != '\'')
				stat = P_QUOTE;
		if (str[index] == '\"')
			while (str[index++] && str[index] != '\"')
				stat = P_DBQUOTE;
		if (str[index] == '`')
			while (str[index++] && str[index] != '`')
				stat = P_BQUOTE;
		index++;
	}
	*state = stat;
	return (index);
}

t_lst		*word_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	int		i;
	char	*str;
	e_pstate state;

	i = lexer->buf_pos;
	str = NULL;
	state = P_WORD;
	if (!(i = get_word_size_ntype(i, lexer->buff, &state)))
		return (NULL);
	if (!(str = ft_strsub(lexer->buff, lexer->buf_pos, i - lexer->buf_pos)))
		return (NULL);
	ft_lstappend(&lexer_token, ft_lstnew(
		fetch_token(&lexer->token, state, str), sizeof(t_token)));
	free(str);
	lexer->ntok++;
	lexer->buf_pos = i;
	return (lexer_token);
}

t_lst		*name_lexer(t_lexer *lexer, t_lst *lexer_token)
{
	if (lexer->buff == '\0')
	{
		lexer->status = L_END;
		return (lexer_token);
	}
	if (ft_strchr(EXPANSION, lexer->buff[lexer->buf_pos]))
		lexer_token = expansion_lexer(lexer, lexer_token);
	else
		lexer_token = word_lexer(lexer, lexer_token);
	lexer->status = L_START;
	return (lexer_token);
}
