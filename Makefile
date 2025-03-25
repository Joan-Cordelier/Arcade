##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

OBJ_DIR	=	obj
LIB_DIR	=	lib

#ARCADE
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -Iinclude

NAME_ARCADE	=	arcade
#LIB
LIBFLAGS = -Wall -Wextra -fPIC -shared -std=c++17

DIR_ARCADE	=	src

SRCS_ARCADE	=	$(wildcard $(DIR_ARCADE)/*.cpp)
OBJS_ARCADE	=	$(SRCS_ARCADE:$(DIR_ARCADE)/%.cpp=$(OBJ_DIR)/%.o)

LIBS = $(patsubst %, $(LIB_DIR)/arcade_%.so, $(notdir $(SUBDIRS_LIB)))

SUBDIRS_LIB	=	Display/ncurses	\
				Display/sdl2	\
				Games/menu


all: $(LIB_DIR) $(NAME_ARCADE) $(LIBS)

$(LIB_DIR):
	mkdir -p $@

$(LIB_DIR)/arcade_%.so:
	@echo "Compiling $@"
	@filtered_src=$(wildcard $(filter %/$*, $(SUBDIRS_LIB))/*.cpp); \
	g++ $(LIBFLAGS) -Iinclude -o $@ $$filtered_src

#ARCADE
$(NAME_ARCADE):	$(OBJS_ARCADE)
	g++ $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(DIR_ARCADE)/%.cpp
	@mkdir -p $(dir $@)
	g++ $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR) $(LIB_DIR)

fclean: clean
	@rm -f $(OBJS_ARCADE) $(NAME_ARCADE)

re: fclean all

.PHONY: all clean fclean re
