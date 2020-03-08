/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_redir_tok_exp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:47:03 by guvillat          #+#    #+#             */
/*   Updated: 2020/03/08 15:33:26 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <stdlib.h>

int8_t			add_assign_env(t_core *shell, const char *key, char *value)
{
	if (!key || !shell->env)
		return (FAILURE);
	if (edit_var(shell, key, value, INTERNAL_VAR) != SUCCESS)
		return (FAILURE);
	return (TRUE);
}

void			add_assign_envp(const char *key, char *value, char ***envp)
{
	char		*tmp;
	char		**tablo;
	int			i;

	tmp = NULL;
	tablo = *envp;
	i = -1;
	tmp = ft_strjoin(key, "=");
	tmp = ft_strjoinf(tmp, value, 4);
	while (tablo[++i])
	{
		if (!ft_strncmp(tablo[i], key, ft_strlen(key)))
		{
			ft_strdel(&tablo[i]);
			tablo[i] = ft_strdup(tmp);
			ft_strdel(&tmp);
			*envp = tablo;
			return ;
		}
	}
	tablo = ft_add_arg_cmd_process(tablo, tmp);
	ft_strdel(&tmp);
	*envp = tablo;
}

char			**add_underscore_envp(char **envp, char *data)
{
	int			i;

	i = 0;
	if (!*envp || !data)
		return (envp);
	while (envp[i])
	{
		if (envp[i][0] == '_' && envp[i][1] == '=')
			break ;
		i++;
	}
	ft_strdel(&(envp[i]));
	envp[i] = ft_strjoin("_=", data);
	return (envp);
}

u_int8_t		is_expansion(enum e_estate id)
{
	if (id == E_TILDEP)
		return (1);
	else if (id == E_TILDEM)
		return (2);
	else if (id == E_TILDE)
		return (3);
	else if (id == E_DBPARENT)
		return (4);
	else if (id == E_PARENT || id == E_BQUOTE)
		return (5);
	else if (id == E_BRACKET)
		return (6);
	else if (id == E_HOOK)
		return (7);
	else if (id == E_DOLLAR)
		return (8);
	else if (id == E_DBQUOTE)
		return (9);
	else if (id == E_QUOTE)
		return (0);
	return (0);
}

t_expansion		*init_expansion_inhibiteurs(t_expansion *exp)
{
	if (!(exp = (t_expansion*)malloc(sizeof(t_expansion))))
		return (NULL);
	exp->index = 0;
	exp->discarded = 0;
	exp->res = ft_strnew(0);
	exp->st = E_START;
	exp->quotus = NB_EXPANSION_STATE;
	exp->sionat[0] = no_exp;
	exp->sionat[1] = exp_tilde;
	exp->sionat[2] = exp_tilde;
	exp->sionat[3] = exp_tilde;
	exp->sionat[4] = exp_math;
	exp->sionat[5] = exp_cmd_subs;
	exp->sionat[6] = exp_param;
	exp->sionat[7] = exp_math;
	exp->sionat[8] = exp_param;
	exp->biteurs[E_START] = start_biteurs;
	exp->biteurs[E_EXP] = exp_biteurs;
	exp->biteurs[E_WORD] = word_biteurs;
	exp->biteurs[E_QUOTES] = quotes_biteurs;
	exp->biteurs[E_DISCARD] = discard_biteurs;
	exp->erience = 0;
	return (exp);
}
