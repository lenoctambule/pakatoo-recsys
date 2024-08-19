CC		= c++
FLAGS	= 
INCS	= -I./includes
SRCS	= SparseHN.cpp \
			Tensor.cpp \
			Interface.cpp \
			utils.cpp 
OBJ		= $(SRCS:%.cpp=$(OBJ_DIR)/%.o)
OBJ_DIR	= ./obj
SRC_DIR = ./src/
NAME	= ml-100k_test
LIBNAME = sparse-hopnet-cpp.a
DEPS	= $(OBJ:%.o=%.d)

all: $(NAME)

-include $(DEPS)
$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INCS) -MMD -c $< -o $@

$(LIBNAME): $(OBJ)
	ar rcs $(LIBNAME) $(OBJ)

$(NAME): $(LIBNAME)
	$(CC) $(FLAGS) $(INCS) main.cpp $(LIBNAME) -o $(NAME)

clean :
	rm -rf ./obj 

fclean : clean
	rm -f $(NAME) $(LIBNAME)

re : fclean all

.PHONY :
	clean fclean re all