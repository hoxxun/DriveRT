#include <stdio.h>

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

//문자열 배열은 pointer를 쓰는구나
//값 수정 안시킬거니까 const 붙임
const char * state_buf[] = {
    "STATE_STOP",
    "STATE_RUNNING",
    "STATE_ERROR",
    "STATE_RECOVERY"
};

int main(void)
{
    State current_state = STATE_STOP;
    Event current_event = EVENT_RUN;

    printf("[LOG] current state: %s\n", state_buf[current_state]);

    switch(current_state)
    {
    case STATE_STOP:
        if(current_event == EVENT_RUN)
        {
            current_state = STATE_RUNNING;
        }
        if(current_event == EVENT_FAULT)
        {
            current_state = STATE_ERROR;
        }
        break;
    case STATE_RUNNING:
        if(current_event == EVENT_STOP)
        {
            current_state = STATE_STOP;
        }
        if (current_event == EVENT_FAULT)
        {
            current_state = STATE_ERROR;
        }
        break;
    case STATE_ERROR:
        if(current_event == EVENT_RECOVER)
        {
            current_state = STATE_RECOVERY;
        }
        break;
    case STATE_RECOVERY:
        if(current_event == EVENT_RECOVERY_OK)
        {
            current_state = STATE_STOP;
        }
        if(current_event == EVENT_RECOVERY_FAIL)
        {
            current_state = STATE_ERROR;
        }
        break;
    }

    printf("[LOG] current state: %s\n", state_buf[current_state]);
}