#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stddef.h>
#include <stdint.h>

#define LINKEDLIST_TYPES(X) \
    X(int8_t,   i8  ) \
    X(uint8_t,  ui8 ) \
    X(int16_t,  i16 ) \
    X(uint16_t, ui16) \
    X(int32_t,  i32 ) \
    X(uint32_t, ui32) \
    X(int64_t,  i64 ) \
    X(uint64_t, ui64) \
    X(float,    f32 ) \
    X(double,   f64 ) 

// Node and LinkedList structures
#define GEN_STRUCTS(type, tag) \
    typedef struct _LinkedList_##tag LinkedList_##tag;   \
    typedef struct _Node_##tag Node_##tag; 
LINKEDLIST_TYPES(GEN_STRUCTS)

// Constructor for linked lists of all types
#define GEN_CREATE_LIST(type, tag) LinkedList_##tag *create_linked_list_##tag(void);
LINKEDLIST_TYPES(GEN_CREATE_LIST)

// Constructors for nodes of all types
#define GEN_CREATE_NODE(type, tag) Node_##tag *create_node_##tag(type data);
LINKEDLIST_TYPES(GEN_CREATE_NODE)

#define LINKEDLIST_STRUCTS(X) \
    X(LinkedList_i8,   i8  )  \
    X(LinkedList_ui8,  ui8 )  \
    X(LinkedList_i16,  i16 )  \
    X(LinkedList_ui16, ui16)  \
    X(LinkedList_i32,  i32 )  \
    X(LinkedList_ui32, ui32)  \
    X(LinkedList_i64,  i64 )  \
    X(LinkedList_ui64, ui64)  \
    X(LinkedList_f32,  f32)  \
    X(LinkedList_f64,  f64)

// Prepend 

#define GEN_PREPEND(type, tag) void prepend_##tag(LinkedList_##tag *list, type data);
LINKEDLIST_TYPES(GEN_PREPEND)

#define PREPEND_CASES(listtype, tag) listtype*: prepend_##tag,
#define prepend(list, data)               \
    _Generic((list),                      \
        LINKEDLIST_STRUCTS(PREPEND_CASES) \
        default: exit(1))(list, data)   


// Append 

#define GEN_APPEND(type, tag) void append_##tag(LinkedList_##tag *list, type data);
LINKEDLIST_TYPES(GEN_APPEND)

#define APPEND_CASES(listtype, tag) listtype*: append_##tag,
#define append(list, data)                \
    _Generic((list),                      \
        LINKEDLIST_STRUCTS(APPEND_CASES)  \
        default: exit(1))(list, data)   


// Push 

#define GEN_PUSH(type, tag) void push_##tag(LinkedList_##tag *list, type data, int position);
LINKEDLIST_TYPES(GEN_PUSH)

#define PUSH_CASES(listtype, tag) listtype*: push_##tag,
#define push(list, data, position)                  \
    _Generic((list),                                \
        LINKEDLIST_STRUCTS(PUSH_CASES)              \
        default: exit(1))(list, data, position)   

// Remove_head 

#define GEN_REMOVE_HEAD(type, tag) void remove_head_##tag(LinkedList_##tag *list);
LINKEDLIST_TYPES(GEN_REMOVE_HEAD)

#define REMOVE_HEAD_CASES(listtype, tag) listtype*: remove_head_##tag,
#define remove_head(list)                        \
    _Generic((list),                             \
        LINKEDLIST_STRUCTS(REMOVE_HEAD_CASES)    \
        default: exit(1))(list)   

// Remove_tail 

#define GEN_REMOVE_TAIL(type, tag) void remove_tail_##tag(LinkedList_##tag *list);
LINKEDLIST_TYPES(GEN_REMOVE_TAIL)

#define REMOVE_TAIL_CASES(listtype, tag) listtype*: remove_tail_##tag,
#define remove_tail(list)                        \
    _Generic((list),                             \
        LINKEDLIST_STRUCTS(REMOVE_TAIL_CASES)    \
        default: exit(1))(list)   

// Pop 

#define GEN_POP(type, tag) void pop_##tag(LinkedList_##tag *list, int position);
LINKEDLIST_TYPES(GEN_POP)

#define POP_CASES(listtype, tag) listtype*: pop_##tag,
#define pop(list, position)                     \
    _Generic((list),                            \
        LINKEDLIST_STRUCTS(POP_CASES)           \
        default: exit(1))(list, position)   

// Free_list 

#define GEN_FREE_LIST(type, tag) void free_list_##tag(LinkedList_##tag *list);
LINKEDLIST_TYPES(GEN_FREE_LIST)

#define FREE_LIST_CASES(listtype, tag) listtype*: free_list_##tag,
#define free_list(list)                         \
    _Generic((list),                            \
        LINKEDLIST_STRUCTS(FREE_LIST_CASES)     \
        default: exit(1))(list)

// Get_at_index 

#define GEN_GET_AT_INDEX(type, tag) type get_at_index_##tag(LinkedList_##tag *list, int position);
LINKEDLIST_TYPES(GEN_GET_AT_INDEX)

#define GET_AT_INDEX_CASES(listtype, tag) listtype*: get_at_index_##tag,
#define get_at_index(list, position)            \
    _Generic((list),                            \
        LINKEDLIST_STRUCTS(GET_AT_INDEX_CASES)  \
        default: exit(1))(list, position)

// Set_at_index 

#define GEN_SET_AT_INDEX(type, tag) void set_at_index_##tag(LinkedList_##tag *list, type data, int position);
LINKEDLIST_TYPES(GEN_SET_AT_INDEX)

#define SET_AT_INDEX_CASES(listtype, tag) listtype*: set_at_index_##tag,
#define set_at_index(list, data, position)      \
    _Generic((list),                            \
        LINKEDLIST_STRUCTS(SET_AT_INDEX_CASES)  \
        default: exit(1))(list, data, position)

// Incr_at_index 

#define GEN_INCR_AT_INDEX(type, tag) void incr_at_index_##tag(LinkedList_##tag *list, type delta, int position);
LINKEDLIST_TYPES(GEN_INCR_AT_INDEX)

#define INCR_AT_INDEX_CASES(listtype, tag) listtype*: incr_at_index_##tag,
#define incr_at_index(list, delta, position)        \
    _Generic((list),                                \
        LINKEDLIST_STRUCTS(INCR_AT_INDEX_CASES)     \
        default: exit(1))(list, delta, position)

// Get_length 

#define GEN_GET_LENGTH(type, tag) size_t get_length_##tag(LinkedList_##tag *list);
LINKEDLIST_TYPES(GEN_GET_LENGTH)

#define GET_LENGTH_CASES(listtype, tag) listtype*: get_length_##tag,
#define get_length(list)                            \
    _Generic((list),                                \
        LINKEDLIST_STRUCTS(GET_LENGTH_CASES)        \
        default: exit(1))(list)

// Print_list 

#define GEN_PRINT_LIST(type, tag) void print_list_##tag(LinkedList_##tag *list);
LINKEDLIST_TYPES(GEN_PRINT_LIST)

#define PRINT_LIST_CASES(listtype, tag) listtype*: print_list_##tag,
#define print_list(list)                            \
    _Generic((list),                                \
        LINKEDLIST_STRUCTS(PRINT_LIST_CASES)        \
        default: exit(1))(list)

// Max_in_list 

#define GEN_MAX_IN_LIST(type, tag) type max_in_list_##tag(LinkedList_##tag *list);
LINKEDLIST_TYPES(GEN_MAX_IN_LIST)

#define MAX_IN_LIST_CASES(listtype, tag) listtype*: max_in_list_##tag,
#define max_in_list(list)                           \
    _Generic((list),                                \
        LINKEDLIST_STRUCTS(MAX_IN_LIST_CASES)       \
        default: exit(1))(list)

#endif
