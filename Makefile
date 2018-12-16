# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbueno-m <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/18 16:24:59 by fbueno-m          #+#    #+#              #
#    Updated: 2018/04/18 16:25:01 by fbueno-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = clang

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror

LIBFT = libft

LIB = libft.a

SRCS = check_options.c \
		ft_printf.c \
		handle_b.c \
		handle_c.c \
		handle_d_i.c \
		handle_o.c \
		handle_p.c \
		handle_s.c \
		handle_u.c \
		handle_ws.c \
		handle_x.c \
		is_flag.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):
	make -C $(LIBFT)
	$(CC) $(FLAGS) -c $(SRCS) -I $(LIBFT)
	ar rcs $(NAME) $(OBJS) $(LIBFT)/*.o
	ranlib $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)/$(LIB)

re: fclean all
