/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 18:00:58 by pgore             #+#    #+#             */
/*   Updated: 2017/02/20 14:28:20 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list			*redo_env(t_list **env, char *c)
{
	t_list		*new;
	char		*buff;

	new = *env;
	buff = ft_strnew(MSIZE);
	while (*env)
	{
		if (ft_strstr((*env)->content, c))
		{
			(*env)->content = (void*)ft_strjoin(c, getcwd(buff, MSIZE));
			(*env)->content_size = ft_strlen((*env)->content);
			break ;
		}
		*env = (*env)->next;
	}
	free(buff);
	return (new);
}

char			**go_home(t_list *env)
{
	char		**new;
	char		*tmp;
	int			flg;

	flg = 0;
	new = (char**)malloc(sizeof(char*) * 3);
	new[0] = ft_strdup("cd");
	tmp = NULL;
	while (env)
	{
		if (ft_strstr(env->content, "HOME"))
		{
			flg = 1;
			tmp = ft_strdup((char*)(env->content));
			new[1] = ft_strdup(&tmp[5]);
			break ;
		}
		env = env->next;
	}
	if (!flg)
		new[1] = getcwd(tmp, 100);
	new[2] = NULL;
	free(tmp);
	return (new);
}

int				check_if_dir(t_msh *k)
{
	struct stat	st;

	if (!k->arg[1] || (k->arg[1] && !ft_strcmp(k->arg[1], "~")))
	{
		k->env = redo_env(&(k->env), "OLDPWD=");
		k->arg = go_home(k->env);
	}
	if (lstat(k->arg[1], &st) < 0)
		ft_err("cd: no such file or directory: ", k->arg[1]);
	else if (S_ISDIR(st.st_mode))
	{
		if (!access(k->arg[1], X_OK))
		{
			k->env = redo_env(&(k->env), "OLDPWD=");
			chdir(k->arg[1]);
			k->env = redo_env(&(k->env), "PWD=");
		}
		else
			ft_err("cd: permission denied: ", k->arg[1]);
	}
	else
		ft_err("cd: not a directory: ", k->arg[1]);
	k->strenv = lst_to_str(k->env);
	return (0);
}
