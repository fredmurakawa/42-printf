/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_o.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbueno-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 20:44:32 by fbueno-m          #+#    #+#             */
/*   Updated: 2018/06/20 20:44:34 by fbueno-m         ###   ########.fr       */
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
		cpy /= 10;
		ret++;
	}
	return (ret);
}

static	char	*set_octal_prec(t_form *format, long long number)
{
	char	*ret;
	char	*precision;
	char	*tmp_str;
	int		digits;
	int		nbr;

	tmp_str = ft_itoa_base_uns(number, 8, 'x');
	if (number == 0 && (format->point || format->flag.gate))
		tmp_str = ft_strnew(0);
	nbr = ft_strlen(tmp_str);
	if (format->prec > nbr)
		digits = format->prec;
	else
		digits = nbr;
	precision = ft_strnew(digits + 1);
	ret = precision;
	while (format->prec > nbr++)
		*(precision++) = '0';
	ft_strcpy(precision, tmp_str);
	format->len = ft_strlen(ret);
	ft_memdel((void **)&tmp_str);
	return (ret);
}

static void		set_prefix(t_form *format, char **value, char **begin)
{
	if (format->flag.gate)
	{
		if (format->flag.zero && !format->point && !format->flag.min)
			*begin = ft_strjoin(ft_strsub("0", 0, 1), *begin);
		else
			*value = ft_strjoin(ft_strsub("0", 0, 1), *value);
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
		format->len = format->len + 1;
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

char			*print_octal(t_form *format, va_list *arg)
{
	char					*ret;
	char					*oct_prec;
	char					*oct_wid;
	unsigned long long int	nbr;

	if (format->param == '0')
		nbr = (unsigned long long)va_arg(*arg, unsigned long long);
	else
		nbr = set_u_param_flags(format, arg);
	format->len = count_digits(nbr);
	oct_prec = set_octal_prec(format, nbr);
	oct_wid = set_width(format);
	set_prefix(format, &oct_prec, &oct_wid);
	if (format->flag.min)
		ret = ft_strjoin(oct_prec, oct_wid);
	else
		ret = ft_strjoin(oct_wid, oct_prec);
	format->len = ft_strlen(ret);
	return (ret);
}
