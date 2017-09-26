/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 08:52:49 by pgore             #+#    #+#             */
/*   Updated: 2017/02/21 20:05:28 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	one_more(char *line)
{
	int		i;

	i = 0;
	while (line[i] && if_space(line[i]))
		i++;
	if (line[i])
		return (1);
	return (0);
}

void		separate(char **line, char **next)
{
	int		i;

	i = 0;
	while ((*line)[i] && (*line)[i] != SEPAR)
		i++;
	if ((*line)[i] == SEPAR)
	{
		(*line)[i] = '\0';
		if (one_more(&((*line)[i + 1])))
			*next = &((*line)[i + 1]);
		else
			*next = &((*line)[i]);
	}
}

int			is_empty(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
		if (!if_space(line[i]))
			return (0);
	return (1);
}

int			walk_through(char *line)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (line[i])
	{
		if (line[i] == SEPAR && line[i + 1] && line[i + 1] != SEPAR)
			cnt++;
		else if (line[i] == SEPAR && line[i + 1] && line[i + 1] == SEPAR)
		{
			cnt = -1;
			break ;
		}
		i++;
	}
	return (cnt);
}

int			get_input(t_msh *k)
{
	int		cnt;

	cnt = 0;
	get_next_line(STDIN, &(k->line));
	if ((cnt = walk_through(k->line)) < 0)
	{
		ft_putstr_fd(KNRM"minishell: parse error near ';;'\n", STDERR);
		return (-1);
	}
	if (k->line[ft_strlen(k->line) - 1] == SEPAR)
		k->line[ft_strlen(k->line) - 1] = '\0';
	if (cnt)
		k->nextline = ft_strnew(1000);
	while (cnt)
	{
		ft_putstr(KNRM);
		separate(&(k->line), &(k->nextline));
		do_commands(k);
		k->line = k->nextline;
		cnt--;
	}
	return (is_empty(k->line));
}
