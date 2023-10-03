SRCS := srcs/main.cpp \
		srcs/init.cpp \
		srcs/input.cpp \
		srcs/parsing/parseObjFile.cpp \
		srcs/parsing/parseMtlFile.cpp \
		includes/glad/glad.cpp \
		srcs/classes/Camera/Camera.cpp \
		srcs/classes/Shader/Shader.cpp \
		srcs/classes/Texture/Texture.cpp \
		srcs/classes/Time/Time.cpp \
		srcs/classes/Object/Object.cpp \
		srcs/classes/Utils/Utils.cpp \
		srcs/classes/Matrix/Matrix.cpp \
		srcs/classes/Material/Material.cpp

OBJS := $(SRCS:.cpp=.o)

NAME := scop

COMPILER ?= c++

RM		:= rm -f

CFLAGS 	:= -Wall -Werror -Wextra -g

LIBRARIES := -Lincludes/glfw3/build/src -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

.cpp.o:
			${COMPILER} ${CFLAGS} -c $< -o ${<:.cpp=.o}

all: 		${NAME}

${NAME}:	${OBJS}
			${COMPILER} ${OBJS} -o ${NAME} ${LIBRARIES}

clean:
			${RM} ${OBJS}

fclean: 	clean
			${RM} ${NAME}

re:
			make fclean
			make

.PHONY: 	all clean fclean re
