# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/23 17:44:55 by zwina             #+#    #+#              #
#    Updated: 2023/06/24 02:51:25 by zwina            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# styles
ANSI_RESET          := \\033[0m
ANSI_BOLD           := \\033[2m
ANSI_BOLD_RESET     := \\033[22m
ANSI_ULINE          := \\033[4m
ANSI_ULINE_RESET    := \\033[24m
ANSI_ITALIC         := \\033[3m
ANSI_ITALIC_RESET   := \\033[23m
ANSI_RED            := \\033[38;5;125m
ANSI_LRED           := \\033[38;5;196m
ANSI_WHITE          := \\033[38;5;15m
ANSI_YELLOW         := \\033[38;5;3m
ANSI_GREEN          := \\033[38;5;2m
ANSI_ORANGE         := \\033[38;5;208m
ANSI_LORANGE        := \\033[38;5;215m
ANSI_GOLD           := \\033[38;5;214m
ANSI_BLUE           := \\033[38;5;4m
ANSI_PURPLE         := \\033[38;5;129m
ANSI_CYAN           := \\033[38;5;44m

# compilation
DEBUG   := -fsanitize=address -g
CCWI    := g++-13 -Wall -Wextra -Werror -Iincludes -std=c++98
# directories
OBJSDIR 		:= objs
SRCSDIR 		:= srcs
CLASSESDIR 		:= classes
CONFIGDIR 		:= Config
CONNECTIONDIR	:= Connection
# sources
CFILES  :=\
	$(CLASSESDIR)/$(CONFIGDIR)/Config.cpp \
	$(CLASSESDIR)/$(CONFIGDIR)/Location.cpp \
	$(CLASSESDIR)/$(CONFIGDIR)/Server.cpp \
	$(CLASSESDIR)/$(CONNECTIONDIR)/Connection.cpp \
	$(CLASSESDIR)/$(CONNECTIONDIR)/Request.cpp \
	$(CLASSESDIR)/$(CONNECTIONDIR)/Response.cpp \
	$(CLASSESDIR)/WebServ.cpp \
	main.cpp \
	our_functions.cpp
SRCS    := $(foreach F,$(CFILES),$(SRCSDIR)/$(F))
# objects
OBJS    := $(patsubst $(SRCSDIR)/%.cpp,$(OBJSDIR)/%.o,$(SRCS))
# program name
NAME    := webserv

all : $(NAME)

bonus : all

debug : CCWI += $(DEBUG)
debug : all

$(NAME) : $(OBJSDIR) $(OBJS)
	@$(CCWI) $(OBJS) -o $(NAME)
	@printf "$(ANSI_CYAN)"
	@printf "|----------------------|\n"
	@printf "  Creating WEBSERV ...\n"
	@printf "       [DONE].\n"
	@printf "|----------------------|\n"
	@printf "$(ANSI_RESET)"

$(OBJSDIR) :
	@mkdir $(OBJSDIR)
	@mkdir $(OBJSDIR)/$(CLASSESDIR)
	@mkdir $(OBJSDIR)/$(CLASSESDIR)/$(CONFIGDIR)
	@mkdir $(OBJSDIR)/$(CLASSESDIR)/$(CONNECTIONDIR)

$(OBJS) : $(OBJSDIR)/%.o : $(SRCSDIR)/%.cpp
	@$(CCWI) -c $< -o $@
# @printf "$(ANSI_CYAN)"
# @printf $@"\n"
# @printf "$(ANSI_RESET)"

clean :
	@rm -rf $(OBJSDIR)
	@printf "$(ANSI_CYAN)"
	@printf "|-------------------|\n"
	@printf "  Cleaning OBJS ...\n"
	@printf "       [DONE].\n"
	@printf "|-------------------|\n"
	@printf "$(ANSI_RESET)"

fclean : clean
	@rm -rf $(NAME)
	@printf "$(ANSI_CYAN)"
	@printf "|----------------------|\n"
	@printf "   REMOVE WEBSERV ...\n"
	@printf "         [DONE].\n"
	@printf "|----------------------|\n"
	@printf "$(ANSI_RESET)"

re : fclean all

.PHONY : clean
