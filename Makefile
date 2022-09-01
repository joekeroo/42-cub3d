NAME		= cub3d

SRC_DIR		= src/cub3d
OBJ_DIR		= obj
LIBFT_DIR	= src/libft
INC_DIR		= inc
MLX_DIR		= mlx

SRC_FILES	= main.c cub3d.c cub3d_utils.c cub3d_init.c cub3d_screen_utils.c \
			  parser.c parsing_utils.c map_error_check.c map_error_utils.c \
			  filename_error_check.c texture_error_check.c texture_error_utils.c \
			  color_error_check.c color_error_utils.c \
			  ray_casting.c ray_casting_utils.c controls.c \
			  get_next_line.c draw.c

OBJ_FILES	= ${addprefix ${OBJ_DIR}/, ${SRC_FILES:.c=.o}}

GCC			= gcc
CFLAGS		= -Wall -Wextra -Werror
SANITIZE	= -fsanitize=address -g3
RM			= rm -f

MFLAGS		= -framework OpenGL -framework AppKit

INCLUDES	= -I ${INC_DIR} -I ${MLX_DIR}

LIBFT_FILE	= ${LIBFT_DIR}/libft.a
LIBFT		= -L${LIBFT_DIR} -lft
LIB_MLX		= -L${MLX_DIR} -lmlx
LIBRARIES	= ${LIBFT} ${LIB_MLX}

all:	${NAME}

${OBJ_DIR}/%.o:	${SRC_DIR}/%.c
	${GCC} ${CFLAGS} ${INCLUDES} -c $< -o $@

${LIBFT_FILE}:
	make -C ${LIBFT_DIR}

${NAME}:	${LIBFT_FILE} ${OBJ_FILES}
	${GCC} ${CFLAGS} ${MFLAGS} -o ${NAME} ${OBJ_FILES} ${LIBRARIES}

sanitize:	${LIBFT_FILE} ${OBJ_FILES}
	${GCC} ${CFLAGS} ${MFLAGS} -o ${NAME} ${OBJ_FILES} ${LIBRARIES} ${SANITIZE}

test:	cubclean all
	./cub3d test_maps/test.cub

clean:
	${RM} ${OBJ_DIR}/*
	make clean -C ${LIBFT_DIR}

fclean:
	${RM} ${NAME}
	${RM} ${OBJ_DIR}/*
	make fclean -C ${LIBFT_DIR}

cubclean:
	${RM} ${NAME}
	${RM} ${OBJ_DIR}/*

re:	fclean all

.PHONY:	all clean fclean re