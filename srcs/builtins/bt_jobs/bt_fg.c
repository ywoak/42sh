/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 10:54:45 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/17 01:56:38 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "builtins.h"

int			bt_fg(t_job *j, char **av, t_redirection *r)
{
	char	*cmd;
	t_job	*job_launch;

	if (j->fg == 0)
	{
		display_no_job_control(r, "fg");
		return (1);
	}
	job_launch = job_for_bg_fg(av, r);
	if (!job_launch)
	{
		display_no_current_job(r, "fg");
		return (-2);
	}
	change_fg_var_job(job_launch, 1);
	cmd = cmd_job_s(job_launch);
	if (cmd)
		ft_dprintf(STDOUT_FILENO, "%s\n", cmd);
	ft_strdel(&cmd);
	continue_job(job_launch, 1);
	return (0);
}