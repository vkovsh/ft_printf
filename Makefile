# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/16 19:36:03 by vkovsh            #+#    #+#              #
#    Updated: 2018/02/21 16:40:52 by vkovsh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	libftprintf.a

CC 			=	gcc
CC_FLAGS 	=	-Wall -Werror -Wextra

SRC_PATH 	=	./srcs/

INC_PATH	=	./includes/ $(LIBFT_PATH)/includes/
OBJ_PATH	=	./obj/
LIBFT_PATH	=	./libft/

LIBFT		=	$(LIBFT_PATH)libft.a

OBJ			=	$(addprefix $(OBJ_PATH),$(OBJ_NAME))

INC			=	$(addprefix -I, $(INC_PATH))

OBJ_NAME	=	$(SRC_NAME:.c=.o)

SRC_NAME	=	ft_printf.c

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_PATH)
	@ar rc $@ $^ $(LIBFT)
	@ranlib $@
	@echo "Compiling" [ $(NAME) ]

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CC_FLAGS) -o $@ -c $< $(INC)
	@echo "Linking" [ $< ]

clean:
	@make -C $(LIBFT_PATH) clean
	@rm -rf $(OBJ_PATH)
	@echo "Cleaning obj [ $(NAME) ]..."

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	@echo "Remove..." [ $(NAME) ]

re: fclean all

.PHONY: all clean fclean re

.NOTPARALLEL: all clean fclean re 
