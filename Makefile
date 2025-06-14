NAME = minishell
CC = cc
SANITIZE			=	-fsanitize=address

SRC =			src/main/main.c \
				src/main/msh_loop.c \
				src/parser/env.c \
				src/parser/envp_1.c \
				src/parser/envp_2.c \
				src/parser/init_commands.c \
				src/parser/init_exec.c \
				src/parser/init.c \
				src/parser/parser1.c \
				src/parser/parser2.c \
				src/parser/parser3.c \
				src/parser/parser4.c \
				src/parser/parser5.c \
				src/parser/parser6.c \
				src/parser/spaces1.c \
				src/parser/spaces2.c \
				src/parser/spaces3.c \
				src/parser/splitter1.c \
				src/parser/splitter2.c \
				src/parser/splitter3.c \
				src/parser/matrix.c \
				src/parser/parse_command1.c \
				src/parser/parse_command2.c \
				src/expander/expand1.c \
				src/expander/expand2.c \
				src/expander/expand3.c\
				src/expander/expand4.c \
				src/expander/expand5.c \
				src/expander/expand6.c \
				src/expander/quotes.c \
				src/signals/signals_1.c \
				src/signals/signals_2.c \
				src/executor/redirection_1.c \
				src/executor/redirection_2.c \
				src/executor/sys_call_error_1.c \
				src/executor/sys_call_error_2.c \
				src/executor/exec_builtins.c \
				src/builtins/cd1.c \
				src/builtins/cd2.c \
				src/builtins/echo.c \
				src/builtins/env1.c \
				src/builtins/env2.c \
				src/builtins/exit.c \
				src/builtins/export1.c \
				src/builtins/export2.c \
				src/builtins/export3.c \
				src/builtins/export4.c \
				src/builtins/pwd.c \
				src/builtins/unset.c \
				src/heredoc/run_doc.c \
				src/heredoc/waitpid.c \
				src/utils/free_1.c \
				src/utils/free_2.c \
				src/utils/libft_utils1.c \
				src/utils/libft_utils2.c \
				src/utils/libft_utils3.c \
				src/utils/libft_utils4.c \
				src/utils/libft_utils5.c \
				src/utils/libft_utils6.c \
				src/utils/malloc.c \
				src/utils/syntax_errors.c \
				src/utils/utils_builtins.c \
				src/utils/utils_str.c \
				src/utils/utils1.c \
				src/utils/utils2.c \
				src/utils/utils3.c \
				src/utils/utils4.c \
				src/executor/exec1.c \
				src/executor/exec2.c \
				src/executor/exec3.c \
				src/executor/exec4.c \
				src/executor/exec5.c \
				src/executor/exec6.c \
				src/executor/path_finder.c \
				src/heredoc/heredoc.c \

CFLAGS =		-I./includes -g -Wall -Wextra -Werror #-fsanitize=address
OTHERFLAGS =	-lreadline #-lasan -O3

OBJ_DIR =		./obj/
OBJS =			$(patsubst src/%.c, $(OBJ_DIR)%.o, $(SRC))


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LINKS) $(OTHERFLAGS) -o $(NAME)

sanitize: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(OTHERFLAGS) $(SANITIZE) -o $(NAME)

$(OBJ_DIR)%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

valgrind:
	valgrind --suppressions=readline.supp --track-fds=yes --leak-check=full --trace-children=yes --show-leak-kinds=definite --track-origins=yes  ./minishell

