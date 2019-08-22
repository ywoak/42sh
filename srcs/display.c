/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 09:47:57 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/22 09:38:05 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "job.h"

static char	*info_display(char *buf)
{
	int		i;
	char	*tmp;
	char	*dst;

	tmp = value_line_path("HOME", 0);
	if (!tmp)
	{
		dst = ft_strdup(buf);
		return (dst);
	}
	i = -1;
	while (tmp[++i])
		if ((!buf[i]) || tmp[i] != buf[i])
		{
			dst = ft_strdup(buf);
			ft_strdel(&tmp);
			return (dst);
		}
	ft_strdel(&tmp);
	tmp = ft_strsub(buf, i, ft_strlen(buf));
	dst = ft_strjoin("~", tmp);
	ft_strdel(&tmp);
	return (dst);
}

static char	*pwd_display(void)
{
	char	*stock;
	char	*path;
	char	buf[BUF_S];

	ft_bzero(buf, BUF_S);
	path = getcwd(buf, BUF_S);
	if (!path)
	{
		stock = value_line_path("PWD", 0);
		if (stock)
		{
			ft_cpy_str(&buf, stock);
			ft_strdel(&stock);
		}
	}
	path = info_display(buf);
	return (path);
}

void		display_prompt(void)
{
	char	*path;
	char	*user;

	path = pwd_display();
	user = value_line_path("USER", 0);
	ft_putstr("❰\033[32;01m");
	ft_putstr(user);
	ft_putstr("\033[00m ❙ \033[33;01m");
	ft_putstr(path);
	ft_putstr("\033[00m❱ ");
	if (check_last_command() == 0)
		ft_putstr("\033[32;01m✔\033[00m > ");
	else
		ft_putstr("\033[31;01m✘\033[00m > ");
	ft_strdel(&path);
	ft_strdel(&user);
}
