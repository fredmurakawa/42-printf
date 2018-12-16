/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ws.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbueno-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 20:46:10 by fbueno-m          #+#    #+#             */
/*   Updated: 2018/09/25 20:46:13 by fbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*set_ws_prec(t_form *format, wchar_t *wchar)
{
	char	*ret;
	int		i;
	char	*tmp_str;

	i = 0;
	tmp_str = ft_strnew(format->len);
	while (*((unsigned *)wchar) != L'\0')
	{
		tmp_str[i] = *wchar;
		wchar++;
		i++;
	}
	if (format->prec < format->len && format->prec > 0)
		ret = ft_strsub(tmp_str, 0, format->prec);
	else
		ret = ft_strsub(tmp_str, 0, format->len);
	free(tmp_str);
	return (ret);
}

static char	*set_width(t_form *format)
{
	int		nbr;
	char	*ret;
	char	charac;

	charac = ' ';
	if (format->prec < format->len && format->prec > 0)
		nbr = format->width - format->prec;
	else
		nbr = format->width - format->len;
	if (nbr < 0)
		nbr = 0;
	ret = ft_strnew(nbr);
	ft_memset(ret, charac, nbr);
	return (ret);
}

char		*print_w_string(t_form *format, va_list *arg)
{
	char	*ret;
	char	*ws_prec;
	char	*ws_wid;
	wchar_t	*wchar;

	wchar = va_arg(*arg, wchar_t*);
	format->len = (int)(w_strlen((unsigned *)wchar));
	ws_prec = set_ws_prec(format, wchar);
	ws_wid = set_width(format);
	if (format->flag.min)
		ret = ft_strjoin(ws_prec, ws_wid);
	else
		ret = ft_strjoin(ws_wid, ws_prec);
	format->len = ft_strlen(ret);
	return (ret);
}

size_t		w_strlen(unsigned *str)
{
	size_t len;

	len = 0;
	while (*str != L'\0')
	{
		len++;
		++str;
	}
	return (len);
}
