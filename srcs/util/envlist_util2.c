/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 00:37:36 by youlee            #+#    #+#             */
/*   Updated: 2021/01/16 03:13:46 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_str_de(void)
{
	int		idx;
	int		idx2;

	idx = 0;
	while (soenvl[idx][12])
	{
		ft_strlcpy(soenvl[idx], "declare -x", 11);
		soenvl[idx][10] = ' ';
		idx++;
	}
}

bool	check_env(char *find, char *b)
{
	int		idx;

	idx = 0;
	while (find[idx])
	{
		if (find[idx] != b[idx])
			return (false);
		idx++;
	}
	if (find[idx] != '\0' || b[idx] != '=')
		return (false);
	return (true);
}

void	set_env_list(char *name, char *value) // 
{
	int		idx;
	char	temp[2048];
	
	idx = 0;
	ft_strlcpy(temp, ft_strjoin(ft_strjoin(name, "="),value),
			ft_strlen(name)+ft_strlen(value) + 3);
	while (envl[idx][0])
		idx++;
	ft_strlcpy(envl[idx + 1], envl[idx], ft_strlen(envl[idx]));
	ft_strlcpy(envl[idx], envl[idx - 1], ft_strlen(envl[idx - 1]));
	ft_strlcpy(envl[idx - 1], temp, ft_strlen(temp) + 1);
}

void	add_double(char (*env)[2048])
{
	printf("%s\n",*env);
	char **name_value;
	char *temp;

	name_value = ft_split(*env, '=');
	if (ft_strchr(name_value[1], '\"') != 0)
		return ;
	temp = ft_strjoin(ft_strjoin("\"", name_value[1]),
			"\"");
	ft_strlcpy((*env), ft_strjoin(ft_strjoin(name_value[0], "="),
				temp),
			ft_strlen(*env) + 4);
}
