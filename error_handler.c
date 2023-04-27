#include "shell.h"

/**
 * error_handler - Handles errors for the shell
 * @error_code: The error code to handle
 * @cmd: The command that caused the error
 * @line_number: The line number that caused the error
 */
void error_handler(int error_code, char *cmd, int line_number)
{
    switch (error_code)
    {
        case UNKNOWN:
            fprintf(stderr, "%s: %d: %s: Unknown error\n", program_name, line_number, cmd);
            break;
        case NO_FILE:
            fprintf(stderr, "%s: %d: %s: No such file or directory\n", program_name, line_number, cmd);
            break;
        case NO_PERM:
            fprintf(stderr, "%s: %d: %s: Permission denied\n", program_name, line_number, cmd);
            break;
        case BAD_CMD:
            fprintf(stderr, "%s: %d: %s: command not found\n", program_name, line_number, cmd);
            break;
        case NOT_DIR:
            fprintf(stderr, "%s: %d: %s: Not a directory\n", program_name, line_number, cmd);
            break;
        case NO_MEM:
            fprintf(stderr, "%s: %d: %s: Not enough memory\n", program_name, line_number, cmd);
            break;
        case NOT_SET:
            fprintf(stderr, "%s: %d: %s: Variable not set\n", program_name, line_number, cmd);
            break;
        default:
            fprintf(stderr, "%s: %d: %s: Unknown error\n", program_name, line_number, cmd);
            break;
    }
}
