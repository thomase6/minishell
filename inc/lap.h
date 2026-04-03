#ifndef LAP_H
#define LAP_H

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./minishell.h"

/* ===================== Token Types ===================== */
typedef enum e_token_type
{
	TOKEN_WORD,             	//      0  
	TOKEN_PIPE,             	// |	1
	TOKEN_HEREDOC,          	// <<	2
	TOKEN_REDIR_IN,         	// <	3
	TOKEN_REDIR_OUT,			// >	4
	TOKEN_REDIR_OUT_APPEND,		// >>	5
	TOKEN_NONE = -1         	// special value for parser internal use
}   t_token_type;

/* ===================== Token Struct ===================== */
typedef struct s_token
{
	t_token_type    type;		// token type
	char            *value;		// string value
	int             quoted;		// 0 = no quotes 1 = single 2 = double
	struct s_token  *next;		// linked list pointer
}   t_token;

/* ===================== Intern helper ================== */
typedef struct s_parser_intern
{
	t_token			**token;
	t_cmd			**cmds;
	int				last_exit;
	t_token_type	*expect;
}	t_parser_intern;

typedef struct s_heredoc
{
	char	*line;
	char	*content;
	char	*new_content;
	size_t	content_len;
	size_t	line_len;
}	t_heredoc;

/* ===================== Macro for scan functions ===================== */
#define SCAN_OR_BREAK(scan_call)			\
	do {									\
		i = check_scan(scan_call, &head);	\
		if (i == -1)						\
			break;							\
	} while (0)

#define PARSE_OR_ERROR(call)				\
	do {									\
		if ((call)== -1)					\
			return (NULL);					\
	} while (0)

/* ===================== Lexer / Parser ===================== */
// main lexer
t_token	*lexer(const char * input);  // input string -> linked list of tokens

// parser (syntax check / grouping)
t_cmd	*parser(t_token * tokens,char **envp, int last_exit);

/* ===================== Parser Heleprs ==================== */
t_cmd	*new_cmd(void);
char	**add_args(char **argv, char *word);
int		add_args_cmd(t_cmd *cmd, char *arg);
int		handle_redir_in(t_cmd *cmd, t_token **token);
int		handle_redir_out(t_cmd *cmd, t_token **token);
int		handle_redir_out_append(t_cmd *cmd, t_token **token);
int		handle_heredoc(t_cmd *cmd, t_token **token, int last_exit);
int		expand_tokens(t_token *tokens, char **envp, int last_exit);
void	free_cmds_lap(t_cmd *cmds);
t_cmd	*handle_pipe(t_cmd *current);
t_cmd	*build_commands(t_token *tokens);
	
/* ===================== Lexer Helpers ===================== */

t_token	*add_token(t_token **head, t_token_type type, const char *value, int len);
int		check_scan(int i, t_token ** head);           // helper for macro
int		scan_word(const char * input, int i, t_token ** head);
int		scan_pipe(const char * input, int i, t_token ** head);
int		scan_redirections(const char * input, int i, t_token ** head);
int		scan_single_quote(const char * input, int i, t_token ** head);
int		scan_double_quote(const char * input, int i, t_token ** head);

/* ===================== Utils ===================== */
void	free_tokens(t_token * head);
// void	print_tokens(t_token * head);
// void	print_cmds(t_cmd *cmds);

/* ===================== Later functions ===================== */
//void     *expand_variables(t_token *tokens);
void	remove_quotes(t_token * tokens);
/* ====================== helper functions =================== */
char	*ft_strdup_lap(const char *s);
char	*ft_strndup(const char *s, size_t n);
char	*ft_itoa_lap(int n);
int		ft_strcmp_lap(const char *s1, const char *s2);
int		ft_strlen_lap(const char *s);
char	*ft_strcpy_lap(char *dest, const char *src);
char	*ft_strcat_lap(char *dest, const char *src);
char	*ft_strjoin_lap(const char *s1, const char *s2);
char	*ft_strstr_lap(const char *haystack, const char *needle);
char	*ft_replace(char *str, const char *old, const char *niew);
char	*ft_strjoin_free(char *s1, const char *s2);
char	*ft_substr_lap(const char *line, int start, int len);
void	*ft_memcpy_lap(void *dest, const void *src, size_t n); // add function

#endif
