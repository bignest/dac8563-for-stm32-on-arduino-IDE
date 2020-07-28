/*
 * Simple example of using DAC8563 library for stm32duino of galvanometer application 
 *
 * For STM32 vet6, MOSI = PB5, sck = PB3
 *
 * You can define your Slave Select pin using the DAC8562 construction 
 * as showed in the example below
 *
 * inspired by @machinesalem modified by @bignest and @k164v 
 *
 * 2018-07-24 @km7,  (cc) https://creativecommons.org/licenses/by/3.0/
 *
 * @auther km7
 */

#include <DAC8562.h>
//This power is for referencing
//In case you do not have a pefect 5 volt power supply.
#define REF_POWER 5
#define SS_PIN 10
#define printimpact 0.5
#define compensaimpact 100
float x1,r1,x,y,k,b,distance;
//Initialize the DAC object
DAC8562 dac=DAC8562(SS_PIN,REF_POWER);

void setup() {
pinMode(SS_PIN, OUTPUT);  
dac.begin();


}

void loop() {

scan(0*printimpact,3*printimpact);
scan(1*printimpact,1*printimpact);
scan(3*printimpact,1*printimpact);
scan(1*printimpact,-1*printimpact);
scan(2*printimpact,-3*printimpact);
scan(0*printimpact,-1*printimpact);
scan(-2*printimpact,-3*printimpact);
scan(-1*printimpact,-1*printimpact);
scan(-3*printimpact,1*printimpact);
scan(-1*printimpact,1*printimpact);
}

void scan(float x2, float y2)
{ 
distance=sqrt((float)(x1-x2)*(x1-x2)+(float)(r1-y2)*(r1-y2));
k=(y2-r1)/(x2-x1);
b=y2-k*x2;


if(x1<x2)
{ 
for (x=x1; x<x2; x=x+(abs(x1-x2))/(distance*compensaimpact)) 
  {
  y=k*x+b;
 
  dac.writeA(x);

  dac.writeB(y);

  }
  x1=x2;
  r1=y2;
}


if(x1>x2)
{ 
for (x=x1; x >x2; x=x-(abs(x1-x2))/(distance*compensaimpact)) 
  {
  y=k*x+b;
 
  dac.writeA(x);

  dac.writeB(y);

  }
  x1=x2;
  r1=y2;
}

if(x1==x2)
{ 
  if(y2>r1)
  {
for (y=r1; y<y2; y=y+0.005) 
  {
  dac.writeA(x);
  dac.writeB(y);
  }
  x1=x2;
  r1=y2;
}
  if(y2<r1)
 {
  for (y=r1; y>y2; y=y-0.005) 
    {
      dac.writeA(x);
     dac.writeB(y);
    }
  x1=x2;
  r1=y2;
 }
}
  
}
