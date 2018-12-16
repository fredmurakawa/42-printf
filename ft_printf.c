/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbueno-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 19:21:23 by fbueno-m          #+#    #+#             */
/*   Updated: 2018/06/16 19:21:24 by fbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *restrict format, ...)
{
	size_t		ret;
	size_t		i;
	va_list		args;
	t_form		*temp;

	i = 0;
	ret = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] != '%')
		{
			write(1, (format + i), 1);
			ret++;
		}
		else
		{
			temp = check_flags((char *)format, &args, &i);
			ret = ret + print_param(temp, &args);
			freemem(temp);
		}
		i++;
	}
	va_end(args);
	return (ret);
}

void	freemem(t_form *array)
{
	if (!array)
		return ;
	ft_strdel(&(array->lngth));
	ft_memdel((void **)&array);
}
