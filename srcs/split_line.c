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

static int		parse_quote_section(const char *line, char **p_data, \
		size_t *p_start, const char q)
{
	size_t			len;
	size_t			start;

	len = 0;
	start = *p_start + 1;
	while (line[start + len] != q)
	{
		if (line[start + len] == '\\')
			len++;
		if (line[start + len] == 0)
			return (2);			//multiple commands
		len++;
	}
	if ((update_data(line, p_data, &start, &len)))
		return (1);				//malloc fail
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
				c == '\'' || c == '\"')
			my_errno |= update_data(line, p_data, &start, &len);
		if (c == ';' || c == '>' || c == '<' || c == '|' || c == ' ')
			my_errno |= flush_data(p_out, line, p_data, &start);
		else if (c == '\'' || c == '\"')
			my_errno |= parse_quote_section(line, p_data, &start, c);
		else
			len += (c == '\\') ? 2 : 1; //multiple commands handle
	}
	my_errno |= update_data(line, p_data, &start, &len);
	my_errno |= flush_data(p_out, line, p_data, &start);
	return (my_errno);
}

t_list			*split_line(const char *line)
{
	char			*data;
	t_list			*out;

	data = 0;
	out = 0;
	if (!split_line_main(&out, &data, line))
		return (out);
	if (data)
		free(data);
	free_list(out);
	return (0);
}
