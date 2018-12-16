/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbueno-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 16:40:17 by fbueno-m          #+#    #+#             */
/*   Updated: 2018/04/24 16:40:18 by fbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*res(int i, unsigned long long *param, char c)
{
	int			n;
	char		*base_x;
	char		*base_for_x;
	char		*res;

	n = 0;
	base_for_x = "0123456789ABCDEF";
	base_x = "0123456789abcdef";
	res = ft_strnew(sizeof(char) * i);
	i--;
	while (i >= 0)
	{
		if (c == 'x')
			res[n] = base_x[param[i]];
		if (c == 'X')
			res[n] = base_for_x[param[i]];
		n++;
		i--;
	}
	return (res);
}

char		*ft_itoa_base_uns(unsigned long long value, int base, char c)
{
	int					i;
	unsigned long long	param[64];

	i = 0;
	if (value == 0)
		return (ft_strsub("0", 0, 1));
	while (value != 0)
	{
		param[i++] = value % base;
		value = value / base;
	}
	return (res(i, param, c));
}
