/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoaf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbueno-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 19:21:23 by fbueno-m          #+#    #+#             */
/*   Updated: 2018/06/16 19:21:24 by fbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_counter(uintmax_t number)
{
	int			i;

	i = 0;
	while (number > 0)
	{
		number = number / 10;
		i++;
	}
	return (i);
}

char			*ft_itoaf(uintmax_t number)
{
	int			i;
	char		*new;

	if (number == 0)
		return (ft_strdup("0"));
	i = ft_counter(number);
	if (!(new = ft_strnew(i)))
		return (NULL);
	while (number > 0)
	{
		new[i - 1] = number % 10 + '0';
		number = number / 10;
		i--;
	}
	return (new);
}
