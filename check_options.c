/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbueno-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 15:52:58 by fbueno-m          #+#    #+#             */
/*   Updated: 2018/06/18 15:52:59 by fbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

static void	dictionary(t_fun *func)
{
	func['d'] = &print_number;
	func['D'] = &print_number;
	func['i'] = &print_number;
	func['u'] = &print_u_number;
	func['U'] = &print_u_number;
	func['c'] = &print_char;
	func['C'] = &print_char;
	func['s'] = &print_string;
	func['S'] = &print_w_string;
	func['b'] = &print_binary;
	func['x'] = &print_hex;
	func['X'] = &print_hex;
	func['o'] = &print_octal;
	func['O'] = &print_octal;
	func['p'] = &print_pointer;
}

int			print_param(t_form *form, va_list *arg)
{
	int		ret;
	t_fun	func;
	char	*val;

	func = set_function(form->param);
	if (func)
		val = func(form, arg);
	else if (form->width != 0)
	{
		form->len = form->width;
		val = ft_strnew(form->width);
		ft_memset(val, ' ', form->width);
		ret = (form->flag.min) ? 0 : form->width - 1;
		ft_memset(val + ret, form->param, 1);
	}
	else
	{
		form->len = 1;
		val = ft_strnew(1);
		ft_memset(val, form->param, 1);
	}
	ret = write(1, val, form->len);
	ft_memdel((void **)&val);
	return (ret);
}

t_fun		set_function(char c)
{
	int				param;
	static t_fun	*func;

	if (!func)
	{
		func = ft_memalloc(sizeof(*func) * 256);
		if (func)
			dictionary(func);
	}
	param = (int)c;
	return (func[param]);
}

long long	set_param_flags(t_form *format, va_list *arg)
{
	long long number;

	number = 0;
	if (!(ft_strcmp(format->lngth, "")))
		number = va_arg(*arg, int);
	else if (!(ft_strcmp(format->lngth, "l")))
		number = va_arg(*arg, long);
	else if (!(ft_strcmp(format->lngth, "ll")))
		number = va_arg(*arg, long long);
	else if (!(ft_strcmp(format->lngth, "h")))
		number = (short)va_arg(*arg, int);
	else if (!(ft_strcmp(format->lngth, "hh")))
		number = (char)va_arg(*arg, int);
	else if (!(ft_strcmp(format->lngth, "z")))
		number = va_arg(*arg, size_t);
	else if (!(ft_strcmp(format->lngth, "j")))
		number = va_arg(*arg, intmax_t);
	return (number);
}
