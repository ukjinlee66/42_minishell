/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 16:48:22 by youlee            #+#    #+#             */
/*   Updated: 2020/08/19 17:06:14 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;
	
	if (!(res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		res[i++] = s1[j++];
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

int		get_next_line(char **line)
{
	int		size;
	char	buf[2];
	char	*store;
	char	*temp;
	
	size = 1;
	store = ft_strjoin("", "");
	buf[size] = '\0';
	while (size == 1 && buf[0] != '\n')
	{
		size = read(0, buf, 1); //서브젝트에 나오는 파일디스크립터 넘버를 넣어야함. 0, 1
		if (buf[0] != '\n' && size > 0)
		{
			temp = ft_strjoin(store, buf);
			free(store);
			store = temp;
		}
	}
	*line = store;
	return (size);
}
