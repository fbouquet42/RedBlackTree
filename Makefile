.PHONY: all clean fclean re

#==========EXECUTABLES==========#

EXE= rbt

#=======COMPILER AND FLAGS======#

CC= gcc
FLAGS= -Wall -Wextra -Werror

#============COLORS=============#

RED=\033[1;31m
GREEN=\033[1;32m
EOC=\033[0m

#=============SOURCES============#

#SRCIN = $(addprefix $(S_PATH), $(SRCS))

S_PATH= src/
SRCS = main.c

SRC_PATH_MAPS	= $(S_PATH)maps/

SRC_MAPS	= stdmap.c uint_map.c

SRC_PATH_RBT	= $(S_PATH)rbt/

SRC_RBT		= leaf_promote.c tree_get_depth.c tree_replace.c tree_add.c \
		  tree_get_leaf.c tree_resolve_double_red.c tree_delete.c \
		  tree_is_valid.c tree_emplace.c tree_remove.c

#============HEADERS============#

H_PATH= inc/

#============OBJECTS============#

O_PATH= .obj/
OBJIN = $(addprefix $(O_PATH), $(OBJS)) \
	$(addprefix $(O_PATH), $(OBJ_RBT)) \
	$(addprefix $(O_PATH), $(OBJ_MAPS))

OBJS= $(SRCS:.c=.o)
OBJ_RBT= $(SRC_RBT:.c=.o)
OBJ_MAPS= $(SRC_MAPS:.c=.o)

#=============RULES=============#

all: $(EXE)

$(O_PATH)%.o: $(S_PATH)%.c Makefile $(H_PATH)
	@mkdir -p $(O_PATH)
	@$(CC) $(FLAGS) -c $< -o $@ -I $(H_PATH)
	@printf "$(GREEN)+$(EOC)"

$(O_PATH)%.o: $(SRC_PATH_RBT)%.c Makefile $(H_PATH)
	@mkdir -p $(O_PATH)
	@$(CC) $(FLAGS) -c $< -o $@ -I $(H_PATH)
	@printf "$(GREEN)+$(EOC)"

$(O_PATH)%.o: $(SRC_PATH_MAPS)%.c Makefile $(H_PATH)
	@mkdir -p $(O_PATH)
	@$(CC) $(FLAGS) -c $< -o $@ -I $(H_PATH)
	@printf "$(GREEN)+$(EOC)"

$(EXE): $(LIBRARY) $(OBJIN)
	@echo "\t$(EXE)'s objects compiled"
	@$(CC) $(FLAGS) $^ -o $(EXE)
	@echo "executable $(GREEN)$(EXE)$(EOC) created"
	@echo "$(GREEN)---------->>>$(EOC)"

clean:
	@rm -f $(OBJIN)
	@rmdir $(O_PATH) 2> /dev/null || true
	@echo "$(RED)[x]$(EOC) $(EXE)'s objects cleaned"

fclean: clean
	@rm -f $(EXE)
	@echo "executable $(RED)$(EXE)$(EOC) removed"
	@echo "$(RED)<<<----------$(EOC)"

re: fclean all
