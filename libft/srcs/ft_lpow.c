/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lpow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 09:49:37 by apruvost          #+#    #+#             */
/*   Updated: 2019/06/11 14:58:12 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_lpow(long a, long b)
{
	long	p;
	long	i;

	if (a == 0)
		return (1);
	p = a;
	i = 0;
	while (i < b)
	{
		p *= a;
		++i;
	}
	return (p);
}
