#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
} LinkedList;

LinkedList *createLinkedList() {
    LinkedList *list = malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

void addNode(LinkedList *list, int data) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void deleteNode(LinkedList *list, int data) {
    if (list->head == NULL) {
        return;
    }

    if (list->head->data == data) {
        Node *temp = list->head;
        list->head = list->head->next;
        free(temp);
        return;
    }

    Node *current = list->head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }

    if (current->next != NULL) {
        Node *temp = current->next;
        current->next = current->next->next;
        free(temp);
    }
}

void printList(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    LinkedList *list = createLinkedList();

    addNode(list, 1);
    addNode(list, 2);
    addNode(list, 3);
    addNode(list, 4);

    printf("Initial list: ");
    printList(list);

    deleteNode(list, 3);

    printf("List after deleting 3: ");
    printList(list);

    return 0;
}
