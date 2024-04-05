##========== SOURCES ==========##

SRC =	interpreter/parser/lexer.c \
		interpreter/parser/parser.c \
		interpreter/expansion/expand.c \
		interpreter/expansion/wildcards.c \
		interpreter/execution/update_inputs.c \
		interpreter/execution/update_outputs.c \
		interpreter/execution/execution.c \
		interpreter/execution/execution_utils.c \
		utils/create_tokens.c \
		utils/create_nodes.c \
		utils/create_env.c \
		utils/str_utils.c \
		utils/prompt.c \
		builts-in/env.c \
		builts-in/export/export_print.c \
		builts-in/export/export_set.c \
		builts-in/unset.c \
		builts-in/echo.c \
		builts-in/cd/cd.c \
		builts-in/cd/cd_utils.c \
		interactive/signals.c

MAIN = minishell.c

##========== NAMES ==========##

NAME = minishell
SRCS_DIR = SRC/
OBJS_DIR = OBJ/
LIBFT_DIR = libft
PIPEX_DIR = pipex
INCLUDE_DIR = includes

##========== OBJECTS ==========##

OBJS := $(addprefix $(OBJS_DIR),$(SRC:.c=.o))
MAIN_OBJ = $(addprefix $(OBJS_DIR),$(MAIN:.c=.o))

##========== COLORS ==========##

BASE_COLOR 	=		\001\033[0;39m\002
GRAY 		=		\001\033[0;90m\002
RED 		=		\001\033[0;91m\002
GREEN 		=		\001\033[0;92m\002
YELLOW 		=		\001\033[0;93m\002
BLUE 		=		\001\033[0;94m\002
MAGENTA		=		\001\033[0;95m\002
CYAN 		=		\001\033[0;96m\002
WHITE		=		\001\033[0;97m\002

##========== COMPILATOR ==========##

CC = cc

##========== FLAGS ==========##

CFLAGS = #-Wall -Wextra -Werror
LDFLAGS = $(LIBS)
LIBS = -I$(INCLUDE_DIR)
LIBFT = $(LIBFT_DIR)/libft.a
ARCHIVES =  $(PIPEX_DIR)/pipex.a $(LIBFT)

##========== MODES ==========##

TIMER = 0.0
IS_PRINT = 1

ifdef DEBUG
    CFLAGS += -g
	DEBUG_MODE = 1
endif

ifdef FAST
	J4 = -j$(nproc)
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

$(NAME) : $(LIBFT) pipex $(OBJS) $(MAIN_OBJ)
	@$(CC) -o $(NAME) $(CFLAGS) -lreadline $(MAIN_OBJ) $(OBJS) $(LDFLAGS) pipex/pipex.a libft/libft.a
	@echo "$(GREEN)-= Minishell compiled =-$(BASE_COLOR)"

$(LIBFT) :
	@DEBUG=$(DEBUG_MODE) TIMER=$(TIMER) IS_PRINT=$(IS_PRINT) FSANITIZE=$(FSANITIZE_MODE) $(MAKE) -C $(LIBFT_DIR) --no-print-directory $(J4)

pipex :
	@DEBUG=$(DEBUG_MODE) TIMER=$(TIMER) IS_PRINT=$(IS_PRINT) FSANITIZE=$(FSANITIZE_MODE) $(MAKE) -C $(PIPEX_DIR) --no-print-directory $(J4)

clean :
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(PIPEX_DIR) clean --no-print-directory

fclean : clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@$(MAKE) -C $(PIPEX_DIR) fclean --no-print-directory
	@echo "$(CYAN)Files cleaned$(BASE_COLOR)"

re : fclean all

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
##	@echo -e "\033[$(shell expr $(NUM_LINES_TO_CLEAR));H\033[K"
ifeq ($(IS_PRINT),1)
	@sleep $(TIMER)
	@clear
	@echo "$(GREEN)Compiling Minishell$(BASE_COLOR)"
	@echo "╔==============================================╗"
	@echo -n "║$(GREEN)"
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
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@
endif



#bonus : all $(CHECKER)
#
#$(CHECKER) : $(OBJS) $(LIBFT) $(BONUS_MAIN_OBJ)
#		$(CC) -o $(CHECKER) $(CFLAGS) $(BONUS_MAIN_OBJ) $(OBJS) $(LDFLAGS)


.PHONY : all bonus clean fclean re pipex
