//Servo motor library
#include <Servo.h>
//Initialize variables
int  mode = 0;
int axe = 0;            
int buttonState1 = 0;    
int buttonState2  = 0;   
int prevButtonState1 = 0;
int prevButtonState2 = 0; 
 
int ldrtopr=  2;                // top-right LDR                          
int ldrtopl = 1;               // top-left LDR                          
int ldrbotr = 3;               //  bottom-right LDR                     
int ldrbotl = 4;               // bottom-left  LDR                   
int topl = 0;
int topr = 0; 
int botl = 0;
int  botr = 0;

//Declare two servos
Servo servo_updown;
Servo servo_rightleft;

int  threshold_value=1;           //measurement sensitivity

void setup()
{
  Serial.begin(9600);                                //serial connection setup  //opens  serial port, sets data rate to 9600 bps
  Serial.println("CLEARDATA");                       //clear  all data that’s been place in already
  Serial.println("LABEL,t,voltage,current,power,Mode");   //define the column headings (PLX-DAQ command)

  
  servo_updown.attach(9);             //Servo motor up-down movement
  servo_rightleft.attach(8);          //Servo motor right-left movement
}

void loop()
{


      
    automaticsolartracker(); //send Mode "Automatic" to serial port
    
}

void  automaticsolartracker(){
  
     //capturing analog values of each LDR
     topr= analogRead(ldrtopr);         //capturing analog value of top right LDR
     topl= analogRead(ldrtopl);         //capturing analog value of top left LDR
     botr= analogRead(ldrbotr);         //capturing analog value of bot right LDR
     botl= analogRead(ldrbotl);         //capturing analog value of bot left LDR
  
  
  
  
  // print LDR readings to serial monitor
  Serial.print("LDR 1 reading: ");
  Serial.println(topr);
  Serial.print("LDR 2 reading: ");
  Serial.println(topl);
  Serial.print("LDR 3 reading: ");
  Serial.println(botr);
  Serial.print("LDR 4 reading: ");
  Serial.println(botl);
  Serial.println();
  delay(1000);
  
    
    // calculating average
     int avgtop = (topr + topl) / 2;     //average  of top LDRs
     int avgbot = (botr + botl) / 2;     //average of bottom LDRs
     int avgleft = (topl + botl) / 2;    //average of left LDRs
     int avgright  = (topr + botr) / 2;   //average of right LDRs
   
    //Get the different  
     int diffelev = avgtop - avgbot;      //Get the different average betwen  LDRs top and LDRs bot
     int diffazi = avgright - avgleft;    //Get the different  average betwen LDRs right and LDRs left
    
    //left-right movement of  solar tracker
     
      if (abs(diffazi) >= threshold_value){        //Change  position only if light difference is bigger then the threshold_value
       if  (diffazi > 0) {
        if (servo_rightleft.read() < 180) {
          servo_rightleft.write((servo_updown.read()  + 10));
        }
      }
      if (diffazi <  0) {
        if (servo_rightleft.read()  > 0) {
          servo_rightleft.write((servo_updown.read() - 10));
        }
      }
    }
             
      //up-down movement of solar tracker

      if (abs(diffelev) >= threshold_value){    //Change position only if light  difference is bigger then thethreshold_value
       if (diffelev > 0) {
        if  (servo_updown.read() < 180) {
          servo_updown.write((servo_rightleft.read()  - 10));
        }
      }
      if (diffelev <  0) {
        if (servo_updown.read()  > 0) {
          servo_updown.write((servo_rightleft.read() + 10));
        }
      }
    }       
 }  
