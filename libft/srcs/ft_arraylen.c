/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraylen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 14:41:36 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 10:00:09 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_arraylen(char **src)
{
	int	i;

	i = 0;
	if ((!src) || (!src[0]))
		return (0);
	while (src[i])
		++i;
	return (i);
}
