#include "Thread_Display.h"

void Thread_Display(void const *argument); 
osThreadId tid_Thread_Display;                            
osThreadDef(Thread_Display, osPriorityNormal, 1, 0);

//Create the thread for the display
int start_Thread_Display(void)
{
	tid_Thread_Display = osThreadCreate(osThread(Thread_Display ), NULL); 
  if (!tid_Thread_Display) return(-1); 
  return(0);
}

void Thread_Display(void const *argument)
{
	while(1)
	{
		
	}
}

void init_display(void)
{
	
}


