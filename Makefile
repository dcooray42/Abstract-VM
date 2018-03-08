NAME = abstract_vm

SRC_PATH = ./srcs/

OBJ_PATH = ./objs/

SRC_NAME = main.cpp\
		FactoryMethod.cpp\
		ErrorException.cpp

OBJ_NAME = $(SRC_NAME:.cpp=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

INCLUDE = -I ./includes

FLAGS = -std=c++11 -Wall -Werror -Wextra

CC = clang++

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(INCLUDE) -o $(NAME) $^

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(FLAGS) $(INCLUDE) -o $@ -c $<

clean:
	/bin/rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
