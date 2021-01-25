/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_util3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 01:06:44 by youlee            #+#    #+#             */
/*   Updated: 2021/01/26 01:26:14 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_list2(char *name, char *value) // 
{
	int		idx;
	char	temp[2048];
	
	idx = get_env_list(name);
	ft_strlcpy(temp, ft_strjoin(ft_strjoin(name, "="),value),
			ft_strlen(name)+ft_strlen(value) + 2);
	ft_strlcpy(envl[idx], temp, ft_strlen(temp) + 1);
	//ft_strlcpy(envl[idx + 1], envl[idx], ft_strlen(envl[idx]) + 1);
	//ft_strlcpy(envl[idx], envl[idx - 1], ft_strlen(envl[idx - 1]) + 1);
}
