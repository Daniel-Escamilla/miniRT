# Nombre del ejecutable
NAME = minirt

# Compilador y flags
CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror -lmlx -lX11 -lXext -lXrender

# Directorio de fuentes
SRC_DIR = src

MAIN_SRC =      src/main/ft_main.c \
				src/main/ft_window.c \
				src/main/ft_initialize.c \

FILE_SRC =		src/file/ft_file_exist.c \

HOOKS_SRC =		

RENDER_SRC =    

GNL_SRC =		get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \

# Archivos fuente
SRCS = 	$(GNL_SRC) \
		$(MAIN_SRC) \
		$(FILE_SRC) \
		$(HOOKS_SRC) \
		$(RENDER_SRC) \

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
# Directorio de archivos objeto
OBJDIR = $(NAME)_objects
# Directorio de la libft
LIBFT_DIR = ./libft
# Libreria a utilizar
LIBFT = $(LIBFT_DIR)/libft.a

# Directorio de MiniLibX
MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

# Flags para MiniLibX
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/include/../lib -lXext -lX11 -lm

# Reglas
all: $(OBJDIR) libft mlx $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(MLX_FLAGS)

# Aquí no se requiere usar notdir
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJDIR):
	@mkdir -p $(OBJDIR)/src/*

libft:
	@make -sC $(LIBFT_DIR) --no-print-directory

mlx:
	@make -sC $(MLX_DIR) --no-print-directory

clean:
	@rm -rf $(OBJDIR)
	@make -sC $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -sC $(LIBFT_DIR) fclean
	@make -sC $(MLX_DIR) clean

re: fclean all

run: Z_To-Do_Z/To-Do.py
	python3 Z_To-Do_Z/To-Do.py

.PHONY: all clean fclean re libft run mlx
