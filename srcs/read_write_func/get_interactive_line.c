/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_interactive_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 15:16:04 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 18:56:30 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**		return 1 for read success
**		return 0 for EOF
**		return -1 for read fail
**		return -2 for malloc fail
*/

int		get_interactive_line(char **line)
{
	int		size;
	char	buf[2];
	char	*store;
	char	*temp;

	size = 1;
	ft_bzero((void *)buf, 2);
	if (!(store = (char *)malloc(sizeof(char))))
		return (-2);
	store[0] = '\0';
	while ((size = read(0, buf, 1)) > 0)
	{
		if (buf[0] == '\n')
			break ;
		temp = ft_strjoin((char const *)store, \
				(char const *)buf);
		free(store);
		store = temp;
		if (store == 0)
			return (-2);
	}
	if (size >= 0)
		*line = store;
	return (size);
}
