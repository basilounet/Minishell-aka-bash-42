##========== SOURCES ==========##

SRC =	builts-in/cd/cd_utils.c \
		builts-in/cd/cd.c \
		builts-in/export/export_print.c \
		builts-in/export/export_set.c \
		builts-in/echo.c \
		builts-in/env.c \
		builts-in/exit.c \
		builts-in/pwd.c \
		builts-in/unset.c \
		interpreter/execution/execution_utils.c \
		interpreter/execution/execution.c \
		interpreter/execution/fork.c \
		interpreter/execution/ifs.c \
		interpreter/execution/heredoc.c \
		interpreter/execution/pids.c \
		interpreter/execution/prepare_execution.c \
		interpreter/execution/update_inputs.c \
		interpreter/execution/update_outputs.c \
		interpreter/execution/fds.c \
		interpreter/expansion/expand.c \
		interpreter/expansion/expand_arg.c \
		interpreter/expansion/expand_utils.c \
		interpreter/expansion/wildcards.c \
		interpreter/expansion/wc_mask.c \
		interpreter/expansion/wc_sort.c \
		interpreter/parser/lexer.c \
		interpreter/parser/parse_cmd.c \
		interpreter/parser/parse_logex.c \
		interpreter/parser/parse_utils.c \
		utils/builts_in_utils.c \
		utils/create_nodes.c \
		utils/create_env.c \
		utils/print_node.c \
		utils/create_tokens.c \
		utils/tok_utils.c \
		utils/env_utils.c \
		utils/create_wc.c \
		utils/prompt.c \
		utils/str_utils.c \
		utils/signals.c

MAIN = minishell.c

##========== NAMES ==========##

NAME = minishell
SRCS_DIR = src/
OBJS_DIR = obj/
LIBFT_DIR = libft
INCLUDE_DIR = includes

##========== OBJECTS ==========##

OBJS = $(addprefix $(OBJS_DIR),$(SRC:.c=.o))
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

CFLAGS = -Wall -Wextra -Werror
LDFLAGS = $(LIBS)
LIBS = -I$(INCLUDE_DIR)
LIBFT = $(LIBFT_DIR)/libft.a
ARCHIVES =  $(PIPEX_DIR)/pipex.a $(LIBFT)

##========== MODES ==========##

TIMER = 0.0
IS_PRINT = 1

ifdef DEBUG
    CFLAGS += -g
	LDFLAGS += -D DEBUG=42
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

$(NAME) : $(LIBFT) $(OBJS) $(MAIN_OBJ)
	@$(CC) -o $(NAME) $(CFLAGS) -lreadline $(MAIN_OBJ) $(OBJS) $(LDFLAGS) libft/libft.a
	@echo "$(GREEN)-= Minishell compiled =-$(BASE_COLOR)"

$(LIBFT) :
	@DEBUG=$(DEBUG_MODE) TIMER=$(TIMER) IS_PRINT=$(IS_PRINT) FSANITIZE=$(FSANITIZE_MODE) $(MAKE) -C $(LIBFT_DIR) --no-print-directory $(J4)

clean :
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean : clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(CYAN)Files cleaned$(BASE_COLOR)"

re : fclean all

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
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
	@echo "$(BASE_COLOR)║" $(shell expr $(INDEX) \* 100 / $(NUM_SRC))%
	@echo "╚==============================================╝"
	@$(eval INDEX=$(shell expr $(INDEX) + 1))
	@echo "Compiling : $<"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@
else
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@
endif


.PHONY : all clean fclean re
