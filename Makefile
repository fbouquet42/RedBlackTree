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

S_PATH= src/
SRCIN = $(addprefix $(S_PATH), $(SRCS))
SRCS = main.c rbt.c

#============HEADERS============#

H_PATH= inc/

#============OBJECTS============#

O_PATH= .obj/
OBJIN = $(addprefix $(O_PATH), $(OBJS))
OBJS= $(SRCS:.c=.o)

#=============RULES=============#

all: $(EXE)

$(O_PATH)%.o: $(S_PATH)%.c Makefile $(H_PATH)
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
