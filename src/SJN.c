#include "../lib/SJN.h"

static queue_object* SJN_queue;
//You can add more global variables here

process* SJN_tick (process* running_process){
    // TODO
    if (running_process==NULL || running_process->time_left==0){
        running_process=queue_poll(SJN_queue);
    }
    if (running_process!=NULL){
        running_process->time_left--;
    }

    return running_process;
}

int SJN_startup(){
    // TODO
    SJN_queue=new_queue();
    if (SJN_queue==NULL){
        return 1;
    }
    return 0;

}

process* SJN_new_arrival(process* arriving_process, process* running_process){
    // TODO
    if(arriving_process != NULL){
        queue_object* head = SJN_queue;
        queue_object* new = malloc(sizeof(queue_object));
        new->object = arriving_process;
        new->next = NULL;
        while(SJN_queue->next != NULL){
            if(arriving_process->time_left < ((process*)SJN_queue->next->object)->time_left){
                SJN_queue = SJN_queue->next;
            }
            else{
                break;
            }
        }
        new->next = SJN_queue->next;
        SJN_queue->next = new;
        SJN_queue = head;
    }
    return running_process;
}

void SJN_finish(){
    // TODO
    free_queue(SJN_queue);
}
