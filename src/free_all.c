/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 11:13:33 by pgore             #+#    #+#             */
/*   Updated: 2017/02/20 17:56:41 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		init_data(t_msh *sh_data)
{
	ft_bzero(sh_data, sizeof(t_msh));
}

void		free_dbl(char **str)
{
	int		i;

	if (str != NULL)
	{
		i = 0;
		while (str[i])
			free(str[i++]);
		free(str);
	}
}

void		ft_delmem(void **data)
{
	if (data && *data)
	{
		free(*data);
		*data = NULL;
	}
}

void		del_env_cell(void *str, size_t size)
{
	(void)size;
	if (str)
		free(str);
}

void		free_all(t_msh *k)
{
	ft_delmem((void*)(&(k->line)));
	ft_delmem((void*)(&(k->comm)));
	ft_lstdel(&(k->env), &del_env_cell);
	ft_delmem((void*)(&(k->strenv)));
	free_dbl(k->arg);
}
