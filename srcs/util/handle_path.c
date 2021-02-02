/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:31:19 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 18:24:38 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				dir_err(char **path, char **argv, char **envp)
{
	char	**name_value;
	char	**path2;
	int		idx[3];
	char	p[1024];

	idx[0] = 0;
	if ((idx[0] = get_env_list("PATH")) == -1)
		return (0);
	name_value = ft_split(g_envl[idx[0]], '=');
	path2 = ft_split(name_value[1], ':');
	free(name_value[0]);
	free(name_value[1]);
	free(name_value);
	idx[1] = 0;
	while (path2[idx[1]])
	{
		path2[idx[1]] = ft_strjoin(ft_strjoin(path2[idx[1]], "/"), argv[0]);
		ft_strlcpy(p, path2[idx[1]], ft_strlen(path2[idx[1]]) + 1);
		if (execve(p, argv, envp) == -1)
			free(path2[idx[1]]);
		idx[1]++;
	}
	free(path2);
	return (0);
}
