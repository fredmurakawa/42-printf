/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbueno-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 19:22:09 by fbueno-m          #+#    #+#             */
/*   Updated: 2018/06/16 19:22:11 by fbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <wchar.h>
# include "libft/libft.h"

typedef struct		s_flags
{
	int				add;
	int				min;
	int				gate;
	int				zero;
	int				spc;
}					t_flags;

typedef struct		s_form
{
	char			param;
	t_flags			flag;
	int				width;
	int				prec;
	char			*lngth;
	int				point;
	int				len;
}					t_form;

typedef char		*(*t_fun)(t_form*, va_list*);

int					ft_printf(const char *restrict format, ...);
t_form				*check_flags(char *format, va_list *arg, size_t *i);
t_flags				check_main_flags(char *format, size_t *i);
int					check_flag_width(char *format, size_t *i,
											va_list *arg, t_form *form);
int					check_precision(char *format, size_t *i,
											va_list *arg, t_form *form);
char				*check_length(char *format, size_t *i);
int					print_param(t_form *form, va_list *arg);
t_fun				set_function(char c);
char				*print_number(t_form *format, va_list *arg);
char				*print_u_number(t_form *format, va_list *arg);
char				*print_char(t_form *format, va_list *arg);
char				*print_string(t_form *format, va_list *arg);
char				*print_w_string(t_form *format, va_list *arg);
char				*print_binary(t_form *format, va_list *arg);
char				*print_hex(t_form *format, va_list *arg);
char				*print_octal(t_form *format, va_list *arg);
char				*print_pointer(t_form *format, va_list *arg);
size_t				w_strlen(unsigned *str);
long long			set_param_flags(t_form *format, va_list *arg);
unsigned long long	set_u_param_flags(t_form *format, va_list *arg);
void				freemem(t_form *array);

#endif
