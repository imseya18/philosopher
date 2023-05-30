NAME = philo

SOURCES =   main.c\
			utils.c


OBJECTS = $(SOURCES:.c=.o)

FLAGS = -Wall -Wextra -Werror -pthread -pthread -g -fsanitize=address

CC = gcc $(FLAGS)

all: $(NAME)

$(NAME): $(SOURCES) $(OBJECTS) 
	@$(CC) $(OBJECTS) -o $(NAME)

clean:
	rm -f $(OBJECTS) $(OBJECTS_BONUS)
fclean: clean
	rm -f $(NAME)
re: fclean $(NAME)
