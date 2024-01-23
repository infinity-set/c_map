#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in a linked list
typedef struct lst_node
{
    char *data; // Character array to store key data
    int length; // Length of the key data
    int alloc;  // Allocated memory for key data
} lst_node;

// Structure to represent an entry in the map
typedef struct MapEntry
{
    char *key;               // Public: Key for the map entry
    int value;               // Public: Value associated with the key
    struct MapEntry *__prev; // Private: Pointer to the previous map entry
    struct MapEntry *__next; // Private: Pointer to the next map entry
} MapEntry;

// Structure to represent an iterator for iterating over map entries
typedef struct MapIterator
{
    MapEntry *__current;                         // Pointer to the current MapEntry
    MapEntry *(*next)(struct MapIterator *self); // Function pointer for getting the next MapEntry
    void (*del)(struct MapIterator *self);       // Function pointer for deleting the MapIterator

} MapIterator;

// Structure to represent a map
typedef struct Map
{
    // Private attributes
    MapEntry *__head; // Head of the map entry linked list
    MapEntry *__tail; // Tail of the map entry linked list
    int __count;      // Count of map entries

    // Public Methods
    void (*put)(struct Map *self, const char *key, int value);        // Add or update a map entry
    int (*get)(struct Map *self, const char *key, int default_value); // Get the value associated with a key
    MapEntry *(*find)(struct MapEntry *self, const char *key);        // Find a map entry by key
    int (*size)(struct Map *self);                                    // Get the size of the map
    void (*print)(struct Map *self);                                  // Print the map entries
    void (*del)(struct Map *self);                                    // Delete the map
    lst_node *(*new_key_node)(const char *key);                       // Create a new key node
    MapIterator *(*iter)(struct Map *self);                           // Create a new iterator

} Map;

// Function prototype declarations
Map *Map_new();                                                      // // Implementation of a new map
void __Map_put(struct Map *self, const char *key, int value);        // Implementation of put method
int __Map_get(struct Map *self, const char *key, int default_value); // Implementation of get method
MapEntry *__Map_find(struct MapEntry *self, const char *key);        // Implementation of find method
lst_node *__Map_new_key_node(const char *key);                       // Implementation of new_key_node method
int __Map_size(struct Map *self);                                    // Implementation of size method
void __Map_del(struct Map *self);                                    // Implementation of del method
void __Map_print(struct Map *self);                                  // Implementation of print method
MapIterator *__Map_iter(struct Map *self);                           // Implementation of iter method
MapEntry *__MapIter_next(MapIterator *self);                         // Implementation of next method
void __MapIter_del(MapIterator *self);                               // Implementation of del method

// Main function
int main()
{
    printf("\nMap Class\n");
    Map *map = Map_new(); // Create a new map
    map->print(map);      // Print the initial map
    map->put(map, "a", 2);
    map->put(map, "b", 7);
    map->print(map); // Print the map after adding entries
    map->put(map, "a", 6);
    map->print(map); // Print the map after updating an entry
    map->put(map, "c", 8);
    map->put(map, "d", 9);
    map->print(map); // Print the map after adding more entries

    printf("\nPrint value of key, else print default value\n");
    printf("a = %d\n", map->get(map, "a", -1));
    printf("a = %d\n", map->get(map, "z", -1));

    printf("\nIterate\n");
    MapIterator *iter = map->iter(map); // Create a new iterator
    while (1)
    {
        MapEntry *current = iter->next(iter); // Get the next map entry
        if (current == NULL)
        {
            break;
        }
        else
        {
            printf("%s = %d\n", current->key, current->value);
        }
    }

    iter->del(iter); // Delete the iterator
    map->del(map);   // Delete the map

    return 0;
}

// Function to create a new Map instance
Map *Map_new()
{
    Map *newMap = (Map *)malloc(sizeof(Map));
    if (newMap == NULL)
    {
        printf("Could not allocate memory!");
        return newMap;
    }
    newMap->__head = NULL;
    newMap->__tail = NULL;
    newMap->__count = 0;

    // Assigning function pointers to methods
    newMap->put = &__Map_put;
    newMap->get = &__Map_get;
    newMap->find = __Map_find; // You don't need the & operator for function pointers.
    newMap->size = &__Map_size;
    newMap->del = &__Map_del;
    newMap->print = &__Map_print;
    newMap->new_key_node = __Map_new_key_node; // You don't need the & operator for function pointers.
    newMap->iter = __Map_iter;                 // You don't need the & operator for function pointers.

    return newMap;
}

// Implementation of the put method
void __Map_put(struct Map *self, const char *key, int value)
{
    // If the map is empty
    if (self->__head == NULL)
    {
        // Create a new map entry
        MapEntry *newEntry = (MapEntry *)malloc(sizeof(MapEntry));
        if (newEntry == NULL)
        {
            printf("Could not allocate memory!");
            self->del(self);
        }
        // Initialize the new map entry
        self->__head = newEntry;
        self->__tail = self->__head;
        lst_node *new_node = self->new_key_node(key);
        newEntry->key = new_node->data;
        newEntry->value = value;
        newEntry->__prev = NULL;
        newEntry->__next = NULL;
        self->__count++;
    }
    else
    {
        // Check if the key already exists
        MapEntry *duplicate = self->find(self->__head, key);
        if (duplicate)
        {
            // Update the value if the key exists
            duplicate->value = value;
        }
        else
        {
            // Create a new map entry
            MapEntry *newEntry = (MapEntry *)malloc(sizeof(MapEntry));
            if (newEntry == NULL)
            {
                printf("Could not allocate memory!");
                self->del(self);
            }
            // Link the new map entry to the tail
            self->__tail->__next = newEntry;
            MapEntry *oldTail = self->__tail;
            self->__tail = newEntry;
            self->__tail->__prev = oldTail;
            self->__tail->__next = NULL;
            // Initialize the new map entry
            lst_node *new_node = self->new_key_node(key);
            self->__tail->key = new_node->data;
            self->__tail->value = value;
            self->__count++;
        }
    }
}

// Implementation of the new_key_node method
lst_node *__Map_new_key_node(const char *key)
{
    // Allocate memory for a new list node
    lst_node *new_node = (lst_node *)malloc(sizeof(lst_node));

    // Check if memory allocation was successful
    if (new_node == NULL)
    {
        printf("Could not allocate memory!");
        return NULL;
    }

    // Initialize the new node attributes
    new_node->alloc = 10;
    new_node->length = 0;
    new_node->data = (char *)calloc(new_node->alloc, sizeof(char));

    // Check if memory allocation for node data was successful
    if (new_node->data == NULL)
    {
        printf("Could not allocate memory!");
        free(new_node); // Free previously allocated memory for the node
        return NULL;
    }

    // Copy characters from the key to the node's data
    if (key != NULL)
    {
        for (int i = 0; key[i] != '\0'; i++)
        {
            if (new_node->length < (new_node->alloc - 1))
            {
                // Move NULL character from array to the next position
                new_node->data[new_node->length + 1] = new_node->data[new_node->length];
                // Place the new character where the "NULL" character used to be
                new_node->data[new_node->length] = key[i];
                // Increment length of array
                new_node->length++;
            }
            else
            {
                // If all positions are filled in the array, copy the array to a new array with "10" more spaces
                new_node->data = (char *)realloc(new_node->data, new_node->alloc + 10);

                // Check if realloc was successful
                if (new_node->data == NULL)
                {
                    printf("Not enough memory!");
                    free(new_node); // Free previously allocated memory for the node
                    return NULL;    // Return an error indicator
                }

                new_node->alloc += 10;
                // Move NULL character from array to the next position
                new_node->data[new_node->length + 1] = new_node->data[new_node->length];
                // Place the new character where the "NULL" character used to be
                new_node->data[new_node->length] = key[i];
                // Increment length of array
                new_node->length++;
            }
        }
    }
    return new_node;
}
// Return the count of elements in the Map
int __Map_size(struct Map *self)
{
    return self->__count;
}

// Get the value associated with the given key; return default_value if key is not found
int __Map_get(struct Map *self, const char *key, int default_value)
{
    // Find the MapEntry associated with the key
    MapEntry *retrieve = __Map_find(self->__head, key);

    // If key is not found, return the default_value
    if (retrieve == NULL)
    {
        return default_value;
    }
    // If key is found, return the value associated with the key
    else
    {
        return retrieve->value;
    }
}

// Find and return the MapEntry associated with the given key
MapEntry *__Map_find(struct MapEntry *self, const char *key)
{
    // Start from the head of the MapEntry linked list
    MapEntry *ptr = self;

    // Iterate through the linked list
    while (ptr != NULL)
    {
        // Check if the current node is not NULL and has valid data
        if (ptr != NULL && ptr->key[0] != '\0')
        {
            int i;
            // Iterate through the characters of both the input string and the node's key
            for (i = 0; key[i] && ptr->key[i]; i++)
            {
                // If characters don't match, break the loop
                if (key[i] != ptr->key[i])
                {
                    break;
                }
            }
            // If both strings match until the end, return the pointer to the node
            if (key[i] == '\0' && ptr->key[i] == '\0')
            {
                return ptr;
            }
        }
        // Move to the next node in the dictionary
        ptr = ptr->__next;
    }
    // Return NULL if the key is not found
    return NULL;
}

// Delete the Map along with its entries
void __Map_del(struct Map *self)
{
    // Check if the Map is not NULL
    if (self != NULL)
    {
        MapEntry *current, *next;
        current = self->__head;

        // Iterate through the MapEntry linked list
        while (current)
        {
            // Free memory allocated for the key of the current MapEntry
            free(current->key);

            // Save the next MapEntry before freeing the current one
            next = current->__next;

            // Free memory allocated for the current MapEntry
            free(current);

            // Move to the next MapEntry
            current = next;
        }

        // Free memory allocated for the Map itself
        free(self);
        self = NULL;
    }
    else
    {
        // Print a message if there is no map to delete
        printf("No map to delete!\n");
    }
}

// Print the contents of the Map
void __Map_print(struct Map *self)
{
    // Check if the Map or its head is NULL
    if (self == NULL || self->__head == NULL)
    {
        // Print Map Count and an empty dictionary if it's empty
        printf("\nMap Count: %d\n{}\n", __Map_size(self));
        return;
    }

    MapEntry *current;

    // Print Map Count
    printf("\nMap Count: %d\n", self->__count);

    // Iterate through the MapEntry linked list and print key-value pairs
    for (current = self->__head; current != NULL; current = current->__next)
    {
        printf("%s = %d\n", current->key, current->value);
    }
}

// Implementation of creating a new MapIterator
MapIterator *__Map_iter(Map *self)
{
    // Allocate memory for a new MapIterator
    MapIterator *iter = (MapIterator *)malloc(sizeof(MapIterator));

    // Check if memory allocation was successful
    if (iter == NULL)
    {
        printf("Could not allocate memory!"); // Print an error message
        self->del(self);                      // Delete the Map to avoid memory leaks
        return NULL;                          // Return NULL as an indicator of failure
    }

    // Set the current MapEntry to the head of the map
    iter->__current = self->__head;

    // Set function pointers for MapIterator operations
    iter->next = &__MapIter_next;
    iter->del = &__MapIter_del;

    return iter; // Return the newly created MapIterator
}

// Implementation of getting the next MapEntry using the MapIterator
MapEntry *__MapIter_next(MapIterator *self)
{
    MapEntry *map_node = self->__current; // Get the current MapEntry

    // Check if the current MapEntry is NULL
    if (map_node == NULL)
    {
        return NULL; // Return NULL to indicate the end of iteration
    }

    // Move to the next MapEntry for the next iteration
    self->__current = self->__current->__next;

    return map_node; // Return the current MapEntry for processing
}

// Implementation of deleting the MapIterator
void __MapIter_del(MapIterator *self)
{
    free(self); // Free the memory allocated for the MapIterator
}
