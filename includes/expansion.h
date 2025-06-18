#ifndef EXPANSION_H
#define EXPANSION_H

#include "minishell.h"
#include "parsing.h"
#include "minishell2.h"

void expand(t_ast *ast, t_env *env, t_token *token);
// char *expand_arg(const char *arg, t_env *env);
char *get_env_value(t_env *env, const char *var_name);
int mask_len(t_token *token);
t_env *make_env(const char *name, const char *value);
void free_env(t_env *env);
void print_args(t_token *args);
void test_expansion(const char *input, t_env *env);

#endif // EXPANSION_H