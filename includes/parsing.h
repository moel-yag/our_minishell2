#ifndef PARSING_H
#define PARSING_H

#include "minishell2.h"
#include "minishell.h"

typedef struct s_redir
{
    int type; // Type of redirection (e.g., input, output, append)
    char *filename; // Filename for the redirection
}            t_redir;

typedef struct  s_ast
{
    t_list *args; // List of arguments
    t_list *redirections; // List of redirections
    struct s_ast *next; // Pointer to the next command in the pipeline
}               t_ast;

t_ast *parser(const char *input);
t_token *tokenize(const char *input);
void free_ast(t_ast *ast);
void free_ast_list(t_ast *head);
void add_ast_node(t_ast **head, t_ast *new_node);
char *ft_token_gettype(t_token_type type);
bool ft_token_is_redirection(t_token_type type);
void print_ast(t_ast *ast);
void ft_lst_push(t_list **head, void *value);
void add_token(t_token **head, t_token *new_token);
void free_tokens(t_token *head);
t_token *tokenize_input(const char *input);
bool unclosed_quotes(const char *input);
void print_tokens(t_token *tokens);

#endif // PARSING_H