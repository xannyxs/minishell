# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jobvan-d <jobvan-d@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/14 12:53:47 by jobvan-d      #+#    #+#                  #
#    Updated: 2022/02/03 15:57:54 by jobvan-d      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := libft
OBJ_DIR = obj
CFLAGS := -Wall -Wextra -Werror
#MANDATORY_DEPS = $(wildcard ft_*.c)
MANDATORY_DEPS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
	ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
	ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
	ft_substr.c ft_ctolower.c ft_ctoupper.c ft_str_contains_char.c \
	ft_itoa_hex.c ft_strtoupper.c ft_strtolower.c ft_cisupper.c \
	ft_cislower.c ft_uitoa.c ft_free_str_arr.c ft_strcmp.c \
	ft_strndup_unsafe.c ft_isspace.c

MANDATORY_OBJ = $(MANDATORY_DEPS:%.c=$(OBJ_DIR)/%.o)
HEADERS = $(NAME).h
BONUS_DEPS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c \
	ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c \
	ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c
BONUS_OBJ = $(BONUS_DEPS:%.c=$(OBJ_DIR)/%.o)

# rule:
# target: prerequisites
#	recipe

# $@ = target
# $^ = all prerequisites
# $< first prerequisite

ifdef	MAKE_BONUS
	OBJ = $(MANDATORY_OBJ) $(BONUS_OBJ)
else
	OBJ = $(MANDATORY_OBJ)
endif

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

# I would really like to know how to do this without recursive make
# this would be a topic for the future.
bonus:
	@$(MAKE) MAKE_BONUS=1

.PHONY: clean fclean all re force $(NAME) bonus
