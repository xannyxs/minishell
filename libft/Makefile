# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jobvan-d <jobvan-d@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/14 12:53:47 by jobvan-d      #+#    #+#                  #
#    Updated: 2022/03/30 16:46:16 by jobvan-d      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := libft
OBJ_DIR = obj
CFLAGS := -Wall -Wextra -Werror
#DEPS = $(wildcard ft_*.c)
DEPS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
	ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
	ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
	ft_substr.c ft_ctolower.c ft_ctoupper.c ft_str_contains_char.c \
	ft_itoa_hex.c ft_strtoupper.c ft_strtolower.c ft_cisupper.c \
	ft_cislower.c ft_uitoa.c ft_free_str_arr.c ft_strcmp.c \
	ft_strndup_unsafe.c ft_isspace.c

OBJ = $(DEPS:%.c=$(OBJ_DIR)/%.o)
HEADERS = $(NAME).h

# rule:
# target: prerequisites
#	recipe

# $@ = target
# $^ = all prerequisites
# $< first prerequisite

all: $(NAME)

$(NAME): $(NAME).a

$(NAME).a: $(OBJ)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJ_DIR):
	mkdir $@

clean:
	rm -f $(OBJ_DIR)/*.o

fclean: clean
	rm -f $(NAME).a

re: fclean all
force: re

.PHONY: clean fclean all re force $(NAME)
