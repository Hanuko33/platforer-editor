#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct List * List_create()
{
    struct List * list = malloc(sizeof(struct List));

    list->var=NULL;
    list->next=NULL;
    list->previous=NULL;

    return list;
}

void List_new_next(struct List* list, void * var)
{
    list->next = List_create();
    list->next->previous = list;
    list->next->var = var;
}

void List_delete(struct List* list)
{
    if (list->previous && list->next)
    {
        struct List * previous = list->previous;
        struct List * next = list->next;
        next->previous = previous;
        previous->next = next;
    }
    else if (!list->next && list->previous)
        list->previous->next = NULL;
    else if (!list->previous && list->next)
        list->next->previous = NULL;

    list->next=NULL;
    list->previous=NULL;
    free(list);
    list = NULL;
}

void List_append(struct List * list, void * var)
{
    struct List * current = list;
    for (int i = 0;; i++)
    {
        if (current->next)
            current=current->next;
        else 
            break;
    }

    current->next = List_create();
    current->next->previous = current;
    current->next->var = var;
}

void List_append_left(struct List * list, void * var)
{
    struct List * current = list;
    for (int i = 0;; i++)
    {
        if (current->previous)
            current=current->previous;
        else 
            break;
    }

    current->previous = List_create();
    current->previous->next = current;
    current->previous->var = var;
}


struct List * List_next(struct List* list, int index)
{
    struct List * current = list;
    for (int i = 0; i < index; i++) 
    {
        if (current->next)
        {
            current = current->next;
        }
        else 
        {
            return NULL;
        }
    }
    return current;
}

struct List * List_previous(struct List* list, int index)
{
    struct List * current = list;
    for (int i = 0; i < index; i++) 
    {
        if (current->previous)
        {
            current = current->previous;
        }
        else 
        {
            return NULL;
        }
    }
    return current;
}

struct List * List_next_search(struct List* list, void * var)
{
    struct List * current = list;
    for (int i = 0;; i++) 
    {
        if (!current)
        {
            return NULL;
        }
        if (current->var && current->var == var)
        {
            break;
        }
        if (current->next)
        {
            current = current->next;
        }
        else 
        {
            return NULL;
        }
    }
    return current;
}

struct List * List_previous_search(struct List* list, void * var)
{
    struct List * current = list;
    for (int i = 0;; i++) 
    {
        if (!current)
        {
            return NULL;
        }
        if (current->var && current->var == var)
        {
            break;
        }
        if (current->previous)
        {
            current = current->previous;
        }
        else 
        {
            return NULL;
        }
    }
    return current;
}

struct List * List_search(struct List * list, void * var)
{
    if (List_previous_search(list, var))
        return List_previous_search(list, var);
    else if (List_next_search(list, var))
        return List_next_search(list, var);
    else
        return NULL;
}

