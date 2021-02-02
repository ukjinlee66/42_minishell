/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:18:51 by sseo              #+#    #+#             */
/*   Updated: 2021/02/02 21:54:06 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		parse_double_quote(const char *line, char **p_data, \
		size_t *p_start)
{
	int				eno;
	size_t			len;
	size_t			start;

	len = 0;
	start = *p_start + 1;
	while (line[start + len] != '\"')
		if ((eno = parse_double_quote_loop(line, p_data, &start, &len)))
			return (eno);
	if ((update_data(line, p_data, &start, &len)))
		return (1);
	*p_start = start + 1;
	return (0);
}

static int		parse_single_quote(const char *line, char **p_data, \
		size_t *p_start)
{
	size_t			len;
	size_t			start;

	len = 0;
	start = *p_start + 1;
	while (line[start + len] != '\'')
	{
		if (line[start + len] == 0)
			return (2);
		len++;
	}
	if ((update_data(line, p_data, &start, &len)))
		return (1);
	*p_start = start + 1;
	return (0);
}

static int		support_split_line(const char *line, char **p_data, \
		size_t *p_start, char c)
{
	size_t			len;
	int				my_errno;

	my_errno = 0;
	if (c == '$')
		my_errno |= parse_env_variables(line, p_data, p_start);
	else if (c == '\'')
		my_errno |= parse_single_quote(line, p_data, p_start);
	else if (c == '\"')
		my_errno |= parse_double_quote(line, p_data, p_start);
	else if (c == '\\')
	{
		len = 1;
		(*p_start)++;
		my_errno |= update_data(line, p_data, p_start, &len);
	}
	return (my_errno);
}

static int		split_line_main(t_list **p_out, char **p_data, const char *line)
{
	char			c;
	int				my_errno;
	size_t			start;
	size_t			len;

	my_errno = 0;
	start = 0;
	len = 0;
	while ((c = line[start + len]) && !my_errno)
	{
		if (c == ';' || c == '>' || c == '<' || c == '|' || c == ' ' || \
				c == '\'' || c == '\"' || c == '\\' || c == '$')
			my_errno |= update_data(line, p_data, &start, &len);
		if (c == ';' || c == '>' || c == '<' || c == '|' || c == ' ')
			my_errno |= flush_data(p_out, line, p_data, &start);
		else if (c == '$' || c == '\'' || c == '\"' || c == '\\')
			my_errno |= support_split_line(line, p_data, &start, c);
		else
			len++;
	}
	my_errno |= update_data(line, p_data, &start, &len);
	my_errno |= flush_data(p_out, line, p_data, &start);
	return (my_errno);
}

t_list			*split_line(const char *line)
{
	char			*data;
	t_list			*out;
	t_list			*temp;
	int				arg_type;
	int				my_error;

	data = 0;
	out = 0;
	my_error = split_line_main(&out, &data, line);
	temp = out;
	free((void *)line);
	while (temp)
	{
		arg_type = get_arg_type((const char *)temp->data);
		if (arg_type <= 3 && arg_type > 0)
			if (!temp->next || get_arg_type((const char *)temp->next->data))
			{
				my_error |= 4;
				break ;
			}
		temp = temp->next;
	}
	if (!my_error)
		return (out);
	return (print_parse_error(out, data, my_error, temp));
}
