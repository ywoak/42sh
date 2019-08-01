/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 03:02:22 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/01 13:04:24 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "sh21.h"
#include "env.h"

int			get_argc(t_lex *cursor)
{
	int		len;

	len = 0;
	while (cursor)
	{
		if (cursor->token->type == WORD || cursor->token->type == NUMBER)
			len++;
		cursor = cursor->next;
	}
	return (len);
}

char		**get_argv(t_token *cmd_list)
{
	char	**argv;
	t_lex	*cursor;
	int		len;
	int		i;

	i = 0;
	cursor = cmd_list->command;
	len = get_argc(cursor);
	if (!(argv = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (cursor)
	{
		if (cursor->token->type == WORD || cursor->token->type == NUMBER)
			argv[i++] = ft_strdup(cursor->token->data);
		cursor = cursor->next;
	}
	argv[i] = NULL;
	return (argv);
}

int		files_handler(t_token *cmd_list, t_pos *pos)
{
	t_lex	*cursor;

	cursor = cmd_list->command;
	while (cursor)
	{
		if (cursor->token->type == REDIR)
			if (open_file_command(cursor->redir, pos) == -1)
				return (-1);
		cursor = cursor->next;
	}
	return (0);
}

int			*run_pipe(t_token *cmd_list, t_pos *pos, int end_pipe, int bg)
{
	char	**argv;

	argv = get_argv(cmd_list);
	if (files_handler(cmd_list, pos) != -1)
		ft_pipe(argv, cmd_list, end_pipe, bg);
	ft_arraydel(&argv);
	return (0);
}

int			*run_cmd(t_token *cmd_list, t_pos *pos, int bg)
{
	char	**argv;

	argv = get_argv(cmd_list);
	if (files_handler(cmd_list, pos) != -1)
		ft_simple_command(argv, cmd_list, pos, bg);
	ft_arraydel(&argv);
	return (0);
}

int			check_last(void)
{
	int		check;
	char	*str;

	str = value_line_path("?", 0);
	check = ft_atoi(str);
	ft_strdel(&str);
	return (check);
}
