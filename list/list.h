#ifndef LIST_H
#define LIST_H

struct List
{
    struct List * next;
    struct List * previous;
    void * var;
};

struct List * List_create();
void List_new_next(struct List* list, void * var);
void List_append(struct List * list, void * var);
void List_append_left(struct List * list, void * var);
void List_delete(struct List * list);
struct List * List_next(struct List* list, int index);
struct List * List_previous(struct List* list, int index);
struct List * List_next_search(struct List* list, void * var);
struct List * List_previous_search(struct List* list, void * var);
struct List * List_search(struct List * list, void * var);

#endif
