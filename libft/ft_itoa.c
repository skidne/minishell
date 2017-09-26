/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 18:51:20 by pgore             #+#    #+#             */
/*   Updated: 2016/10/17 18:51:23 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int n)
{
	int		k;
	int		l;

	k = 1;
	l = 0;
	if (n < 0)
		n = -n;
	while (n / k > 0)
	{
		k *= 10;
		l++;
	}
	return (l);
}

static int	div_num(int n)
{
	int		k;
	int		l;

	k = 1;
	l = 0;
	if (n < 0)
		n = -n;
	while (n / k > 0)
	{
		k *= 10;
		l++;
	}
	k /= 10;
	return (k);
}

static char	*ft_fill_str(char *str, int tab[20], int n)
{
	while (tab[1] > 0)
	{
		str[tab[0]] = (n / tab[2]) % 10 + '0';
		tab[0]++;
		tab[2] /= 10;
		tab[1]--;
	}
	str[tab[0]] = '\0';
	return (str);
}

char		*ft_itoa(int n)
{
	int		tab[20];
	char	*str;

	tab[0] = 0;
	tab[1] = get_size(n);
	str = (char*)ft_memalloc(sizeof(char) * tab[1] + 1);
	if (n == 0)
		return (ft_strdup("0"));
	if (n == 2147483647)
		return (ft_strdup("2147483647"));
	if (n == (-2147483648))
		return (ft_strdup("-2147483648"));
	tab[2] = div_num(n);
	if (n < 0)
	{
		n = -n;
		str[0] = '-';
		tab[0] += 1;
	}
	str = ft_fill_str(str, tab, n);
	return (str);
}
