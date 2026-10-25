*This project has been created as part of the 42 curriculum by balsaray.*

# get_next_line

## Description

`get_next_line` is a C function that reads from a file descriptor and returns one line at a time:

```c
char	*get_next_line(int fd);
```

Each call returns the next line, including the terminating `\n` (unless the file ends without one). It returns `NULL` when there is nothing left to read or when an error occurs. It works with regular files and with standard input.

The goal of the project is to learn about **static variables**, file descriptors, `read()`, and careful dynamic memory management in C.

The **bonus** part handles multiple file descriptors at the same time using a single static variable. You can switch between fds 3, 4 and 5 from one call to the next without losing each fd's reading state.

## Instructions

### Files

| Mandatory | Bonus |
|---|---|
| `get_next_line.c` | `get_next_line_bonus.c` |
| `get_next_line_utils.c` | `get_next_line_utils_bonus.c` |
| `get_next_line.h` | `get_next_line_bonus.h` |

### Compilation

Include the header in your program and compile it with the sources. `BUFFER_SIZE` sets how many bytes each `read()` call reads (it defaults to 100 if not defined):

```bash
# mandatory
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

# bonus
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```

### Usage example

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

Each returned line is heap-allocated, so the caller must `free()` it.

## Algorithm

The function keeps a **static buffer** (`buff`) holding whatever has been read but not yet returned. The work is split into three steps:

1. **`readbuff(fd, buff)`: read until a line is complete.**
   Allocate a temporary buffer of `BUFFER_SIZE + 1` bytes. Then keep calling `read()` and appending each chunk to `buff` with `ft_strjoin`, until `buff` contains a `\n` or `read()` returns 0 (end of file). If `read()` returns -1, everything is freed and `NULL` is returned.

2. **`getreqline(buff)`: extract the line.**
   Count characters up to and including the first `\n` (or to the end of the string). Then allocate a new string and copy that part of `buff` into it. If `buff` is empty, there is no line, so it returns `NULL`.

3. **`remainings(line, buff)`: keep the rest.**
   Skip the part of `buff` that was just returned and `ft_strdup` what's left into a new buffer. The old `buff` is freed. If nothing is left, `buff` becomes `NULL`.

The static `buff` then holds the leftover text for the next call.

### Why this approach

- **It reads as little as possible.** Reading stops as soon as a `\n` is in the buffer, so the whole file is never loaded at once, as the subject requires.
- **A static variable** is the simplest way to remember leftover data between calls without using a global variable, which is forbidden.
- **Any `BUFFER_SIZE` works**, from 1 to 10,000,000, because chunks are joined until a full line is available, however the line is split across reads.
- **No leaks on any path.** Every error path (failed `read()`, failed `malloc`) frees the static buffer and returns `NULL`. `freebuff()` frees a pointer and returns `NULL` in one step, which keeps these paths short.
- **Bonus:** the single static variable becomes an array, `static char *buff[1024]`, indexed by fd. Each descriptor keeps its own leftover buffer, so reading from several fds in turns works independently. Fds outside `0–1023` are rejected.

## Resources

- `man 2 read`, `man 3 malloc`, `man 3 free`
- [Static variables in C – GeeksforGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)
- [File descriptors – Wikipedia](https://en.wikipedia.org/wiki/File_descriptor)
- The 42 Norm (norminette) documentation
- Valgrind documentation for leak checking: https://valgrind.org/docs/manual/quick-start.html

### AI usage

AI (Claude) was used **after** the implementation was written, to review the project:
- **Understanding concepts:** explanations of static variables and how they keep their value between calls, file descriptors and how `read()` works, defining `BUFFER_SIZE` at compile time with `-D` and `#ifndef`, include guards, and managing heap memory to avoid leaks.
- **Tooling:** help with compiler error messages, fixing norminette formatting errors, finding a memory leak in `readbuff` with valgrind, and testing with different `BUFFER_SIZE` values and edge-case files.
- making test cases with several `BUFFER_SIZE` values, edge-case files, and valgrind
- drafting this README

