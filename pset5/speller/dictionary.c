// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include "dictionary.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;

}
node;

// Number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

//counter
int counter = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    node *cursor = table[index];
    while (cursor != NULL)
    {
//if word exists returns true
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
//if not skips to next node
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number using function adapted by Neel Mehta from http://stackoverflow.com/questions/2571683/djb2-hash-function
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;

    for (const char *ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
//opens file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char buffer[45];
//loads into buffer
    while (fscanf(file, "%s", buffer) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        unsigned int index = hash(buffer);
//if unloaded begins process
        if (table[index] == NULL)
        {
            strcpy(n->word, buffer);
            n->next = NULL;
            table[index] = n;
        }
//otherwise continues loading process
        else
        {
            strcpy(n->word, buffer);
            n->next = table[index];
            table[index] = n;
        }
        counter++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (counter != 0)
    {
        return counter;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *temp;
    node *cursor;
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
//sets cursor equal to header
            cursor = table[i];
            while (cursor != NULL)
            {
//sets temp to next node
                temp = cursor->next;
                free(cursor);
//sets cursor to temp location after free
                cursor = temp;
            }
        }
    }
    return true;
}
