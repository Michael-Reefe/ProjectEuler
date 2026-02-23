
#ifndef LL_TYPE
#error "LL_TYPE must be defined"
#endif

#ifndef LL_TAG
#error "LL_TAG must be defined"
#endif

#ifndef LL_FMT
#error "LL_FMT must be defined"
#endif

// Generic doubly linked list structure and functions
#define CONCAT_HIDDEN(a, b) a##_##b
#define CONCAT(a, b) CONCAT_HIDDEN(a, b)

#define NODE_NAME CONCAT(Node, LL_TAG)
#define _NODE_NAME CONCAT(_Node, LL_TAG)
#define LIST_NAME CONCAT(LinkedList, LL_TAG)
#define _LIST_NAME CONCAT(_LinkedList, LL_TAG)

/* 
    A node is an element in a linked list,
    holding a Number (the data itself), and 
    pointers to the previous and next node   
*/
typedef struct _NODE_NAME {
    LL_TYPE data;
    struct _NODE_NAME *prev;
    struct _NODE_NAME *next;
} NODE_NAME;

typedef struct _LIST_NAME {
    size_t length;
    NODE_NAME *head;
    NODE_NAME *tail;
} LIST_NAME;

// Linked List constructor function
LIST_NAME *CONCAT(create_linked_list, LL_TAG)() {
    LIST_NAME *list = (LIST_NAME*)malloc(sizeof(LIST_NAME));
    assert(list);
    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

// Node constructor function
NODE_NAME *CONCAT(create_node, LL_TAG)(LL_TYPE data) {
    NODE_NAME *node = (NODE_NAME*)malloc(sizeof(NODE_NAME));
    assert(node);
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// Prepend to the BEGINNING of the list
void CONCAT(prepend, LL_TAG)(LIST_NAME *list, LL_TYPE data) {
    assert(list != NULL);

    // Initialize a new node with the given data
    NODE_NAME *node = CONCAT(create_node, LL_TAG)(data);

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

// Append to the END of a list
void CONCAT(append, LL_TAG)(LIST_NAME *list, LL_TYPE data) {
    assert(list != NULL);

    // Initialize the new node
    NODE_NAME *node = CONCAT(create_node, LL_TAG)(data);

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
void CONCAT(push, LL_TAG)(LIST_NAME *list, LL_TYPE data, int position) {
    assert(list != NULL);
    assert(position >= 0 && position <= list->length);

    // if we are inserting at head or tail
    if (position == 0) {
        CONCAT(prepend, LL_TAG)(list, data);
        return;
    }
    // (this can be list->size because we are inserting AFTER the current last element)
    if (position == list->length) {
        CONCAT(append, LL_TAG)(list, data);
        return;
    }
    NODE_NAME *node = CONCAT(create_node, LL_TAG)(data);

    // make the new node and traverse the list up to position
    NODE_NAME *pos_node = list->head;
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
void CONCAT(remove_head, LL_TAG)(LIST_NAME *list) {
    assert(list != NULL);
    assert(list->head != NULL);
    
    // Move the head to the next position
    NODE_NAME *last_head = list->head;
    list->head = list->head->next;
    if (list->head != NULL) {
        list->head->prev = NULL;
    }

    // Free the last head (data and node itself) from memory
    free(last_head);
    last_head = NULL;

    // Decrement size counter
    list->length--;
}

// Function to delete a node from the END of a list
void CONCAT(remove_tail, LL_TAG)(LIST_NAME *list) {
    assert(list != NULL);
    assert(list->tail != NULL);

    // Move the tail to the previous position
    NODE_NAME *last_tail = list->tail;
    list->tail = list->tail->prev;
    if (list->tail != NULL) {
        list->tail->next = NULL;
    }

    // Free the last tail (data and node itself) from memory
    free(last_tail);
    last_tail = NULL;

    // Decrement size counter
    list->length--;
}

// Function to delete a node from ANY position in the list
void CONCAT(pop, LL_TAG)(LIST_NAME *list, int position) {
    assert(list != NULL);
    assert(list->head != NULL);
    assert(position >= 0 && position <= list->length-1);

    // if we are deleting at head or tail
    if (position == 0) {
        CONCAT(remove_head, LL_TAG)(list);
        return;
    }
    if (position == list->length-1) {
        CONCAT(remove_tail, LL_TAG)(list);
        return;
    }

    // traverse the list up to position
    NODE_NAME *pos_node = list->head;
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
    free(pos_node);
    pos_node = NULL;

    // Decrement size counter
    list->length--;
}

// Function to fully delete a linked list
void CONCAT(free_list, LL_TAG)(LIST_NAME *list) {
    assert(list != NULL);

    if (list->head != NULL) {
        // loop through the list and free all nodes
        NODE_NAME *pos_node = list->head;
        while (pos_node != NULL) {
            NODE_NAME *current_node = pos_node;
            pos_node = pos_node->next;
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

// Getter at index
LL_TYPE CONCAT(get_at_index, LL_TAG)(LIST_NAME *list, int position) {
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
    NODE_NAME *pos_node = list->head;
    for (int i = 0; pos_node != NULL && i < position; i++) {
        pos_node = pos_node->next;
    }

    // Get the value
    return pos_node->data;
}

// Setter at index
void CONCAT(set_at_index, LL_TAG)(LIST_NAME *list, LL_TYPE data, int position) {     
    assert(list != NULL);                                                                   
    assert(list->head != NULL);                                                             
    assert(position >= 0 && position <= list->length-1);                                      

    if (position == 0) {                                                                    
        list->head->data = data;
        return;
    }
    if (position == list->length-1) {                                                         
        list->tail->data = data;
        return;
    } 
    
    NODE_NAME *node = list->head;                                                            
    for (int i = 0; node != NULL && i < position; i++) {                                
        node = node->next;                                                          
    }                                                                                       

    node->data = data;
}

// Incrementer at index
void CONCAT(incr_at_index, LL_TAG)(LIST_NAME *list, LL_TYPE delta, int position) {     
    assert(list != NULL);                                                                   
    assert(list->head != NULL);                                                             
    assert(position >= 0 && position <= list->length-1);                                      

    if (position == 0) {                                                                    
        list->head->data += delta;
        return;
    }
    if (position == list->length-1) {                                                         
        list->tail->data += delta;
        return;
    } 
    
    NODE_NAME *node = list->head;                                                            
    for (int i = 0; node != NULL && i < position; i++) {                                
        node = node->next;                                                          
    }                                                                                       

    node->data += delta;
}

// Get the number of elements in the list
size_t CONCAT(get_length, LL_TAG)(LIST_NAME *list) {
    return list->length;
}

// Print out the whole list
void CONCAT(print_list, LL_TAG)(LIST_NAME *list) {
    assert(list != NULL);
    printf("[ ");
    NODE_NAME *current = list->head;
    while (current != NULL) {
        printf(LL_FMT, current->data);
        printf(" ");
        current = current->next;
    }
    printf("]\n");
}

// Get the maximum number in the list
LL_TYPE CONCAT(max_in_list, LL_TAG)(LIST_NAME *list) {
    assert(list != NULL);
    assert(list->head != NULL);
    LL_TYPE maxval = list->head->data;
    LL_TYPE curval = list->head->data;
    NODE_NAME *cur_node = list->head->next;
    while (cur_node != NULL) {
        curval = cur_node->data;
        if (curval > maxval) maxval = curval;
        cur_node = cur_node->next;
    }
    return maxval;
}

#undef NODE_NAME 
#undef _NODE_NAME 
#undef LIST_NAME 
#undef _LIST_NAME 
#undef LL_TYPE
#undef LL_TAG
#undef LL_FMT
