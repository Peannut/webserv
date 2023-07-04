# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/04 17:29:18 by zoukaddo          #+#    #+#              #
#    Updated: 2023/07/04 18:03:27 by zoukaddo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CPPFLAGS = #-Wall -Wextra -Werror -std=c++98 -I ./inc #-fsanitize=address -g

SRCS = ./parsing/src/main.cpp ./parsing/src/config_pars.cpp \
		./parsing/src/utils.cpp ./parsing/src/web.cpp

NAME = webserv

all: $(NAME)

$(NAME): $(SRCS)
	c++ $(CPPFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re