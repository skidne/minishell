/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 18:33:25 by pgore             #+#    #+#             */
/*   Updated: 2017/04/06 10:14:44 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				*ft_lstsearch(t_list *lst, char *cont)
{
	if (lst == NULL)
		return (NULL);
	if (ft_strstr((char*)lst->content, cont) && \
		!ft_strstr((char*)lst->content, "DEFAULTS_PATH"))
		return ((char*)lst->content);
	return (ft_lstsearch(lst->next, cont));
}

char				*found_path_mid(char **path, char *arg)
{
	struct dirent	*diren;
	char			*smpath;
	DIR				*dr;
	int				flg;
	int				i;

	i = -1;
	flg = 0;
	while (path[++i])
	{
		if (!(dr = opendir(path[i])))
			break ;
		while ((diren = readdir(dr)))
		{
			if (!ft_strcmp(diren->d_name, arg))
			{
				flg = 1;
				break ;
			}
		}
		if (flg)
			break ;
	}
	smpath = path[i];
	return (smpath);
}

char				*found_path(t_list *env, char *arg)
{
	char			**path;
	char			*smpath;

	if (!arg || !env)
		return (NULL);
	smpath = NULL;
	path = (char**)malloc(sizeof(char*) * 10);
	if (!(path = ft_strsplit(env_get_val("PATH", env), ':')))
		return (NULL);
	if (path)
	{
		smpath = found_path_mid(path, arg);
		if (smpath)
		{
			smpath = ft_strjoin(smpath, "/");
			smpath = ft_strjoin(smpath, arg);
		}
	}
	free_dbl(path);
	return (smpath);
}

int					exit_prog(t_msh *k)
{
	int				tmp;

	if (!ft_strcmp(k->arg[0], EXIT))
	{
		if (k->arg[1] && k->arg[2])
		{
			ft_putstr_fd("exit: too many arguments\n", STDERR);
			return (0);
		}
		else if (k->arg[1])
		{
			tmp = ft_atoi(k->arg[1]);
			free_all(k);
			exit(tmp);
		}
		else
		{
			free_all(k);
			exit(0);
		}
	}
	return (1);
}
