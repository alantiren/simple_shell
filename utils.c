#include "utils.h"
#include <unistd.h>
#include <stdbool.h>

/**
* is_valid_executable - function prototype
* access - system call to check
* filename - exists and is executable by the user
* Description - checks if a string represents valid executable file
* Return : (true) Otherwise, it returns (false)
**/

bool is_valid_executable(const char *filename)
{
if (access(filename, X_OK) == 0)
{
return (true);
}
else
{
return (false);
}
}
