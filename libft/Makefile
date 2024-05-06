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
BLACK		=		\033[30m
GRAY 		=		\033[0;90m
DARK_GRAY	=		\033[37m
RED 		=		\033[0;91m
DARK_GREEN	=		\033[32m
DARK_RED	=		\033[31m
GREEN 		=		\033[0;92m
ORANGE 		=		\033[0;93m
DARK_YELLOW	=		\033[33m
BLUE 		=		\033[0;94m
DARK_BLUE	=		\033[34m
MAGENTA		=		\033[0;95m
DARK_MAGENTA=		\033[35m
CYAN 		=		\033[0;96m
WHITE		=		\033[0;97m

##========== COMPILATOR ==========##

CC = clang

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
NUMBER_OF_ANIMATION = 9
ifndef
	ANIMATION_RATE = 4
endif

all : $(CLEAR) $(NAME)

$(NAME) : $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "$(RED)-= Libft compiled =-$(BASE_COLOR)"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
ifeq ($(IS_PRINT),1)
	@sleep $(TIMER)
	@clear
	@echo "$(RED)Compiling Libft$(BASE_COLOR)"
	$(animations)
	$(loading)
	$(file_size_graph)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@
else
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@
endif

define animations
	$(animation_$(shell expr $(INDEX) / $(ANIMATION_RATE) % $(NUMBER_OF_ANIMATION)))
endef

define loading
	@$(eval INDEX=$(shell expr $(INDEX) + 1))
	@echo "╔═══════════════════════════════════════════════════╗"
	@echo -n "║"
	$(loading_color)
	@echo -n "▓"
	@for i in $$(seq 1 $$(expr $(INDEX) \* 50 / $(NUM_SRC))); do \
		echo -n "▓"; \
	done
	@for i in $$(seq 1 $$(expr 50 - $(INDEX) \* 50 / $(NUM_SRC))); do \
		echo -n " "; \
	done
	@echo "$(BASE_COLOR)║" $(shell expr $(INDEX) \* 100 / $(NUM_SRC))%
	@echo "╚═══════════════════════════════════════════════════╝"
endef

define loading_color
	@if [ $(INDEX) -lt $$(expr $(NUM_SRC) \* 1 / 5) ]; then \
		echo -n "$(DARK_RED)" ; \
	elif [ $(INDEX) -lt $$(expr $(NUM_SRC) \* 2 / 5) ]; then \
		echo -n "$(RED)" ; \
	elif [ $(INDEX) -lt $$(expr $(NUM_SRC) \* 3 / 5) ]; then \
		echo -n "$(ORANGE)" ; \
	else \
		echo -n "$(GREEN)" ; \
	fi
endef

define file_size_graph
	@awk -v size=$(shell stat -c %s $<) 'BEGIN { printf "[ "; for (i=0; i<int(size/1000); i++) printf "#"; printf " ] (%d KB)\n", size/1000 }'
endef

clean :
	@rm -rf $(OBJS_DIR)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

define animation_0
	@echo "           $(BLUE) _        _     _          __    _   $(BASE_COLOR)                          "
	@echo "  $(WHITE)  o O O  $(BLUE)| |      (_)   | |__      / _|  | |_ $(BASE_COLOR)                          "
	@echo "  $(WHITE) o       $(BLUE)| |__    | |   | '_ \    |  _|  |  _|$(BASE_COLOR)                          "
	@echo "  $(DARK_YELLOW)TS$(RED)__$(DARK_YELLOW)[O]  $(BLUE)|$(RED)____$(BLUE)|  $(RED)_$(BLUE)|$(RED)_$(BLUE)|$(RED)_  $(BLUE)|$(RED)_.__$(BLUE)/   $(RED)_$(BLUE)|$(RED)_$(BLUE)|$(RED)_   $(RED)_$(BLUE)\\\\$(RED)__$(BLUE)|$(BASE_COLOR)                          "
	@echo " $(RED){======|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|$(BASE_COLOR)                         "
	@echo "$(RED)./$(DARK_YELLOW)o$(RED)--$(DARK_YELLOW)000$(RED)'\"\`-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'$(BASE_COLOR)                 "
endef

define animation_1
	@echo "  $(BLUE) _        _     _          __    _                                      "
	@echo "  $(BLUE)| |      (_)   | |__      / _|  | |_                            $(WHITE)  o O O "
	@echo "  $(BLUE)| |__    | |   | '_ \    |  _|  |  _|                           $(WHITE) o      "
	@echo "  $(BLUE)|$(RED)____$(BLUE)|  $(RED)_$(BLUE)|$(RED)_$(BLUE)|$(RED)_  $(BLUE)|$(RED)_.__$(BLUE)/   $(RED)_$(BLUE)|$(RED)_$(BLUE)|$(RED)_   $(RED)_$(BLUE)\\\\$(RED)__$(BLUE)|                           $(DARK_YELLOW)TS$(RED)__$(DARK_YELLOW)[O] "
	@echo "$(RED)_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)| $(BASE_COLOR)                        $(RED){======| "
	@echo "$(RED)\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'$(BASE_COLOR)                        $(RED)./$(DARK_YELLOW)o$(RED)-$(RED)-$(DARK_YELLOW)000$(RED)'$(BASE_COLOR)   "
endef

define animation_2
	@echo "$(BLUE)    _     _          __    _                                        _     "
	@echo "$(BLUE)   (_)   | |__      / _|  | |_                            $(WHITE)  o O O  $(BLUE)| |    "
	@echo "$(BLUE)   | |   | '_ \    |  _|  |  _|                           $(WHITE) o       $(BLUE)| |__  "
	@echo "$(BLUE)  $(RED)_$(BLUE)|$(RED)_$(BLUE)|$(RED)_  $(BLUE)|$(RED)_.__$(BLUE)/   $(RED)_$(BLUE)|$(RED)_$(BLUE)|$(RED)_   _$(BLUE)\\\\$(RED)__$(BLUE)|                           $(DARK_YELLOW)TS$(RED)__$(DARK_YELLOW)[O]  $(BLUE)|$(RED)____$(BLUE)| "
	@echo "$(RED)_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|$(BASE_COLOR)                         $(RED){======|_|$(ORANGE)\"\"\"\"\"$(RED)| "
	@echo "\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'$(BASE_COLOR)                        $(RED)./$(DARK_YELLOW)o$(RED)--$(DARK_YELLOW)000$(RED)'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-' $(BASE_COLOR)  $(BASE_COLOR)"
endef

define animation_3
	@echo "$(BLUE)  _          __    _                                       $(BLUE) _        _    "
	@echo "$(BLUE) | |__      / _|  | |_                             $(WHITE) o O O  $(BLUE)| |      (_)   "
	@echo "$(BLUE) | '_ \    |  _|  |  _|                            $(WHITE)o       $(BLUE)| |__    | |   "
	@echo "$(BLUE) |$(RED)_.__$(BLUE)/   $(RED)_$(BLUE)|$(RED)_$(BLUE)|$(RED)_   _$(BLUE)\\\\$(RED)__$(BLUE)|                           $(DARK_YELLOW)TS__$(DARK_YELLOW)[O]  $(BLUE)|$(RED)____$(BLUE)|  $(RED)_$(BLUE)|$(RED)_$(BLUE)|$(RED)_  "
	@echo "$(RED)_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|    $(BASE_COLOR)                     $(RED){======$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)| "
	@echo "\"\`-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'$(BASE_COLOR)                        $(RED)./o-$(RED)-$(DARK_YELLOW)000$(RED)'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0-' $(BASE_COLOR)"
endef

define animation_4
	@echo "$(BLUE)     __    _                                        _     $(BLUE)   _     _      "
	@echo "$(BLUE)    / _|  | |_                             $(WHITE) o O O $(BLUE) | |      (_)   | |__   "
	@echo "$(BLUE)   |  _|  |  _|                            $(WHITE)o      $(BLUE) | |__    | |   | '_ \  "
	@echo "  $(RED)_$(BLUE)|_$(BLUE)|$(RED)_   _$(BLUE)\\\\$(RED)__$(BLUE)|                           $(DARK_YELLOW)TS$(RED)__$(DARK_YELLOW)[O]  $(BLUE)|____$(BLUE)|  $(RED)_$(BLUE)|$(RED)_$(BLUE)|$(RED)_  $(BLUE)|$(RED)_.__$(BLUE)/  "
	@echo "$(RED)_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|$(BASE_COLOR)                         $(RED){======|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)| "
	@echo "\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-' $(BASE_COLOR)                       $(RED)./$(DARK_YELLOW)o$(RED)--$(DARK_YELLOW)000$(RED)'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0-' $(BASE_COLOR)"
endef

define animation_5
	@echo "$(BLUE)   _                                        _    $(BLUE)    _     _          __  "
	@echo "$(BLUE)  | |_                             $(WHITE) o O O$(BLUE)  | |      (_)   | |__      / _| "
	@echo "$(BLUE)  |  _|                            $(WHITE)o     $(BLUE)  | |__    | |   | '_ \    |  _| "
	@echo "  _$(BLUE)\\\\$(RED)__$(BLUE)|                           $(DARK_YELLOW)TS$(RED)__$(DARK_YELLOW)[O]  $(BLUE)|____$(BLUE)|  $(RED)_$(BLUE)|$(RED)_$(BLUE)|$(RED)_  $(BLUE)|$(RED)_.__$(BLUE)/   $(RED)_$(BLUE)|$(RED)_$(BLUE)|$(RED)_  "
	@echo "_|$(ORANGE)\"\"\"\"\"$(RED)|$(BASE_COLOR)                         $(RED){======|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)| "
	@echo "\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-' $(BASE_COLOR)                       $(RED)./$(DARK_YELLOW)o$(RED)--$(DARK_YELLOW)000$(RED)'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-' $(BASE_COLOR)"
endef

define animation_6
	@echo "                                    $(BLUE)_        _     _          __    _     "
	@echo "                           $(WHITE) o O O$(BLUE)  | |      (_)   | |__      / _|  | |_   "
	@echo "                           $(WHITE)o     $(BLUE)  | |__    | |   | '_ \    |  _|  |  _|  "
	@echo "                          $(DARK_YELLOW)TS$(RED)__$(DARK_YELLOW)[O]  $(BLUE)|$(RED)____$(BLUE)|  $(RED)_$(BLUE)|$(RED)_$(BLUE)|$(RED)_  $(BLUE)|$(RED)_.__$(BLUE)/   $(RED)_$(BLUE)|$(RED)_$(BLUE)|$(RED)_  $(RED) _$(BLUE)\\\\$(RED)__$(BLUE)|  "
	@echo "                         $(RED){======|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|$(BASE_COLOR) "
	@echo "                        $(RED)./$(DARK_YELLOW)o$(RED)--$(DARK_YELLOW)000$(RED)'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-' $(BASE_COLOR)"
endef

define animation_7
	@echo "                           $(BLUE) _        _     _          __    _             "
	@echo "                   $(WHITE) o O O $(BLUE) | |      (_)   | |__      / _|  | |_           "
	@echo "                   $(WHITE)o      $(BLUE) | |__    | |   | '_ \    |  _|  |  _|          "
	@echo "                  $(DARK_YELLOW)TS$(RED)__$(DARK_YELLOW)[O]  $(BLUE)|$(RED)____$(BLUE)|  $(RED)_$(BLUE)|$(RED)_$(BLUE)|$(RED)_  $(BLUE)|$(RED)_.__$(BLUE)/   $(RED)_$(BLUE)|$(RED)_$(BLUE)|$(RED)_   $(RED)_$(BLUE)\\\\$(RED)__$(BLUE)|          "
	@echo "                 $(RED){======|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|$(BASE_COLOR)         "
	@echo "                $(RED)./$(DARK_YELLOW)o$(RED)--$(DARK_YELLOW)000$(RED)'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-' $(BASE_COLOR)"
endef

define animation_8
	@echo "                   $(BLUE) _        _     _          __    _                     "
	@echo "           $(WHITE) o O O $(BLUE) | |      (_)   | |__      / _|  | |_                   "
	@echo "           $(WHITE)o      $(BLUE) | |__    | |   | '_ \    |  _|  |  _|                  "
	@echo "          $(DARK_YELLOW)TS$(RED)__$(DARK_YELLOW)[O]  $(BLUE)|$(RED)____$(BLUE)|  $(RED)_$(BLUE)|$(RED)_$(BLUE)|$(RED)_  $(BLUE)|$(RED)_.__$(BLUE)/   $(RED)_$(BLUE)|$(RED)_$(BLUE)|$(RED)_   $(RED)_$(BLUE)\\\\$(RED)__$(BLUE)|                  "
	@echo "         $(RED){======|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)|_|$(ORANGE)\"\"\"\"\"$(RED)| $(BASE_COLOR)                "
	@echo "        $(RED)./$(DARK_YELLOW)o$(RED)--$(DARK_YELLOW)000$(RED)'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-'\"\`$(RED)-$(DARK_YELLOW)0$(RED)-$(DARK_YELLOW)0$(RED)-' $(BASE_COLOR)      "
endef

.PHONY : all clean fclean re