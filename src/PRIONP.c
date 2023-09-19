#include "../lib/PRIONP.h"
#include <stdio.h>

static queue_object* PRIONP_queue;
//You can add more global variables here

process* PRIONP_tick (process* running_process){
    // TODO
    if (running_process==NULL || running_process->time_left==0){
        running_process=queue_poll(PRIONP_queue);
    }
    if (running_process!=NULL){
        running_process->time_left--;
    }

    return running_process;
}

int PRIONP_startup(){
    // TODO
    PRIONP_queue=new_queue();
    if (PRIONP_queue==NULL){
        return 1;
    }
    return 0;
}

process* PRIONP_new_arrival(process* arriving_process, process* running_process){
    // TODO
    // queue poll  ->  queue add
    // arriving ->start time <= start time + time->left <=

    if(arriving_process != NULL){
        queue_object* head = PRIONP_queue;
        queue_object* new = malloc(sizeof(queue_object));
        new->object = arriving_process;
        new->next = NULL;
        while(PRIONP_queue->next != NULL){
            if(arriving_process->priority > ((process*)PRIONP_queue->next->object)->priority){
                PRIONP_queue = PRIONP_queue->next;
            }
            else{
                break;
            }
        }
        new->next = PRIONP_queue->next;
        PRIONP_queue->next = new;
        PRIONP_queue = head;
    }
    return running_process;
}

void PRIONP_finish(){
    // TODO
    free_queue(PRIONP_queue);
}
