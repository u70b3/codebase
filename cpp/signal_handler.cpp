#include <signal.h>

#include <iostream>

static volatile bool is_running = true;

// sigint sigkill sigterm
static void sigterm_handler(int sig)
{
    std::cout << "Receive Signal: " << sig;
    is_running = false;
}

// sigchild
void sigchld_handler(int sig)
{
    while (waitpid(-1, 0, WNOHANG) > 0)
        ;
    return;
}

int main()
{
    signal(SIGCHLD, sigchld_handler); // child_process exit
    signal(SIGINT, sigterm_handler);  // ctrl -c
    signal(SIGTERM, sigterm_handler); // kill
    signal(SIGKILL, sigterm_handler); // kill -9

    return 0;
}