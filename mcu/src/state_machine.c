//STM32로 가져가는데 44번째 줄 printf는 수정 필요

#include <stdio.h>
#include "../include/state_machine.h"

State getNextState(State current_state, Event current_event)
{
    switch(current_state)
    {
    case STATE_STOP:
        if(current_event == EVENT_RUN) 
            return STATE_RUNNING;
        
        if(current_event == EVENT_FAULT)
            return STATE_ERROR;
        
        return current_state;

    case STATE_RUNNING:
        if(current_event == EVENT_STOP)
            return STATE_STOP;
        
        if (current_event == EVENT_FAULT)
            return STATE_ERROR;
       
        return current_state;

    case STATE_ERROR:
        if(current_event == EVENT_RECOVER)
            return STATE_RECOVERY;
        
        return current_state;

    case STATE_RECOVERY:
        if(current_event == EVENT_RECOVERY_OK)
            return STATE_STOP;
        
        if(current_event == EVENT_RECOVERY_FAIL)
            return STATE_ERROR;
        
        return current_state;


    default:
        printf("[LOG] invalid state\n");
        return current_state;
    }  
}