#ifndef ILIST_H_
#define ILIST_H_

typedef int (*i_func)(int);
typedef int (*i_bifunc)(int, int);

/* Integer Linked List */

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *first;
    Node *last;
    int size;
} IList;

/* Returns true if this list contains some elements. */
extern int is_empty(IList*);

/* Returns true if this list contains no elements. */
extern int is_not_empty(IList*);

/* Returns a empty list. */
extern IList* empty_list();

/* Returns a list containing only the specified object. */
extern IList* single_list_of();

/* Returns a list containing an arbitrary number of elements. */
extern IList* list_of(int, ...);

/* Returns a sequential ordered IList from start (inclusive)
    to end (inclusive) by an incremental step of 1 (or -1). */
extern IList* range(int, int);

/* Returns a sequential ordered IList from start (inclusive)
    to end (inclusive) by a specified step. */
extern IList* range_step(int, int, int);

/* Returns a sequential ordered IList from start (inclusive)
    to end (exclusive) by an incremental step of 1 (or -1). */
extern IList* range_ex(int, int);

/* Returns a sequential ordered IList from start (inclusive)
    to end (exclusive) by a specified step. */
extern IList* range_step_ex(int, int, int);

/* Returns a list of n elements produced by iterative application
    of a function to an initial element. */
extern IList* generate_n(int, i_func, int);

/* Returns a list produced by iterative application of a function
    to an initial element while the condition is satisfied. */
extern IList* generate_while(int, i_func, i_func);

/* Returns a list consisting of n copies of the specified object. */
extern IList* repeat(int, int);

/* Delete the list. */
extern void delete_list(IList**);

/* Returns true if the arguments are equal to each other and false otherwise. */
extern int equals(IList*, IList*);

/* Returns a size of the list. */
extern int get_size(IList*);

/* [Mutator] Pushes an element onto the stack represented by this list.
    (Inserts the specified element at the beginning of this list.) */
extern IList* push(IList*, int);

/* [Mutator] Appends the specified element to the end of this list. */
extern IList* push_back(IList*, int);

/* [Mutator] Inserts the specified element at the position of this list. */
extern IList* insert(IList*, int, int);

/* [Mutator] Pops an element from the stack represented by this list.
    (Removes and returns the first element from this list.) */
extern int pop(IList*);

/* [Mutator] Removes and returns the last element from this list. */
extern int pop_back(IList*);

/* [Mutator] Removes the element at the specified position in this list. */
extern IList* delete(IList*, int);

/* [Mutator] Removes all occurrences of the specified element from this list. */
extern IList* delete_item(IList*, int);

/* [Mutator] Removes the first element from this list. */
extern IList* drop(IList*);

/* [Mutator] Removes the last element from this list. */
extern IList* drop_back(IList*);

/* [Mutator] Removes first n elements from this list. */
extern IList* drop_n(IList*, int);

/* [Mutator] Removes last n elements from this list. */
extern IList* drop_back_n(IList*, int);

/* [Mutator] Removes first elements from this list while the condition is satisfied. */
extern IList* drop_while(IList*, i_func);

/* [Mutator] Removes last elements from this list while the condition is satisfied. */
extern IList* drop_back_while(IList*, i_func);

/* [Mutator] Replaces the element at the specified position in this list
    with the specified value. */
extern IList* update(IList*, int, int);

/* [Mutator] Returns sublist. */
extern IList* sublist(IList*, int, int);

/* Returns a list containing elements of the array. */
extern IList* from_array(int, int*);

/* Returns an array containing elements of the list. */
extern int* to_array(IList*);

/* Performs the given action for each element of the list. */
extern void foreach(IList*, void (*op)(int));

/* Print the list. */
extern void print_list(IList*);

/* Returns new list with elements in reversed order. */
extern IList* reverse(IList*);

/* Returns a first node of the list. */
extern Node* get_first_node(IList*);

/* Returns a last node of the list. */
extern Node* get_last_node(IList*);

/* Returns a node of the list at the specified position. */
extern Node* get_node(IList*, int);

/* Returns a first value of the list. */
extern int get_first(IList*);

/* Returns a last value of the list. */
extern int get_last(IList*);

/* Returns a value of the list at the specified position. */
extern int get(IList*, int);

/* Finds the first element of the list a predicate. */
extern int find(IList*, i_func);

/* Finds the first element of the list a negative predicate. */
extern int find_not(IList*, i_func);

/* Finds the first element of the list a predicate or returns default value. */
extern int find_or(IList*, i_func, int);

/* Finds the first element of the list a negative predicate or returns default value. */
extern int find_not_or(IList*, i_func, int);

/* Returns the index of the first occurrence of the specified element in this list,
    or -1 if this list does not contain the element. */
extern int index_of(IList*, int);

/* Returns the index of the last occurrence of the specified element in this list,
    or -1 if this list does not contain the element. */
extern int last_index_of(IList*, int);

/* Returns a copy of this. */
extern IList* clone(IList*);

/* Returns a list consisting of the results of applying the given function
    to the elements of this list. */
extern IList* map(IList*, i_func);

/* Returns a list consisting of the elements of this list that match the given predicate. */
extern IList* filter(IList*, i_func);

/* Returns a list consisting of the elements of this list that
    match the negation given predicate. */
extern IList* filter_not(IList*, i_func);

/* [Mutator] Appends all of the elements in the second collection to the end of first list. */
extern IList* add_all(IList*, IList*);

/* Returns true if the list contains the specified element. */
extern int contains(IList*, int);

/* Applies a binary operator to a start value and all elements of the list, going left to right. */
extern int fold_left(int, IList*, i_bifunc);

/* Applies a binary operator to all elements of the list, going left to right. */
extern int reduce_left(IList*, i_bifunc);

/* Applies a binary operator to all elements of the list and a start value, going right to left. */
extern int fold_right(int, IList*, i_bifunc);

/* Applies a binary operator to all elements of the list, going right to left. */
extern int reduce_right(IList*, i_bifunc);

/* Selects first n elements. */
extern IList* take(IList*, int);

/* Takes longest prefix of elements that satisfy a predicate. */
extern IList* take_while(IList*, i_func);

/* Selects last n elements. */
extern IList* take_right(IList*, int);

/* Takes longest suffix of elements that satisfy a predicate. */
extern IList* take_right_while(IList*, i_func);

/* Returns a list containing the elements greater than or equal to index from extending up
    to index until of the list. */
extern IList* slice(IList*, int, int);

/* Tests whether a predicate holds for all elements of the list. */
extern int forall(IList*, i_func);

/* Tests whether a predicate holds for at least one element of the list. */
extern int exists(IList*, i_func);

/* Counts the number of elements in the list which satisfy a predicate. */
extern int count(IList*, i_func);

/* Builds a new list from the list without any duplicate elements. */
extern IList* unique(IList*);

/* [Mutator] Returns a list consisting only of the distinct elements (according to ==). */
extern IList* distinct(IList*);

/* [Mutator] Swap values of two elements in the list. */
extern IList* swap(IList*, int, int);

/* Returns true iff the first list is a prefix of the second. */
extern int is_prefix(IList*, IList*);

/* Returns true iff the first list is a suffix of the second. */
extern int is_suffix(IList*, IList*);

/* Returns true iff the first list is a sublist of the second. */
extern int is_sublist(IList*, IList*);

/* Returns a new list containing elements that `interspersed`
    by the element between the elements of the list. */
extern IList* intersperse(IList*, int);

/* Finds the largest element. */
extern int max(IList*);

/* Finds the smallest element. */
extern int min(IList*);

/* Sums up the elements of the list. */
extern int sum(IList*);

#endif
