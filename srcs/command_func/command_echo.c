/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 16:15:59 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 17:31:46 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			command_echo(char **argv, int *receiver, int *sender,
		bool option_val)
{
	int		cnt;

	cnt = 1;
	if (argv[1] == NULL)
		write(1, "\n", 1);
	else
	{
		while (argv[cnt])
		{
			if ((ft_strcmp(argv[cnt], "-n") == 0))
			{
				option_val = true;
				cnt++;
				continue;
			}
			ft_strlcpy(g_print_buf, argv[cnt], ft_strlen(argv[cnt]) + 1);
			write(1, g_print_buf, ft_strlen(g_print_buf));
			if (argv[cnt + 1] != NULL)
				write(1, " ", 1);
			cnt++;
		}
		if (option_val == false)
			write(1, "\n", 1);
	}
	return (0);
}
