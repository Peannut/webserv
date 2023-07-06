# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zwina <zwina@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/23 17:44:55 by zwina             #+#    #+#              #
#    Updated: 2023/07/05 19:27:46 by zwina            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# styles
ANSI_RESET          := \\033[0m
ANSI_BOLD           := \\033[1m
ANSI_BOLD_RESET     := \\033[22m
ANSI_ULINE          := \\033[4m
ANSI_ULINE_RESET    := \\033[24m
ANSI_ITALIC         := \\033[3m
ANSI_ITALIC_RESET   := \\033[23m
ANSI_GREEN          := \\033[32m
ANSI_YELLOW			:= \\033[33m

# compilation
DEBUG   := -fsanitize=address -g
CCWI    := g++ -Wall -Wextra -Werror -Iincludes -std=c++98
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
	@printf "$(ANSI_GREEN)$(ANSI_BOLD)\n"
	@printf "██╗    ██╗███████╗██████╗ ███████╗███████╗██████╗ ██╗   ██╗\n"
	@printf "██║    ██║██╔════╝██╔══██╗██╔════╝██╔════╝██╔══██╗██║   ██║\n"
	@printf "██║ █╗ ██║█████╗  ██████╔╝███████╗█████╗  ██████╔╝██║   ██║\n"
	@printf "██║███╗██║██╔══╝  ██╔══██╗╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝\n"
	@printf "╚███╔███╔╝███████╗██████╔╝███████║███████╗██║  ██║ ╚████╔╝ \n"
	@printf " ╚══╝╚══╝ ╚══════╝╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝   is Ready\n"
	@printf "$(ANSI_RESET)\n"

$(OBJSDIR) :
	@mkdir $(OBJSDIR)
	@mkdir $(OBJSDIR)/$(CLASSESDIR)
	@mkdir $(OBJSDIR)/$(CLASSESDIR)/$(CONFIGDIR)
	@mkdir $(OBJSDIR)/$(CLASSESDIR)/$(CONNECTIONDIR)

$(OBJS) : $(OBJSDIR)/%.o : $(SRCSDIR)/%.cpp
	@printf "$(ANSI_YELLOW)$(ANSI_BOLD)\n"
	@printf "Compiling $(notdir $<) ... "
	@printf "$(ANSI_RESET)"
	@$(CCWI) -c $< -o $@
	@printf "$(ANSI_GREEN)$(ANSI_BOLD)"
	@printf "[DONE]"
	@printf "$(ANSI_RESET)"

clean :
	@rm -rf $(OBJSDIR)
	@printf "$(ANSI_GREEN)$(ANSI_BOLD)\n"
	@printf "|-------------------|\n"
	@printf "  Cleaning OBJS ...\n"
	@printf "       [DONE].\n"
	@printf "|-------------------|\n"
	@printf "$(ANSI_RESET)\n"

fclean : clean
	@rm -rf $(NAME)
	@printf "$(ANSI_GREEN)$(ANSI_BOLD)\n"
	@printf "|----------------------|\n"
	@printf "   REMOVE WEBSERV ...\n"
	@printf "         [DONE].\n"
	@printf "|----------------------|\n"
	@printf "$(ANSI_RESET)\n"

re : fclean all

.PHONY : clean
