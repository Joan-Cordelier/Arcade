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

DIR_ARCADE	=	Core
# Find all .cpp files in Core and its subdirectories
SRCS_ARCADE	=	$(shell find $(DIR_ARCADE) -name "*.cpp")
OBJS_ARCADE	=	$(SRCS_ARCADE:%.cpp=$(OBJ_DIR)/%.o)

SUBDIRS_DISPLAY = Display/ncurses
SUBDIRS_GAMES = Games/

SUBDIRS_LIB	=	$(SUBDIRS_DISPLAY) $(SUBDIRS_GAMES)

LIBS_DISPLAY = $(patsubst %, $(LIB_DIR)/arcade_%.so, $(notdir $(SUBDIRS_DISPLAY)))
LIBS_GAMES = $(patsubst %, $(LIB_DIR)/arcade_%.so, $(notdir $(SUBDIRS_GAMES)))
LIBS = $(LIBS_DISPLAY) $(LIBS_GAMES)


all: $(LIB_DIR) core games graphicals

$(LIB_DIR):
	mkdir -p $@

$(LIB_DIR)/arcade_%.so:
	@echo "Compiling $@"
	@filtered_src=$(wildcard $(filter %/$*, $(SUBDIRS_LIB))/*.cpp); \
	if [ "$*" = "ncurses" ]; then \
		g++ $(LIBFLAGS) -Iinclude -o $@ $$filtered_src -lncurses; \
	else \
		g++ $(LIBFLAGS) -Iinclude -o $@ $$filtered_src; \
	fi

# Core rule - builds only the core program
core: $(NAME_ARCADE)

# Games rule - builds only the game libraries
games: $(LIB_DIR) $(LIBS_GAMES)

# Graphicals rule - builds only the graphical libraries
graphicals: $(LIB_DIR) $(LIBS_DISPLAY)

#ARCADE
$(NAME_ARCADE):	$(OBJS_ARCADE)
	g++ $(CXXFLAGS) -o $@ $^

# Updated object file rule to handle subdirectories in Core
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	g++ $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR) $(LIB_DIR)

fclean: clean
	@rm -f $(OBJS_ARCADE) $(NAME_ARCADE)

re: fclean all

.PHONY: all clean fclean re core games graphicals
