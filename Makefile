.PHONY: all clean fclean re

#==========EXECUTABLES==========#

EXE= rbt

#=======COMPILER AND FLAGS======#

CC= gcc
FLAGS= -Wall -Wextra -Werror

#============HEADERS============#

HEADER= inc

#============COLORS=============#

RED=\033[1;31m
GREEN=\033[1;32m
EOC=\033[0m

#=============LEM_IN============#

SRCIN = $(addprefix ./src/, $(SRC))
SRC = main.c rbt.c

OBJS= ${SRCIN:.c=.o}

#=============RULES=============#

all: $(EXE)

%.o: %.c Makefile $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@ -I $(HEADER)
	@printf "$(GREEN)+$(EOC)"

$(EXE): $(LIBRARY) $(OBJS)
	@echo "\t$(EXE)'s objects compiled"
	@$(CC) $(FLAGS) $^ -o $(EXE)
	@echo "executable $(GREEN)$(EXE)$(EOC) created"
	@echo "$(GREEN)---------->>>$(EOC)"

clean:
	@rm -f $(OBJS)
	@echo "$(RED)[x]$(EOC) $(EXE)'s objects cleaned"

fclean:
	@rm -f $(OBJS)
	@echo "$(RED)[x]$(EOC) $(EXE)'s objects cleaned"
	@rm -f $(EXE)
	@echo "executable $(RED)$(EXE)$(EOC) removed"
	@echo "$(RED)<<<----------$(EOC)"

re: fclean all
