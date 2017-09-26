/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 12:08:29 by pgore             #+#    #+#             */
/*   Updated: 2017/02/23 17:56:29 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			find_that_env(char *name, char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] != '=' && arg[i] == name[i])
		i++;
	if (arg[i] == '=')
		return (1);
	return (0);
}

t_list		*find_list_env(char *arg, t_list *env, size_t *found_len)
{
	size_t	max_len;
	size_t	tmp;
	t_list	*match;
	char	*equal_ptr;

	max_len = 0;
	match = NULL;
	while (env)
	{
		equal_ptr = ft_strchr(LSTR(env), '=');
		if (equal_ptr == NULL)
			ft_fatal("internal error: invalid environment declaration");
		*equal_ptr = 0;
		tmp = ft_strlen(LSTR(env));
		if (ft_strnequ(arg, LSTR(env), tmp) && tmp > max_len)
		{
			max_len = tmp;
			match = env;
		}
		*equal_ptr = '=';
		LTONEXT(env);
	}
	*found_len = max_len;
	return (match);
}

char		*env_get_val(char *arg, t_list *env)
{
	t_list	*needle;
	size_t	len;

	if (arg == NULL || env == NULL)
		return (NULL);
	needle = find_list_env(arg, env, &len);
	if (needle == NULL || ft_strlen(arg) != len)
		return (NULL);
	return (LSTR(needle) + len + 1);
}
