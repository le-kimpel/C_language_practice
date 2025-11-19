
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
