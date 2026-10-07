NAME :=	ft_ssl

CC := cc
CCFLAGS :=	-g -MP -MMD -Wall -Wextra -Werror

LIB_DIR :=	lib/
INC_DIR :=	inc/
SRC_DIR :=	src/
OBJ_DIR :=	.obj/

INCLUDE_DIRS :=	-I$(INC_DIR) -I$(LIB_DIR)
LFLAGS :=

SRCS :=	src/main.c	\

OBJS :=	$(SRCS:%.c=$(OBJ_DIR)%.o)
DEPS :=	$(SRCS:%.c=$(OBJ_DIR)%.d)

all: $(NAME)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(NAME): $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $(OBJS) $(LFLAGS)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
