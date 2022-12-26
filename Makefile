# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 20:44:34 by dcarvalh          #+#    #+#              #
#    Updated: 2022/12/22 18:53:11 by dcarvalh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex
B_NAME = pipex_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS =	main.c \
		pipex.c \
		path.c \
		cmds.c \
		ft_split.c \
		free.c

B_SRCS =	main_bonus.c \
			pipex.c \
		 	path.c \
		 	cmds.c \
		 	ft_split.c \
			free.c

OBJS = $(SRCS:.c=.o)
B_OBJS = $(B_SRCS:.c=.o)

C_RED = \033[0;31m
C_GREEN = \033[1;92m
C_RESET = \033[0m
C_PURPLE = \033[0;35m
C_RED = \033[0;31m
BG_YELLOW = \x1b[43m

SRCS := $(addprefix srcs/, $(SRCS))
B_SRCS := $(addprefix srcs/bonus/, $(B_SRCS))

echo = /bin/echo -e

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -Iincs
	@$(echo) "$(C_GREEN) [OK]   $(C_PURPLE) Compiling:$(C_RESET)" $<

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@$(echo) "$(C_GREEN) [OK]   $(C_PURPLE) Compiling:$(C_RESET)" $(NAME)
	@$(echo) "$(C_GREEN)\tCompiled $(NAME)$(C_RESET)"
	
all : $(NAME)

bonus : $(B_OBJS)
	@$(CC) $(B_OBJS) -o pipex
	@$(echo) "$(C_GREEN) [OK]   $(C_PURPLE) Compiling:$(C_RESET)" $(NAME)
	@$(echo) "$(C_GREEN)\tCompiled $(NAME)$(C_RESET)"

clean:
	@rm -f $(OBJS) $(B_OBJS)
	@$(echo) "$(C_RED)\tRemoved object files$(C_RESET)"
	
fclean: clean
	@rm -f $(NAME) *.txt
	@$(echo) "$(C_RED)\tRemoved $(NAME)$(C_RESET)"
	
re: fclean all
	
sanitize: $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) -fsanitize=address -g


norm_M:
	@$(echo) "$(C_RED)$(BG_YELLOW)[Norminette]$(C_RESET)"
	@$(shell (norminette $(SRCS) incs/$(NAME).h > norm.txt))
	@if [ $(shell (< norm.txt wc -l)) -eq $(shell (< norm.txt grep "OK" | wc -l)) ] ;then \
		$(echo) "$(C_PURPLE)[Mandatory]: $(C_GREEN) [OK]$(C_RESET)" ; \
	else \
		$(echo) "$(C_PURPLE)[Mandatory]: $(C_RED) [KO]$(C_RESET)"; \
		< norm.txt cat | grep -v "OK" | grep --color=always -e "^" -e "Error:"; \
	fi ;
	@rm -f norm.txt

norm : norm_M
	@$(shell (norminette $(B_SRCS) $(NAME).h > norm.txt))
	@if [ $(shell (< norm.txt wc -l)) -eq $(shell (< norm.txt grep "OK" | wc -l)) ] ;then \
		$(echo) "$(C_PURPLE)[BONUS]: $(C_GREEN) [OK]$(C_RESET)" ; \
	else \
		$(echo) "$(C_PURPLE)[BONUS]: $(C_RED) [KO]$(C_RESET)"; \
		< norm.txt cat | grep -v "OK" | grep --color=always -e "^" -e "Error:"; \
	fi ;
	@rm -f norm.txt