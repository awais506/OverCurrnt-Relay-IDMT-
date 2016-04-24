/*
Author Muhammad Awais
UET Lahore
Fb/awais12506
engr.mahmed506@gmail.com

Program Descrption: This program Measures AC voltage applied at A0 of arduino. A step down transformer with ratio 34.375
and Voltage divider of 3 is being used.
*/

float ADCvalue0;
float Voltage[199];
float Volt=0;
float ActualVolt;
float Current;
void setup() {
  //To start Serial Communication 
  Serial.begin(9600);
}


void loop() {

Volt=0;
  // Measure Voltage 200 times and store result in an array
  for(int i=1;i<=199;i++)
  {
  ADCvalue0 = analogRead(A0);
  Voltage[i]=(5.0*ADCvalue0)/1024.0;
  
  
}
//Find Max value of Array to find Vmax
for(int j=0;j<=199;j++)
  { 
    if(Voltage[j]>Volt)
    {
      Volt=Voltage[j];
    }
    
}
Serial.print("v=");
  Serial.println(Volt);
//culating at 100,110,200,220 .it was found that an error of 5% is being intrduced. Value being calulting is sligthly more so....
//Volt=Volt-(Volt*.05);

ActualVolt =Volt-2.5; // offset voltage is 2.5v
Current =ActualVolt*10;
Current=Current/2;
Current=Current*0.7071;

  
  Serial.print("I=");
  Serial.println(Current);
delay(100);
}
    
