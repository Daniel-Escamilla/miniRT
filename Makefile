NAME = minirt

CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror -Iinclude -lmlx -lX11 -lXext -lXrender# -Wpedantic -Wshadow -Wformat -Wnull-dereference -Wconversion -Wstrict-overflow -Wsign-conversion -Wimplicit-fallthrough=5 -Wdouble-promotion -Wvla -Wformat-security -Wcast-align=strict -Wredundant-decls -Wlogical-op -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Winit-self -Wuninitialized -Wbad-function-cast -Wmissing-field-initializers

TIDY_FLAGS = --checks="*,-clang-analyzer-alpha.*,-google-readability-braces-around-statements,-hicpp-braces-around-statements,-readability-braces-around-statements,-modernize-*,-cppcoreguidelines-*,-clang-analyzer-cplusplus.*"

# analyze:
# 	@if [ -z "$(FILE)" ]; then \
# 		echo "Por favor, especifica el archivo que quieres analizar con FILE=archivo.c"; \
# 	else \
# 		clang-tidy $(FILE) $(TIDY_FLAGS) -- -Iinclude -Wall -Wextra -Werror; \
# 	fi

SRC_DIR = src
OBJDIR = $(NAME)_objects

INCLUDE_SRC =	file.h \
				main.h \
				utils.h \
				struct.h \
				colors.h \
				include.h \
				math_struct.h \
				objects_struct.h \

INCLUDES = $(addprefix include/, $(INCLUDE_SRC))

MAIN_SRC =      src/main/ft_main.c \
				src/main/ft_window.c \
				src/main/ft_initialize.c \

FILE_SRC =		src/file/ft_open_file.c \
				src/file/ft_file_exist.c \
				src/file/ft_create_file.c \

UTILS_SRC =		src/utils/ft_atof.c \
				src/utils/ft_atoi_mod.c \
				src/utils/ft_free_struct.c \
				src/utils/ft_print_struct.c \
				src/utils/ft_strstr_utils.c \

GNL_SRC =		get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \

SRCS = 	$(GNL_SRC) \
		$(MAIN_SRC) \
		$(FILE_SRC) \
		$(UTILS_SRC) \

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm

all: $(OBJDIR) libft mlx $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(MLX_FLAGS)

$(OBJDIR)/%.o: %.c $(INCLUDES) | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

libft:
	@make -C $(LIBFT_DIR) --no-print-directory

mlx:
	@make -C $(MLX_DIR) --no-print-directory

clean:
	@rm -rf $(OBJDIR)
	@make -C $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re libft mlx
