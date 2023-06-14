NAME = philo

SOURCES =  	memory_manager.c\
			memory_manager_utils.c\
			memory_manager_2.c\
			main.c\
			utils.c\
			time.c\
			philo_routine.c\
			checker_routine.c

OBJECTS = $(SOURCES:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = gcc $(FLAGS)

all: $(NAME)

$(NAME): $(SOURCES) $(OBJECTS) 
	@$(CC) $(OBJECTS) -o $(NAME)

clean:
	rm -f $(OBJECTS) $(OBJECTS_BONUS)
fclean: clean
	rm -f $(NAME)
re: fclean $(NAME)
