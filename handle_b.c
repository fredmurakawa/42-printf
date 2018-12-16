/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbueno-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 20:43:39 by fbueno-m          #+#    #+#             */
/*   Updated: 2018/09/25 20:43:42 by fbueno-m         ###   ########.fr       */
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

static	char	*set_bin_prec(t_form *format, long long number)
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
	precision = ft_strnew(digits);
	ret = precision;
	while (format->prec > nbr++)
		*(precision++) = '0';
	if (number < 0)
		number = -number;
	tmp_str = ft_itoa_base_uns(number, 2, 'x');
	ft_strcpy(precision, tmp_str);
	format->len = ft_strlen(ret) + 2;
	ft_memdel((void*)&tmp_str);
	return (ret);
}

static char		*set_width(t_form *format)
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

char			*print_binary(t_form *format, va_list *arg)
{
	char				*temp;
	char				*bin_prec;
	char				*bin_wid;
	char				*res;
	unsigned long long	nbr;

	nbr = set_u_param_flags(format, arg);
	format->len = count_digits(nbr);
	bin_prec = set_bin_prec(format, nbr);
	bin_wid = set_width(format);
	if (format->flag.min)
		temp = ft_strjoin(bin_prec, bin_wid);
	else
		temp = ft_strjoin(bin_wid, bin_prec);
	res = temp;
	format->len = ft_strlen(res);
	return (res);
}
