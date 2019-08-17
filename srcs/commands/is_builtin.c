/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:57:48 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/17 01:20:20 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtins.h"
#include "job.h"

/*
** search if it's a builtin:
**	return 0 if it's a builtin and if it's command work
**	return -2 if it's a builtin and if it's command not work
**	return -1 if it's not a builtin
*/

/*
** Check if builtin contains the right number of args
** Args:	char **argv -> command
**			int nb -> nb of allowed args
**			char *name -> name of builtin
*/

static int	verif_set(char **argv, int nb, t_redirection *r, char *name)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (nb == i || (nb == 3 && i == 2))
		return (1);
	else if (i > nb)
		display_too_many_arg(r, name);
	else
	{
		if (ft_strequ(name, "setenv"))
			builtin_env_display(r);
		else
			display_too_few_arg(r, name);
	}
	return (0);
}

static int	is_builtin_env(t_process *p, char **av, t_pos *pos)
{
	int	verif;

	if (ft_strequ(av[0], "set"))
		verif = verif_set(p->cmd, 1, p->r, "set") ? builtin_set(p->r) : 1;
	else if (ft_strequ(av[0], "setenv"))
		verif = verif_set(av, 3, p->r, "setenv")
			? edit_setenv(av[1], av[2]) : -2;
	else if (ft_strequ(av[0], "unsetenv"))
		verif = ft_unsetenv(av);
	else if (ft_strequ(av[0], "export"))
		verif = bt_export(av, p->r);
	else if (ft_strequ(av[0], "unset"))
		verif = ft_unset(av);
	else if (ft_strchr_exist(av[0], '='))
		verif = edit_set(av, p->r, pos);
	else
		verif = -1;
	return (verif);
}

static int	is_builtin_jobs(t_job *j, t_process *p, char **av)
{
	int	verif;

	verif = -1;
	if (ft_strequ(av[0], "jobs"))
		verif = bt_jobs(j, av, p->r);
	else if (ft_strequ(av[0], "fg"))
		verif = bt_fg(j, av, p->r);
	else if (ft_strequ(av[0], "bg"))
		verif = bt_bg(j, av, p->r);
	return (verif);
}

static int	is_builtin_other(t_pos *pos, char **av)
{
	int	verif;

	verif = -1;
	if (ft_strequ(av[0], "fc"))
		verif = builtin_fc(av, pos);
	else if (ft_strequ(av[0], "test"))
		verif = builtin_fc(av, pos);
	else if (ft_strequ(av[0], "alias"))
		verif = bt_alias(av);
	else if (ft_strequ(av[0], "unalias"))
		verif = bt_unalias(av);
	else if (ft_strequ(av[0], "hash"))
		verif = bt_hash(av);
	return (verif);
}

void		save_redirection(int (*fd)[3])
{
	(*fd)[0] = dup(STDIN_FILENO);
	(*fd)[1] = dup(STDOUT_FILENO);
	(*fd)[2] = dup(STDERR_FILENO);
}

void		restore_redirection(int fd[3])
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	dup2(fd[2], STDERR_FILENO);
	close(fd[2]);
}

/*
** if builtin not exist return -1
** if exist and good execution return 0 otherwise return -2
*/

int			is_builtin(t_job *j, t_process *p, t_pos *pos)
{
	int		verif;
	char	**av;
	int		fd[3];

	av = p->cmd;
	save_redirection(&fd);
	verif = is_builtin_env(p, av, pos);
	if (verif != -1)
		;
	else if (ft_strequ(av[0], "echo"))
		verif = bt_echo(av, p->r);
	else if (ft_strequ(av[0], "cd"))
		verif = bt_cd(av);
	else if (ft_strequ(av[0], "exit"))
		verif = bt_exit(j, pos);
	else if ((verif = is_builtin_jobs(j, p, av)) != -1)
		;
	else if ((verif = is_builtin_other(pos, av)) != -1)
		;
	else
		verif = -1;
	restore_redirection(fd);
	if (verif != -1)
		gest_return(verif == -2 ? 1 : verif);
	return (verif);
}

int			builtin_exist(char *cmd)
{
	if (ft_strequ(cmd, "echo") || ft_strequ(cmd, "cd") || ft_strequ(cmd, "exit")
		|| ft_strequ(cmd, "fc") || ft_strequ(cmd, "test")
		|| ft_strequ(cmd, "alias") || ft_strequ(cmd, "unalias")
		|| ft_strequ(cmd, "hash")
		|| ft_strequ(cmd, "jobs")
		|| ft_strequ(cmd, "fg") || ft_strequ(cmd, "bg")
		|| ft_strequ(cmd, "set") || ft_strequ(cmd, "setenv")
		|| ft_strequ(cmd, "unsetenv") || ft_strequ(cmd, "export")
		|| ft_strequ(cmd, "unset") || ft_strchr_exist(cmd, '='))
		return (1);
	return (0);
}

/*
** Folowing of launch_job_blt function
*/

int			launch_process_blt(t_job *j, t_process *p, t_pos *pos,
				int fg)
{
	char	**environ;
	int		verif;

	environ = create_list_env(get_env(0, NULL), 1);
	config_pid_process(j->pgid, fg);
	redirection_fd(p->r);
	verif = is_builtin(j, p, pos);
	execve("/bin/test", NULL, NULL);
	exit(verif);
}

/*
** launch builtin in fork if is background command
*/

int			launch_job_blt(t_job *j, t_process *p, t_pos *pos, int fg)
{
	pid_t		pid;
	int			verif;

	verif = 0;
	pid = fork();
	if (pid == 0)
		verif = launch_process_blt(j, p, pos, fg);
	else if (pid < 0)
		display_error_fork(p->r);
	else
		edit_pid_shell(pid, j, p);
	update_status();
	p = p->next;
	act_job(j, fg);
	return (verif);
}

/*
** Launch builtin command
*/

int			builtin(t_job *j, t_process *p, t_pos *pos, int fg)
{
	int		verif;

	verif = -1;
	if (fg == 1)
		return (is_builtin(j, p, pos));
	else
		launch_job_blt(j, p, pos, fg);
	return (verif);
}
