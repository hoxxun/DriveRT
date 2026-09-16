//STM32로 가져갈 것

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef enum
{
    STATE_STOP, 
    STATE_RUNNING, 
    STATE_ERROR, 
    STATE_RECOVERY
} State;

typedef enum
{
    EVENT_RUN, 
    EVENT_STOP, 
    EVENT_FAULT, 
    EVENT_RECOVER, 
    EVENT_RECOVERY_OK, 
    EVENT_RECOVERY_FAIL
} Event;


State getNextState(State current_state, Event current_event);
#endif