/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_excutable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 20:09:45 by youlee            #+#    #+#             */
/*   Updated: 2021/01/30 16:08:49 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int		launch_excutable(char **argv, int *receiver, int *sender)
{
	write(1, (*argv), ft_strlen(*argv) + 1);
	write(1, ": command not found\n", 21);
	return (127);
}
