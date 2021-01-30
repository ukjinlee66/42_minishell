/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:10:27 by youlee            #+#    #+#             */
/*   Updated: 2021/01/30 14:56:33 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sig(int sig_num)
{
	ft_putstr_fd("\n", 1);
	ft_strlcpy(ret_str, "130", 4);
}

void	handle_sig2(int sig_num)
{
	ft_putstr_fd("^\\Quit: 3\n", 1);
	ft_strlcpy(ret_str, "131", 4);
}
