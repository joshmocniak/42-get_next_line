# 42-get_next_line
Reads the next line from a file descriptor and stores it in *line.

```C
int		get_next_line(const int fd, char **line);
```

Created C function, that when called successively on a file descriptor, reads the next line of characters from a file or input/output resource, into a char buffer.  get_next_line is similar to C Standard Library function getline, but differs in requiring file descriptors instead of file pointers.  get_next_line expects parameter line to be a pointer to a NULL pointer (or pointer that has already been freed).  getline has a similar parameter, linep, but linep can also be a pointer to a malloced buffer.  get_next_line supports interspliced calls on multiple file descriptors.

RETURN VALUE
Returns 1 when a line has been successfully read.  0 when reading has completed.  -1 on error.

