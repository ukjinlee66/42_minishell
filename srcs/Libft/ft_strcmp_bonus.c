/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:08:26 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 19:08:31 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strcmp(const char *src1, const char *src2)
{
	while (*src1 && *src2)
	{
		if (*src1 != *src2)
			break ;
		src1++;
		src2++;
	}
	return ((unsigned char)*src1 - (unsigned char)*src2);
}
