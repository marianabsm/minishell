NAME = minishell
CC = cc
SANITIZE			=	-fsanitize=address

SRC =			src/main/main.c \
				src/parser/env.c \
				src/parser/envp_1.c \
				src/parser/envp_2.c \
				src/parser/init_commands.c \
				src/parser/init_exec.c \
				src/parser/init.c \
				src/parser/parser.c \
				src/parser/spaces.c \
				src/parser/splitter.c \
				src/parser/matrix.c \
				src/parser/parse_command1.c \
				src/parser/parse_command2.c \
				src/expander/expand1.c \
				src/expander/expand2.c \
				src/signals/signals_1.c \
				src/signals/signals_2.c \
				src/executor/redirection_1.c \
				src/executor/redirection_2.c \
				src/executor/start_executer_1.c \
				src/executor/sys_call_error_1.c \
				src/executor/sys_call_error_2.c \
				src/executor/new_exec.c \
				src/builtins/execute_builtins.c \
				src/builtins/cd.c \
				src/builtins/echo.c \
				src/builtins/env1.c \
				src/builtins/env2.c \
				src/builtins/exit.c \
				src/builtins/export1.c \
				src/builtins/export2.c \
				src/builtins/pwd.c \
				src/builtins/unset1.c \
				src/heredoc/doc_loop.c \
				src/heredoc/run_doc.c \
				src/heredoc/waitpid.c \
				src/utils/free_1.c \
				src/utils/free_2.c \
				src/utils/heredoc_utils.c \
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
				testers_for_printing.c\

CFLAGS =		-I./includes -g #-Wall -Wextra -Werror #-fsanitize=address
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
	valgrind --suppressions=readline.supp --track-fds=all --leak-check=full --show-leak-kinds=all --track-origins=yes  ./minishell


