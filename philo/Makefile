NAME = philo

FLAGS = -Wall -Werror -Wextra -g

SRCS = ./srcs/check_death.c ./srcs/init_table.c ./srcs/main.c \
		./srcs/philo_utils.c ./srcs/simulation.c ./srcs/thread.c \
		./srcs/init_utils.c ./srcs/simulation_utils.c

OBJS = ${SRCS:.c=.o}

all: ${NAME}

.c.o:
	cc ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	cc ${FLAGS} -lpthread -o ${NAME} ${OBJS}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: re fclean clean all 
