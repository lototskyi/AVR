#include "stepmotor.h"

#define SM_port PORTC
#define SM_ddr DDRC

#define IN1 PORTC0
#define IN2 PORTC1
#define IN3 PORTC2
#define IN4 PORTC3

#define SM_delay _delay_ms(5)

void SM_init()
{
	SM_ddr |= (1 << IN4) | (1 << IN3) | (1 << IN2) | (1 << IN1);
	SM_port &= ~((1 << IN4) | (1 << IN3) | (1 << IN2) | (1 << IN1));
}

/*
1000
1001
0001
0011
0010
0110
0100
1100
*/


void SM_set1() //1000
{
	SM_port |= 1 << IN1;
	SM_port &= ~(1 << IN2);
	SM_port &= ~(1 << IN3);
	SM_port &= ~(1 << IN4);
	SM_delay;
}

void SM_set2() //1001
{
	SM_port |= 1 << IN1;
	SM_port |= 1 << IN4;
	SM_port &= ~(1 << IN2);
	SM_port &= ~(1 << IN3);
	SM_delay;
}

void SM_set3() //0001
{
	SM_port |= 1 << IN4;
	SM_port &= ~(1 << IN1);
	SM_port &= ~(1 << IN2);
	SM_port &= ~(1 << IN3);
	SM_delay;
}

void SM_set4() //0011
{
	SM_port |= 1 << IN4;
	SM_port |= 1 << IN3;
	SM_port &= ~(1 << IN1);
	SM_port &= ~(1 << IN2);
	SM_delay;
}
void SM_set5() //0010
{
	SM_port |= 1 << IN3;
	SM_port &= ~(1 << IN1);
	SM_port &= ~(1 << IN2);
	SM_port &= ~(1 << IN4);
	SM_delay;
}

void SM_set6() //0110
{
	SM_port |= 1 << IN3;
	SM_port |= 1 << IN2;
	SM_port &= ~(1 << IN1);
	SM_port &= ~(1 << IN4);
	SM_delay;
}

void SM_set7() //0100
{
	SM_port |= 1 << IN2;
	SM_port &= ~(1 << IN1);
	SM_port &= ~(1 << IN3);
	SM_port &= ~(1 << IN4);
	SM_delay;
}

void SM_set8() //1100
{
	SM_port |= 1 << IN1;
	SM_port |= 1 << IN2;
	SM_port &= ~(1 << IN3);
	SM_port &= ~(1 << IN4);
	SM_delay;
}

void SM_forward()
{
	SM_set1();
	SM_set2();
	SM_set3();
	SM_set4();
	SM_set5();
	SM_set6();
	SM_set7();
	SM_set8();
	
}

void SM_back()
{
	SM_set8();
	SM_set7();
	SM_set6();
	SM_set5();
	SM_set4();
	SM_set3();
	SM_set2();
	SM_set1();
}