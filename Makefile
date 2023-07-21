# styles
ANSI_RESET          := \\033[0m
ANSI_BOLD           := \\033[1m
ANSI_BOLD_RESET     := \\033[22m
ANSI_ULINE          := \\033[4m
ANSI_ULINE_RESET    := \\033[24m
ANSI_ITALIC         := \\033[3m
ANSI_ITALIC_RESET   := \\033[23m
ANSI_RED			:= \\033[31m
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
REQUESTDIR		:= Request
RESPONSEDIR		:= Response
# sources
CFILES  :=\
	$(CLASSESDIR)/$(CONFIGDIR)/Config.cpp \
	$(CLASSESDIR)/$(CONFIGDIR)/Location.cpp \
	$(CLASSESDIR)/$(CONFIGDIR)/Server.cpp \
	$(CLASSESDIR)/$(CONNECTIONDIR)/Connection.cpp \
	$(CLASSESDIR)/$(CONNECTIONDIR)/Request.cpp \
	$(CLASSESDIR)/$(CONNECTIONDIR)/Response.cpp \
	$(CLASSESDIR)/WebServ.cpp \
	$(CONFIGDIR)/utils.cpp \
	$(REQUESTDIR)/body.cpp \
	$(REQUESTDIR)/fields.cpp \
	$(REQUESTDIR)/request_line.cpp \
	$(REQUESTDIR)/utils.cpp \
	$(RESPONSEDIR)/responseBuilding.cpp \
	$(RESPONSEDIR)/utils.cpp \
	main.cpp \
	multiplexing.cpp
SRCS    := $(foreach F,$(CFILES),$(SRCSDIR)/$(F))
# objects
OBJS    := $(patsubst $(SRCSDIR)/%.cpp,$(OBJSDIR)/%.o,$(SRCS))
# program name
NAME    := webserv

all : $(NAME)

bonus : all

debug : CCWI += $(DEBUG)
debug : all
	@printf "$(ANSI_RED)$(ANSI_BOLD)"
	@printf "[Debuging Mode]\n\n"
	@printf "$(ANSI_RESET)"

$(NAME) : $(OBJSDIR) $(OBJS)
	@printf "$(ANSI_GREEN)$(ANSI_BOLD)\n\n"
	@printf "Linking WebServ ... "
	@printf "$(ANSI_RESET)\n"
	@$(CCWI) $(OBJS) -o $(NAME)
	@printf "$(ANSI_GREEN)$(ANSI_BOLD)"
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
	@mkdir $(OBJSDIR)/$(CONFIGDIR)
	@mkdir $(OBJSDIR)/$(REQUESTDIR)
	@mkdir $(OBJSDIR)/$(RESPONSEDIR)

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
