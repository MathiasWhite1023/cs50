// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

int word_counter = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // firt the for loop set the pointer to the head of the list,
    // and then while it doesn't found the end of it (NULL)
    // it points the pointer to the next field it is the next pointer
    for (node *ptr = table[hash(word)]; ptr != NULL; ptr = ptr->next)
    {
        if (strcasecmp(word, ptr->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    // Read each word in the file
    if (source == NULL)
    {
        return false;
    }
    char buffer[LENGTH + 1];
    while (fscanf(source, "%s", buffer) !=
           EOF) // while it doesn't read the end o the file text (EOF)

    {

        unsigned int index =
            hash(buffer); // a int that is positive = unsigned int / index will store the value
                          // that the hash function gives to make the hash table

        // Add each word to the hash table
        word_counter++;

        node *n = malloc(
            sizeof(node)); // in the loop, n is a new variable each time. When you call malloc, it
                           // allocates
                           // new memory for a new node, and n points to this new memory. Each node
                           // in the linked list is a separate memory allocation, so they don’t
                           // interfere with each other.The linked list uses a new node for each
                           // word. The variable n is just a pointer to the current node you’re
                           // working with. Once you insert the node into the list, you don’t need
                           // to worry about n anymore, because the list keeps track of the nodes.

        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, buffer); // copy the word stored on the buffer to the node

        // insert the node into the hash table
        n->next = table[index]; // sets the new node to the current head of the linked list at
                                // table[index] This effectively inserts the new node at the
                                // beginning of the list.
        table[index] = n;       // updadtes the head of the linked list to point to the new node
                                //  now the new node is the first node in the list
    }

    // Close the dictionary file
    fclose(source);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    for (int t = 0; t < N - 1; t++)
    {
        node *n = table[t];
        while (n != NULL)
        {
            node *next = n->next;
            free(n);
            n = next;
        }
    }
    return true;
}
