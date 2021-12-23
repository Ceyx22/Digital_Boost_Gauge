/* 

This sketch was based off of InterlinkKnight using https://www.youtube.com/watch?v=wIWxSLVAAQE
This sketch is made to take information from HMI scrpipt and animate it into the screen
This is just a test for me to mess around with the screen most of the code was written by InterlinkKnight

The data can be text, numbers, or any other atribute of an object.

Can also change brightness, serial baud rate, etc.

Connection with Arduino Nano:
* +5V = 5V
* TX  = none
* RX  = pin 1 (TX)
* GND = GND

*Things to adresss/fix
One flaw in the current design of this is the current flash memory on screen it is not enough will have to upgrade

*/

int variable1 = 0;  // This is a simple variable to keep increasing a number to have something dynamic to show on the display.


void setup() {  // Put your setup code here, to run once:
  
  Serial.begin(9600);  // Starting serial comunication at baud=9600.

}  // End of setup


void loop() {  // Put your main code here, to run repeatedly:

  variable1++;  // Increase the value of the variable by 1.
  if(variable1 == 201){  // If the variable reach 201...
    variable1 = 0;  // Set the variable to 0 so it starts over again.
  }

  /*
  ************************************IMPORTNAT!!!***************************************

  For changing atributes in script
  Serial.print("j0.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print(variable1);  // This is the value you want to send to that object and atribute mention before.
  */


  //sending the variable value to object called n0:
  // After the name of the object you need to put the dot val because val is the atribute we want to change on that object.
  Serial.print("n0.val=");  // Setting up change in Nextion Display
  Serial.print(variable1);  // Setting variable to attribute.
  Serial.write(0xff);  // Always have to send this three lines after each command for nextion display.
  Serial.write(0xff);
  Serial.write(0xff);

  //possible Gas intergration?
  // update progress bar
  //Bar range goes from 0 to 100, When the variable is 100, the progress bar be 100.
  Serial.print("j0.val=");  // Setting up change in Nextion Display
  Serial.print(variable1);  // Setting variable to attribute.
  Serial.write(0xff);  // Always have to send this three lines after each command for nextion display.
  Serial.write(0xff);
  Serial.write(0xff);

  // Updating gauge to show varaible
  // Updating through variable va0 
  // Have code in HMI for Timmer which will compare value of variable with current gauge and update when diffrent 
  // The gauge range goes from 30inHG to 30 PSI (going clockwise).
  Serial.print("va0.val=");  // Setting up change in Nextion Display
  Serial.print(variable1);  // Setting variable to attribute.
  Serial.write(0xff);  // Always have to send this three lines after each command for nextion display.
  Serial.write(0xff);
  Serial.write(0xff);

  //probably not going to use this but can in some future itteration
  // Showingg "Hot!" when the variable is greater than 99, and show "Normal" when variable is below 100.
    if(variable1 > 99){  // If the variable is greater than 99...
    Serial.print("t0.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");  // Since we are sending text we need to send double quotes before and after the actual text.
    Serial.print("Hot!");  // This is the text we want to send to that object and atribute mention before.
    Serial.print("\"");  // Since we are sending text we need to send double quotes before and after the actual text.
    Serial.write(0xff);  // Always have to send this three lines after each command for nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }else{  // Since condition was false, do the following:
    Serial.print("t0.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");  // Since we are sending text we need to send double quotes before and after the actual text.
    Serial.print("Normal");  // This is the text we want to send to that object and atribute mention before.
    Serial.print("\"");  // Since we are sending text we need to send double quotes before and after the actual text.
    Serial.write(0xff);  // Always have to send this three lines after each command for nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }

  // We are going to hide the progress bar if the variable is greater than 119:
  if(variable1 > 119){  // If the variable is greater than 119...
    Serial.print("vis j0,0");  // Hiding object. Could be usefull The name of the object comes before the comma, and after the comma goes a 0 to hide or 1 to show.
    Serial.write(0xff);  // Always have to send this three lines after each command for nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }else{  // Since condition was false, do the following:
    Serial.print("vis j0,1"); // Hiding object. Could be usefull The name of the object comes before the comma, and after the comma goes a 0 to hide or 1 to show.
    Serial.write(0xff);  // Always have to send this three lines after each command for nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }

  // We are going to change the color of the progress bar to red if the variable is greater than 49, and change to green if is below 50:
  if(variable1 > 49){  // If the variable is greater than 49...
    Serial.print("j0.pco=63488");  // Change color of the progress bar to red.
    Serial.write(0xff);  // Always have to send this three lines after each command for nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }else{  // Since condition was false, do the following:
    Serial.print("j0.pco=1024");  // Change color of the progress bar to green.
    Serial.write(0xff);  // Always have to send this three lines after each command for nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }
}   // End of loop


