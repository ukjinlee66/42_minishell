/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uppercase_conversion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:21:27 by youlee            #+#    #+#             */
/*   Updated: 2021/01/26 19:17:55 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*uppercase_conversion(char *str)
{
	int len;

	len = 0;
	while (str[len])
	{
		if (65 <= str[len] && str[len] <= 90)
			str[len] += 32;
		len++;
	}
	return (str);
}
