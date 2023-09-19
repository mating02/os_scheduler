#include "../lib/queue.h"
#include <stdlib.h>
#include <stdio.h>

int queue_add(void* new_object, queue_object* queue){
    // TODO
    if(queue == NULL){
        return 1;
    }
    else{
        queue_object* newqueue_obj = malloc(sizeof(queue_object));
        newqueue_obj->object = new_object;
        newqueue_obj->next = queue->next;
        queue->next = newqueue_obj;
        return 0;
    }
}

void* queue_poll(queue_object* queue){
    // TODO
    if(queue == NULL || queue->next == NULL){
        return NULL;
    }
    while(queue->next->next != NULL){
        queue = queue->next;
    }
    void* value = queue->next->object;
    queue_object* next = queue->next;
    queue->next = NULL;
    free(next);
    return value;
}

queue_object* new_queue(){
    // TODO
    queue_object* new = malloc(sizeof(queue_object));
    new->next = NULL;
    new->object = NULL;
    return new;
}


void free_queue(queue_object* queue){
    // TODO

    queue_object* nextel = queue;
    while(nextel->next != NULL){
        free(queue);
        nextel = nextel->next;
        queue = nextel;
    }
    free(queue);
}

void* queue_peek(queue_object* queue){
    // TODO
    if(queue == NULL){
        return NULL;
    }
    queue_object* nextel = queue;
    while(nextel->next != NULL) {
        nextel = nextel->next;
    }
    if(nextel->object != NULL){
        return nextel->object;
    }
    else{
        return NULL;
    }
}
