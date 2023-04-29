#include "main.h"

/**
 * a_alias_e - Adds a node to the end of a alias_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @name: The name of the new alias to be added.
 * @v: The value of the new alias to be added.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
aliases_t *a_alias_e(aliases_t **head, char *name, char *v)
{
	aliases_t *new_node = malloc(sizeof(aliases_t));
	aliases_t *last;

	if (!new_node)
		return (NULL);

	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (str_len(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->v = v;
	str_cpy(new_node->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * a_node_e - Adds a node to the end of a list_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @dir: The directory path for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
lists_t *a_node_e(lists_t **head, char *dir)
{
	lists_t *new_node = malloc(sizeof(lists_t));
	lists_t *last;

	if (!new_node)
		return (NULL);

	new_node->dir = dir;
	new_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * f_alias_l - Frees a alias_t linked list.
 * @head: THe head of the alias_t list.
 */
void f_alias_l(aliases_t *head)
{
	aliases_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->v);
		free(head);
		head = next;
	}
}

/**
 * f_list - Frees a list_t linked list.
 * @head: The head of the list_t list.
 */
void f_list(lists_t *head)
{
	lists_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
