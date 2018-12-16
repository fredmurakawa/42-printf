/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbueno-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 17:52:26 by fbueno-m          #+#    #+#             */
/*   Updated: 2018/06/20 17:52:27 by fbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long	set_u_param_flags(t_form *format, va_list *arg)
{
	unsigned long long	number;

	number = 0;
	if (!(ft_strcmp(format->lngth, "")))
		number = va_arg(*arg, unsigned int);
	else if (!(ft_strcmp(format->lngth, "l")))
		number = va_arg(*arg, unsigned long);
	else if (!(ft_strcmp(format->lngth, "ll")))
		number = va_arg(*arg, unsigned long long);
	else if (!(ft_strcmp(format->lngth, "h")))
		number = (unsigned short)va_arg(*arg, unsigned int);
	else if (!(ft_strcmp(format->lngth, "hh")))
		number = (unsigned char)va_arg(*arg, unsigned int);
	else if (!(ft_strcmp(format->lngth, "z")))
		number = va_arg(*arg, size_t);
	else if (!(ft_strcmp(format->lngth, "j")))
		number = va_arg(*arg, uintmax_t);
	return (number);
}

static int			count_digits(unsigned long long nbr)
{
	int					ret;
	unsigned long long	cpy;

	ret = 1;
	cpy = nbr;
	while (cpy > 9)
	{
		cpy /= 10;
		ret++;
	}
	return (ret);
}

static	char		*u_int_precision(t_form *format, long long number)
{
	char	*ret;
	char	*precision;
	char	*tmp_str;
	int		nbr;
	int		digits;

	nbr = count_digits(number);
	if (format->prec > nbr)
		digits = format->prec;
	else
		digits = nbr;
	precision = ft_strnew(digits + 1);
	ft_bzero(precision, digits + 1);
	ret = precision;
	while (format->prec > nbr++)
		*(precision++) = '0';
	tmp_str = ft_itoaf(number);
	if (format->point && number == 0)
		tmp_str = ft_strsub("", 0, 0);
	ft_strcpy(precision, tmp_str);
	format->len = ft_strlen(ret);
	free(tmp_str);
	return (ret);
}

static char			*set_width(t_form *format)
{
	char	*ret;
	char	*temp;
	char	charac;
	int		flag_zero;
	int		len;

	flag_zero = 0;
	if (format->flag.zero && !format->point && !format->flag.min)
		flag_zero = 1;
	len = format->width < format->len ? 0 : format->width;
	temp = ft_strnew(len + 1);
	ret = temp;
	ft_bzero(temp, len + 1);
	charac = (flag_zero ? '0' : ' ');
	if (len)
		while (len > format->len++)
			*(temp++) = charac;
	return (ret);
}

char				*print_u_number(t_form *format, va_list *arg)
{
	char					*temp;
	char					*value;
	char					*join;
	unsigned long long int	number;

	if (format->param == 'U')
		number = (unsigned long long)va_arg(*arg, unsigned long long);
	else
		number = set_u_param_flags(format, arg);
	format->len = count_digits(number);
	value = u_int_precision(format, number);
	join = set_width(format);
	if (format->flag.min)
		temp = ft_strjoin(value, join);
	else
		temp = ft_strjoin(join, value);
	format->len = ft_strlen(temp);
	return (temp);
}
