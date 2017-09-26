/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 08:24:50 by pgore             #+#    #+#             */
/*   Updated: 2017/02/20 11:32:32 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*g_env;

void			go_signal(t_list *env)
{
	g_env = env;
	echo_off();
	signal(SIGINT, handle_signal);
	echo_on();
}

void			handle_signal(int sign)
{
	if (sign == SIGINT)
	{
		PUTEND;
		put_prompt(g_env);
	}
}

void			echo_on(void)
{
	tcsetattr(0, TCSANOW, &g_stored);
	return ;
}

void			echo_off(void)
{
	struct termios	new;

	tcgetattr(0, &g_stored);
	ft_memcpy(&new, &g_stored, sizeof(struct termios));
	new.c_lflag &= (~ECHO);
	tcsetattr(0, TCSANOW, &new);
}
