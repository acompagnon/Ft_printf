# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acompagn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/15 17:22:57 by acompagn          #+#    #+#              #
#    Updated: 2018/12/17 16:40:19 by acompagn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c \
	   conv.c \
	   itoas.c \
	   get_argument.c \

OBJECTS = $(SRCS:.c=.o)

HEADERS = libft/

CFLAGS =

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
CYAN = \033[36m
END= \033[0m

all: $(NAME)

$(NAME): libft/libft.a $(OBJECTS)
	@libtool -static -o $@ $^
	@echo "$(GREEN)[OK]$(END) Executable ft_printf"

libft/libft.a: 
	@(cd libft/ && make)

test: all
	@gcc main.c -L. -lftprintf -o printest -I $(HEADERS)

%.o: %.c $(HEADERS) ft_printf.h
	@gcc $(CFLAGS) -I $(HEADERS) -o $@ -c $<
	@echo "$(CYAN)[CC]$(END) $<"

.PHONY: clean

clean:
	@rm -f $(OBJECTS)
	@(cd libft/ && make $@)
	@echo "$(GREEN)[OK]$(END) Clean ft_printf objects"

fclean:
	@rm -f $(OBJECTS)
	@echo "$(GREEN)[OK]$(END) Clean ft_printf objects"
	@rm -f $(NAME)
	@(cd libft/ && make $@)
	@echo "$(GREEN)[OK]$(END) Delete ft_printf"

re: fclean all
