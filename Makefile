# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/16 19:36:03 by vkovsh            #+#    #+#              #
#    Updated: 2018/02/21 18:28:12 by vkovsh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	libftprintf.a

CC 			=	gcc
CC_FLAGS 	=	-Wall -Werror -Wextra

SRC_PATH 	=	./srcs/

INC_PATH	=	./includes/ $(LIBFT_PATH)includes/
OBJ_PATH	=	./obj/
LIBFT_PATH	=	./libft/

OBJ			=	$(addprefix $(OBJ_PATH),$(OBJ_NAME))

INC			=	$(addprefix -I, $(INC_PATH))

OBJ_NAME	=	$(SRC_NAME:.c=.o)

OBJ_NAME	+=	$(LIBFT_NAME:.c=.o)

SRC_NAME	=	ft_printf.c 	\
				get_spec.c 		\
				format_value.c

LIBFT_NAME	=	ft_islow.c 		\
				ft_lstrev.c		\
				ft_memalloc.c 	\
				ft_putendl.c 	\
				ft_strcpy.c 	\
				ft_strmapi.c 	\
				ft_strsub.c		\
				ft_isprint.c	\
				ft_memccpy.c	\
	   			ft_putendl_fd.c	\
				ft_strdel.c		\
				ft_strncat.c	\
	   			ft_strtolower.c	\
				ft_arealpha.c	\
				ft_isupper.c	\
	   			ft_memchr.c		\
				ft_putnbr.c		\
				ft_strdup.c		\
	   			ft_strncmp.c	\
				ft_strtoupper.c	\
				ft_aredigits.c	\
				ft_itoa.c		\
				ft_memcmp.c		\
				ft_putnbr_fd.c	\
				ft_strequ.c		\
				ft_strncpy.c	\
				ft_strtrim.c	\
				ft_atoi.c		\
				ft_lstadd.c		\
				ft_memcpy.c		\
				ft_putstr.c		\
				ft_striter.c	\
				ft_strnequ.c	\
				ft_tolower.c	\
				ft_bzero.c		\
				ft_lstdel.c		\
				ft_memdel.c		\
				ft_putstr_fd.c	\
				ft_striteri.c	\
				ft_strnew.c		\
				ft_toupper.c	\
				ft_isalnum.c	\
				ft_lstdelone.c	\
				ft_memmove.c	\
				ft_strcat.c		\
				ft_strjoin.c	\
				ft_strnstr.c	\
				ft_isalpha.c	\
				ft_lstiter.c	\
				ft_memset.c		\
				ft_strchr.c		\
				ft_strlcat.c	\
				ft_strrchr.c	\
				ft_isascii.c	\
				ft_lstmap.c		\
				ft_putchar.c	\
				ft_strclr.c		\
				ft_strlen.c		\
				ft_strsplit.c	\
				ft_isdigit.c	\
				ft_lstnew.c		\
				ft_putchar_fd.c	\
				ft_strcmp.c		\
				ft_strmap.c		\
				ft_strstr.c		\
				ft_lstcount.c	\
				get_next_line.c	\
				ft_ishex.c		\
				ft_arehex.c 	\
				ft_lltoa.c 		\
				ft_lltoa_base.c

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $^
	@ranlib $@
	@echo "Compiling" [ $(NAME) ]

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CC_FLAGS) -o $@ -c $< $(INC)
	@echo "Linking" [ $< ]

$(OBJ_PATH)%.o: $(LIBFT_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CC_FLAGS) -o $@ -c $< $(INC)
	@echo "Linking" [ $< ]

clean:
	@rm -rf $(OBJ_PATH)
	@echo "Cleaning obj [ $(NAME) ]..."

fclean: clean
	@rm -f $(NAME)
	@echo "Remove..." [ $(NAME) ]

re: fclean all

.PHONY: all clean fclean re

.NOTPARALLEL: all clean fclean re 
