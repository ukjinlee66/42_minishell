/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:19:03 by sseo              #+#    #+#             */
/*   Updated: 2021/02/02 20:39:18 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				update_data(const char *line, char **p_data, \
				size_t *p_start, size_t *p_len)
{
	char		*new_data;
	char		*data;
	size_t		start;
	size_t		len;

	data = *p_data;
	start = *p_start;
	len = *p_len;
	*p_start = start + len;
	*p_len = 0;
	if (len == 0)
		return (0);
	if (!(new_data = ft_substr(line, (unsigned int)start, len)))
		return (1);
	if (data == 0)
		*p_data = new_data;
	else
	{
		*p_data = ft_strjoin((char const *)data, (char const *)new_data);
		free(data);
		free(new_data);
		if (*p_data == 0)
			return (1);
	}
	return (0);
}

int				flush_data(t_list **p_out, const char *line, \
				char **p_data, size_t *p_start)
{
	char			c;
	void			*data;
	size_t			len;

	c = line[*p_start];
	data = (void *)(*p_data);
	if (add_data(p_out, &data))
		return (1);
	if (c == '>' && line[*p_start + 1] == '>')
		len = 2;
	else if (c == ';' || c == '>' || c == '<' || c == '|' || c == ' ')
		len = 1;
	else
		len = 0;
	if (c == ';' || c == '>' || c == '<' || c == '|' || len == 2)
	{
		if (!(data = (void *)ft_substr(line, (unsigned int)*p_start, len)))
			return (1);
		if (add_data(p_out, &data))
			return (1);
	}
	*p_start += len;
	*p_data = 0;
	return (0);
}

t_list			*print_parse_error(t_list *out, char *data, int eno, \
				t_list *temp)
{
	if (data)
		free(data);
	if (eno & 4)
	{
		write(1, "syntax error near unexpected token \'", 36);
		if (!temp->next)
			write(1, "newline\'\n", 9);
		else
		{
			write(1, temp->next->data, ft_strlen(temp->next->data));
			write(1, "\'\n", 2);
		}
	}
	else if (eno & 2)
		write(1, "multiline error\n", 16);
	else if (eno & 1)
		write(1, "malloc error\n", 13);
	free_list(out);
	return (0);
}

static size_t	check_env_variable(const char *line, size_t *p_start, \
				char **p_data, size_t *p_origin_start)
{
	size_t		len;

	len = 0;
	while ((line[*p_start + len] >= 'a' && line[*p_start + len] <= 'z') || \
			(line[*p_start + len] >= 'A' && line[*p_start + len] <= 'Z') || \
			(line[*p_start + len] >= '0' && line[*p_start + len] <= '9'))
		len++;
	if (!len)
	{
		if (line[*p_start] == '?')
		{
			*p_origin_start += 2;
			*p_start = 0;
			len = ft_strlen(g_ret_str);
			if (update_data(g_ret_str, p_data, p_start, &len))
				return (0);
		}
		len = 1;
		if (update_data(line, p_data, p_origin_start, &len))
			return (0);
	}
	return (len);
}

int				parse_env_variables(const char *line, char **p_data, \
				size_t *p_start)
{
	size_t		len;
	size_t		start;
	char		*target_variable;
	int			env_idx;

	start = *p_start + 1;
	if ((len = check_env_variable(line, &start, p_data, p_start)))
	{
		if (!(target_variable = ft_substr(line, (unsigned int)start, len)))
			return (1);
		env_idx = get_env_list(target_variable);
		free(target_variable);
		*p_start = start + len;
		if (env_idx >= 0)
		{
			start = len + 1;
			len = ft_strlen(g_envl[env_idx]) - start;
			return (update_data(g_envl[env_idx], p_data, &start, &len));
		}
	}
	return (0);
}
