/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 00:22:17 by pgore             #+#    #+#             */
/*   Updated: 2017/02/20 15:42:01 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			clear_win(char **av, char **envp)
{
	static int	i = 0;
	pid_t		pid;

	if (i)
		return ;
	i = 1;
	pid = fork();
	if (!pid)
		execve("/usr/bin/clear", av, envp);
	else
		(pid > 0) ? (pid = wait(NULL)) : exit(EXIT_FAILURE);
	ft_putendl("\t\t+-------------------------------+");
	ft_putendl("\t\t|       M I N I S H E L L       |");
	ft_putendl("\t\t+-------------------------------+\n");
}

void			replace_home(char *home, char **buff)
{
	int			i;

	i = ft_strlen(home);
	if ((*buff)[i])
		*buff = ft_strjoin("~", &(*buff)[i]);
	else
		*buff = ft_strdup("~");
}

void			look_for_home(t_list *env, char **buff)
{
	char		*home;

	if (!(home = env_get_val("HOME", env)))
		return ;
	if (ft_strstr(*buff, home))
		replace_home(home, buff);
}

void			put_prompt(t_list *env)
{
	char		*buff;

	buff = ft_strnew(MSIZE);
	buff = getcwd(buff, MSIZE);
	look_for_home(env, &buff);
	ft_putstr(KMAG"╭─{"KDS2);
	ft_putstr(buff);
	ft_putstr(KMAG"}\n╰─>");
	PROMPT;
	free(buff);
}
