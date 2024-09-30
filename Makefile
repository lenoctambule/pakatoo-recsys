CC		= c++
FLAGS	= -g -ffast-math -Wall -Werror -Wextra
INCS	= -I ./includes
SRC_DIR = ./lib
SRCS	+= $(addprefix $(SRC_DIR)/core/,\
						SparseHN.cpp \
						Tensor.cpp \
						utils.cpp \
			)
SRCS	+= $(addprefix $(SRC_DIR)/interface/, \
						Instance.cpp \
						Shell.cpp \
			)
SRCS	+= $(addprefix $(SRC_DIR)/ipc/, \
						Client.cpp \
						Request.cpp \
						SocketIPC.cpp \
			)
OBJ		= $(SRCS:%.cpp=$(OBJ_DIR)/%.o)
OBJ_DIR	= ./obj
LIBNAME = pakatoo-cpp.a
DEPS	= $(OBJ:%.o=%.d)

all: $(LIBNAME) server benchmark

-include $(DEPS)
$(OBJ): $(OBJ_DIR)/%.o : %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INCS) -MMD -c $< -o $@

$(LIBNAME): $(OBJ)
	ar rcs $(LIBNAME) $(OBJ)

ml-100k:
	wget https://files.grouplens.org/datasets/movielens/ml-100k.zip
	unzip ml-100k.zip
	rm -rf ml-100k.zip

ml-1m:
	wget https://files.grouplens.org/datasets/movielens/ml-1m.zip
	unzip ml-1m.zip
	rm -rf ml-1m.zip

server: $(LIBNAME) ./ml-100k ./ml-1m lib/server.cpp
	@mkdir -p ./bin
	$(CC) $(FLAGS) $(INCS) lib/server.cpp $(LIBNAME) -o ./bin/server

benchmark: $(LIBNAME) ./ml-100k ./ml-1m tests/benchmark.cpp
	@mkdir -p ./bin
	$(CC) $(FLAGS) $(INCS) tests/benchmark.cpp $(LIBNAME) -o ./bin/benchmark

clean :
	rm -rf ./obj 

fclean : clean
	rm -rf $(LIBNAME) ./bin

re : fclean all

.PHONY :
	clean fclean re all
