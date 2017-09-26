/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 18:09:27 by pgore             #+#    #+#             */
/*   Updated: 2017/02/28 18:17:04 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*echo_add(t_list *env, char *name)
{
	char	*new;

	while (env)
	{
		if (ft_strstr((char*)env->content, name))
		{
			new = ft_strdup((char*)env->content);
			new = ft_equaltrim(new);
			return (new);
		}
		env = env->next;
	}
	return (NULL);
}

char		*for_echo(t_msh *k)
{
	int		i;
	char	*new;
	char	*rez;

	i = 0;
	rez = ft_strnew(MSIZE);
	new = ft_strnew(MSIZE);
	while (k->line[i])
	{
		if (k->line[i] == DOLLAR)
		{
			add_echo_extra(k, &new, &i);
			if (found_env(k->env, new))
				rez = ft_strcat(rez, ft_strcat(echo_add(k->env, new), \
					(k->line[i] == DOLLAR) ? "" : " "));
		}
		else
			rez[ft_strlen(rez)] = k->line[i++];
	}
	free(new);
	return (rez);
}

char		*do_bslash(char *line)
{
	char	*new;

	ft_putstr("> ");
	get_next_line(STDIN, &new);
	line[ft_strlen(line) - 1] = '\0';
	new = ft_strcat(line, new);
	return (new);
}

char		*do_quote(char *put, char *line, char q)
{
	char	*new;
	int		i[2];

	new = ft_strnew(MSIZE);
	i[0] = 0;
	i[1] = 0;
	while (line[i[0]] != q && line[i[0]])
		new[i[1]++] = line[i[0]++];
	(line[i[0]] == q) ? i[0]++ : 0;
	while (line[i[0]] != q)
	{
		while (line[i[0]] && line[i[0]] != q)
			new[i[1]++] = line[i[0]++];
		if (!line[i[0]])
		{
			new[i[1]++] = '\n';
			ft_putstr(put);
			get_next_line(STDIN, &line);
		}
		else
			break ;
		i[0] = 0;
	}
	fuck_you_norme(line, new, i[0], i[1]);
	return (new);
}

void		specialcheck(t_msh *k)
{
	int		i;
	char	*new;

	i = -1;
	new = ft_strnew(MSIZE);
	while (k->line[++i])
	{
		if (FUCK_NORME(k->line, ECHOO) && k->line[i] == DOLLAR)
		{
			k->line = for_echo(k);
			break ;
		}
		else if (k->line[i] == BSLASH && k->line[i + 1])
			k->line = ft_strcat(new, &(k->line[++i]));
		else if (k->line[i] == BSLASH && !k->line[i + 1])
			k->line = do_bslash(k->line);
		else if (k->line[i] == QUOTE && k->flg != DQUOTE)
			k->line = do_quote("quote> ", k->line, QUOTE);
		else if (k->line[i] == DQUOTE && k->flg != QUOTE)
			k->line = do_quote("dquote> ", k->line, DQUOTE);
		else
			new[i] = k->line[i];
	}
	free(new);
}
