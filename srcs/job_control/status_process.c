/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 11:34:26 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/20 06:01:53 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "builtins.h"
#include <errno.h>

static void	job_done(t_job *j)
{
	char	*cmd;
	char	c;

	c = value_char_job(j->current, get_shell()->max_job_current);
	cmd = cmd_job_s(j);
	ft_printf("[%d]%c Done	%s\n", j->process_id, c, cmd);
	j->notif_stop = 1;
	ft_strdel(&cmd);
}

static int	check_is_terminated(t_job *j)
{
	int			num_sig;
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		num_sig = (p->status < 32) ? p->status : WSTOPSIG(p->status);
		if (p->status < 13 && p->status > 15)
			return (0);
		p = p->next;
	}
	return (0);
}

static int	display_stat_process(t_job *j, t_process *p, int notified)
{
	if ((!notified) && (p->status != p->last_status && p->status != 2))
	{
		if (j->fg == 0 && job_is_completed(j))
			bt_jobs_s(j, get_shell()->max_job_current, j->r);
			//job_done(j);
		else if ((!notified) && (j->fg == 0 || job_is_stopped(j)))
		{
			ft_putchar('\n');
			bt_jobs_s(j, get_shell()->max_job_current, j->r);
		}
		notified = 1;
	}
	p->last_status = p->status;
	return (notified);
}

/*
** Parcours chaque process d'un job et utilise la fonction
**	display_stat_process pour afficher le status d'un process
**	si besoin
** Args:	t_job *j -> process a check
*/

static void	display_stat_job(t_job *j)
{
	int			notified;
	t_process	*p;

	notified = 0;
	if (check_is_terminated(j))
	{
		ft_printf("coucou\n");
		if (j->first_process->status != 0)
			bt_jobs_s(j, get_shell()->max_job_current, j->r);
		return ;
	}
	if (j->first_process->fg == 0)
		if (job_is_completed(j) && j->first_process->status == 0)
		{
			job_done(j);
			return ;
		}
	p = j->first_process;
	while (p)
	{
		notified = display_stat_process(j, p, notified);
		p = p->next;
	}
}

void		job_notif(void)
{
	t_job	*j;

	update_status();
	j = get_first_job(NULL);
	while (j)
	{
		display_stat_job(j);
		j = j->next;
	}
	clean_fuck_list(0);
}

void		job_running(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		p->stopped = 0;
		p = p->next;
	}
	j->notified = 0;
}

void		continue_job(t_job *j, int fg)
{
	job_running(j);
	j->notif_stop = 0;
	if (fg)
		add_in_fg(j, 1);
	else
		add_in_bg(j, 1);
	clean_fuck_list(0);
}
