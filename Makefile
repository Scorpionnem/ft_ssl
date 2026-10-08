NAME :=	ft_ssl

CMD_PATH := cmd/

MD5 := md5
SHA256 := sha256
BASE64 := base64

MD5_PATH := $(CMD_PATH)$(MD5)
SHA256_PATH := $(CMD_PATH)$(SHA256)
BASE64_PATH := $(CMD_PATH)$(BASE64)

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

all: $(MD5) $(SHA256) $(BASE64) $(NAME)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(NAME): $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $(OBJS) $(LFLAGS)
	@echo Compiled $(NAME)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(MD5):
	@make -C $(MD5_PATH) all --no-print-directory
	@cp $(MD5_PATH)/$(MD5) $(MD5)

$(SHA256):
	@make -C $(SHA256_PATH) all --no-print-directory
	@cp $(SHA256_PATH)/$(SHA256) $(SHA256)

$(BASE64):
	@make -C $(BASE64_PATH) all --no-print-directory
	@cp $(BASE64_PATH)/$(BASE64) $(BASE64)

clean:
	@make -C $(MD5_PATH) clean --no-print-directory
	@make -C $(SHA256_PATH) clean --no-print-directory
	@make -C $(BASE64_PATH) clean --no-print-directory
	rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(MD5_PATH) fclean --no-print-directory
	@make -C $(SHA256_PATH) fclean --no-print-directory
	@make -C $(BASE64_PATH) fclean --no-print-directory
	rm -rf $(NAME)
	rm -rf $(MD5)
	rm -rf $(SHA256)
	rm -rf $(BASE64)

re: fclean all

.PHONY: all clean fclean re $(NAME) $(MD5) $(SHA256) $(BASE64)

-include $(DEPS)
