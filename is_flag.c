/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbueno-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 19:30:17 by fbueno-m          #+#    #+#             */
/*   Updated: 2018/06/21 19:30:18 by fbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_form			*check_flags(char *format, va_list *arg, size_t *i)
{
	t_form		*ret;

	ret = malloc(sizeof(t_form));
	ft_bzero(ret, sizeof(t_form));
	ret->flag = check_main_flags(format, i);
	ret->width = check_flag_width(format, i, arg, ret);
	ret->prec = check_precision(format, i, arg, ret);
	ret->lngth = check_length(format, i);
	ret->param = format[(*i)];
	return (ret);
}

t_flags			check_main_flags(char *format, size_t *i)
{
	t_flags		ret;

	ft_bzero(&ret, sizeof(t_flags));
	(*i)++;
	while (format[*i] == '+' || format[*i] == '-' ||
			format[*i] == ' ' || format[*i] == '0' || format[*i] == '#')
	{
		if (format[*i] == '-')
			ret.min = 1;
		if (format[*i] == '+')
			ret.add = 1;
		if (format[*i] == '#')
			ret.gate = 1;
		if (format[*i] == '0')
			ret.zero = 1;
		if (format[*i] == ' ')
			ret.spc = 1;
		(*i)++;
	}
	return (ret);
}

int				check_flag_width(char *format, size_t *i, va_list *arg,
	t_form *form)
{
	size_t		index;
	int			ret;

	index = *i;
	while (ft_isdigit(format[*i]))
		(*i)++;
	if (format[(*i)] == '*')
	{
		ret = va_arg(*arg, int);
		if (ret < 0)
		{
			ret *= -1;
			form->flag.min = 1;
		}
		(*i)++;
	}
	else
		ret = ft_atoi(format + index);
	return (ret);
}

int				check_precision(char *format, size_t *i, va_list *arg,
	t_form *form)
{
	int				index;
	int				ret;

	ret = 0;
	if (format[(*i)] == '.')
	{
		form->point = 1;
		(*i)++;
		index = *i;
		while (ft_isdigit(format[*i]))
			(*i)++;
		if (format[(*i)] == '*')
		{
			ret = va_arg(*arg, int);
			if (ret < 0)
			{
				ret *= -1;
				form->flag.min = 1;
			}
			(*i)++;
		}
		else
			ret = ft_atoi(format + index);
	}
	return (ret);
}

char			*check_length(char *format, size_t *i)
{
	char			*ret;

	ret = ft_strnew(2);
	if (format[*i] == 'h' || format[*i] == 'l' || format[*i] == 'L' ||
			format[*i] == 't' || format[*i] == 'j' || format[*i] == 'z')
	{
		*ret = format[(*i)++];
		if (format[*i] == 'h' || format[*i] == 'l')
		{
			*(++ret) = format[(*i)];
			(*i)++;
			ret--;
		}
	}
	return (ret);
}
