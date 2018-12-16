/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbueno-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 21:42:50 by fbueno-m          #+#    #+#             */
/*   Updated: 2018/06/20 21:42:51 by fbueno-m         ###   ########.fr       */
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

static	char	*set_point_prec(t_form *format, long long number)
{
	char	*ret;
	char	*precision;
	char	*tmp_str;
	int		nbr;
	int		digits;

	nbr = count_digits(number);
	tmp_str = ft_itoa_base_uns(number, 16, 'x');
	if (number == 0 && format->point)
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
	if (number < 0)
		number = -number;
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

static void		set_prefix(t_form *format, char **value, char **begin)
{
	if (format->flag.zero && !format->point && !format->flag.min)
		*begin = ft_strjoin(ft_strsub("0x", 0, 2), *begin);
	else
		*value = ft_strjoin(ft_strsub("0x", 0, 2), *value);
	return ;
}

char			*print_pointer(t_form *format, va_list *arg)
{
	char					*ret;
	char					*point_prec;
	char					*point_wid;
	unsigned long long int	nbr;
	void					*pointer;

	pointer = va_arg(*arg, void*);
	nbr = (unsigned long long)pointer;
	format->len = count_digits(nbr);
	point_prec = set_point_prec(format, nbr);
	point_wid = set_width(format);
	set_prefix(format, &point_prec, &point_wid);
	if (format->flag.min)
		ret = ft_strjoin(point_prec, point_wid);
	else
		ret = ft_strjoin(point_wid, point_prec);
	format->len = ft_strlen(ret);
	return (ret);
}
