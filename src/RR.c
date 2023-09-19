#include "../lib/RR.h"

static queue_object* RR_queue;
//You can add more global variables
static int Quantum;
static int count = 0;

process* RR_tick (process* running_process){
    // TODO
    if (running_process==NULL || running_process->time_left==0 || count == Quantum){
        if(count == Quantum && running_process != NULL){
            if(running_process->time_left > 0){
                queue_add(running_process, RR_queue);
            }
        }
        running_process=queue_poll(RR_queue);
        count = 0;
    }
    if (running_process!=NULL){
        running_process->time_left--;
        count++;
    }

    return running_process;
}

int RR_startup(int quantum){
    // TODO
    Quantum = quantum;
    RR_queue=new_queue();
    if (RR_queue==NULL){
        return 1;
    }
    return 0;
}


process* RR_new_arrival(process* arriving_process, process* running_process){
    // TODO
    if(arriving_process!=NULL){
        queue_add(arriving_process, RR_queue);
    }
    return running_process;
}


void RR_finish(){
    free_queue(RR_queue);
    // TODO
}
