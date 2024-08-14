CC		= c++
FLAGS	= -g
INCS	= -I./includes
SRCS	= SparseHN.cpp Tensor.cpp utils.cpp test.cpp
OBJ		= $(SRCS:%.cpp=$(OBJ_DIR)/%.o)
OBJ_DIR	= ./obj
NAME	= slm_test
DEPS	= $(OBJ:%.o=%.d)

all: $(NAME)

-include $(DEPS)
$(OBJ_DIR)/%.o : %.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) $(INCS) -o obj/$(<:.cpp=.o) -c $<


$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean :
	rm -rf ./obj 

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY :
	clean fclean re all