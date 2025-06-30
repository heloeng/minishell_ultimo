
#include "minishell.h"

void handle_ctrlc(int sig)
{
    
    (void)sig;

    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void configure_signal()
{
    signal(SIGINT, handle_ctrlc);
    signal(SIGQUIT, SIG_IGN);
}
