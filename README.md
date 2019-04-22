# 42-get_next_line
Created a C function that reads the next line of characters from a file descriptor.
A file descriptor is an abstract reference to a file or input/output resource.

```C
int		get_next_line(const int fd, char **line);
```

get_next_line reads the next line from fd and updates *line with a pointer to a character string.  get_next_line is similar to C Standard Library function getline, but differs in requiring file descriptors instead of file pointers.  get_next_line expects parameter line to be a pointer to a NULL pointer (or pointer that has already been freed).  getline has a similar parameter, linep, but linep can also be a pointer to a malloced buffer.  get_next_line supports interspliced calls on multiple file descriptors.

RETURN VALUE\
Returns 1 when a line has been successfully read.  0 when reading has completed.  -1 on error.

Getting Started
---------------
1. Clone the repo and fetch 42-libft submodule  
  `git clone --recurse-submodules https://github.com/joshmocniak/42-get_next_line.git`  
2. Compile 42-libft  
  `cd 42-get_next_line/42-libft`  
  `make`  
  `cd ..`  
3. Compile and run project that uses get_next_line  
  `gcc -I 42-libft get_next_line.c test_project.c -o test_project`  
  `./test_project`  

test_project.c
--------------

```C
#include "get_next_line.h"


void  print_and_free(char **line)
{
  //placeholder
}

int   main(void)
{
  int   fd0 = 0; //stdin
  int   fd1;
  int   fd2;
  int   ret;
  char  *line = NULL;
  
  fd1 = open('file.txt', O_RDONLY);
  fd2 = open('anotherfile.txt', O_RDONLY);
  
  ret = get_next_line(fd, &line);
  //placeholder
  close(fd);
  return (0);
}

```
