# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 20:44:34 by dcarvalh          #+#    #+#              #
#    Updated: 2022/12/19 20:42:17 by dcarvalh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS =  main.c \
		pipex.c \
		path.c \
		cmds.c \
		ft_split.c \
		utils.c \
		free.c

OBJS = $(SRCS:.c=.o)

C_RED = \033[0;31m
C_GREEN = \033[1;92m
C_RESET = \033[0m
C_PURPLE = \033[0;35m
C_RED = \033[0;31m
BG_YELLOW = \x1b[43m

echo = /bin/echo -e
%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(echo) "$(C_GREEN) [OK]   $(C_PURPLE) Compiling:$(C_RESET)" $<

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@$(echo) "$(C_GREEN) [OK]   $(C_PURPLE) Compiling:$(C_RESET)" $(NAME)
	@$(echo) "$(C_GREEN)\tCompiled $(NAME)$(C_RESET)"
	
all : $(NAME)

clean:
	@rm -f $(OBJS) 
	@$(echo) "$(C_RED)\tRemoved object files$(C_RESET)"
	
fclean: clean
	@rm -f $(NAME) *.txt
	@$(echo) "$(C_RED)\tRemoved $(NAME)$(C_RESET)"
	
re: fclean all
	
sanitize: $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) -fsanitize=address -g


norm:
	@$(shell (norminette $(SRCS) $(NAME).h > norm.txt))
	@if [ $(shell (< norm.txt wc -l)) -eq $(shell (< norm.txt grep "OK" | wc -l)) ] ;then \
		$(echo) "$(C_PURPLE)[NORMINETTE]: $(C_GREEN) [OK]$(C_RESET)" ; \
	else \
		$(echo) "$(C_PURPLE)[NORMINETTE]: $(C_RED) [KO]$(C_RESET)"; \
		< norm.txt cat | grep -v "OK" | grep --color=always -e "^" -e "Error:"; \
	fi ;
	@rm -f norm.txt