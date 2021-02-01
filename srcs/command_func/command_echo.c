/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 16:15:59 by youlee            #+#    #+#             */
/*   Updated: 2021/02/01 14:39:13 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			command_echo(char **argv, int *receiver, int *sender)
{
	int		cnt;
	char	*res;
	char	*temp;
	bool	option_val;

	option_val = false;
	cnt = 1;
	if (argv[1] == NULL)
		write(1, "\n", 5);
	else
	{
		temp = ft_strjoin("", "");
		while (argv[cnt])
		{
			if ((ft_strcmp(argv[cnt], "-n") == 0))
			{
				option_val = true;
				cnt++;
				continue;
			}
			res = ft_strjoin(temp, argv[cnt]);
			ft_putstr_fd(argv[cnt], 1);
			if (sender[0] != -1)
			{
				//ft_strlcpy(g_print_buf, argv[cnt], ft_strlen(argv[cnt]) + 1);
				write(1, argv[cnt], ft_strlen(argv[cnt]) + 1);
			}
			if (argv[cnt + 1] != NULL)
				write(1, " ", 1);
			temp = res;
			cnt++;
		}
		if (option_val == false)
			write(1, "\n", 1);
		free(temp);
	}
	return (0);
}

void		command_echo2(char **argv, int *receiver, int *sender)
{

}
