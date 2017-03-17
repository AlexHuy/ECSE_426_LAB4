#include "Thread_Keypad.h"

void Thread_Keypad(void const *argument); 
osThreadId tid_Thread_Keypad;                            
osThreadDef(Thread_Keypad, osPriorityNormal, 1, 0);

//Create the thread for the display
int start_Thread_Keypad(void)
{
	tid_Thread_Keypad = osThreadCreate(osThread(Thread_Keypad ), NULL); 
  if (!tid_Thread_Keypad) return(-1); 
  return(0);
}

void Thread_Keypad(void const *argument)
{
	while(1)
	{
		
	}
}

void init_keypad(void)
{
	
}

