# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/01 14:31:21 by xvoorvaa      #+#    #+#                  #
#    Updated: 2022/03/29 16:04:20 by xvoorvaa      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
OBJ_DIR			=	OBJ
SRC_DIR			=	SRC
INC_DIR			=	INC
LIBFT_DIR		=	libft
PF_DIR			=	ft_printf
BREW_INC_DIR	=	~/.brew/opt/readline/include
BREW_LIB_DIR	=	~/.brew/opt/readline/lib
LIBFT_H			=	$(LIBFT_DIR)/libft.h
LIBFT_A			=	$(LIBFT_DIR)/libft.a

# ft_printf stuff
PF_H			=	$(PF_DIR)/ft_printf.h $(PF_DIR)/pf_util.h $(LIBFT_H)
PF_A			=	$(PF_DIR)/libftprintf.a
PF_PDEPS		=	pf_parsing.c pf_print_hex.c pf_print_int.c \
					pf_print_pointer.c pf_print_str_char.c pf_printing.c \
					pf_printing_util.c ft_printf.c
PF_DEPS			=	$(PF_PDEPS:%.c=$(PF_DIR)/%.c)
PF_OBJ			=	$(PF_DEPS:$(PF_DIR)/%.c=$(PF_DIR)/$(OBJ_DIR)/%.o)

# using temporary wildcards for now
SOURCES		:= $(shell find $(SRC_DIR) -type f -name "*.c")
HEADERS		:= $(LIBFT_H) $(wildcard INC/*.h)
OBJS		:= $(SOURCES:.c=.o)
OBJECTS		:= $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(OBJS))

ifdef LEAKS
	CFLAGS += -g3 -fsanitize=address
endif

GREEN			=	\033[1;32m
BLUE			=	\033[1;36m
RED				=	\033[0;31m
NC				=	\033[0m # No Color

START			= "$(BLUE)---\nStarting...!\n---$(NC)"
MESSAGE			= "$(BLUE)---\nCompiling done! Run ./$(NAME)\n---$(NC)"
COMP_MESSAGE	= "$(GREEN)Building C object... $(NC)%-33.33s\r\n"
REM_MESSAGE		= "$(RED)Removing files...$(NC)"

all:	$(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR) -I$(LIBFT_DIR) -I$(PF_DIR) \
		-I $(BREW_INC_DIR)

$(OBJ_DIR):
	@mkdir $@

$(NAME): $(OBJECTS) $(LIBFT_A) $(PF_A)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -L$(LIBFT_DIR) -L$(PF_DIR) \
		-L $(BREW_LIB_DIR) -lreadline -lftprintf -lft
	@clear
	@echo $(START)
	@printf $(COMP_MESSAGE) $(SOURCES)
	@echo $(MESSAGE)

$(LIBFT_A): $(LIBFT_H)
	$(MAKE) -C $(LIBFT_DIR)

# ft_printf stuff
$(PF_A): $(PF_OBJ)
	ar rcs $@ $^

$(PF_DIR)/$(OBJ_DIR)/%.o: $(PF_DIR)/%.c $(PF_H) | $(PF_DIR)/$(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(PF_DIR) -I$(LIBFT_DIR) -c -o $@ $<

$(PF_DIR)/$(OBJ_DIR):
	mkdir $@

clean:
	@echo "\n"
	@echo $(OBJECTS)
	@rm -rf $(OBJ_DIR)/*
	@printf $(REM_MESSAGE)
	@echo "\n"


fclean:		clean
	@rm -f $(NAME)
	@rm -rf $(NAME).dSYM
	@rm -f $(PF_DIR)/$(OBJ_DIR)/*.o
	@rm -f $(LIBFT_A)
	@rm -f $(PF_A)
	$(MAKE) -C $(LIBFT_DIR) $@

re:			fclean all

.PHONY:		all clean fclean re
