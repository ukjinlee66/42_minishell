#include "minishell.h"

static int		update_data(const char *line, char **p_data, size_t *p_start, size_t *p_len)
{
	char			*new_data;
	char			*data;
	size_t			start;
	size_t			len;

	data = *p_data;
	start = *p_start;
	len = *p_len;
	*p_start = start + len;
	*p_len = 0;
	if (len == 0)
		return (0);
	if (!(new_data = ft_substr(line, (unsigned int)start, len)))
		return (1);			//malloc fail
	if (data == 0)
		*p_data = new_data;
	else
	{
		*p_data = ft_strjoin((char const *)data, (char const *)new_data);
		free(data);
		free(new_data);
		if (*p_data == 0)
			return (1);		//malloc fail
	}
	return (0);
}

static int		flush_data(t_list **p_out, const char *line, char **p_data, size_t *p_start)
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

static int		parse_env_variables(const char *line, char **p_data, size_t *p_start)
{
	size_t		len;
	size_t		start;
	char		*target_variable;
	int			env_idx;

	len = 0;
	start = *p_start + 1;
	while ((line[start + len] >= 'a' && line[start + len] <= 'z') || \
			(line[start + len] >= 'A' && line[start + len] <= 'Z') || \
			(line[start + len] >= '0' && line[start + len] <= '9'))
		len++;
	if (!len)		//not count $! or $#
	{
		if (line[start] == '?')
		{
			*p_start += 2;
			start = 0;
			len = ft_strlen(ret_str);
			return (update_data(ret_str, p_data, &start, &len));
		}
		len = 1;
		return (update_data(line, p_data, p_start, &len));
	}
	if (!(target_variable = ft_substr(line, (unsigned int)start, len)))
		return (1);		//malloc failed
	env_idx = get_env_list(target_variable);
	free(target_variable);
	*p_start = start + len;
	if (env_idx >= 0)
	{
		start = len + 1;
		len = ft_strlen(envl[env_idx]) - start;
		return (update_data(envl[env_idx], p_data, &start, &len));
	}
	return (0);
}

static int		parse_double_quote(const char *line, char **p_data, size_t *p_start)
{
	size_t			len;
	size_t			start;
	char			*tmp_s;
	int				tmp_idx;
	size_t			tmp_len, tmp_start;

	len = 0;
	start = *p_start + 1;
	while (line[start + len] != '\"')
	{
		if (line[start + len] == '\\')
		{
			if (update_data(line, p_data, &start, &len))
				return (1);
			start++;
			len++;
			if (update_data(line, p_data, &start, &len))
				return (1);
		}
		else if (line[start + len] == '$')
		{
			if (update_data(line, p_data, &start, &len))
				return (1);
			if (parse_env_variables(line, p_data, &start))
				return (1);
		}
		else if (line[start + len] == 0)
			return (2);			//multiple commands
		else
			len++;
	}
	if ((update_data(line, p_data, &start, &len)))
		return (1);				//malloc fail
	*p_start = start + 1;
	return (0);
}

static int		parse_single_quote(const char *line, char **p_data, size_t *p_start)
{
	size_t			len;
	size_t			start;

	len = 0;
	start = *p_start + 1;
	while (line[start + len] != '\'')
	{
		if (line[start + len] == 0)
			return (2);		//multiple commands
		len++;
	}
	if ((update_data(line, p_data, &start, &len)))
		return (1);
	*p_start = start + 1;
	return (0);
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
		else if (c == '$')
			my_errno |= parse_env_variables(line, p_data, &start);
		else if (c == '\'')
		{
			my_errno |= parse_single_quote(line, p_data, &start);
		}
		else if (c == '\"')
		{
			my_errno |= parse_double_quote(line, p_data, &start);
		}
		else
		{
			len++; //multiple commands handle
			if (c == '\\')
			{
				start++;
				my_errno |= update_data(line, p_data, &start, &len);
			}
		}
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
				my_error |= 4;
		temp = temp->next;
	}
	if (!my_error)
		return (out);
	if (data)
		free(data);
	free_list(out);
	write(1, "parsing error\n", 14);
	return (0);
}
