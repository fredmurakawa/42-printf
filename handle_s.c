/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbueno-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 15:36:48 by fbueno-m          #+#    #+#             */
/*   Updated: 2018/06/20 15:36:53 by fbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*str_precision(t_form *format, char *str)
{
	char *ret;

	if (format->prec < format->len && format->prec > 0)
		ret = ft_strsub(str, 0, format->prec);
	else if (format->point && format->prec == 0)
		ret = ft_strnew(0);
	else
		ret = ft_strsub(str, 0, format->len);
	return (ret);
}

static char	*set_width(t_form *format)
{
	int		n;
	char	*str;
	char	str_wid;

	str_wid = ' ';
	if (format->prec > 0 && format->prec < format->len)
		n = format->width - format->prec;
	else if (format->prec == 0 && format->point)
		n = format->width;
	else
		n = format->width - format->len;
	if (!format->flag.min && format->flag.zero)
		str_wid = '0';
	if (n < 0)
		n = 0;
	str = ft_strnew(n);
	ft_memset(str, str_wid, n);
	return (str);
}

char		*print_string(t_form *format, va_list *arg)
{
	char *str;
	char *str_wid;
	char *str_prec;
	char *tmp;

	if (ft_strcmp(format->lngth, "l"))
	{
		tmp = va_arg(*arg, char *);
		if (!tmp)
			tmp = "(null)";
		format->len = ft_strlen(tmp);
		str_prec = str_precision(format, tmp);
		str_wid = set_width(format);
		if (format->flag.min)
			str = ft_strjoin(str_prec, str_wid);
		else
			str = ft_strjoin(str_wid, str_prec);
		format->len = ft_strlen(str);
	}
	else
		str = print_w_string(format, arg);
	return (str);
}
