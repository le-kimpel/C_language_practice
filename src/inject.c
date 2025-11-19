#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/user.h>
#include <wait.h>
#include "inject.h"

/* Locate a process by name, extract the PID, then use ptrace to overwrite the memory location we have identified and then restore the registers once we decide to nope outta there. Makes use of DL_OPEN to load all the libraries we want.*/ 
void inject(long addr, long free_addr, long dlopen_addr)
{
  // nothing to be done yet
}

int procfs_proc_mem_write(long address, long pid, const char *payload)
{

  char filepath[256];

  snprintf(filepath, sizeof(filepath), "/proc/%ld/mem", pid);

  FILE *file = fopen(filepath, "w+");
  fseek(file, address, SEEK_SET);

  fwrite(payload, sizeof(char), strlen(payload), file);
  fclose(file);

  return 0;
}

int procfs_proc_mem_exec(long address, long pid)
{
  char filepath[256];

  long rip_address = procfs_get_rip(pid);

  snprintf(filepath, sizeof(filepath), "/proc/%ld/mem", pid);

  FILE *file = fopen(filepath, "w+");
  fseek(file, rip_address, SEEK_SET);


  fwrite("\x48\x88", sizeof(char), 2, file);
  fwrite(((unsigned char *)(&address)), sizeof(char), 6, file);
  fwrite("\x00\x00", sizeof(char), 2, file);
  fwrite("\xFF\xe0", sizeof(char), 2, file);

  fclose(file);
  return 0;
}


int main(int argc, char **argv)
{
  /* Usage: ./inject [TARGET_LIBRARY_PATH] [PROC_NAME]*/

  // pull out the commands from the args
  char *command = argv[1];
  char *target_library = argv[2];
  char *target_process = argv[3];
  char *lib_path = realpath(target_library, NULL);

  char *procname = NULL;
  pid_t target_pid = 0;
  
  if (!lib_path)
    {
      fprintf(stderr, "unable to locate \%s\"\n", target_library);
      return 1;
    }
  if (!strcmp(command, "-n"))
    {
      target_pid = loc_process(target_process); 
    }
  return 0;
}
