
#ifndef PROJECTEULERC_LISTS
#define PROJECTEULERC_LISTS

    // Generic doubly linked list structure and functions

    // Use macros to generate list functions for whatever types the list may hold
    #define LINKEDLIST_TYPES(X) \
        X(int16_t,  i16,  %4d) \
        X(uint16_t, ui16, %4u) \
        X(int32_t,  i32,  %6d) \
        X(uint32_t, ui32, %6u) \
        X(int64_t,  i64,  %9lld) \
        X(uint64_t, ui64, %9llu) \
        X(float,    f32,  %.4g) \
        X(double,   f64,  %.8g) 
    
    // Used internally with the LinkedList
    typedef enum _Type {
    #define GEN_ENUM(type, tag, fmt) tag,
        LINKEDLIST_TYPES(GEN_ENUM)
    #undef GEN_ENUM
    } Type;

    /* 
        a node is an element in a linked list,
        holding a void pointer to the data itself, and 
        pointers to the previous and next node   
    */
    typedef struct _Node {
        void* data;
        struct _Node *prev;
        struct _Node *next;
    } Node;

    typedef struct _LinkedList {
        Type type;           // data type of elements in the list
        size_t length;       // number of elements in the list
        size_t data_size;    // data size of each element in the list
        Node *head;          // the head (first) node
        Node *tail;          // the tail (last) node
    } LinkedList;	

    // Functions for linked lists
    LinkedList* create_linked_list(Type type, size_t data_size);

    // Other useful functions that don't require macro wizardry
    Node*      create_node(void *data, size_t data_size);
    void           prepend(LinkedList *list, void *data);
    void            append(LinkedList *list, void *data);
    void              push(LinkedList *list, void *data, int position);
    void       remove_head(LinkedList *list);
    void       remove_tail(LinkedList *list);
    void               pop(LinkedList *list, int position);
    void        remove_all(LinkedList *list);
    void*     get_value_at(LinkedList *list, int position);
    void      set_value_at(LinkedList *list, void *new_data, int position);
    size_t      get_length(LinkedList *list);
    void        print_list(LinkedList *list);

    // Macro wizardry
    #define __GEN_INCR_VALUE_AT(type, tag, fmt) \
        void incr_value_at_##tag(LinkedList *list, type delta, int position);
    LINKEDLIST_TYPES(__GEN_INCR_VALUE_AT)
    
    #define GEN_GENERAL_INCR_VALUE_AT(type, tag, fmt) type: incr_value_at_##tag,
    #define incr_value_at(list, delta, position)                \
        _Generic((delta),                                       \
                 LINKEDLIST_TYPES(GEN_GENERAL_INCR_VALUE_AT)    \
                 default: exit(1)                               \
                )(list, delta, position) 

    #define __GEN_LIST_MAX(type, tag, fmt) \
        type max_##tag(LinkedList *list);
    LINKEDLIST_TYPES(__GEN_LIST_MAX)

    #define GEN_GENERAL_LIST_MAX(type, tag, fmt) type: max_##tag,
    #define get_max_list(list)                              \
        _Generic((list->type),                              \
                 LINKEDLIST_TYPES(GEN_GENERAL_LIST_MAX)     \
                 default: exit(1)                           \
                )(list)

#endif