#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h> // for loading reasons
#include "etc.h"

/* Note it's probably more efficient and reasonable to do this in Python. However my C skills are rusty and I need to keep in shape. Parses /proc/ pseudofilesystem for the PID associated with a particular process name. */
pid_t loc_process(char *target)
  {
    if (target == NULL)
      {
	return -1;
      }
    // we'll be stepping through /proc/maps to locate
    // the PID by name, returning the PID.
    struct dirent *proc_dir;
    DIR *directory = opendir("/proc/");
    if (directory)
      {
	while((proc_dir = readdir(directory)) != NULL)
	  {
	    if (proc_dir->d_type != DT_DIR)
	      continue;
	    // grab the pid associated with the directory entry in /proc/
	    pid_t pid = atoi(proc_dir->d_name);
	    int pathlen = 10 + strlen(proc_dir->d_name) + 1;
	    char *path = malloc(pathlen * sizeof(char));
	    if (path == NULL)
	      {
		continue;
	      }
	    sprintf(path, "/proc/%s/exe", proc_dir->d_name);
	    path[pathlen-1] = '\0';
	    char * buf = malloc(PATH_MAX * sizeof(char));
	    if (buf == NULL)
	      {
		free(path);
		continue;
	      }
	    ssize_t len = readlink(path, buf, PATH_MAX - 1);
	    if (len == -1)
	      {
		free(path);
		free(buf);
		continue;
	      }
	    buf[len] = '\0';
	    char * name = NULL;
	    char * token = strtok(buf, "/");
	    while (token)
	      {
		name = token;
		token = strtok(NULL, "/");
	      }
	    if (strcmp(name, target) == 0)
	      {
		free(path);
		free(buf);
	      }
	  }
	    closedir(directory);
	  }
	return -1;
      }
