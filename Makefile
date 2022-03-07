# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/26 21:56:29 by fdidelot          #+#    #+#              #
#    Updated: 2022/03/07 15:19:53 by fdidelot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-----------------------------------------------#
################# PROG_NAME #####################
#-----------------------------------------------#
NAME = ircserv

#-----------------------------------------------#
################## COMPILO ######################
#-----------------------------------------------#
CXX = clang++

#-----------------------------------------------#
################### PATHS #######################
#-----------------------------------------------#
PATH_HEAD	=	./headers/
PATH_SRCS	=	./sources/						\
				./sources/commands/				\
				./sources/classes/
PATH_OBJS	=	./objects/

#-----------------------------------------------#
################## SOURCES ######################
#-----------------------------------------------#
SRCS =		main.cpp							\
			Server.cpp							\
			Command.cpp							\
			User.cpp							\
			Channel.cpp							\
			PassCmd.cpp							\
			NickCmd.cpp							\
			CapCmd.cpp							\
			ModeCmd.cpp							\
			JoinCmd.cpp							\
			PingCmd.cpp							\
			PrivmsgCmd.cpp						\
			UserCmd.cpp							\
			PartCmd.cpp							\
			QuitCmd.cpp							\
			OperCmd.cpp							\
			MotdCmd.cpp							\
			KillCmd.cpp							\
			WhoisCmd.cpp						\
			NoticeCmd.cpp						\
			TopicCmd.cpp						\
			NamesCmd.cpp						\
			ListCmd.cpp							\
			InviteCmd.cpp						\
			KickCmd.cpp

vpath %.cpp $(PATH_SRCS)

#-----------------------------------------------#
################## HEADERS ######################
#-----------------------------------------------#
HEADERS		=	Server.hpp						\
				Command.hpp						\
				User.hpp						\
				Channel.hpp						\
				err.hpp							\
				rpl.hpp

vpath %.hpp $(PATH_HEAD)

#-----------------------------------------------#
################## OBJECTS ######################
#-----------------------------------------------#
OBJS = $(addprefix $(PATH_OBJS), $(SRCS:.cpp=.o))


#-----------------------------------------------#
################### FLAGS #######################
#-----------------------------------------------#
CXXFLAGS =	-Wall -Wextra -Werror -std=c++98
ifeq ($(d), 0)
#	CXXFLAGS	+= -g3
#	CXXFLAGS	+= -Wpadded
	CXXFLAGS	+= -fsanitize=address,undefined
endif
ifeq ($(d), 1)
	CXXFLAGS	+= -g
endif

#-----------------------------------------------#
################# CPPFLAGS ######################
#-----------------------------------------------#
CPPFLAGS	+=	-I $(PATH_HEAD)					\
# Multiple header directories
#CPPFLAGS	+= $(foreach DIR, $(HDRS_DIRS), $(addprefix -I , $(DIR)))
#

#-----------------------------------------------#
################# LIBRARIES #####################
#-----------------------------------------------#
ifeq ($(d), 0)
	LDFLAGS		+= -fsanitize=address,undefined
endif

#-----------------------------------------------#
################### RULES #######################
#-----------------------------------------------#

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(PATH_OBJS)%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(CPPFLAGS)

$(OBJS): Makefile $(HEADERS) | $(PATH_OBJS)

$(PATH_OBJS):
	mkdir $@

clean:
	rm -rf $(PATH_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
