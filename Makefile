CC= g++
FLAGS=-Wall -Wextra -Wno-deprecated-declarations -std=c++11 -I./includes/ -I./includes/GLFW
NAME=mod1 

SRC= main.cpp \
	 WindowManager.cpp \
	 GenerateMatrix.cpp \
	 MeshManager.cpp

OBJ= $(SRC:.cpp=.o)

LIB=  -L./libs/ -lglad -lglfw3
INC= -I/opt/X11/include
FRWK=   -framework AGL \
		-framework Cocoa \
		-framework OpenGL \
		-framework IOKit \
		-framework CoreFoundation \
		-framework CoreVideo

.PHONY: clean fclean re
.SILENT:

all:$(NAME) 

$(NAME): $(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LIB) $(FRWK) $(INC) $(FLAGS)
		echo "\t\xF0\x9F\x8F\x81   Compiling \033[35m$(NAME) \033[0mDONE!"

%.o: %.cpp
		echo "\t\xF0\x9F\x94\xA7   Building \033[34m $@ \033[0m" 
		$(CC) -c $(FLAGS) $(INC) -o $@ $<

clean:
		echo "\t\xF0\x9F\x92\xA3   Cleaning"
		rm -rf $(OBJ)

fclean: clean
		echo "\t\xF0\x9F\x9A\xBD   Full Clean"
		rm -rf $(NAME)

re: fclean all
