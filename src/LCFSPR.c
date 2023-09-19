#include "../lib/LCFSPR.h"

static queue_object* LCFSPR_queue;
//You can add more global variables here
static int counter = 0;

int LCFSPR_startup(){
    // TODO
    LCFSPR_queue=new_queue();
    if (LCFSPR_queue==NULL){
        return 1;
    }
    return 0;
}

process* LCFSPR_tick (process* running_process){
    // TODO
    // if counter = peek.start time
    counter++;
    process* elinqueue = queue_peek(LCFSPR_queue);
    if(elinqueue != NULL){
        if(running_process != NULL && (counter-1) == (int)elinqueue->start_time){
            if(running_process->time_left > 0){
                queue_add(running_process, LCFSPR_queue);
            }
            running_process=queue_poll(LCFSPR_queue);
            running_process->time_left--;
            return running_process;
        }
    }
    if (running_process==NULL || running_process->time_left==0){
        running_process=queue_poll(LCFSPR_queue);
    }
    if (running_process!=NULL){
        running_process->time_left--;
    }
    return running_process;
}


process* LCFSPR_new_arrival(process* arriving_process, process* running_process){
    // TODO
    if(arriving_process != NULL){
        queue_object* head = LCFSPR_queue;
        queue_object* new = malloc(sizeof(queue_object));
        new->object = arriving_process;
        new->next = NULL;
        while(LCFSPR_queue->next != NULL){
            if(arriving_process->start_time > ((process*)LCFSPR_queue->next->object)->start_time){
                LCFSPR_queue = LCFSPR_queue->next;
            }
            else{
                break;
            }
        }
        new->next = LCFSPR_queue->next;
        LCFSPR_queue->next = new;
        LCFSPR_queue = head;
    }
    return running_process;
}

void LCFSPR_finish(){
    // TODO
    free_queue(LCFSPR_queue);
}
