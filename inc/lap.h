/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lap.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 10:41:58 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/22 12:36:36 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAP_H
# define LAP_H

# include "./minishell.h"

# define ERR_PREFIX "syntax error "

/* ===================== Token Types ===================== */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_HEREDOC,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_OUT_APPEND,
	TOKEN_NONE = -1
}	t_token_type;

/* ===================== Token Struct ===================== */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				quoted;
	int				has_space_before;
	int				is_heredoc_delim;
	struct s_token	*next;
}	t_token;

/* ===================== Intern helper ================== */
typedef struct s_parser_intern
{
	t_token			**token;
	t_cmd			**cmds;
	t_shell			*shell;
	t_token_type	*expect;
}	t_parser_intern;

typedef struct s_heredoc
{
	char			*line;
	char			*content;
	char			*new_content;
	size_t			content_len;
	size_t			line_len;
}	t_heredoc;

typedef struct s_token_data
{
	t_token_type	type;
	const char		*value;
	int				len;
	int				has_space;
}	t_token_data;

typedef struct s_index
{
	size_t			i;
	size_t			j;
}	t_index;

typedef struct s_scan_ctx
{
	const char	*input;
	t_token		**head;
	int			has_space;
}	t_scan_ctx;

typedef struct s_expand_ctx
{
	char		*res;
	char		*val;
	size_t		i;
	size_t		j;
	t_shell		*shell;
}	t_expand_ctx;

typedef struct s_redir
{
	int			type;
	const char	*input;
	int			len;
	int			has_space;
}	t_redir;

/* ===================== Lexer / Parser ===================== */
t_token			*lexer(t_shell *shell, const char *input);
t_cmd			*parser(t_token *tokens, t_shell *shell);
t_token			*process_input(char *line, t_shell *shell);

/* ===================== Parser Helpers ==================== */
t_cmd			*new_cmd(void);
char			**add_args(char **argv, char *word);
char			*my_getenv_len(char *name, size_t len, char **envp);
int				add_args_cmd(t_cmd *cmd, char *arg);
int				is_redirection(t_token_type type);
int				validate_syntax(t_shell *shell, t_token *head);
int				handle_redir_in(t_cmd *cmd, t_token **token);
int				handle_redir_out(t_cmd *cmd, t_token **token);
int				handle_redir_out_append(t_cmd *cmd, t_token **token);
int				handle_heredoc(t_cmd *cmd, t_token **token, t_shell *shell);
int				handle_exit(char *res, size_t *j, t_shell *shell);
int				join_last_arg(t_cmd *current, char *val);
int append_heredoc(t_heredoc *tmp);
void    expand_heredoc_line(char **line, t_shell *shell);
int handle_sigint(char *line, char *content, t_shell *shell);
int is_delimiter(char *line, const char *delimiter);
int process_line(t_heredoc *tmp, const char *delimiter, int quoted, t_shell *shell);
void			merge_adjacent_tokens(t_token *tokens);
void			free_cmds(t_cmd *cmds);
t_cmd			*handle_pipe(t_cmd *current);
t_cmd			*build_commands(t_token *tokens);
/* ===================== EXPANDER HELPER =================== */
int				expand_token_value(t_token *t, t_shell *shell);
int				expand_tokens(t_token *tokens, t_shell *shell);
int	ft_intlen(int n);
size_t	handle_var(t_expand_ctx *ctx);
/* ===================== Lexer Helpers ===================== */
t_token			*add_token(t_token **head, t_token_data data);
int				check_scan(int i, t_token **head);
int				scan_word(t_shell *shell, t_scan_ctx *cntx, int i);
int				scan_pipe(t_shell *shell, t_scan_ctx *cntx, int i);
int				scan_redirections(t_shell *shell, t_scan_ctx *cntx, int i);
int				scan_single_quote(t_shell *shell, t_scan_ctx *cntx, int i);
int				scan_double_quote(t_shell *shell, t_scan_ctx *cntx, int i);
/* ===================== Utils ===================== */
void			free_tokens(t_token *head);
void			handle_syntax_error(t_shell *shell, const char *token_str,
					int missing_next);
char			*my_getenv(char *name, char **envp);
void			remove_quotes(t_token *tokens);
/* ====================== helper functions =================== */
int				ft_strcmp_lap(const char *s1, const char *s2);
int				ft_strncmp_lap(const char *s1, const char *s2, size_t n);
int				ft_strlen_lap(const char *s);
int				ft_isalnum_lap(int c);
char			*ft_strcpy_lap(char *dest, const char *src);
char			*ft_strcat_lap(char *dest, const char *src);
char			*ft_strjoin_lap(const char *s1, const char *s2);
char			*ft_strstr_lap(const char *haystack, const char *needle);
char			*ft_replace_lap(char *str, const char *old, const char *niew);
char			*ft_strjoin_free_lap(char *s1, const char *s2);
char			*ft_substr_lap(const char *line, int start, int len);
char			*ft_strncpy_lap(char *dest, char *src, size_t n);
char			*ft_strdup_lap(const char *s);
char			*ft_strndup_lap(const char *s, size_t n);
char			*ft_itoa_lap(int n);
void			*ft_memcpy_lap(void *dest, const void *src, size_t n);

#endif
