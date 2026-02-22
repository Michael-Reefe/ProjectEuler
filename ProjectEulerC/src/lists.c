#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "lists.h"

/*****************************************
Make the framework for doubly linked lists 
*****************************************/

// Linked List constructor function
LinkedList* create_linked_list(Type type, size_t data_size) {
    assert(data_size > 0);

    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    list->type = type;
    list->length = 0;
    list->data_size = data_size;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

// Node Constructor function given some new data and the size of the data
Node* create_node(void *data, size_t data_size) {

    // sanity checking
    assert(data != NULL);
    assert(data_size > 0);

    // allocate the new node
    Node *new_node = calloc(sizeof(Node), 1);
    assert(new_node);

    // allocate the data inside the node
    new_node->data = malloc(data_size);
    assert(new_node->data);
    memcpy(new_node->data, data, data_size);

    // pointers to previous/next node(s)
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}

// Function to insert a new node at the BEGINNING of a list
void prepend(LinkedList *list, void *data) {
    assert(list != NULL);
    assert(data != NULL);

    Node *node = create_node(data, list->data_size);

    // Increment list size
    list->length++;

    // If this is a new list (head and tail are empty), then
    // we need to set head and tail to the new node
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
        return;
    }

    // Otherwise, we need to replace the current head
    // with node and update the relevant pointers
    node->prev = NULL;
    node->next = list->head;
    list->head->prev = node;
    list->head = node;
}


// Function to insert a new node at the END of a list
void append(LinkedList *list, void *data) {
    assert(list != NULL);
    assert(data != NULL);

    Node *node = create_node(data, list->data_size);

    // Increment list size
    list->length++;

    // If this is a new list (head and tail are empty), then
    // we need to set head and tail to the new node
    if (list->tail == NULL) {
        list->head = node;
        list->tail = node;
        return;
    }

    // Otherwise, we need to replace the current tail
    // with node and update the relevant pointers 
    node->prev = list->tail;
    node->next = NULL;
    list->tail->next = node;
    list->tail = node;
}


// Function to insert a new node at ANY position in the list
void push(LinkedList *list, void *data, int position) {
    assert(list != NULL);
    assert(data != NULL);
    assert(position >= 0 && position <= list->length);

    // if we are inserting at head or tail
    if (position == 0) {
        prepend(list, data);
        return;
    }
    // (this can be list->size because we are inserting AFTER the current last element)
    if (position == list->length) {
        append(list, data);
        return;
    }

    // make the new node and traverse the list up to position
    Node *node = create_node(data, list->data_size);
    Node *pos_node = list->head;
    for (int i = 0; pos_node != NULL && i < position - 1; i++) {
        pos_node = pos_node->next;
    }

    // Insert the new node after the position node
    node->next = pos_node->next;
    node->prev = pos_node;
    if (pos_node->next != NULL) {
        pos_node->next->prev = node;
    }
    pos_node->next = node;

    // Increment size counter
    list->length++;
}

// Function to delete a node from the BEGINNING of the list
void remove_head(LinkedList *list) {
    assert(list != NULL);
    assert(list->head != NULL);
    
    // Move the head to the next position
    Node* last_head = list->head;
    list->head = list->head->next;
    if (list->head != NULL) {
        list->head->prev = NULL;
    }

    // Free the last head (data and node itself) from memory
    free(last_head->data);
    free(last_head);
    last_head = NULL;

    // Decrement size counter
    list->length--;
}

// Function to delete a node from the END of a list
void remove_tail(LinkedList *list) {
    assert(list != NULL);
    assert(list->tail != NULL);

    // Move the tail to the previous position
    Node* last_tail = list->tail;
    list->tail = list->tail->prev;
    if (list->tail != NULL) {
        list->tail->next = NULL;
    }

    // Free the last tail (data and node itself) from memory
    free(last_tail->data);
    free(last_tail);
    last_tail = NULL;

    // Decrement size counter
    list->length--;
}

// Function to delete a node from ANY position in the list
void pop(LinkedList *list, int position) {
    assert(list != NULL);
    assert(list->head != NULL);
    assert(position >= 0 && position <= list->length-1);

    // if we are deleting at head or tail
    if (position == 0) {
        remove_head(list);
        return;
    }
    if (position == list->length-1) {
        remove_tail(list);
        return;
    }

    // traverse the list up to position
    Node* pos_node = list->head;
    for (int i = 0; pos_node != NULL && i < position; i++) {
        pos_node = pos_node->next;
    }

    // Unlink pos_node from the list
    if (pos_node->next != NULL) {
        pos_node->next->prev = pos_node->prev;
    }
    if (pos_node->prev != NULL) {
        pos_node->prev->next = pos_node->next;
    }

    // Free pos_node from memory
    free(pos_node->data);
    free(pos_node);
    pos_node = NULL;

    // Decrement size counter
    list->length--;
}

// Function to fully delete a linked list
void remove_all(LinkedList *list) {
    assert(list != NULL);

    if (list->head != NULL) {
        // loop through the list and free all nodes
        Node* pos_node = list->head;
        while (pos_node != NULL) {
            Node* current_node = pos_node;
            pos_node = pos_node->next;
            free(current_node->data);
            free(current_node);
            current_node = NULL;
            list->length--;
        }
        list->head = NULL;
    }
    free(list);
    list = NULL;

    return;
}

void* get_value_at(LinkedList *list, int position) {
    assert(list != NULL);
    assert(list->head != NULL);
    assert(position >= 0 && position <= list->length-1);
    
    // if we are getting the value at head or tail
    if (position == 0) {
        return list->head->data;
    } 
    if (position == list->length-1) {
        return list->tail->data;
    }

    // traverse the list up to position
    Node* pos_node = list->head;
    for (int i = 0; pos_node != NULL && i < position; i++) {
        pos_node = pos_node->next;
    }

    // Get the value
    return pos_node->data;
}


void set_value_at(LinkedList *list, void *new_data, int position) {     
    assert(list != NULL);                                                                   
    assert(list->head != NULL);                                                             
    assert(position >= 0 && position <= list->length-1);                                      
    assert(new_data != NULL);

    Node *node = NULL;

    if (position == 0) {                                                                    
        node = list->head;
    } else if (position == list->length-1) {                                                         
        node = list->tail;
    } else {
        node = list->head;                                                            
        for (int i = 0; node != NULL && i < position; i++) {                                
            node = node->next;                                                          
        }                                                                                       
    } 

    memcpy(node->data, new_data, list->data_size);
}

#define GEN_INCR_VALUE_AT(type, tag, fmt)                                       \
    void incr_value_at_##tag(LinkedList *list, type delta, int position) {      \
        assert(list != NULL);                                                   \
        assert(list->head != NULL);                                             \
        assert(position >= 0 && position <= list->length-1);                    \
                                                                                \
        Node *node = NULL;                                                      \
                                                                                \
        if (position == 0) {                                                    \
            node = list->head;                                                  \
        } else if (position == list->length-1) {                                \
            node = list->tail;                                                  \
        } else {                                                                \
            node = list->head;                                                  \
            for (int i = 0; node != NULL && i < position; i++) {                \
                node = node->next;                                              \
            }                                                                   \
        }                                                                       \
                                                                                \
        type value = *(type*)node->data;                                        \
        value += delta;                                                         \
        memcpy(node->data, &value, list->data_size);                            \
    }
LINKEDLIST_TYPES(GEN_INCR_VALUE_AT)


// Get the number of elements in the list
size_t get_length(LinkedList *list) {
    return list->length;
}

// Print out the whole list
void print_list(LinkedList *list) {
    assert(list != NULL);
    printf("[ ");
    Node *current = list->head;
    while (current != NULL) {
        switch (list->type) {
            #define GEN_LIST_PRINT_CASES(type, tag, fmt) \
                case (tag):                              \
                    printf(#fmt, *(type*)current->data); \
                    break;
            LINKEDLIST_TYPES(GEN_LIST_PRINT_CASES)
            #undef GEN_LIST_PRINT_CASES
        }
        current = current->next;
    }
    printf("]\n");
}

// Get the maximum (works because all elements in a list must be
// the same type)
#define GEN_LIST_MAX(type, tag, fmt)                                \
    type max_##tag(LinkedList *list) {                              \
        assert(list != NULL);                                       \
        Node *current = list->head;                                 \
        type max_val = *(type*)current->data;                       \
        type current_val = *(type*)current->data;                   \
        while (current != NULL) {                                   \
            current_val = *(type*)current->data;                    \
            if (current_val > max_val) max_val = current_val;       \
            current = current->next;                                \
        }                                                           \
        return max_val;                                             \
    }
LINKEDLIST_TYPES(GEN_LIST_MAX)
