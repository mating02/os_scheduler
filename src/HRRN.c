#include "../lib/HRRN.h"

static queue_object* HRRN_queue;
//You can add more global variables and structs here

float RRcalc(float time_left, float waiting_time){
    float calc = (time_left +waiting_time) / time_left;
    return calc;
}

process* HRRN_tick (process* running_process){
    // TODO
    
    if (running_process==NULL || running_process->time_left==0){
        HRRN_process* new = queue_poll(HRRN_queue);
        if(new != NULL){
            running_process = new->this_process;
        }
        else{
            running_process = NULL;
        }
    }
    if (running_process!=NULL){
        queue_object* tmp = HRRN_queue;
        running_process->time_left--; 
            while(tmp->next != NULL){
                tmp = tmp->next;
                HRRN_process* this = tmp->object;
                this->waiting_time++;
                this->rr = (float)RRcalc((float)this->this_process->time_left, (float)this->waiting_time);
            }
            
        }
        //waiting time ++;

    return running_process;
}

int HRRN_startup(){
    // TODO
    HRRN_queue=new_queue();
    if (HRRN_queue==NULL){
        return 1;
    }
    return 0;
}

process* HRRN_new_arrival(process* arriving_process, process* running_process){
    // TODO
    

    if(arriving_process != NULL){
        HRRN_process* newprocess = malloc(sizeof(HRRN_process));
        newprocess->waiting_time = 0;
        newprocess->rr = 1;
        newprocess->this_process = arriving_process;
        queue_object* head = HRRN_queue;
        queue_object* new = malloc(sizeof(queue_object));
        new->object = newprocess;
        new->next = NULL;
        while(HRRN_queue->next != NULL){
            if(newprocess->rr > ((HRRN_process*)HRRN_queue->next->object)->rr){
                HRRN_queue = HRRN_queue->next;
            }
            else{
                break;
            }
        }
        new->next = HRRN_queue->next;
        HRRN_queue->next = new;
        HRRN_queue = head;
    }
    return running_process;
}

void HRRN_finish(){
    // TODO
    free_queue(HRRN_queue);
}



//wait time = running_process->time_left
//arriving->time_left : Bedienzeit
//rr = siehe Formel
//float rr[arriving->starting_time] vergleichen;
/*while(head->next != NULL){
                HRRN_process* lookatu = queue_peek(head);
                if(lookatu->rr >= ((HRRN_process*)head->next->object)->rr){
                    head = head->next;
                }
                else{
                    HRRN_process* swap = head->next->object;
                    head->next->object = head->object;
                    head->object = swap;
                }
            }
*/