##========== SOURCES ==========##

SRC = parse.c \
		struct_init.c \
		unleak.c \
		errors.c \
		fork.c \
		pipe.c \
		here_doc.c
MAIN = pipex.c

##========== NAMES ==========##

NAME = pipex.a
SRCS_DIR = SRC/
OBJS_DIR = OBJ/
LIBFT_DIR = ../libft
INCLUDE_DIR = ../includes

##========== OBJECTS ==========##

OBJS := $(addprefix $(OBJS_DIR),$(SRC:.c=.o))
MAIN_OBJ = $(addprefix $(OBJS_DIR),$(MAIN:.c=.o))

##========== COLORS ==========##

BASE_COLOR 	=		\033[0;39m
GRAY 		=		\033[0;90m
RED 		=		\033[0;91m
GREEN 		=		\033[0;92m
YELLOW 		=		\033[0;93m
BLUE 		=		\033[0;94m
MAGENTA		=		\033[0;95m
CYAN 		=		\033[0;96m
WHITE		=		\033[0;97m

##========== COMPILATOR ==========##

CC = cc

##========== FLAGS ==========##

CFLAGS = -Wall -Wextra -Werror
LDFLAGS = $(LIBS) #-fsanitize=address
LIBS = -I$(INCLUDE_DIR)
ARCHIVES = $(LIBFT_DIR)/libft.a

##========== MODES ==========##

TIMER = 0.0
IS_PRINT = 1

ifdef DEBUG
    CFLAGS += -g
	DEBUG_MODE = 1
endif

ifdef FAST
	J4 = -j4
endif

ifdef FSANITIZE
	LDFLAGS += -fsanitize=address
	FSANITIZE_MODE = 1
endif

##========== ANIMATIONS ==========##

NUM_SRC = $(words $(SRC))
INDEX = 0
NUM_LINES_TO_CLEAR = 1

all : $(NAME)

$(NAME) : $(OBJS) $(MAIN_OBJ)
	@ar rcs $(NAME) $(OBJ) $(MAIN_OBJ) $(ARCHIVES)
#	@$(CC) -o $(NAME) $(CFLAGS) $(MAIN_OBJ) $(OBJS) $(LDFLAGS) $(ARCHIVES)
	@echo "$(YELLOW)-= Pipex compiled =-$(BASE_COLOR)"

clean :
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean : clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(CYAN)Files cleaned$(BASE_COLOR)"

re : fclean all

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
##	@echo -e "\033[$(shell expr $(NUM_LINES_TO_CLEAR));H\033[K"
ifeq ($(IS_PRINT),1)
	@sleep $(TIMER)
	@clear
	@echo "$(YELLOW)Compiling Pipex$(BASE_COLOR)"
	@echo "╔==============================================╗"
	@echo -n "║$(YELLOW)"
	@echo -n "▓"
	@for i in $$(seq 1 $$(expr $(INDEX) \* 45 / $(NUM_SRC))); do \
		echo -n "▓"; \
	done
	@for i in $$(seq 1 $$(expr 45 - $(INDEX) \* 45 / $(NUM_SRC))); do \
		echo -n " "; \
	done
	@echo "$(BASE_COLOR)║"
	@echo "╚==============================================╝"
	@$(eval INDEX=$(shell expr $(INDEX) + 1))
	@echo "Compiling : $<"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@
else
	@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@
endif



#bonus : all $(CHECKER)
#
#$(CHECKER) : $(OBJS) $(LIBFT) $(BONUS_MAIN_OBJ)
#		$(CC) -o $(CHECKER) $(CFLAGS) $(BONUS_MAIN_OBJ) $(OBJS) $(LDFLAGS)


.PHONY : all bonus clean fclean re
