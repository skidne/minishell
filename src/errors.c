/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 16:54:22 by pgore             #+#    #+#             */
/*   Updated: 2017/02/20 14:33:08 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_err_comm(char *name)
{
	ft_putstr_fd(SHNAME, STDERR);
	ft_putstr_fd(": command not found: ", STDERR);
	if (name)
		ft_putstr_fd(name, STDERR);
	ft_putchar_fd('\n', STDERR);
}

void	ft_err_perm(char *name)
{
	ft_putstr_fd(SHNAME, STDERR);
	ft_putstr_fd(": permission denied: ", STDERR);
	if (name)
		ft_putstr_fd(name, STDERR);
	ft_putchar_fd('\n', STDERR);
}

void	ft_err_mem(void)
{
	ft_putstr_fd(SHNAME, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(strerror(ENOMEM), STDERR);
	ft_putchar_fd('\n', STDERR);
	exit(EXIT_FAILURE);
}

void	ft_err(char *str, char *name)
{
	ft_putstr_fd(str, STDERR);
	if (name)
		ft_putstr_fd(name, STDERR);
	ft_putchar_fd('\n', STDERR);
}

void	ft_fatal(char *msg)
{
	ft_putstr_fd(SHNAME, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(msg, STDERR);
	ft_putchar_fd('\n', STDERR);
	exit(EXIT_FAILURE);
}
