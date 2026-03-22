#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>

/* ===================== Token Types ===================== */
typedef enum e_token_type
{
    TOKEN_WORD,               //    0  
    TOKEN_PIPE,              // |   1
    TOKEN_HEREDOC,          // <<   2
    TOKEN_REDIR_IN,          // <   3
    TOKEN_REDIR_OUT,         // >   4
    TOKEN_REDIR_OUT_APPEND,   // >> 5
    TOKEN_NONE = -1           //  special value for parser internal use
}   t_token_type;

/* ===================== Token Struct ===================== */
typedef struct s_token
{
    t_token_type        type;    // token type
    char            *value;  // string value
    int		quoted; // 0 = no quotes 1 = single 2 = double
    struct s_token  *next;   // linked list pointer
}   t_token;

/* ===================== Command Struct ===================== */
typedef struct s_cmd
{
    char        **argv;      // command + args
    char        *infile;     // < infile
    char        *outfile;    // > or >> outfile
    int         append;      // 1 if >>, 0 if >
    char	*heredoc_delim; // << delimter (parser only)
    int		heredoc_quoted; // 1 if delimiter quoted
    char	*heredoc_content; // << content lines
    struct s_cmd *next;      // next command (pipe)
}   t_cmd;

/* ===================== Macro for scan functions ===================== */
#define SCAN_OR_BREAK(scan_call)          \
    do {                                  \
        i = check_scan(scan_call, &head); \
        if (i == -1)                      \
            break;                        \
    } while (0)

#define PARSE_OR_ERROR(call)              \
    do {                                  \
        if ((call)== -1)                      \
            return (NULL);                \
    } while (0)

/* ===================== Lexer / Parser ===================== */
// main lexer
t_token  *lexer(const char * input);  // input string -> linked list of tokens

// parser (syntax check / grouping)
t_cmd    *parser(t_token * tokens,char **envp, int last_exit);

/* ===================== Parser Heleprs ==================== */
t_cmd	*new_cmd(void);
char	**add_args(char **argv, char *word);
int	add_args_cmd(t_cmd *cmd, char *arg);
int	handle_redir_in(t_cmd *cmd, t_token **token);
int	handle_redir_out(t_cmd *cmd, t_token **token);
int	handle_redir_out_append(t_cmd *cmd, t_token **token);
int	handle_heredoc(t_cmd *cmd, t_token **token, int last_exit);
int	expand_tokens(t_token *tokens, char **envp, int last_exit);
void     free_cmds(t_cmd *cmds);
t_cmd	*handle_pipe(t_cmd *current);
t_cmd *build_commands(t_token *tokens);
	
/* ===================== Lexer Helpers ===================== */

t_token  *add_token(t_token **head, t_token_type type, const char *value, int len);
int      check_scan(int i, t_token ** head);           // helper for macro
int      scan_word(const char * input, int i, t_token ** head);
int      scan_pipe(const char * input, int i, t_token ** head);
int      scan_redirections(const char * input, int i, t_token ** head);
int      scan_single_quote(const char * input, int i, t_token ** head);
int      scan_double_quote(const char * input, int i, t_token ** head);

/* ===================== Utils ===================== */
void     free_tokens(t_token * head);
void     print_tokens(t_token * head);
void     print_cmds(t_cmd *cmds);

/* ===================== Later functions ===================== */
//void     *expand_variables(t_token *tokens);
void     remove_quotes(t_token * tokens);
/* ====================== helper functions =================== */
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);
char	*ft_itoa(int n);
int	ft_strcmp(const char *s1, const char *s2);
int ft_strlen(const char *s);
char *ft_strcpy(char *dest, const char *src);
char *ft_strcat(char *dest, const char *src);
char *ft_strjoin(const char *s1, const char *s2);
char    *ft_strstr(const char *haystack, const char *needle);
char    *ft_replace(char *str, const char *old, const char *niew);
char    *ft_strjoin_free(char *s1, const char *s2);
char *ft_substr(const char *line, int start, int len);

#endif
