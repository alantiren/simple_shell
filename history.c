-#include "shell.h"

/**
 * add_history - Add a command to the history.
 * @hist: The history.
 * @cmd: The command to add.
 *
 * Return: On success, 0. On failure, -1.
 */
int add_history(history_t *hist, char *cmd)
{
    history_t *new_node;

    new_node = malloc(sizeof(history_t));
    if (!new_node)
        return (-1);

    new_node->cmd = strdup(cmd);
    if (!new_node->cmd) {
        free(new_node);
        return (-1);
    }

    new_node->prev = NULL;
    new_node->next = hist->head;

    if (hist->head)
        hist->head->prev = new_node;

    hist->head = new_node;
    hist->count++;

    return (0);
}

/**
 * print_history - Print the history.
 * @hist: The history.
 */
void print_history(history_t *hist)
{
    history_t *node;

    for (node = hist->head; node; node = node->next)
        printf("%d %s\n", node->num, node->cmd);
}

/**
 * free_history - Free the history.
 * @hist: The history.
 */
void free_history(history_t *hist)
{
    history_t *node, *next;

    for (node = hist->head; node; node = next) {
        next = node->next;
        free(node->cmd);
        free(node);
    }
}

/**
 * save_history - Save the history to a file.
 * @hist: The history.
 * @filename: The name of the file to save to.
 *
 * Return: On success, 0. On failure, -1.
 */
int save_history(history_t *hist, const char *filename)
{
    FILE *fp;
    history_t *node;

    fp = fopen(filename, "w");
    if (!fp)
        return (-1);

    for (node = hist->head; node; node = node->next)
        fprintf(fp, "%s\n", node->cmd);

    fclose(fp);
    return (0);
}

/**
 * load_history - Load the history from a file.
 * @hist: The history.
 * @filename: The name of the file to load from.
 *
 * Return: On success, 0. On failure, -1.
 */
int load_history(history_t *hist, const char *filename)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int line_num = 0;

    fp = fopen(filename, "r");
    if (!fp)
        return (-1);

    while ((read = getline(&line, &len, fp)) != -1) {
        line_num++;

        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        if (add_history(hist, line) != 0) {
            fprintf(stderr, "load_history: failed to add line %d to history\n", line_num);
            free(line);
            fclose(fp);
            return (-1);
        }
    }

    free(line);
    fclose(fp);
    return (0);
}
