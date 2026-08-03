# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Cloud <Cloud@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/01 13:32:34 by marvin            #+#    #+#              #
#    Updated: 2026/08/03 14:44:35 by Cloud            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
AR= ar rcs
CFLAGS= -Wall -Wextra -Werror
FILES_C= *.c
FILES_O= *.o
EXEC= ./a.out
PROGRAM= libft.a
.PHONY:
	all clean fclean re

all:
	$(CC) $(CFLAGS) -c $(FILES_C) && $(AR) $(PROGRAM) *.o

clean:
	rm -i *.o

fclean:
	rm *.o $(PROGRAM) $(EXEC)
re:
	$(fclean) $(all)
