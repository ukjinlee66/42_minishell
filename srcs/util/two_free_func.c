/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_free_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:15:57 by youlee            #+#    #+#             */
/*   Updated: 2021/01/26 20:25:22 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	two_pointer_free(char ***argv)
{
	int index;

	index = 0;
	while ((*argv)[index])
		free((*argv)[index++]);
	free((*argv));
	(*argv) = 0;
}
