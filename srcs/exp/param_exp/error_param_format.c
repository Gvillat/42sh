/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_param_format.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:29:22 by guvillat          #+#    #+#             */
/*   Updated: 2020/04/23 16:56:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

char	*error_moar_format_third(char **tablo, char *data, t_core *shell)
{
	ft_dprintf(STDERR_FILENO,
		"42sh: %s: %s  syntax error: operand expected\
(error token is \"%s\")\n", tablo[0], data, data);
	ft_tabfree(tablo);
	shell->status = 2;
	shell->subst_error = 1;
	return (NULL);
}

char	*error_moar_format_bis(char *data, t_core *shell)
{
	ft_dprintf(STDERR_FILENO,
		"42sh: %s  syntax error: operand expected\
(error token is \":\")\n", data);
	ft_strdel(&data);
	shell->status = 2;
	shell->subst_error = 1;
	return (NULL);
}

char	*one_moar_error(char **tablo, char *data, t_core *shell)
{
	ft_dprintf(STDERR_FILENO, "42sh: %s : bad substitution\n", tablo[0]);
	ft_tabfree(tablo);
	ft_strdel(&data);
	shell->status = 2;
	shell->subst_error = 1;
	return (NULL);
}

char	*error_moar_format_param(char **tablo, char *data, t_core *shell)
{
	ft_dprintf(STDERR_FILENO,
		"42sh: %s  syntax error: operand expected (error token is \"%s\")\n",
		data, &data[ft_strlen(tablo[0])
		+ ft_strlen(tablo[1]) + ft_strlen(tablo[2]) + 2]);
	ft_tabfree(tablo);
	ft_strdel(&data);
	shell->status = 2;
	shell->subst_error = 1;
	return (NULL);
}

char	*dash_format(char **tablo, t_core *shell)
{
	char	*value;
	size_t	i;

	i = 1;
	value = NULL;
	if ((value = check_env_key(tablo[0], shell)))
	{
		ft_tabfree(tablo);
		return (ft_strdup(value));
	}
	if (tablo[1])
	{
		if (tablo[1][1] == '$')
			value = exp_param(&tablo[1][1], shell);
		else if (tablo[1][1] == '~')
			value = exp_tilde(&tablo[1][1], shell);
		else
			value = ft_strdup(&tablo[1][1]);
	}
	ft_tabfree(tablo);
	return (value);
}
