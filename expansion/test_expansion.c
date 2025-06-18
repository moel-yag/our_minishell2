#include "../includes/minishell.h"
#include "../includes/minishell2.h"
#include "../includes/parsing.h"
#include "../includes/expansion.h"

// Dummy env list for testing
t_env *make_env(const char *name, const char *value)
{
    t_env *env = malloc(sizeof(t_env));
    env->name = strdup(name);
    env->value = strdup(value);
    env->next = NULL;
    return env;
}

void free_env(t_env *env)
{
    while (env)
    {
        t_env *next = env->next;
        free(env->name);
        free(env->value);
        free(env);
        env = next;
    }
}

void print_args(t_token *token)
{
    int i = 0;

    t_token *current = token;
    while (current && current->type != TOKEN_EOF)
    {
        printf("-----Arg[%d]: %s\n", i++, current->value);
        current = current->next; // Move to the next token
    }
}

void test_expansion(const char *input, t_env *env)
{
    printf("\nInput: %s\n", input);
    t_token *tokens = tokenize(input);
    if (!tokens)
    {
        printf("Tokenization failed!\n");
        return;
    }
    t_ast *ast = parser(input);
    if (!ast)
    {
        printf("Parsing failed!\n");
        free_tokens(tokens);
        return;
    }
    print_args(tokens);
    expand(ast, env, tokens);
    printf("After expansion:\n");
    print_args(tokens);
    // free_ast(ast);
    free_tokens(tokens);
}

int main(void)
{
    // Setup environment: HOME=/home/user, USER=test, PATH=/bin:/usr/bin
    t_env *env = make_env("HOME", "/home/user");
    env->next = make_env("USER", "test");
    env->next->next = make_env("PATH", "/bin:/usr/bin");

    test_expansion("echo > $HOME", env);
    test_expansion("        ", env);
    test_expansion("", env);
    test_expansion("echo >> $HOME", env);
    test_expansion("echo << $HOME", env);
    test_expansion("echo > < $HOME", env);
    test_expansion("echo $HOME", env);
    test_expansion("echo $USER", env);
    test_expansion("echo $HOME $USER", env);
    test_expansion("echo \"Hello $USER, home: $HOME\"", env);
    printf("=======================Testing quotes:\n");
    test_expansion("echo '$HOME'", env);
    test_expansion("echo \"$USER\"", env);
    test_expansion("echo $UNSETVAR", env);
    test_expansion("echo $HOME $USER", env);
    test_expansion("echo \"Hello $USER, home: $HOME\" | ls | cat file", env);
    test_expansion("echo 'Hello $USER, home: $HOME'", env);
    test_expansion("echo $PATH", env);

    free_env(env);
    return 0;
}
