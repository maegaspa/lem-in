# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/10 19:59:22 by cgarrot      #+#   ##    ##    #+#        #
#    Updated: 2020/01/14 07:05:47 by hmichel     ###    #+. /#+    ###.fr      #
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
		src/utils3\
		src/init\
		src/set_all_tab\
		src/main\
		src/clear_matrix\
		src/bfs1\
		src/bfs2\
		src/bfs3\
		src/display_algo\
		src/print\

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
	@printf $(RED)"                                                                      ___ \n"
	@printf "                                _____________________________________ //  \n"
	@printf "                              / /-----------|  |----------| |--------- \ \n"
	@printf "                            / /             |  |          | |           \ \n"
	@printf "                          / /               |  |          | |           | \n"
	@printf "               _________/ /                 |  |          | |           | \n"
	@printf "      _______"
	@printf $(YELLOW)"("
	@printf $(RED)"|___________\_________________|  |----------===============\          "
	@printf $(W)"(@)\n"
	@printf $(RED)"    /                  |                 (=) |           (=)|            "
	@printf $(YELLOW)"/\ "
	@printf $(RED)"       "
	@printf $(W)"(@) (@)\n"
	@printf $(RED)"  /                   | "
	@printf $(PURPLE)"cgarrot && maegaspa"
	@printf $(RED)" |                |           "
	@printf $(YELLOW)"\/"
	@printf $(RED)"\     "
	@printf $(W)"(@) (@)\n"
	@printf $(RED)" /"
	@printf $(YELLOW)"<>"
	@printf $(RED)"      ________    |       "
	@printf $(PURPLE)"lem-in"
	@printf $(RED)"        |                |________      \     "
	@printf $(W)"(@)\n"
	@printf $(RED)" |      /  "
	@printf $(W)"______"
	@printf $(RED)"  \   |  <==================|===========>  /  "
	@printf $(W)"______"
	@printf $(RED)"  \   -/   "
	@printf $(W)"(@)\n"
	@printf $(RED)" |)    |  "
	@printf $(W)"/ \  / \ "
	@printf $(RED)" |__|_____________________|_____________|  "
	@printf $(W)"/ \  / \ "
	@printf $(RED)" | [ "
	@printf $(W)"(@)\n"
	@printf $(RED)" \____ | "
	@printf $(W)"|   ()   | "
	@printf $(RED)"|______________________________________| "
	@printf $(W)"|   ()   | "
	@printf $(RED)"|_/ \n"
	@printf $(W)"          \_/__\_/                                            \_/__\_/ \n"
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
