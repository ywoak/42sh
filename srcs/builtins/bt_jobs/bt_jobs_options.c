/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_jobs_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 10:54:45 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/17 01:56:38 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "builtins.h"

static int		ft_good_syntax(char *av)
{
	int	i;
	int	percent;

	i = 0;
	if (av[i] == '%')
		++i;
	percent = (i > 0) ? -1 : 1;
	if (!av[i])
		return (4);
	if (av[i] == '%' || av[i] == '+')
		return ((!av[i + 1]) ? 1 * percent : 4 * percent);
	if (av[i] == '-')
		return ((!av[i + 1]) ? 2 * percent : 4 * percent);
	if (av[i] == '?')
		return (5 * percent);
	return (ft_isnumbers(av + i) ? 3 * percent : 4 * percent);
}

t_job			*search_job(char *av)
{
	int	job_id;

	job_id = ft_good_syntax(av);
	if (job_id == 1 || job_id == -1)
		return (last_jobs());
	else if (job_id == 2 || job_id == -2)
		return (previous_jobs());
	else if (job_id == 3 || job_id == -3)
		return (ft_search_id_job(av, (job_id > -1) ? 0 : 1));
	else if (job_id == 4 || job_id == -4)
		return (ft_search_str_job(av, (job_id > -1) ? 0 : 1));
	else if (job_id == 5 || job_id == -5)
		return (ft_search_exist_job(av, (job_id > -1) ? 0 : 1));
	else
		return (NULL);
}

void			display_jobs_options(void (*p)(t_job*, int, t_redirection*),
	t_redirection *r, char **av)
{
	t_job	*j;
	int		i;
	int		verif;
	int		max_current;

	max_current = get_shell()->max_job_current;
	i = (ft_strequ(*av, "--")) ? 1 : 0;
	while (av[i])
	{
		verif = 0;
		j = search_job(av[i]);
		if (j)
		{
			verif = 1;
			if (job_is_completed(j) || job_is_stopped(j))
			{
				(*p)(j, max_current, r);
			}
			else
				display_no_such_job(r, av[i]);
		}
		else
			display_no_such_job(r, av[i]);
		++i;
	}
}