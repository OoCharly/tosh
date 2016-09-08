.PHONY: fclean re
.SUFFIXES:
NAME = 21sh
FLAGS = -Wall -Wextra -Werror
SRCS = $(foreach S, $(SRC), srcs/$(S))
OBJ = $(SRCS:.c=.o)
TERMCAPS = -lm -lncurses
HEAD = -I libft/includes -I includes
OS = $(shell uname -s)
SRC = \
core/cmp.c \
core/environ.c \
core/errors.c \
core/free.c \
core/hash.c \
core/main.c \
core/minishell.c \
history/history.c \
run_command/builtin.c \
run_command/files.c \
run_command/fork.c \
scan_input/arrowlr.c \
scan_input/arrowud.c \
scan_input/autocomp.c \
scan_input/chrparse.c \
scan_input/deletion.c \
scan_input/prompt.c \
scan_input/quotecheck.c \
scan_input/streamscan.c \
scan_input/termcaps.c \

ifeq ($(OS), Linux)
	FLAGS += -D LINUX
endif

all: lib $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $(HEAD) $^ -L libft -l ft -o $@ $(TERMCAPS)

%.o: %.c libft/libft.a
	gcc $(FLAGS) $(HEAD) -c $< -o $@

lib:
	make -C libft

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

re: fclean lib $(DNAME)
