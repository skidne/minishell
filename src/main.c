/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 16:52:05 by pgore             #+#    #+#             */
/*   Updated: 2017/02/23 21:14:57 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**lst_to_str(t_list *lenv)
{
	int			i;
	char		**env;

	if (!(env = (char**)malloc(sizeof(char*) * ft_lstcount(lenv) + 1)))
		ft_err_mem();
	i = 0;
	while (lenv)
	{
		env[i] = (char*)(lenv->content);
		lenv = lenv->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

t_list			*cpy_env(char **environ)
{
	t_list		*res;
	int			i;

	res = NULL;
	i = -1;
	while (environ[++i])
		ft_lstpush(&res, (void*)environ[i], ft_strlen(environ[i]));
	return (res);
}

int				prepare_env(t_msh *k)
{
	int			heh;

	heh = 1;
	if (ft_strlen(k->line) > 0)
	{
		k->arg = ft_strsplit(k->line, ' ');
		k->comm = (k->env) ? found_path(k->env, k->arg[0]) : k->arg[0];
		heh = (k->comm) ? 1 : 0;
		if (access(k->comm, F_OK | X_OK) && ft_strcmp(CD, k->arg[0]))
			heh = NOEXEC;
		if (access(k->comm, F_OK) && ft_strcmp(CD, k->arg[0]))
			heh = NOEXIST;
		if (!ft_strcmp(k->arg[0], ENV))
			heh = display_env(k->env);
		if (!ft_strcmp(k->arg[0], SETENV))
			heh = set_env(k);
		if (!ft_strcmp(k->arg[0], CD))
			heh = check_if_dir(k);
		if (!ft_strcmp(k->arg[0], UNSET))
			heh = unset_env(k);
	}
	else
		heh = -1;
	return (heh);
}

void			do_commands(t_msh *k)
{
	pid_t		pid;

	specialcheck(k);
	k->ok = prepare_env(k);
	k->ok = (exit_prog(k)) ? k->ok : 0;
	if (k->ok > 1)
		(k->ok == NOEXEC) ? ft_err_perm(k->arg[0]) : ft_err_comm(k->arg[0]);
	pid = fork();
	if (!pid && k->ok == 1)
	{
		execve(k->comm, k->arg, k->strenv);
		exit(EXIT_FAILURE);
	}
	else
		(pid > 0) ? (pid = wait(NULL)) : exit(EXIT_FAILURE);
}

int				main(int ac, char **av, char **envp)
{
	t_msh		k;

	(void)ac;
	init_data(&k);
	k.env = cpy_env(envp);
	k.strenv = lst_to_str(k.env);
	go_signal(k.env);
	while (1)
	{
		clear_win(av, envp);
		put_prompt(k.env);
		if (!get_input(&k))
		{
			ft_putstr(KNRM);
			do_commands(&k);
		}
	}
	return (1);
}
