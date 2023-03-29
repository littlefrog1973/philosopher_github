# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/02 12:25:01 by sdeeyien          #+#    #+#              #
#    Updated: 2023/03/29 09:41:35 by sdeeyien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
#CFLAGS = -g
UNAME_S := $(shell uname -s)
SRCDIR = ./src/
OBJDIR =
DEPS = philosopher.h

#SRC = philosopher.c init.c ft_atoi.c philo_thread1.c
SRC = philosopher.c init.c ft_atoi.c philo_thread2.c
BONUS =

OBJ := $(patsubst %.c, $(OBJDIR)%.o, $(SRC))
#BONUS_OBJ := $(patsubst %.c, $(OBJDIR)%.o, $(BONUS))
SRC := $(addprefix $(SRCDIR), $(SRC))
#BONUS := $(addprefix $(SRCDIR), $(BONUS))
DEPS := $(addprefix $(SRCDIR), $(DEPS))

NAME = philosopher
BONUS_NAME =

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

#bonus : $(BONUS_NAME)

#$(BONUS_NAME): $(BONUS_OBJ)
#	make -C $(LIBDIR) all
#	$(CC) $(CFLAGS) $^ $(LIBDIR)/$(LIBOBJ) -o $@

%.o: $(SRCDIR)%.c $(DEPS)
	$(CC) -c $(CFLAGS) $(DEPS) $<

clean :
	rm -f *.o

fclean : clean
	rm -f $(NAME) $(BONUS_NAME)

re : fclean all

.PHONY : all clean fclean re bonus
