#include "../lib/MLF.h"
#include <stdio.h>

static queue_object** MLF_queues;
//You can add more global variables here
static queue_object* queue1;
static queue_object* queue2;
static queue_object* queue3;
static queue_object* queueFCFS;
static int Quantum1 = 1;
static int Quantum2 = 2;
static int Quantum3 = 6;
static int count = 0;

process* SearchForRightQueue(){
        if(queue_peek(queue1) != NULL){
            process* running_process = queue_poll(queue1);
            return running_process;
        }
        if(queue_peek(queue2) != NULL){
            process* running_process = queue_poll(queue2);
            return running_process;
        }
        if(queue_peek(queue3) != NULL){
            process* running_process = queue_poll(queue3);
            return running_process;
        }
        if(queue_peek(queueFCFS) != NULL){
            process* running_process = queue_poll(queueFCFS);
            return running_process;
        }
        return NULL;
}
process* MLF_tick (process* running_process){
    // TODO
    if(running_process == NULL || running_process->time_left == 0){
        running_process = SearchForRightQueue();
        count = 0;
        if (running_process!=NULL){
            running_process->time_left--;
            count++;
        }
        return running_process;
    }

    if(running_process != NULL){
        if(running_process->priority == 1){
            if(count == Quantum1){
                count = 0;
                running_process->priority += 1;
                queue_add(running_process, queue2);
                running_process = SearchForRightQueue();
            }
        }
        if(running_process->priority == 2){
            if(count == Quantum2){
                count = 0;
                running_process->priority += 1;
                queue_add(running_process, queue3);
                running_process = SearchForRightQueue();
            }
        }
        if(running_process->priority == 3){
            if(count == Quantum3){
                count = 0;
                running_process->priority += 1;
                queue_add(running_process, queueFCFS);
                running_process = SearchForRightQueue();
            }
        }
        if(running_process!=NULL){
            running_process->time_left--;
            count++;
        }
    }
    return running_process;
}

/**
 * Do everything you have to at startup in this function. It is called once.
 * @result 0 if everything was fine. Any other number if there was an error.
 */
int MLF_startup(){
    // TODO
    MLF_queues = (queue_object**)malloc(sizeof(queue_object*));
    *MLF_queues = (queue_object*)malloc(sizeof(queue_object));
    (*MLF_queues)->object = NULL;
    (*MLF_queues)->next = (queue_object*)malloc(sizeof(queue_object));
    (*MLF_queues)->next->object = new_queue();
    queue1 =(*MLF_queues)->next->object;
    if (queue1==NULL){
        return 1;
    }
    (*MLF_queues)->next->next = (queue_object*)malloc(sizeof(queue_object));
    (*MLF_queues)->next->next->object = new_queue();
    queue2 =(*MLF_queues)->next->next->object;
    if (queue2==NULL){
        return 1;
    }
    (*MLF_queues)->next->next->next = (queue_object*)malloc(sizeof(queue_object));
    (*MLF_queues)->next->next->next->object = new_queue();
    queue3 =(*MLF_queues)->next->next->next->object;
    if (queue3==NULL){
        return 1;
    }
    (*MLF_queues)->next->next->next->next = (queue_object*)malloc(sizeof(queue_object));
     (*MLF_queues)->next->next->next->next->object = new_queue();
     queueFCFS =(*MLF_queues)->next->next->next->next->object; 
    if (queueFCFS==NULL){
        return 1;
    }
    return 0;
}

process* MLF_new_arrival(process* arriving_process, process* running_process){
    // TODO
    if(arriving_process!=NULL){
        arriving_process->priority = 1;
        queue_add(arriving_process, queue1);
    }
    return running_process;
}

/**
 * is called once after the all processes were handled. In case you want to cleanup something
 */
void MLF_finish(){
    // TODO
    free((*MLF_queues)->next->next->next->next->object);
    free((*MLF_queues)->next->next->next->next);
    free((*MLF_queues)->next->next->next->object);
    free((*MLF_queues)->next->next->next);
    free((*MLF_queues)->next->next->object);
    free((*MLF_queues)->next->next);
    free((*MLF_queues)->next->object);
    free((*MLF_queues)->next);
    free(*MLF_queues);
    free(MLF_queues);
}


/*tmp = queue1;
if count = quantum -> tmp = tmp->next
*/ 