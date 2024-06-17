# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apintus <apintus@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 12:43:39 by apintus           #+#    #+#              #
#    Updated: 2024/06/14 17:12:27 by apintus          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#########################################################
## ARGUMENTS

NAME = philo
HEADER = philo.h
CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m


##########################################################
## SOURCES

SRCS = main.c\
		exit.c\
		parsing.c\
		init.c\
		utils.c\
		dinner.c\
		monitor.c\

OBJS = $(SRCS:.c=.o)

##########################################################
## RULES

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "$(GREEN)Linking libraries and building $@...$(RESET)"
	@$(CC) $(OBJS) -lreadline -o $(NAME)
	@echo "$(GREEN)Success \n$(RESET)"

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@echo "$(RED)Cleaning object files...🧹$(RESET)"
	@$(RM) $(OBJS) $(ARCHIVE)

fclean : clean
	@echo "$(RED)Cleaning all files...🧹$(RESET)"
	@$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
