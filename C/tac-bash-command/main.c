#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ATTENTION! The program only supports lines up to 1024 characters long

// Define a linked-list node structure named 'line'
struct line {
    char *s;           // Pointer to a dynamically allocated string (the line’s text)
    struct line *next; // Pointer to the next node in the linked list
};
typedef struct line line;

int main(int argc, char **argv) {
    // Check if the user provided exactly one command-line argument (the file name)
    if (argc != 2) {
        printf("Error number of arguments. Insert only one file\n");
        return 1;
    }

    // Try to open the file specified by the user for reading
    FILE *f = fopen(argv[1], "r");
    if (!f) { printf("Error opening file\n"); return 1; }

    char buf[1024]; // Buffer for reading each line from the file
    line *head = NULL; // Pointer to the head (start) of the linked list, initially empty

    // Read each line from the file until EOF
    while (fgets(buf, sizeof(buf), f)) {
        // Allocate memory for a new linked list node
        line *l = malloc(sizeof(line));
        // Check for memory allocation failure
        if (!l) { printf("Malloc failed\n"); return 1; }

        // Allocate memory for the string inside the node
        l->s = malloc(strlen(buf) + 1); // +1 for the null terminator
        if (!l->s) { printf("Malloc failed\n"); return 1; }

        // Copy the contents of 'buf' into the newly allocated string
        strcpy(l->s, buf);

        // Insert the new node at the beginning of the linked list
        l->next = head;
        head = l;
    }

    fclose(f); // Close the file after reading all lines

    // Traverse the linked list and print each stored line in reverse order
    for (line *cur = head; cur; cur = cur->next) {
        printf("%s", cur->s);
    }

    // Free all dynamically allocated memory (both strings and list nodes)
    while (head) {
        line *tmp = head;   // Save pointer to current node
        head = head->next;  // Move to next node before freeing
        free(tmp->s);       // Free the string inside the node
        free(tmp);          // Free the node itself
    }

    return 0;
}
