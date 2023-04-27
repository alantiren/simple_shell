#include "utils.h"
#include <unistd.h>
#include <stdbool.h>

/**
* @is_valid_executable - function prototype
* @access - system call to check
* Description - Function for checking if a string represents a valid executable file
* Returns : true. Otherwise, it returns false
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
