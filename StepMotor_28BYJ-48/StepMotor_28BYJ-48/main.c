
#include "main.h"


int main(void)
{
	int i = 0;
	
	SM_init();

    while (1) 
    {
		for (i = 0; i <= 63; i++) {
			SM_forward();
		}
		
		_delay_ms(300);
		
		for (i = 0; i <= 31; i++) {
			SM_back();
		}
		
		_delay_ms(300);
    }
}

