# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cpopa <cpopa@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2021/10/26 11:35:38 by cpopa         #+#    #+#                  #
#    Updated: 2022/01/28 15:33:13 by cpopa         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CFLAGS	= -Wall -Werror -Wextra -g -fsanitize=address

S_SRC	=	main.c\
			input.c\
			pipex.c\
			pipex_utils.c
S_PATH	=	src/
S_OBJ	=	$(S_SRC:%.c=$(S_PATH)%.o)

UTILS		=	error_free_exit.c
UTILS_PATH	=	utils/
UTILS_OBJ	=	$(UTILS:%.c=$(UTILS_PATH)%.o)

OBJ_FILES = $(S_OBJ) $(UTILS_OBJ)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ_FILES) libft/libft.a -o $(NAME)
	
%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C libft
	$(RM) $(OBJ_FILES)

fclean: clean
	$(RM) libft/libft.a
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re