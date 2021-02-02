/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:10:27 by youlee            #+#    #+#             */
/*   Updated: 2021/02/01 23:05:50 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sig(int sig_num)
{
	if (g_pid_stat == true)
		ft_putstr_fd("\b\b  ", 2);
	ft_putstr_fd("\n", 2);
	ft_strlcpy(g_ret_str, "130", 4);
	if (g_pid_stat == true)
	{
		getcwd(g_cur_path, PATH_SIZE);
		write(2, g_cur_path, ft_strlen(g_cur_path));
		write(2, "$ ", 2);
	}
}

void	handle_sig2(int sig_num)
{
	if (g_pid_stat == false)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		ft_strlcpy(g_ret_str, "131", 4);
	}
	else
		ft_putstr_fd("\b\b  \b\b", 2);
}
