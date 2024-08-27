CC		= c++
FLAGS	= -g -ffast-math -Wall -Werror -Wextra
INCS	= -I./includes
SRCS	= SparseHN.cpp \
			Tensor.cpp \
			Interface.cpp \
			utils.cpp \
			Pakatoo.cpp
OBJ		= $(SRCS:%.cpp=$(OBJ_DIR)/%.o)
OBJ_DIR	= ./obj
SRC_DIR = ./src/
NAME	= pakatoo-shell
LIBNAME = sparse-hopnet-cpp.a
DEPS	= $(OBJ:%.o=%.d)

all: $(NAME) benchmark

-include $(DEPS)
$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INCS) -MMD -c $< -o $@

$(LIBNAME): $(OBJ)
	ar rcs $(LIBNAME) $(OBJ)

$(NAME): $(LIBNAME) main.cpp
	$(CC) $(FLAGS) $(INCS) main.cpp $(LIBNAME) -o $(NAME)

benchmark: $(LIBNAME) tests/benchmark.cpp
	$(CC) $(FLAGS) $(INCS) tests/benchmark.cpp $(LIBNAME) -o benchmark

clean :
	rm -rf ./obj 

fclean : clean
	rm -f $(NAME) $(LIBNAME) benchmark

re : fclean all

.PHONY :
	clean fclean re all
