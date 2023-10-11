# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccosta-c <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/04 12:04:13 by ccosta-c          #+#    #+#              #
#    Updated: 2023/07/04 12:04:16 by ccosta-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ COLORS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
RESET	= \033[0m
BLACK 	= \033[1;30m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
PURPLE 	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ COMMANDS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
CC = cc
RM = rm -f
AR = ar -rcs

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ FLAGS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address
MKFLAGS		= --no-print-directory
LIBFTFLAGS	= -L ./libft -lft

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ FOLDERS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
DEPS		= includes
SRCS		= .
SRCS_BONUS	= bonus
LIBFT		= libft

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ FILES _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
SRC				= 	prompt.c \
					lexer.c \
					lst_ops.c \
					lst_ops2.c \
					utils.c \
					debugging.c \
					signals.c \
					frees.c \
					first_checks.c \
					lexer2.c \
					execution.c \
					export.c \
					check_builtins.c \
					execution2.c \
					echo.c \
					echo2.c \
					utils2.c \
					unset.c \
					cd.c \
					utils3.c \
					utils4.c \
					exit.c \
					redirects.c \
					redirects_out2.c \
					redirects_utils.c \
					redirects_utils2.c \
					redirects_out.c \
					redirects_utils3.c \
					utils5.c \
					redirects_in2.c \
					redirects_in.c
OBJS 			:= $(SRC:.c=.o)
NAME			= minishell
TARGET			= $(addprefix $(SRCS)/, $(OBJS))
TARGET_BONUS	= $(addprefix $(SRCS_BONUS)/, $(OBJS_BONUS))


#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ RULES _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
all: $(NAME)

$(NAME): $(TARGET)

	echo "[$(CYAN)Compiling$(RESET)] $(CFLAGS) $(GREEN)libft/*$(RESET)"
	make $(MKFLAGS) -sC $(LIBFT)

	$(CC) $(CFLAGS) -lreadline main.c $(TARGET) $(LIBFTFLAGS) -o $(NAME)

	echo "$(GREEN)  _____                   _ ";
	echo " |  __ \                 | |";
	echo " | |  | | ___  _ __   ___| |";
	echo " | |  | |/ _ \| '_ \ / _ \ |";
	echo " | |__| | (_) | | | |  __/_|";
	echo " |_____/ \___/|_| |_|\___(_)";

%.o : %.c
	echo "[$(CYAN)Compiling$(RESET)] $(CFLAGS) $(GREEN)$<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:

	echo "$(RED)  __  __ _       _     _          _ _ ";
	echo " |  \/  (_)     (_)   | |        | | |";
	echo " | \  / |_ _ __  _ ___| |__   ___| | |";
	echo " | |\/| | | '_ \| / __| '_ \ / _ \ | |";
	echo " | |  | | | | | | \__ \ | | |  __/ | |";
	echo " |_|  |_|_|_| |_|_|___/_| |_|\___|_|_|$(RESET)";

	make clean $(MKFLAGS) -sC $(LIBFT)
	echo "[$(RED) Deleted $(RESET)] $(GREEN)libft/*.o$(RESET)"
	echo "[$(RED) Deleted $(RESET)] $(GREEN)*/*.o$(RESET)"
	$(RM) $(TARGET) $(TARGET_BONUS)

fclean: clean
	make fclean $(MKFLAGS) -sC $(LIBFT)
	echo "[$(RED) Deleted $(RESET)] $(GREEN)$(NAME)$(RESET)"
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re: fclean all


.SILENT:
