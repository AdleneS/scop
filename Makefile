
NAME	= scop
SRCS 	= main.c utils.c
OBJ_DIR = ./.objs
SRC_DIR = ./src
INC_DIR = ./include
INC_HDR =	-I./ -I./glfw-3.3.2/include -I./gl3w/include/GL
INC_LIB =	-L./glfw-3.3.2/src -lglfw3 \
			-framework OpenGL -framework AppKit -framework Cocoa -framework IOKit -framework CoreVideo
INC_H	= ./include/scop.h

CFLAGS	:= -Wall -Wextra -O3 -I$(INC_DIR)
OBJS	:= $(patsubst %.c,$(OBJ_DIR)/%.o,  $(SRCS))

all: CREATE_OBJDIR $(NAME)

CREATE_OBJDIR:
		@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
		@gcc ${CFLAGS} ${INC_LIB} $^ -o ${NAME}
		@printf "\033[1m[ Scop ]\033[1m\t\tcompilation complete.\t\033[0m\n"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_H)
		@gcc $(CFLAGS) -o $@ -c $<

mk: 
	@mkdir -p .objs

clean:
		@rm -rf $(OBJ_DIR)
		@echo "\033[1m[ Scop ]\033[0m\t\tobjects cleared.\033[0m"

fclean : clean
		@rm -f $(NAME)
		@echo "\033[1m[ Scop ]\033[0m\t\tbinary deleted.\033[0m"
re:		fclean all
