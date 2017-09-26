/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 16:54:22 by pgore             #+#    #+#             */
/*   Updated: 2017/02/20 13:52:33 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			fuck_you_norme(char *line, char *new, int i, int j)
{
	while (line[i++])
		new[j++] = line[i];
}

int				ft_count_name(char *arg)
{
	int			i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (!arg[i])
		return (ft_strlen(arg));
	return (i);
}

int				found_env(t_list *lst, char *name)
{
	while (lst)
	{
		if (ft_strnequ(LSTR(lst), name, ft_strlen(name)))
			return (1);
		lst = lst->next;
	}
	return (0);
}

char			*ft_equaltrim(char *str)
{
	char		*new;
	int			i;

	i = 0;
	new = NULL;
	while (str[i] != '=' && str[i])
		i++;
	if (str[i] == '=')
		new = ft_strdup(&(str[i + 1]));
	return (new);
}

void			add_echo_extra(t_msh *k, char **new, int *i)
{
	int			j;

	j = 0;
	while (k->line[++(*i)] && !if_space(k->line[*i]) && k->line[*i] != DOLLAR)
	{
		if (k->line[*i] == BSLASH)
			k->line = do_bslash(k->line);
		(*new)[j++] = k->line[*i];
	}
	(*new)[j] = '\0';
}
