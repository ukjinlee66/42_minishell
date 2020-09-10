#include "minishell.h"

t_list		*split_line(const char *line)
{
	size_t			i;
	size_t			len;
	int				mark[2];
	void			*data;
	t_list			*out;

	i = 0;
	len = 0;
	mark[0] = 0;
	mark[1] = 0;
	out = 0;
	while (line[i + len])
	{
		if (mark[0] == 0 && mark[1] == 0)
		{
			if (line[i + len] == ';' || line[i + len] == '>' || line[i + len] == '<' \
					|| line[i + len] == '|' || line[i + len] == ' ')
			{
				if (len)
				{
					data = (void *)ft_substr(line, (unsigned int)i, len);
					add_data(&out, &data);
					i += len;
					len = 0;
				}
				if (line[i] == '>' && line[i + 1] == '>')
					len = 2;
				else if (line[i] == ';' || line[i] == '>' || \
						line[i] == '<' || line[i] == '|')
					len = 1;
				else
				{
					i++;
				}
				if (len)
				{
					data = (void *)ft_substr(line, (unsigned int)i, len);
					add_data(&out, &data);
					i += len;
					len = 0;
				}
				continue ;
			}
			else if (line[i + len] == 39)
				mark[0] = 1;
			else if (line[i + len] == 34)
				mark[1] = 1;
			len++;
		}
		else
		{
			if (mark[0] && line[i + len] == 39)
				mark[0] = 0;
			else if (mark[1] && line[i + len] == 34)
				mark[1] = 0;
			len++;
		}
	}
	if (len)
	{
		data = (void *)ft_substr(line, (unsigned int)i, len);
		add_data(&out, &data);
	}
	return (out);
}
