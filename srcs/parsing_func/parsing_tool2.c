/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tool2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:22:37 by sseo              #+#    #+#             */
/*   Updated: 2021/02/02 18:40:34 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			parse_double_quote_loop(const char *line, char **p_data, \
		size_t *p_start, size_t *p_len)
{
	if (line[*p_start + *p_len] == '\\' && \
			(line[*p_start + *p_len + 1] == '\\' || \
			 line[*p_start + *p_len + 1] == '\"' || \
			 line[*p_start + *p_len + 1] == '$' || \
			 line[*p_start + *p_len + 1] == '`'))
	{
		if (update_data(line, p_data, p_start, p_len))
			return (1);
		(*p_start)++;
		(*p_len)++;
		if (update_data(line, p_data, p_start, p_len))
			return (1);
	}
	else if (line[*p_start + *p_len] == '$')
	{
		if (update_data(line, p_data, p_start, p_len))
			return (1);
		if (parse_env_variables(line, p_data, p_start))
			return (1);
	}
	else if (line[*p_start + *p_len] == 0)
		return (2);
	else
		(*p_len)++;
	return (0);
}
