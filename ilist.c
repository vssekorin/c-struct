#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "ilist.h"

int is_empty(IList *list) {
    return list->size == 0;
}

int is_not_empty(IList *list) {
    return list->size != 0;
}

IList* empty_list() {
    IList *list = (IList*) malloc(sizeof(IList));
    list->size = 0;
    return list;
}

IList* single_list_of(int value) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    IList *list = (IList*) malloc(sizeof(IList));
    list->first = node;
    list->last = node;
    list->size = 1;
    return list;
}

IList* list_of(int count, ...) {
    va_list items;
    va_start(items, count);
    IList *list = (IList*) malloc(sizeof(IList));
    for (int i = 0; i < count; i++) {
        push_back(list, va_arg(items, int));
    }
    va_end(items);
    return list;
}

IList* range(int first, int last) {
    return range_step(first, last, first < last ? 1 : -1);
}

IList* range_step(int first, int last, int step) {
    IList *list = empty_list();
    if (step > 0) {
        for (int i = first; i <= last; i += step) {
            push_back(list, i);
        }
    } else {
        for (int i = first; i >= last; i += step) {
            push_back(list, i);
        }
    }
    return list;
}

IList* range_ex(int first, int last) {
    return range_step_ex(first, last, first < last ? 1 : -1);
}

IList* range_step_ex(int first, int last, int step) {
    IList *list = empty_list();
    if (step > 0) {
        for (int i = first; i < last; i += step) {
            push_back(list, i);
        }
    } else {
        for (int i = first; i > last; i += step) {
            push_back(list, i);
        }
    }
    return list;
}

IList* generate_n(int start, i_func op, int count) {
    IList *list = empty_list();
    for (int cur = start, i = 0; i < count; cur = op(cur), i++) {
        push_back(list, cur);
    }
    return list;
}

IList* generate_while(int start, i_func op, i_func cond) {
    IList *list = empty_list();
    for (int cur = start; cond(cur); cur = op(cur)) {
        push_back(list, cur);
    }
    return list;
}

IList* repeat(int value, int count) {
    IList *list = empty_list();
    for (int i = 0; i < count; i++) {
        push(list, value);
    }
    return list;
}

void delete_list(IList **list) {
    if (is_not_empty(*list)) {
        Node *node;
        while ((*list)->first->next) {
            node = (*list)->first;
            (*list)->first = (*list)->first->next;
            free(node);
        }
        free((*list)->first);
    }
    free(*list);
}

int equals(IList *fst, IList *snd) {
    if (fst->size != snd->size) {
        return 0;
    }
    for (Node *c1 = fst->first, *c2 = snd->first; c1->next || c2->next; c1 = c1->next, c2 = c2->next) {
        if (c1 == NULL && c2 != NULL || c1 != NULL && c2 == NULL || c1->value != c2->value) {
            return 0;
        }
    }
    return 1;
}

int get_size(IList *list) {
    return list->size;
}

IList* push(IList* list, int value) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->value = value;
    if (is_empty(list)) {
        list->last = node;
    } else {
        node->next = list->first;
    }
    list->first = node;
    list->size++;
}

IList* push_back(IList* list, int value) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    if (is_empty(list)) {
        list->first = node;
    } else {
        list->last->next = node;
    }
    list->last = node;
    list->size++;
    return list;
}

IList* insert(IList *list, int pos, int value) {
    if (pos == 0) {
        push(list, value);
    } else if (pos == list->size) {
        push_back(list, value);
    } else {
        Node *node = (Node*) malloc(sizeof(Node));
        node->value = value;
        Node *prev = get_node(list, pos - 2);
        node->next = prev->next;
        prev->next = node;
        list->size++;
    }
    return list;
}

int pop(IList *list) {
    int value = list->first->value;
    drop(list);
    return value;
}

int pop_back(IList *list) {
    int value = list->last->value;
    drop_back(list);
    return value;
}

IList* delete(IList *list, int pos) {
    Node *prev = get_node(list, pos - 1);
    Node *del = prev->next;
    prev->next = del->next;
    free(del);
    return list;
}

IList* delete_item(IList *list, int value) {
    int index = index_of(list, value);
    while (index != -1) {
        delete(list, index);
        index = index_of(list, value);
    }
    return list;
}

IList* drop(IList *list) {
    Node *node = list->first;
    if (list->size == 1) {
        list->last = NULL;
    }
    list->first = node->next;
    list->size--;
    free(node);
    return list;
}

IList* drop_back(IList *list) {
    Node *node = list->last;
    if (list->size == 1) {
        list->first = NULL;
        list->last = NULL;
    } else {
        Node *prev = get_node(list, list->size - 2);
        prev->next = NULL;
        list->last = prev;
    }
    list->size--;
    free(node);
    return list;
}

IList* drop_n(IList *list, int n) {
    for (int i = 0; i < n && i < list->size - 1; i++) {
        drop(list);
    }
    return list;
}

IList* drop_back_n(IList *list, int n) {
    for (int i = 0; i < n && i < list->size - 1; i++) {
        drop_back(list);
    }
    return list;
}

IList* drop_while(IList *list, i_func pred) {
    while (list->first && pred(list->first->value)) {
        drop(list);
    }
    return list;
}

IList* drop_back_while(IList *list, i_func pred) {
    while (list->last && pred(list->last->value)) {
        drop_back(list);
    }
    return list;
}

IList* update(IList *list, int pos, int value) {
    get_node(list, pos)->value = value;
    return list;
}

IList* sublist(IList *list, int start, int end) {
    for (int i = 0; i < list->size - end; i++) {
        drop_back(list);
    }
    for (int i = 0; i < start; i++) {
        drop(list);
    }
    return list;
}

IList* from_array(int size, int *arr) {
    IList *result = empty_list();
    if (arr == NULL || size == 0) {
        return result;
    }
    for (int i = 0; i < size; i++) {
        push_back(result, arr[i]);
    }
    return result;
}

int* to_array(IList *list) {
    int ind = 0;
    int *arr = (int*) malloc(list->size * sizeof(int));
    for (Node *cur = list->first; cur; cur = cur->next) {
        arr[ind++] = cur->value;
    }
    return arr;
}

void foreach(IList *list, void (*op)(int)) {
    for (Node *cur = list->first; cur; cur = cur->next) {
        op(cur->value);
    }
}

void print_list(IList *list) {
    printf("IList %p : [", list);
    if (is_not_empty(list)) {
        for (Node *cur = list->first; cur, cur->next; cur = cur->next) {
            printf("%d, ", cur->value);
        }
        printf("%d", list->last->value);
    }
    printf("]\n");
}

IList* reverse(IList *list) {
    IList *result = empty_list();
    for (Node *cur = list->first; cur; cur = cur->next) {
        push(result, cur->value);
    }
    return result;
}

Node* get_first_node(IList *list) {
    return list->first;
}

Node* get_last_node(IList *list) {
    return list->last;
}

Node* get_node(IList *list, int index) {
    if (index == 0) {
        return get_first_node(list);
    } else if (index == list->size - 1) {
        return get_last_node(list);
    } else {
        Node* cur = list->first;
        for (int i = 0; cur && i < index; cur = cur->next, i++);
        return cur;
    }
}

int get_first(IList *list) {
    return list->first->value;
}

int get_last(IList *list) {
    return list->last->value;
}

int get(IList *list, int index) {
    return get_node(list, index)->value;
}

int find(IList *list, i_func pred) {
    return find_or(list, pred, 0);
}

int find_not(IList *list, i_func pred) {
    return find_not_or(list, pred, 0);
}

int find_or(IList *list, i_func pred, int default_value) {
    for (Node *cur = list->first; cur; cur = cur->next) {
        if (pred(cur->value)) {
            return cur->value;
        }
    }
    return default_value;
}

int find_not_or(IList *list, i_func pred, int default_value) {
    for (Node *cur = list->first; cur; cur = cur->next) {
        if (!pred(cur->value)) {
            return cur->value;
        }
    }
    return default_value;
}

int index_of(IList *list, int item) {
    int index = 0;
    for (Node *cur = list->first; cur; cur = cur->next) {
        if (item == cur->value) {
            return index;
        }
        index++;
    }
    return -1;
}

int last_index_of(IList *list, int item) {
    int index = -1;
    int i = 0;
    for (Node *cur = list->first; cur; cur = cur->next) {
        if (item == cur->value) {
            index = i;
        }
        i++;
    }
    return index;
}

IList* clone(IList *list) {
    IList *result = empty_list();
    for (Node *cur = list->first; cur; cur = cur->next) {
        push_back(result, cur->value);
    }
    return result;
}

IList* map(IList *list, i_func op) {
    for (Node *cur = list->first; cur; cur = cur->next) {
        cur->value = op(cur->value);
    }
    return list;
}

IList* filter(IList *list, i_func pred) {
    IList *result = empty_list();
    for (Node *cur = list->first; cur; cur = cur->next) {
        if (pred(cur->value)) {
            push_back(result, cur->value);
        }
    }
    return result;
}

IList* filter_not(IList *list, i_func pred) {
    IList *result = empty_list();
    for (Node *cur = list->first; cur; cur = cur->next) {
        if (!pred(cur->value)) {
            push_back(result, cur->value);
        }
    }
    return result;
}

IList* add_all(IList *list, IList *elems) {
    for (Node *cur = elems->first; cur; cur = cur->next) {
        push_back(list, cur->value);
    }
    return list;
}

int contains(IList *list, int value) {
    for (Node *cur = list->first; cur; cur = cur->next) {
        if (cur->value == value) {
            return 1;
        }
    }
    return 0;
}

int fold_left(int init, IList *list, i_bifunc op) {
    int acc = init;
    for (Node *cur = list->first; cur; cur = cur->next) {
        acc = op(acc, cur->value);
    }
    return acc;
}

int reduce_left(IList *list, i_bifunc op) {
    if (is_empty(list)) {
        return 0;
    } else if (list->size == 1) {
        return list->first->value;
    } else {
        Node *first = list->first;
        list->first = list->first->next;
        int result = fold_left(first->value, list, op);
        list->first = first;
        return result;
    }
}

int fold_right(int init, IList *list, i_bifunc op) {
    int acc = init;
    IList *rev = reverse(list);
    for (Node *cur = rev->first; cur; cur = cur->next) {
        acc = op(cur->value, acc);
    }
    delete_list(&rev);
    return acc;
}

int reduce_right(IList *list, i_bifunc op) {
    if (is_empty(list)) {
        return 0;
    } else if (list->size == 1) {
        return list->first->value;
    } else {
        Node *prev = get_node(list, list->size - 2);
        Node *last = list->last;
        prev->next = NULL;
        list->last = prev;
        int result = fold_right(last->value, list, op);
        prev->next = last;
        list->last = last;
        return result;
    }
}

IList* take(IList *list, int n) {
    IList *result = empty_list();
    Node *cur = list->first;
    for (int i = 0; i < n && cur; i++, cur = cur->next) {
        push_back(result, cur->value);
    }
    return result;
}

IList* take_while(IList *list, i_func pred) {
    IList *result = empty_list();
    for (Node *cur = list->first; cur && pred(cur->value); cur = cur->next) {
        push_back(result, cur->value);
    }
    return result;
}

IList* take_right(IList *list, int n) {
    IList *result = empty_list();
    int i = 0;
    for (Node *cur = list->first; cur; cur = cur->next, i++) {
        if (i >= list->size - n) {
            push_back(result, cur->value);
        }
    }
    return result;
}

IList* take_right_while(IList *list, i_func pred) {
    IList *rev = reverse(list);
    IList *tw = take_while(rev, pred);
    IList *result = take_right(list, tw->size);
    delete_list(&rev);
    delete_list(&tw);
    return result;
}

IList* slice(IList *list, int start, int end) {
    if (start == 0) {
        return take(list, end + 1);
    } else if (end == list->size - 1) {
        return take_right(list, end - start + 1);
    } else {
        IList *result = empty_list();
        int i = 0;
        for (Node *cur = list->first; cur; cur = cur->next, i++) {
            if (i >= start && i <= end) {
                push_back(result, cur->value);
            }
        }
        return result;
    }
}

int forall(IList *list, i_func pred) {
    for (Node *cur = list->first; cur; cur = cur->next) {
        if (!pred(cur->value)) {
            return 0;
        }
    }
    return 1;
}

int exists(IList *list, i_func pred) {
    for (Node *cur = list->first; cur; cur = cur->next) {
        if (pred(cur->value)) {
            return 1;
        }
    }
    return 0;
}

int count(IList *list, i_func pred) {
    int count = 0;
    for (Node *cur = list->first; cur; cur = cur->next) {
        if (pred(cur->value)) {
            count++;
        }
    }
    return count;
}

IList* unique(IList *list) {
    IList *result = empty_list();
    for (Node *cur = list->first; cur; cur = cur->next) {
        if (!contains(result, cur->value)) {
            push_back(result, cur->value);
        }
    }
    return result;
}

IList* distinct(IList *list) {
    IList *buffer = empty_list();
    for (Node *cur = list->first; cur; cur = cur->next) {
        if (contains(buffer, cur->value)) {
            delete(list, index_of(list, cur->value));
        } else {
            push(buffer, cur->value);
        }
    }
    delete_list(&buffer);
    return list;
}

IList* swap(IList *list, int i, int j) {
    Node *ni = get_node(list, i);
    Node *nj = get_node(list, j);
    int vi = ni->value;
    ni->value = nj->value;
    nj->value = vi;
    return list;
}

int is_prefix(IList *list, IList *prefix) {
    if (is_empty(prefix)) {
        return 1;
    }
    if (is_empty(list)) {
        return 0;
    }
    for (Node *l = list->first, *p = prefix->first; p; l = l->next, p = p->next) {
        if (!l || l->value != p->value) {
            return 0;
        }
    }
    return 1;
}

int is_suffix(IList *list, IList *suffix) {
    IList *rl = reverse(list);
    IList *rs = reverse(suffix);
    int result = is_prefix(rl, rs);
    delete_list(&rl);
    delete_list(&rs);
    return result;
}

int is_sublist(IList *list, IList *sublist) {
    if (is_empty(sublist)) {
        return 1;
    }
    if (is_empty(list) || list->size < sublist->size) {
        return 0;
    }
    IList *copy = clone(list);
    do {
        drop_n(copy, index_of(copy, sublist->first->value));
        if (is_prefix(copy, sublist)) {
            delete_list(&copy);
            return 1;
        }
    } while (copy->size > sublist->size);
    delete_list(&copy);
    return 0;
}

IList* intersperse(IList *list, int value) {
    IList *result = empty_list();
    if (is_not_empty(list)) {
        for (Node *cur = list->first; cur->next; cur = cur->next) {
            push_back(result, cur->value);
            push_back(result, value);
        }
        push_back(result, list->last->value);
    }
    return result;
}

int max(IList *list) {
    int max = list->first->value;
    for (Node *cur = list->first; cur; cur = cur->next) {
        if (cur->value > max) {
            max = cur->value;
        }
    }
    return max;
}

int min(IList *list) {
    int min = list->first->value;
    for (Node *cur = list->first; cur; cur = cur->next) {
        if (cur->value < min) {
            min = cur->value;
        }
    }
    return min;
}

int sum(IList *list) {
    int sum = 0;
    for (Node *cur = list->first; cur; cur = cur->next) {
        sum += cur->value;
    }
    return sum;
}

