# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/10 19:59:22 by cgarrot      #+#   ##    ##    #+#        #
#    Updated: 2019/11/26 14:53:39 by seanseau    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = libftprintf.a
CC = gcc
FLAGS = -Wall -Wextra -Werror
INC = /includes/ft_printf.h
HEADER = include

#------------------------------------FILE--------------------------------------#

FILES = src/check_caract\
		src/check_digit_param\
		src/check_digit_param2\
		src/check_digit\
		src/check_hexa\
		src/check_hexa_param\
		src/check_hexa_param2\
		src/check_octa\
		src/check_octa_param\
		src/check_pointer\
		src/check_percent\
		src/check_str\
		src/conversion\
		src/ft_printf\
		src/init\
		src/parse\
		src/utils1\
		src/utils2\
		src/utils3\
		src/utils4\
		src/utils_octa_hexa\
		src/check_float\
		src/check_float_param\
		src/check_float_param2\

#----------------------------------COLOR---------------------------------------#

GREY='\x1b[30m'
RED='\x1b[37m'
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
	@cp libft/libft.a ./$(NAME)
	@ar rcs $(NAME) $(OBJ)
	@ranlib $(NAME)

object/%.o: src/%.c $(HEADER)
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
