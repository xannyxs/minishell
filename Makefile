# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/01 14:31:21 by xvoorvaa      #+#    #+#                  #
#    Updated: 2022/03/02 23:04:20 by xvoorvaa      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
OBJ_DIR			=	OBJ
SRC_DIR			=	SRC
INC_DIR			=	INC
LIBFT_DIR		=	libft
LIBFT_H			=	$(LIBFT_DIR)/libft.h
LIBFT_A			=	$(LIBFT_DIR)/libft.a

# using temporary wildcards for now
SOURCES		:= $(shell find $(SRC_DIR) -type f -name "*.c")
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
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR) -I$(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir $@

$(NAME): $(OBJECTS) $(LIBFT_A)
	@clear
	@echo $(START)
	@printf $(COMP_MESSAGE) $(SOURCES)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -L$(LIBFT_DIR) -lreadline -lft -I$(INC_DIR)
	@echo $(MESSAGE)

$(LIBFT_A): $(LIBFT_H)
	$(MAKE) -C $(LIBFT_DIR)

clean:
	@echo "\n"
	@echo $(OBJECTS)
	@rm -f $(OBJECTS)
	@printf $(REM_MESSAGE)
	@echo "\n"


fclean:		clean
	@rm -f $(NAME)
	@rm -rf $(NAME).dSYM
	$(MAKE) -C $(LIBFT_DIR) $@

re:			fclean all

.PHONY:		all clean fclean re
