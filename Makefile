# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rzarhoun <rzarhoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/06 13:45:21 by root              #+#    #+#              #
#    Updated: 2024/12/18 19:19:30 by rzarhoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = src/main.c src/utils/check_args.c src/utils/error.c src/utils/utils.c \
		src/init_struct.c src/parse_data.c src/check_data.c src/game/init_game.c

HEAD = -I includes -I Libft

OBJS = ${SRCS:.c=.o}

NAME = cub3D

CFLAGS = -Wall -Wextra -Werror -g3 $(HEAD) #-fsanitize=address

Includes = includes/cub3d.h \ Libft/libft.h \ minilibx-linux/mlx.h 

all : ${NAME}

${NAME} : ${OBJS} 
	make -C Libft
	cc ${OBJS} ${CFLAGS} -Lminilibx-linux -lmlx -L/usr/lib/X11 -lXext -lX11 -LLibft -lft -o ${NAME}

clean :
	make clean -C Libft
	rm -f ${OBJS}
fclean : clean
	make fclean -C Libft
	rm -f ${NAME}
re : fclean all

.SECONDARY: $(OBJS)
.PHONY: all clean fclean re