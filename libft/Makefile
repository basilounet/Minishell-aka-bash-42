##========== SOURCES ==========##

SRC = ft_abs.c \
	ft_atoi.c \
	ft_atoi_base.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_countc.c \
	ft_free_ptr.c \
	ft_is_x.c \
	ft_itoa.c \
	ft_itob.c \
	ft_lennum.c \
	ft_lst_getel.c \
	ft_lst_getindex.c \
	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstsize.c \
	ft_map.c \
	ft_max.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_mod.c \
	ft_numbers_of_lines.c \
	ft_power.c \
	ft_printf.c \
	ft_putchar_fd.c \
	ft_putchar.c \
	ft_putendl_fd.c \
	ft_putendl.c \
	ft_putmalloc.c \
	ft_putnbr_fd.c \
	ft_putnbr.c \
	ft_putnbru.c \
	ft_putptr.c \
	ft_putstr_fd.c \
	ft_putstr.c \
	ft_rand.c \
	ft_split.c \
	ft_split_plus.c \
	ft_strcat.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strncpy.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	get_next_line_bonus.c

##========== NAMES ==========##

NAME = libft.a
SRCS_DIR = src/
OBJS_DIR = obj/
INCLUDE_DIR = ../includes

##========== OBJECTS ==========##

OBJ = $(addprefix $(OBJS_DIR),$(SRC:.c=.o))

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

##========== MODES ==========##

TIMER = 0.0
IS_PRINT = 1

ifdef DEBUG
    CFLAGS += -g
endif

ifdef FSANITIZE
	LDFLAGS += -fsanitize=address
	FSANITIZE_MODE = 1
endif

##========== ANIMATIONS ==========##

NUM_SRC = $(words $(SRC))
INDEX = 0
NUM_LINES_TO_CLEAR = 1

all : $(CLEAR) $(NAME)

$(NAME) : $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "$(RED)-= Libft compiled =-$(BASE_COLOR)"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
##	@echo -e "\033[$(shell expr $(NUM_LINES_TO_CLEAR));H\033[K"
	@mkdir -p $(OBJS_DIR)
ifeq ($(IS_PRINT),1)
	@sleep $(TIMER)
	@clear
	@echo "$(RED)Compiling Libft$(BASE_COLOR)"
	@echo "╔==================================================╗"
	@echo -n "║$(RED)"
	@echo -n "▓"
	@for i in $$(seq 1 $$(expr $(INDEX) \* 50 / $(NUM_SRC))); do \
		echo -n "▓"; \
	done
	@for i in $$(seq 1 $$(expr 49 - $(INDEX) \* 50 / $(NUM_SRC))); do \
		echo -n " "; \
	done
	@echo "$(BASE_COLOR)║" $(shell expr $(INDEX) \* 100 / $(NUM_SRC))%
	@echo "╚==================================================╝"
	@$(eval INDEX=$(shell expr $(INDEX) + 1))
	@echo "Compiling : $<"
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@
else
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@
endif

clean :
	@rm -rf $(OBJS_DIR)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
