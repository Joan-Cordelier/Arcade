##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

# Directory structure
OBJ_DIR = obj
LIB_DIR = lib

# Core program
NAME_ARCADE = arcade
DIR_CORE = Core

# Compiler flags
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -Iinclude
LIBFLAGS = -Wall -Wextra -fPIC -shared -std=c++17 -Iinclude

# Core source files and objects
SRCS_CORE = $(shell find $(DIR_CORE) -name "*.cpp")
OBJS_CORE = $(SRCS_CORE:%.cpp=$(OBJ_DIR)/%.o)

# Display libraries
DISPLAY_LIBS = ncurses sfml sdl2 
DISPLAY_TARGETS = $(addprefix $(LIB_DIR)/arcade_, \
	$(addsuffix .so, $(DISPLAY_LIBS)))

# Game libraries
GAME_LIBS = menu snake
GAME_TARGETS = $(addprefix $(LIB_DIR)/arcade_, $(addsuffix .so, $(GAME_LIBS)))

# Define phony targets
.PHONY: all core games graphicals clean fclean re prepare

# Main rule - builds everything
all: core games graphicals

# Create necessary directories
prepare:
	@mkdir -p $(OBJ_DIR)/$(DIR_CORE)
	@mkdir -p $(LIB_DIR)
	@for lib in $(DISPLAY_LIBS); do \
		mkdir -p $(OBJ_DIR)/Display/$$lib; \
	done
	@for game in $(GAME_LIBS); do \
		mkdir -p $(OBJ_DIR)/Games/$$game; \
	done

# Core program compilation
core: prepare $(NAME_ARCADE)

$(NAME_ARCADE): $(OBJS_CORE)
	@echo "Building core arcade program: $@"
	@g++ $(CXXFLAGS) -o $@ $^ -ldl

# Games libraries compilation
games: prepare $(GAME_TARGETS)

# Display libraries compilation
graphicals: prepare $(DISPLAY_TARGETS)

# Rules for building libraries
$(LIB_DIR)/arcade_ncurses.so:
	@echo "Building Dncurses library: $@"
	@g++ $(LIBFLAGS) -o $@ $(shell find Display/ncurses \
		-name "*.cpp" 2>/dev/null) -lncurses

$(LIB_DIR)/arcade_sfml.so:
	@echo "Building SFML library: $@"
	@g++ $(LIBFLAGS) -o $@ $(shell find Display/sfml \
		-name "*.cpp" 2>/dev/null) -lsfml-graphics \
		-lsfml-window -lsfml-system

$(LIB_DIR)/arcade_sdl2.so:
	@echo "Building SDL2 library: $@"
	@g++ $(LIBFLAGS) -o $@ $(shell find Display/sdl2 \
		-name "*.cpp" 2>/dev/null) -lSDL2 -lSDL2_ttf

$(LIB_DIR)/arcade_menu.so:
	@echo "Building menu library: $@"
	@g++ $(LIBFLAGS) -o $@ $(shell find Games/menu \
		-name "*.cpp" 2>/dev/null) -ldl

$(LIB_DIR)/arcade_snake.so:
	@echo "Building Snake library: $@"
	@g++ $(LIBFLAGS) -o $@ $(shell find Games/Snake \
		-name "*.cpp" 2>/dev/null) -ldl

# Object files compilation
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling: $<"
	@g++ $(CXXFLAGS) -c $< -o $@

# Clean rules
clean:
	@echo "Cleaning object files and libraries"
	@rm -rf $(OBJ_DIR) $(LIB_DIR)

fclean: clean
	@echo "Cleaning executable"
	@rm -f $(NAME_ARCADE)

re: fclean all
