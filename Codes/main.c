 /******************************************************************************************

This programme controls the speed of the motor by the Pulse Width Modulation method
 
******************************************************************************************/

#include <intrins.h>
#include "p89v51rx2.h"

//direction control bits

sbit LB=P1^0;  //LEFT BACK Pin
sbit LF=P1^1;  //LEFT FRONT Pin
sbit RF=P1^2;  //RIGHT FRONT Pin
sbit RB=P3^4;  //RIGHT BACK Pin

void delay_ms(unsigned int value)
{
 unsigned int i, j;
 for(i=0;i<value;i++)
 	for(j=0;j<53;j++);
}

//Set left motor with velocity vel(compare value). 0x00 will give full (100% duty cycle) velocity, while 0xFF will give zero (0% duty cycle) velocity. Any value in between 0x00 and 0xFF will give intermediate velocity.
void left_motor_velocity(unsigned char vel)
{
CCAP0H=vel;
}

//Set right motor with velocity vel(compare value). 0x00 will give full (100% duty cycle) velocity, while 0xFF will give zero (0% duty cycle) velocity. Any value in between 0x00 and 0xFF will give intermediate velocity.
void right_motor_velocity(unsigned char vel)
{
CCAP1H=vel;
}

// motor direction control subroutines
void forward(void)
{
RF=1;
LF=1;
RB=0;
LB=0;
}

//initialise programmable counter array module to generate pwm
//The CCAPnH register holds the reload value. CCAPnL register increments,and is loaded with this value everytime it overflows
//Thus the value in CCAPnH can be changed to change the motor velocity
void pca_init(void)
{
 CMOD=0x80;	   //80 sets PCA counter to run at Fosc/6; 
 CCON=0x40;	   //start PCA counter
 						
 CCAP0L=0x00;   
 CCAP0H=0xFF;  //Left motor duty cycle register
  
 CCAP1L=0x00;				  
 CCAP1H=0xFF;  //Right motor duty cycle register

 CCAPM0=0x42;  //enable PWM mode and ECOM bits for left motor
 CCAPM1=0x42;  //enable PWM mode and ECOM bits for right motor
}

void main()
{
pca_init();
/*******************************************************************************************
 First set velocity for each motor by calling  left_motor_vel & right_motor_vel	 functions
 Then set the robot to move forward by calling forward function.
 Robot can be made to move right or left by varying the left and right motor velocities.
 If left motor velocity < right motor velocity then robot moves left or vice versa.
 ******************************************************************************************/  
forward();
left_motor_velocity(0x4F);  //0x00 will give full (100% duty cycle) velocity, while 0xFF will give zero (0% duty cycle) velocity. Any value in between 0x00 and 0xFF will give intermediate velocity.			
right_motor_velocity(0x6F); //0x00 will give full (100% duty cycle) velocity, while 0xFF will give zero (0% duty cycle) velocity. Any value in between 0x00 and 0xFF will give intermediate velocity.

while(1);
}

