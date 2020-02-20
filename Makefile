# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2020/02/06 14:32:49 by cgarrot      #+#   ##    ##    #+#        #
#    Updated: 2020/02/10 15:47:18 by cgarrot     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = lem-in
CC = gcc
DEBUG = -fsanitize=address
FLAGS = -Wall -Wextra -Werror
INC = include/lemin.h
HEADER = include
OPTI = -O3 -march=native -flto -ffast-math

#------------------------------------FILE--------------------------------------#

FILES = src/parser\
		src/parser_check\
		src/check_link_name\
		src/ft_list\
		src/utils\
		src/utils2\
		src/utils3\
		src/utils4\
		src/init\
		src/init2\
		src/set_all_tab\
		src/main\
		src/bfs1\
		src/setup_bfs\
		src/bfs2\
		src/function_matrix_state\
		src/bfs4\
		src/bfs5\
		src/bfs6\
		src/bfs7\
		src/display_algo\
		src/free\
		src/dispatch_ant\
		src/clear_path\
		src/free_error\

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

$(NAME): $(OBJ) $(INC)
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
	@$(CC) $(FLAGS) $(OBJ) -L. libft/libftprintf.a -o $(NAME) $(OPTI)


%.o: src/%.c $(INC) libft/libftprintf.a
	@$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $< $(OPTI)

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
