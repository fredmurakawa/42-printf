/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbueno-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 17:37:36 by fbueno-m          #+#    #+#             */
/*   Updated: 2018/06/20 17:37:38 by fbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*set_width(t_form *format)
{
	int		nbr;
	char	*wid_str;
	char	character;

	character = ' ';
	nbr = format->width - format->len;
	if (nbr < 0)
		nbr = 0;
	if (format->flag.zero && !format->flag.min)
		character = '0';
	wid_str = ft_strnew(nbr);
	ft_memset(wid_str, character, nbr);
	return (wid_str);
}

char		*print_char(t_form *format, va_list *arg)
{
	char	*str;
	char	*wid_str;
	char	character;

	if (format->param != '%')
		character = (char)va_arg(*arg, int);
	else
		character = '%';
	format->len = 1;
	wid_str = set_width(format);
	str = ft_strnew(ft_strlen(wid_str) + 1);
	if (format->flag.min)
	{
		*(str) = character;
		ft_strcpy(str + 1, wid_str);
	}
	else
	{
		ft_strcpy(str, wid_str);
		str[ft_strlen(wid_str)] = character;
	}
	ft_memdel((void**)&wid_str);
	format->len = (!character) ? ft_strlen(str) + 1 : ft_strlen(str);
	return (str);
}
