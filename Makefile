# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ojessi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/18 18:05:46 by ojessi            #+#    #+#              #
#    Updated: 2019/08/08 23:05:24 by ojessi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re, obj, red, grn, off

NAME = fractol

# src / obj files
SRC =	main.c \
		color.c \
		init_cl.c \
		key_hook.c \
		frac_params.c \
		cl_and_hook.c

OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))

# compiler
CC = gcc
CFLAGS = -Wextra -Wall -Werror -g

# ft library
FT = ./libft
FT_LIB = $(addprefix $(FT), libft.a)
FT_INC = -I ./libft
FT_LNK = ./libft/libft.a

# mlx library
# In school use it without the rest
#MLX_LNK = -lmlx -framework OpenGL -framework OpenCL -framework AppKit
MLX = ./minilibx/
MLX_LIB = $(addprefix $(MLX), mlx.a)
MLX_INC = -I ./minilibx
MLX_LNK = -L ./minilibx -l mlx -framework OpenGL -framework AppKit -framework OpenCL

# directories
SRCDIR = ./src/
INCDIR = -I ./includes/
OBJDIR = ./obj/

all: $(NAME)

$(NAME): obj $(FT_LIB) grn $(OBJ)
	@$(CC) $(OBJ) $(FT_LNK) $(MLX_LNK) -lm -o $(NAME)
	@echo "\x1b[0m"

red:
	@echo "\x1B[31m"

grn:
	@echo "\x1B[32m"

off:
	@echo "\x1b[0m"

obj:
	@mkdir -p $(OBJDIR)

$(FT_LIB):
	@make -C $(FT)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(FT_INC) $(MLX_INC) $(INCDIR) -o $@ -c $<

clean: red
	/bin/rm -rf $(OBJDIR)
	@make -C $(FT) clean
	@make -C $(MLX) clean

fclean: clean
	/bin/rm -rf $(NAME)
	make -C $(FT) fclean

re: fclean all
