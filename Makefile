# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romasant <romasant@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/19 17:29:03 by romasant          #+#    #+#              #
#    Updated: 2026/09/20 23:12:48 by romasant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -c -Wall -Wextra -Werror -g -std=c99
OBJS = *.c
NAME = libft.a
AR = ar rcs $(NAME) *.o

all: $(NAME)

$(NAME): *.o
	$(CC) $(CFLAGS) $(OBJS)
	$(AR)

clean:
	rm *.o

fclean:
	rm -rf *.o $(NAME)

re: fclean all
