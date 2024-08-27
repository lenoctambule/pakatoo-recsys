CC		= c++
FLAGS	= -g -ffast-math -Wall -Werror -Wextra
INCS	= -I./includes
SRCS	= SparseHN.cpp \
			Tensor.cpp \
			utils.cpp \
			Pakatoo.cpp
OBJ		= $(SRCS:%.cpp=$(OBJ_DIR)/%.o)
OBJ_DIR	= ./obj
SRC_DIR = ./src/
LIBNAME = pakatoo-core.a
DEPS	= $(OBJ:%.o=%.d)

all: $(LIBNAME) benchmark

-include $(DEPS)
$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INCS) -MMD -c $< -o $@

$(LIBNAME): $(OBJ)
	ar rcs $(LIBNAME) $(OBJ)

ml-100k:
	wget https://files.grouplens.org/datasets/movielens/ml-100k.zip
	unzip ml-100k

benchmark: $(LIBNAME) ./ml-100k tests/benchmark.cpp
	$(CC) $(FLAGS) $(INCS) tests/benchmark.cpp $(LIBNAME) -o benchmark

clean :
	rm -rf ./obj 

fclean : clean
	rm -f $(LIBNAME)

re : fclean all

.PHONY :
	clean fclean re all
