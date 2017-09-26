/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 16:59:46 by pgore             #+#    #+#             */
/*   Updated: 2017/02/28 16:58:35 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				display_env(t_list *env)
{
	while (env)
	{
		ft_putendl((char*)env->content);
		LTONEXT(env);
	}
	return (0);
}

void			delete_env(t_list **env, char *name)
{
	t_list		*new;
	t_list		*tmp;

	new = *env;
	tmp = NULL;
	while (new->next && !find_that_env(name, LSTR(new)))
	{
		tmp = new;
		new = new->next;
	}
	if (find_that_env(name, LSTR(new)))
	{
		if (tmp)
			tmp->next = new->next;
		else
			*env = new->next;
		free(new);
	}
}

int				set_env(t_msh *k)
{
	char		*name;
	int			i;

	if (!k->arg[1])
		ft_err("setenv: not enough arguments", NULL);
	name = ft_strnew(MSIZE);
	i = 1;
	while (k->arg[i])
	{
		(!ft_strchr(k->arg[i], '=')) ? k->arg[i] = ft_strjoin(k->arg[i], "=") \
		: 0;
		name = ft_strncpy(name, k->arg[i], ft_count_name(k->arg[i]));
		if (env_get_val(name, k->env))
			delete_env(&(k->env), k->arg[i]);
		ft_lstpush(&(k->env), (void*)k->arg[i], ft_strlen(k->arg[i]));
		i++;
	}
	k->strenv = lst_to_str(k->env);
	free(name);
	return (0);
}

int				unset_env(t_msh *k)
{
	int			i;

	if (!k->arg[1])
		ft_err("unsetenv: not enough arguments", NULL);
	i = 1;
	while (k->arg[i])
	{
		if (env_get_val(k->arg[i], k->env))
			delete_env(&(k->env), k->arg[i]);
		i++;
	}
	k->strenv = lst_to_str(k->env);
	return (0);
}
