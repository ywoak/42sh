/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unary_primaries.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 00:46:12 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/23 05:37:22 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		b_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if ((sb.st_mode & S_IFMT) == S_IFBLK)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		c_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if ((sb.st_mode & S_IFMT) == S_IFCHR)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		d_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if ((sb.st_mode & S_IFMT) == S_IFDIR)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		e_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
			return (0);
	(void)str1;
	(void)str3;
	return (1);
}

int		f_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if ((sb.st_mode & S_IFMT) == S_IFREG)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		g_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if ((sb.st_mode & S_IFMT) == S_ISGID)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		L_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (lstat(str2, &sb) != -1)
	{
		if ((sb.st_mode & S_IFMT) == S_IFLNK)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		p_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if ((sb.st_mode & S_IFMT) == S_IFIFO)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		r_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if (sb.st_mode & S_IRUSR)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		S_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if ((sb.st_mode & S_IFMT) == S_IFSOCK)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		s_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if (sb.st_size > 0)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		u_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if ((sb.st_mode & S_IFMT) == S_ISUID)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		w_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if (sb.st_mode & S_IWUSR)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		x_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if (sb.st_mode & S_IXUSR)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		z_test(char *str1, char *str2, char *str3)
{
	if (ft_strlen(str2) == 0)
		return (0);
	(void)str1;
	(void)str3;
	return (1);
}