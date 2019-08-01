/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:10:40 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/01 13:19:03 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		solo_tree(t_ast *node, t_pos *pos)
{
	if (node->token->type == CMD)
	{
		run_cmd(node->token, pos);
		return (1);
	}
	else
		return (-1);
}

void		background_case(t_ast *node, t_pos *pos, int *bg)
{
	if (node->token->type == AMP)
	{
		*bg = *bg+1;
		if (node->l->token->type == CMD && node->r->token->type == CMD) // OK
		{
			ft_putendl(ft_itoa(*bg));
			run_cmd(node->l->token, pos);
			// if (*bg > 1)
			// 	ft_putendl(ft_itoa(*bg));
			// else
			// 	ft_putendl("0");

			// *bg = *bg-1;
			ft_putendl(ft_itoa(*bg-1));
			run_cmd(node->r->token, pos);
		}
		if (node->l->token->type == CMD && node->r->token->type != CMD) // OK`
			{ft_putendl(ft_itoa(*bg));run_cmd(node->l->token, pos);}
	}
}

void	scolon_case(t_ast *node, t_pos *pos, int bg)
{
	if (node->token->type == SCOLON)
	{
		if (node->l->token->type == CMD && node->r->token->type == CMD)
		{
			ft_putendl(ft_itoa(bg));
			run_cmd(node->l->token, pos);
			ft_putendl(ft_itoa(bg));
			run_cmd(node->r->token, pos);
		}
		if (node->l->token->type == CMD && node->r->token->type != CMD)
			{ft_putendl(ft_itoa(bg));run_cmd(node->l->token, pos);}
	}
}

void	spipe_case(t_ast *node, t_pos *pos, int bg)
{
	static int state;

	if (node->token->type == SPIPE)
	{
		ft_putendl(ft_itoa(bg));
		if (state == 0)
			run_pipe(node->l->token, pos, state++);
		else
			run_pipe(node->l->token, pos, 1);
		if (node->r->token->type == CMD)
		{
			run_pipe(node->r->token, pos, 2);
			state = 0;
		}
	}
}

void	dpipe_case(t_ast *node, t_pos *pos, int bg)
{
	if (node->token->type == DPIPE)
	{
		if (node->l->token->type == CMD && node->r->token->type == CMD)
		{
			ft_putendl(ft_itoa(bg));
			run_cmd(node->l->token, pos);
			printf("CHECKLAST:%d\n", check_last());
			if (check_last() != 0)
			{ft_putendl(ft_itoa(bg));run_cmd(node->r->token, pos);}
		}
		if (node->l->token->type == CMD && node->r->token->type != CMD)
			{ft_putendl(ft_itoa(bg));run_cmd(node->l->token, pos);}
	}
}

void	damp_case(t_ast *node, t_pos *pos, int bg)
{
	if (node->token->type == DAMP)
	{
		if (node->l->token->type == CMD && node->r->token->type == CMD)
		{
			ft_putendl(ft_itoa(bg));
			run_cmd(node->l->token, pos);
			printf("CHECKLAST:%d\n", check_last());
			if (check_last() == 0)
			{ft_putendl(ft_itoa(bg));run_cmd(node->r->token, pos);}
		}
		if (node->l->token->type == CMD && node->r->token->type != CMD)
			{ft_putendl(ft_itoa(bg));run_cmd(node->l->token, pos);}
	}
}

void	edge_case(t_ast *node, t_pos *pos, int bg)
{
	if (node->token->type == SCOLON || node->token->type == AMP)
		if (node->l->token->type != CMD && node->r->token->type == CMD)
			{ft_putendl(ft_itoa(bg));run_cmd(node->r->token, pos);}
	if (node->token->type == DPIPE)
		if (node->l->token->type != CMD && node->r->token->type == CMD)
			if (check_last() != 0)
				{ft_putendl(ft_itoa(bg));run_cmd(node->r->token, pos);}
	if (node->token->type == DAMP)
		if (node->l->token->type != CMD && node->r->token->type == CMD)
			if (check_last() == 0)
				{ft_putendl(ft_itoa(bg));run_cmd(node->r->token, pos);}
}

int		interpreter(t_ast *node, t_pos *pos, int background)
{
	static int bg;

	(void)background;
	if (!node)
		return (-1);
	background_case(node, pos, &bg);
	scolon_case(node, pos, bg);
	dpipe_case(node, pos, bg);
	damp_case(node, pos, bg);
	spipe_case(node, pos, bg);
	interpreter(node->l, pos, bg);
	if (node->token->type == AMP)
		bg--;
	interpreter(node->r, pos, bg);
	edge_case(node, pos, bg);
	return (0);
}
