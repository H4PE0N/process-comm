#include "debug.h"

#include <stdlib.h>
#include <signal.h>
#include <string.h>

void signal_sigint_handler(int sig)
{
  error_print("Keyboard interrupt");

  exit(1);
}

void signal_sigpipe_handler(int sig)
{
  error_print("Pipe has been broken");

  exit(2);
}

void signals_handler_setup(void)
{
  signal(SIGINT, signal_sigint_handler); // Handles SIGINT

  signal(SIGPIPE, signal_sigpipe_handler); // Handles SIGPIPE
}

int main(int argc, char* argv[])
{
  signals_handler_setup();

  char buffer[1024];
  memset(buffer, '\0', sizeof(buffer));

  while(fgets(buffer, sizeof(buffer), stdin) != NULL)
  {
    fputs(buffer, stdout);
    
    memset(buffer, '\0', sizeof(buffer));
  }
  error_print("Input pipe interrupted");

  return 0;
}
