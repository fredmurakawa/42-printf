/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbueno-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:33:41 by fbueno-m          #+#    #+#             */
/*   Updated: 2018/06/20 18:33:42 by fbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		count_digits(unsigned long long nbr)
{
	int					ret;
	unsigned long long	cpy;

	ret = 0;
	cpy = nbr;
	while (cpy > 9)
	{
		cpy = cpy / 10;
		ret++;
	}
	return (ret);
}

static	char	*set_hex_prec(t_form *format, unsigned long long number)
{
	char	*ret;
	char	*precision;
	char	*tmp_str;
	int		nbr;
	int		digits;

	nbr = count_digits(number);
	tmp_str = ft_itoa_base_uns(number, 16, format->param);
	nbr = ft_strlen(tmp_str);
	if (format->prec > nbr)
		digits = format->prec;
	else
		digits = nbr;
	precision = ft_strnew(digits + 1);
	ft_bzero(precision, digits + 1);
	ret = precision;
	while (format->prec > nbr++)
		*(precision++) = '0';
	if (number == 0 && format->point)
		tmp_str = ft_strsub("", 0, 0);
	ft_strcpy(precision, tmp_str);
	ft_memdel((void**)&tmp_str);
	format->len = ft_strlen(ret);
	return (ret);
}

static void		set_prefix(t_form *format,
		char **value, char **begin, unsigned long long nbr)
{
	if (nbr != 0 && format->flag.gate)
	{
		if (format->flag.zero && !format->point && !format->flag.min)
		{
			if (format->param == 'x')
				*begin = ft_strjoin(ft_strsub("0x", 0, 2), *begin);
			else
				*begin = ft_strjoin(ft_strsub("0X", 0, 2), *begin);
		}
		else
		{
			if (format->param == 'x')
				*value = ft_strjoin(ft_strsub("0x", 0, 2), *value);
			else
				*value = ft_strjoin(ft_strsub("0X", 0, 2), *value);
		}
	}
	return ;
}

static char		*set_width(t_form *format)
{
	char	*ret;
	char	*temp;
	int		len;
	char	charac;

	charac = ' ';
	if (format->flag.gate)
		format->len = format->len + 2;
	if (!format->point && !format->flag.min && format->flag.zero)
		charac = '0';
	len = format->width < format->len ? 0 : format->width;
	temp = ft_strnew(len + 1);
	ret = temp;
	if (len)
	{
		while (len > format->len++)
			*(temp++) = charac;
	}
	return (ret);
}

char			*print_hex(t_form *format, va_list *arg)
{
	char					*temp;
	char					*hex_prec;
	char					*hex_wid;
	unsigned long long int	n;

	n = set_u_param_flags(format, arg);
	format->len = count_digits(n);
	hex_prec = set_hex_prec(format, n);
	hex_wid = set_width(format);
	set_prefix(format, &hex_prec, &hex_wid, n);
	if (format->flag.min)
		temp = ft_strjoin(hex_prec, hex_wid);
	else
		temp = ft_strjoin(hex_wid, hex_prec);
	format->len = ft_strlen(temp);
	return (temp);
}
