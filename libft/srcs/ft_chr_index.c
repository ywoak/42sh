/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chr_index.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 00:37:56 by sbelondr          #+#    #+#             */
/*   Updated: 2018/12/11 22:20:38 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				ft_chr_index(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		++i;
	if (s[i] && s[i] == c)
		return (i);
	return (-1);
}
