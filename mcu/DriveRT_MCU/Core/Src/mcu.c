//mcu.c에 필요한 헤더를 스스로 판단해서 include한다.
//기존 parseCommandMessage()를 옮기되 printf() 관련 부분은 제거한다.
//아직 main.c에서 호출하지 말고 우선 Build만 해본다.
#include "mcu.h"

#include <string.h>
#include <stdlib.h>


int parseCommandMessage(char * buf, Command * cmd)
{
    char * cmdType = strtok(buf, ",");
    if(cmdType == NULL)
        return FAIL;

    if(strcmp(cmdType, "MOVE")==0)
    {
        char * cmdSpeed = strtok(NULL, ",");
        if(cmdSpeed == NULL) 
            return FAIL;

        char * cmdDirection = strtok(NULL, ",");
        if(cmdDirection ==  NULL)
            return FAIL;

        cmd->type = CMD_MOVE;


        char * end;
        long speed = strtol(cmdSpeed, &end, 10);
        if(end == cmdSpeed)
            return FAIL;
        if(*end != '\0')
            return FAIL;
        cmd->speed = speed;


        if(strcmp(cmdDirection,"FORWARD")==0)
        {   
            cmd->direction = DIR_FORWARD;
            //Command Message 파싱 됨

            return SUCCESS;
        }
        else if(strcmp(cmdDirection,"BACKWARD")==0)
        {
            cmd->direction = DIR_BACKWARD;
            //Command Messgae 파싱 됨

            return SUCCESS;
        }
        else    
            return FAIL;
    }

    else if(strcmp(cmdType, "STOP")==0)
    {
        cmd->type = CMD_STOP;
        cmd->speed = 0;
        //Command Message 파싱 됨

        return SUCCESS;
    }

    else 
        return FAIL;
}
