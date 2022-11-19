# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 20:44:34 by dcarvalh          #+#    #+#              #
#    Updated: 2022/11/18 21:28:53 by dcarvalh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS =  main.c \
		pipex.c \
		path.c

OBJS = $(SRCS:.c=.o)

C_RED = \033[0;31m
C_GREEN = \033[0;32m
C_RESET = \033[0m
C_ORANGE = \033[0;33m
C_RED = \033[0;31m

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(C_GREEN) [OK]   $(C_ORANGE) Compiling:$(C_RESET)" $<

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@echo "$(C_GREEN) [OK]   $(C_ORANGE) Compiling:$(C_RESET)" $(NAME)
	@echo "$(C_GREEN)\tCompiled $(NAME)$(C_RESET)"
	
all : $(NAME)

clean:
	@rm -f $(OBJS) *.txt
	@echo "$(C_RED)\tRemoved object files$(C_RESET)"
	
fclean: clean
	@rm -f $(NAME)
	@echo "$(C_RED)\tRemoved $(NAME)$(C_RESET)"
	
re: fclean all
	