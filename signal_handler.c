#include "shell.h"

/**
 * sigint_handler - handles the SIGINT signal
 * @sig: signal number
 */
void sigint_handler(int sig)
{
    (void)sig;
    signal(SIGINT, sigint_handler);
    _putchar('\n');
    print_prompt();
    fflush(stdout);
}

/**
 * sigquit_handler - handles the SIGQUIT signal
 * @sig: signal number
 */
void sigquit_handler(int sig)
{
    (void)sig;
    signal(SIGQUIT, sigquit_handler);
    _putchar('\n');
    fflush(stdout);
}

/**
 * set_signal_handlers - sets signal handlers for SIGINT and SIGQUIT
 */
void set_signal_handlers(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);
}
