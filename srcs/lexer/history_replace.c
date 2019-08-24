/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 00:07:18 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/24 23:30:00 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		hist_rep_delstruct(t_hist_rep *to_del)
{
	if (!to_del)
		return ;
	hist_rep_delstruct(to_del->next);
	ft_strdel(&(to_del->base));
	to_del->next = NULL;
	to_del->value = NULL;
	free(to_del);
	to_del = NULL;
	return ;
}

int			hist_rep_exists(t_hist_rep *replace, t_pos *pos)
{
	int	num;

	if (ft_strequ(replace->base, "!!"))
		replace->value = expand_double_schriek(pos);
	else if (replace->base[1] == '\0')
		return (0);
	else if (ft_isstrnum(&(replace->base[1])))
	{
		num = ft_atoi(&(replace->base[1]));
		if (num < 0)
			replace->value = expand_schriek_less(pos, num * -1);
		else
			replace->value = expand_schriek_number(pos, num);
	}
	else
		replace->value = expand_schriek_word(pos, &(replace->base[1]));
	return (1);
}

char		*hist_rep_replace(t_hist_rep *replace, t_pos *pos)
{
	t_hist_rep	*curr;
	char		*new;
	char		*bin;

	curr = replace;
	new = ft_strnew(1);
	while (curr != NULL)
	{
		if (curr->isrep == 0)
		{
			bin = new;
			new = ft_strjoin(new, curr->base);
			ft_strdel(&bin);
		}
		else
		{
			if (hist_rep_exists(curr, pos) && curr->value != NULL)
			{
				bin = new;
				new = ft_strjoin(new, curr->value);
				ft_strdel(&bin);
			}
			else
			{
				ft_strdel(&new);
				ft_dprintf(2, "42sh: %s: event not found\n", curr->base);
				return (NULL);	//  		ERR
			}
		}
		curr = curr->next;
	}
	return (new);
}

int			hist_rep_getexp(char *input)
{
	int		i;

	i = 1;
	if (input[i] == '-' || ft_isdigit(input[i]))
	{
		++i;
		while (input && ft_isdigit(input[i]))
			++i;
		return (i);
	}
	else if (input[i] == '!')
		return (++i);
	while (input && input[i] && input[i] != ' ' && input[i] != '\t'
			&& input[i] != ';' && input[i] != '|' && input[i] != '&'
			&& input[i] != '(' && input[i] != ')' && input[i] != '<'
			&& input[i] != '>')
		++i;
	return (i);
}

t_hist_rep	*hist_rep_saveexp(char *input, int start, int i, t_hist_rep *replace)
{
	t_hist_rep		*new;
	t_hist_rep		*curr;
	int				j;

	if (start == i)
		return (replace);
	if (!(new = (t_hist_rep*)malloc(sizeof(t_hist_rep))))
		return (replace);
	new->isrep = 1;
	new->next = NULL;
	new->value = NULL;
	if (!(new->base = (char *)malloc(sizeof(char) * (i - start + 1))))
	{
		ft_memdel((void**)&new);
		return (replace);
	}
	j = 0;
	while (start < i)
	{
		new->base[j] = input[start];
		++j;
		++start;
	}
	new->base[j] = '\0';
	if (!(replace))
		return (new);
	curr = replace;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
	return (replace);
}

t_hist_rep	*hist_rep_save(char *input, int start, int i, t_hist_rep *replace)
{
	t_hist_rep		*new;
	t_hist_rep		*curr;
	int				j;

	if (start == i)
		return (replace);
	if (!(new = (t_hist_rep*)malloc(sizeof(t_hist_rep))))
		return (replace);
	new->isrep = 0;
	new->next = NULL;
	new->value = NULL;
	if (!(new->base = (char *)malloc(sizeof(char) * (i - start + 1))))
	{
		ft_memdel((void**)&new);
		return (replace);
	}
	j = 0;
	while (start < i)
	{
		new->base[j] = input[start];
		++j;
		++start;
	}
	new->base[j] = '\0';
	if (!(replace))
		return (new);
	curr = replace;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
	return (replace);
}

int			hist_rep_isvalid(char *input)
{
	if (input[0] != '!')
		return (0);
	else if (input[1] == ' ' || input[1] == '\t' || input[1] == '\0'
			|| input[1] == '=' || input[1] == '%' || input[1] == '\n')
		return (0);
	return (1);
}

char		*history_replace(char *input, t_pos *pos)
{
	char	*new_input;
	t_hist_rep	*replace;
	int		i;
	int		start;

	replace = NULL;
	start = 0;
	i = 0;
	if (!input)
		return (input);
	while (input[i])
	{
		if (input[i] == '!' && hist_rep_isvalid(&(input[i])))
		{
			replace = hist_rep_save(input, start, i, replace);
			start = i;
			i += hist_rep_getexp(&(input[start]));
			replace = hist_rep_saveexp(input, start, i, replace);
			start = i;
		}
		else if (!input[i + 1] && replace != NULL)
		{
			replace = hist_rep_save(input, start, i + 1, replace);
			++i;
			start = i;
		}
		else
			++i;
	}
	if (!replace)
		return (input);
	new_input = hist_rep_replace(*(&replace), pos);
	hist_rep_delstruct(&(*replace));
	ft_strdel(&input);
	if (new_input)
		ft_printf("%s\n", new_input);
	return (new_input);
}