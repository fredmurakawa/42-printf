/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_d_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbueno-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 15:38:02 by fbueno-m          #+#    #+#             */
/*   Updated: 2018/06/20 15:38:02 by fbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		count_digits(long long n)
{
	int					ret;
	unsigned long long	cpy;

	if (n == 0)
		return (0);
	cpy = n;
	if (n < 0)
		cpy = -cpy;
	ret = 1;
	while (cpy > 9)
	{
		cpy /= 10;
		ret++;
	}
	return (ret);
}

static void		set_flags(t_form *format, char **flag, long long number)
{
	if (number > 0 && format->flag.spc && !format->flag.add)
		*((*flag)++) = ' ';
	else if (number < 0 && ((!format->flag.zero || format->flag.min ||
																format->point)))
		*((*flag)++) = '-';
	else if (format->flag.add && (format->point || format->flag.min ||
														!(format->flag.zero)))
		*((*flag)++) = '+';
	return ;
}

static char		*int_precision(t_form *format, long long number)
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
	ret = precision;
	set_flags(format, &precision, number);
	while (format->prec > nbr++)
		*(precision++) = '0';
	if (number < 0)
		number *= -1;
	tmp_str = ft_itoaf(number);
	if (number == 0 && format->point)
		tmp_str = ft_strsub("", 0, 0);
	ft_strcpy(precision, tmp_str);
	free(tmp_str);
	format->len = ft_strlen(ret);
	return (ret);
}

static char		*set_width(t_form *format, long long n)
{
	char	*ret;
	char	*temp;
	char	charac;
	int		len;

	charac = ' ';
	if (format->flag.zero && !format->flag.min && !format->point)
	{
		charac = '0';
		if (n < 0 || format->flag.spc)
			(format->len)++;
	}
	len = format->width < format->len ? 0 : format->width;
	temp = ft_strnew(len + 1);
	ret = temp;
	if (charac == '0' && format->flag.spc && !format->flag.add)
		*(temp)++ = ' ';
	else if (n < 0 && charac == '0')
		*(temp++) = '-';
	else if (format->flag.add && charac == '0' && format->len++)
		*(temp++) = '+';
	while (len > format->len++)
		*(temp++) = charac;
	return (ret);
}

char			*print_number(t_form *format, va_list *arg)
{
	long long int	number;
	char			*ret;
	char			*value;
	char			*join;

	if (format->param == 'D')
		number = (long long)va_arg(*arg, long long);
	else
		number = set_param_flags(format, arg);
	format->len = count_digits(number);
	if (format->flag.spc || format->flag.add || number < 0)
		(format->len)++;
	value = int_precision(format, number);
	join = set_width(format, number);
	if (format->flag.min)
		ret = ft_strjoin(value, join);
	else
		ret = ft_strjoin(join, value);
	format->len = ft_strlen(ret);
	return (ret);
}
