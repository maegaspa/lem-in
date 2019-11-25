# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/10 19:59:22 by cgarrot      #+#   ##    ##    #+#        #
#    Updated: 2019/11/25 10:31:05 by seanseau    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = lemin
CC = gcc
DEBUG = -g -fsanitize=address
FLAGS = -Wall -Wextra -Werror -g
INC = include/lemin.h
HEADER = include

#------------------------------------FILE--------------------------------------#

FILES = src/parser\
		src/ft_list\
		src/utils\
		src/utils2\
		src/init\
		src/set_all_tab\
		src/main\
		src/bfs\
		src/pathfinder\

#----------------------------------COLOR---------------------------------------#

GREY='\x1b[30m'
RED='\x1b[34m'
GREEN='\x1b[32m'
YELLOW='\x1b[33m'
BLUE='\x1b[34m'
PURPLE='\x1b[35m'
CYAN='\x1b[36m'
W='\x1b[37m'

#----------------------------------SOURCE--------------------------------------#

SRC = $(addsuffix .c , $(FILES))

#----------------------------------OBJECT--------------------------------------#

OBJ = $(addsuffix .o , $(FILES))

#-----------------------------------RULE---------------------------------------#

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) $(FLAGS) $(SRC) -L. libft/libftprintf.a -o $(NAME)


object/%.o: src/%.c
	@$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

clean:
	@echo "\033[1m|---------------------------------|\033[0m"
	@echo "\033[1m|-------Supprimer les OBJECT------|\033[0m"
	@echo "\033[1m|---------------------------------|\033[0m"
	@rm -f $(OBJ)
	@make clean -C libft/

fclean: clean
	@echo "\n"
	@echo "\033[1m|---------------------------------------|\033[0m"
	@echo "\033[1m|-------Supprimer la libftprintf.a------|\033[0m"
	@echo "\033[1m|---------------------------------------|\033[0m"
	@rm -f $(NAME)
	@make fclean -C libft/

re: fclean all
