#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

bool is_valid_executable(const char *filename)
{
struct stat sb;
if (stat(filename, &sb) == -1)
{
return (false);
}
return (sb.st_mode & S_IXUSR) != (0);
}
