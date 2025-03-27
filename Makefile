NAME = minishell
CC = cc

SRC =			src/main/main.c \
				src/parser/create_tokens.c \
				src/parser/envp_1.c \
				src/parser/envp_2.c \
				src/parser/init_exec.c \
				src/parser/init.c \
				src/parser/parser.c \
				src/parser/quotes.c \
				src/parser/retokenizer_1.c \
				src/parser/retokenizer_2.c \
				src/parser/split_spaces.c \
				src/parser/syntax.c \
				src/parser/tokenizer.c \
				src/parser/rm_quotes1.c \
				src/expander/expander_1.c \
                src/expander/expander_2.c \
                src/expander/expander_3.c \
				src/signals/signals_1.c \
				src/signals/signals_2.c \
				src/executor/fork_and_execute1.c \
				src/executor/redirection_1.c \
				src/executor/redirection_2.c \
				src/executor/start_executer_1.c \
				src/executor/start_executer_2.c \
				src/executor/sys_call_error_1.c \
				src/executor/sys_call_error_2.c \
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
				src/utils/malloc.c \
				src/utils/utils_builtins.c \
				src/utils/utils_str.c \
				src/utils/delete.c

CFLAGS =		-I./includes -g -Wall -Wextra -Werror #-fsanitize=address
OTHERFLAGS =	-lreadline #-lasan -O3

OBJ_DIR =		./obj/
OBJS =			$(patsubst src/%.c, $(OBJ_DIR)%.o, $(SRC))


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(OTHERFLAGS) -o $(NAME)

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
