/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
enum state {idle, collision, busy_high, busy_low} systemState;

CY_ISR(Read_Pin_Handler){
    //If 0, we went from high to low
    //Else, we went from low to high
    if(Read_Pin_Read() == 0){
        switch(systemState){
            case idle:
            //If we are idle and the signal was just high, 
            //Ignore it
            break;
            case collision:
            
            break;
            
            case busy_high:
            //Signal either is stopped or isn't, set to busy_low 
            //and start a timer for 7.5ms
            systemState=busy_low;
            break;
            case busy_low:
            
            break;
         
        }
    }else{
        switch(systemState){
            case idle:
            //Set it to busy and start a 0.6ms timer, we got a signal
            systemState = busy_high;
            break;
            case collision:
            
            break;
            
            case busy_high:
            
            break;
            case busy_low:
            
            break;
        }
    }
    Read_Pin_ClearInterrupt();
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    Read_Pin_ISR_StartEx(Read_Pin_Handler);
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    systemState=idle;
    for(;;)
    {
       switch(systemState){
        case idle:
        LED_Red_Write(0);
        LED_Yellow_Write(0);
        LED_Green_Write(1);
        break;
        case collision:
        LED_Red_Write(1);
        LED_Yellow_Write(0);
        LED_Green_Write(0);
        break;
        case busy_high:
        LED_Red_Write(0);
        LED_Yellow_Write(1);
        LED_Green_Write(0);
        break;
        case busy_low:
        LED_Red_Write(0);
        LED_Yellow_Write(1);
        LED_Green_Write(0);
        break;
        
       }
       /*LED_Green_Write(1);
       CyDelay(500);
       LED_Green_Write(0);
       CyDelay(500);
       LED_Yellow_Write(1);
       CyDelay(500);
       LED_Yellow_Write(0);
       CyDelay(500);
       LED_Red_Write(1);
       CyDelay(500);
       LED_Red_Write(0);
       CyDelay(500);*/
    }
}

/* [] END OF FILE */
