NAME = philo
FLAGS = -Wall -Wextra -Werror -pthread
PATH_OBJ = ./objects/

SRC = actions.c main.c utils.c validation.c init.c is_over.c locks_forks_meals.c

OBJ = ${SRC:%.c=$(PATH_OBJ)%.o}

all:		$(NAME)

$(NAME):	$(OBJ)
	cc $(FLAGS) $(OBJ) -o $(NAME)

$(PATH_OBJ)%.o: %.c
	@mkdir -p $(PATH_OBJ)
	cc $(FLAGS) -c $< -o $@ 
	@echo "\033[1;92m[SUCCESS] $@ Objects creation done!\033[0m"

clean:
	@rm -rf $(PATH_OBJ)
	@echo "\33[1;93m[SUCCESS] Objects removal done!\33[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[1;93m[SUCCESS] Removal done!\33[0m"

re: fclean all

.PHONY: all clean fclean re