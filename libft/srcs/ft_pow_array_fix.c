/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow_array_fix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:07:46 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 10:01:17 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_pow_array_fix(int i, char (*nb)[BUF_S])
{
	int	cnt;

	cnt = 0;
	ft_bzero(&(*nb), BUF_S);
	(*nb)[cnt] = '5';
	while (i-- >= 0)
		(*nb)[++cnt] = '0';
}
