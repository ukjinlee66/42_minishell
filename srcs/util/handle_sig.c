/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:10:27 by youlee            #+#    #+#             */
/*   Updated: 2021/01/30 15:56:59 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sig(int sig_num)
{
	ft_putstr_fd("\b\b  ", 2);
	ft_putstr_fd("\n", 2);
	ft_strlcpy(ret_str, "130", 4);
	getcwd(cur_path, PATH_SIZE);
	write(1, cur_path, ft_strlen(cur_path));
	write(1, "$ ", 2);
}

void	handle_sig2(int sig_num)
{
	if (pid_stat == false)
	{
		ft_putstr_fd("^\\Quit: 3\n", 1);
		ft_strlcpy(ret_str, "131", 4);
	}
	else
		ft_putstr_fd("\b\b  \b\b", 2);
}
