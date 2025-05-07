#include "bsp.h"



void display_icon_function(void)
{

   if(run_t.gMouse==1){
        LED_MOUSE_ON();
   }
   else{
       LED_MOUSE_OFF();

   }

   if(run_t.gDry ==1){
	  LED_DRY_ON();

   }
   else{
	  LED_DRY_OFF();

   }

   if(run_t.gPlasma==1){
   		LED_PLASMA_ON();

   }
   else{
		LED_PLASMA_OFF();

   }



}




