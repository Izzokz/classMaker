NAME = class

SRC = CMCompose.cpp classMaker.cpp
OBJ = $(SRC:.cpp=.o)
DEP = $(SRC:.cpp=.d)

CCA = c++ -std=c++98 -Werror -Wall -Wextra -MP -MMD -g3

all: $(NAME)

$(NAME): $(OBJ)
	@$(CCA) $(OBJ) -o $(NAME)
	@printf "Build Complete !\n"

%.o: %.cpp
	@$(CCA) -o $@ -c $<

clean:
	@rm -f $(OBJ) $(DEP)
	@printf "Objects Cleaned !\n"

fclean:
	@rm -f $(OBJ) $(NAME) $(DEP)
	@printf "Cleaned !\n"

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)
