# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pducos <pducos@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 21:41:25 by nmathieu          #+#    #+#              #
#    Updated: 2022/07/28 11:17:07 by pducos           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

SRCS_DIR	:= srcs
OBJS_DIR	:= objs
INC_DIR 	:= incs

SRCS :=										\
	main.c									\
											\
	state/ms_state.c						\
	state/ms_var_env.c						\
	state/ms_var_set.c						\
	state/ms_var_get.c						\
	state/ms_var.c							\
	state/ms_vars_parse.c					\
	state/ms_setup_vars.c					\
	state/ms_var_remove.c					\
	state/ms_setup_handler.c				\
	state/ms_sigset_prompt.c				\
	state/ms_vars_to_strs.c					\
											\
	parse/lexer/ms_lexer_init.c				\
	parse/lexer/ms_lexer_deinit.c			\
	parse/lexer/ms_lexer_absorbe.c			\
	parse/lexer/ms_tok_reader.c				\
	parse/lexer/ms_tok_reader_next.c		\
	parse/lexer/ms_tok_reader_here_doc.c	\
\
	parse/expand/ms_remove_quotes.c			\
	parse/expand/ms_push_expanded.c			\
	parse/expand/ms_expand_vars.c			\
	parse/expand/ms_split_fields.c			\
	parse/expand/ms_special_vars.c			\
	parse/expand/ms_expand_args.c			\
	parse/expand/ms_expand_filename.c		\
	parse/expand/ms_expand_pathname.c		\
	parse/expand/ms_expast_deinit.c			\
	parse/expand/ms_expast_init.c			\
	parse/expand/ms_expiord.c				\
	parse/expand/ms_expand_tild.c			\
	parse/expand/ms_assign_parse.c			\
	parse/expand/ms_assign.c				\
	parse/expand/ms_init_vars.c				\
	parse/expand/ms_glob.c					\
\
	parse/syn/ms_syner_absorbe.c			\
	parse/syn/ms_syner_parse_iord.c			\
	parse/syn/ms_syner_state_cmd_iords.c	\
	parse/syn/ms_syner_state_command.c		\
	parse/syn/ms_syner_state_cpar_iords.c	\
	parse/syn/ms_syner_state_paren.c		\
	parse/syn/ms_syner_state_init.c			\
	parse/syn/ms_syner.c					\
	parse/syn/ms_syn_reader.c				\
	parse/syn/ms_syn_reader_next.c			\
	parse/syn/ms_syn_free.c					\
	parse/syn/ms_syner_state_op.c			\
	parse/syn/ms_syn_here_doc.c				\
\
	parse/parser/ms_ast_create.c			\
	parse/parser/ms_ast_free.c				\
	parse/parser/ms_ast_precedence.c		\
	parse/parser/ms_ast_reader_next.c		\
	parse/parser/ms_ast_reader.c			\
	parse/parser/ms_iord_free.c				\
	parse/parser/ms_parser_absorbe.c		\
	parse/parser/ms_parser_add_binop.c		\
	parse/parser/ms_parser_add_cmd.c		\
	parse/parser/ms_parser_add_cparen.c		\
	parse/parser/ms_parser_push_scope.c		\
	parse/parser/ms_parser.c				\
	parse/parser/ms_parser_add_oparen.c		\
	parse/parser/ms_parser_get_op_pos.c		\
\
	parse/ms_show_expanded.c	\
	parse/ms_show_ast.c			\
	parse/ms_show_tokens.c		\
	parse/ms_show_syntax.c		\
	parse/ms_tok_show.c			\
	parse/ms_syn_show.c			\
	parse/ms_ast_show.c			\
	parse/ms_iord_show.c		\
	parse/errors.c				\
	parse/ms_command.c			\
\
	parse/lexer/chars/ms_islower.c		\
	parse/lexer/chars/ms_isupper.c		\
	parse/lexer/chars/ms_isalpha.c		\
	parse/lexer/chars/ms_isalphanum.c	\
	parse/lexer/chars/ms_isdigit.c		\
	parse/lexer/chars/ms_isnull.c		\
	parse/lexer/chars/ms_iseol.c		\
	parse/lexer/chars/ms_isspace.c		\
	parse/lexer/chars/ms_isand.c		\
	parse/lexer/chars/ms_isor.c			\
	parse/lexer/chars/ms_isless.c		\
	parse/lexer/chars/ms_isgreat.c		\
	parse/lexer/chars/ms_ispunct.c		\
	parse/lexer/chars/ms_isquestion.c	\
	parse/lexer/chars/ms_isdollar.c		\
	parse/lexer/chars/ms_ischar.c		\
	parse/lexer/chars/ms_isunderscore.c	\
	parse/lexer/chars/ms_issquote.c		\
	parse/lexer/chars/ms_isbackslash.c	\
	parse/lexer/chars/ms_isdquote.c		\
	parse/lexer/chars/ms_isoparen.c		\
	parse/lexer/chars/ms_iscparen.c		\
\
	repl/ms_repl_entry_point.c			\
	repl/ms_repl_engine.c				\
	repl/ms_repl_engine_absorbe.c		\
	repl/ms_repl_engine_absorbe_char.c	\
	repl/ms_submit_history.c			\
\
	exec/ms_execute_ast.c						\
	exec/ms_execute.c							\
	exec/execute/ms_setup_subsh.c				\
	exec/execute/ms_and_if.c					\
	exec/execute/ms_or_if.c						\
	exec/execute/ms_find_cmd.c					\
	exec/execute/ms_pipeline.c					\
	exec/execute/ms_put_sig.c					\
	exec/execute/ms_seq.c						\
	exec/execute/ms_exec_builtin.c				\
	exec/execute/ms_simple_command.c			\
	exec/execute/ms_fri_and_exit.c				\
	exec/general/ms_file_exists.c				\
	exec/general/ms_file_is_directory.c			\
	exec/general/ms_file_is_execable.c			\
	exec/general/ms_file_is_readable.c			\
	exec/general/ms_file_is_writable.c			\
	exec/general/ms_file_status.c				\
	exec/redirection/ms_do_redirections.c		\
	exec/redirection/ms_file_append.c			\
	exec/redirection/ms_file_open.c				\
	exec/redirection/ms_file_write.c			\
	exec/redirection/ms_do_heredoc.c			\
\
	builtins/ms_echo.c		\
	builtins/ms_cd.c			\
	builtins/ms_pwd.c		\
	builtins/ms_exit.c		\
	builtins/ms_env.c		\
	builtins/ms_unset.c	\
	builtins/ms_export.c	\
\
	utils/ms_assert.c							\
	utils/ms_putstr.c							\
	utils/ms_alloc.c							\
	utils/ms_mem_copy.c							\
	utils/ms_mem_set.c							\
	utils/ms_str_cmp.c							\
	utils/ms_str_starts_with.c					\
	utils/ms_alloc_array.c						\
	utils/ms_putdstr.c							\
	utils/ms_str_create.c						\
	utils/ms_vec_realloc.c						\
	utils/ms_vec_reserve.c						\
	utils/ms_vec_append.c						\
	utils/ms_putnbr.c							\
	utils/ms_str_len.c							\
	utils/ms_mem_free.c							\
	utils/ms_close_fd.c							\
	utils/ms_str_cat.c							\
	utils/ms_str_chr.c							\
	utils/ms_strs_len.c							\
	utils/ms_str_dup.c							\
	utils/ms_str_split.c						\
	utils/ms_put_int.c							\
	utils/ms_save_str.c							\
	utils/ms_str_copy.c							\
	utils/ms_str_new.c							\
	utils/ms_error.c							\
	utils/ms_free_array.c						\
	utils/ms_str_append.c						\
	utils/ms_f2d.c


# ============================================================================ #
#                                Intermediates                                 #
# ============================================================================ #

OBJ_FILES := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS))
DEP_FILES := $(OBJ_FILES:.o=.d)
HDR_FILES := $(addprefix $(INC_DIR)/,$(HEADERS)) \
			 $(addprefix $(SRCS_DIR)/,$(PRIV_HEADERS))

ifdef DEBUG
	CFLAGS := -Wall -Wextra -g3
else
	CFLAGS := -Wall -Wextra -Werror 
endif

# ============================================================================ #
#                                   Commands                                   #
# ============================================================================ #

all: $(NAME)

bonus: all

clean:
	@rm -vf $(OBJ_FILES)
	@rm -vrf tests/output

fclean: clean
	@rm -vf $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all bonus clean fclean re

# ============================================================================ #
#                                   Rules                                      #
# ============================================================================ #

$(NAME): $(OBJ_FILES)
	clang $(CFLAGS) -o $(NAME) $(OBJ_FILES) -lreadline

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -vp $(dir $@)
	clang $(CFLAGS) -MMD -I $(INC_DIR) -o $@ -c $<

-include $(DEP_FILES)