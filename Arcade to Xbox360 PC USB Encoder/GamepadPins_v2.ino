/*
    Project     Arduino XInput Library
    @author     David Madison
    @link       github.com/dmadison/ArduinoXInput
    @license    MIT - Copyright (c) 2019 David Madison

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.

    Example:      GamepadPins
    Description:  Uses all of the available pin inputs to build a 'complete'
                  Xbox gamepad, with both analog joysticks, both triggers,
                  and all of the main buttons.

 *                * Joysticks should be your typical 10k dual potentiometers.
                    To prevent random values caused by floating inputs,
                    joysticks are disabled by default.
 *                * Triggers can be either analog (pots) or digital (buttons).
                    Set the 'TriggerButtons' variable to change between the two.
 *                * Buttons use the internal pull-ups and should be connected
                    directly to ground.

                  These pins are designed around the Leonardo's layout. You
                  may need to change the pin numbers if you're using a
                  different board type

*/

//------------------------------------------------------------------------------------------------------//
//Modfied by dekkit for the Arduino Pro Micro as part of an arcade stick to Xbox360 for PC conversion   //
//                                                                                                      //
//                                                                                                      //
// 15/02/2026 v2 - code cleanup / removed uncessary conditional logic                                   //
// 13/02/2026 v1 - initial - test concept of using dpad as virtual left analog stick                    //
//------------------------------------------------------------------------------------------------------//


#include <XInput.h>

// Setup
// in this modification we are using the D pad inputs (e.g. an arcade joystick) to control the left analog (e.g. extreme left/right/up/down)
// in a future enhancement, we'll use this value to enable the user to decide if Dpad will be used as analog or dpad inputs (similar to switches on other fight sticks)
const boolean UseLeftJoystick   = true;  // set to true to enable left joystick



// Button Pins 
//
// Dek 14/2 
// Reordered PIN 0 (Button B) and PIN 1 (Button A) for Arduino PRO MICRO Pinout
// This is because the Pro Micro has pin 0 and pin 1 flipped compared to other version of the board.
// E.g. Compare Pro micro vs Leonardo
//
// Added labels of how it will appear in joy.cpl (windows usb game pad tester .... press win+r then type 'joy.cpl', then select properties to test/see mapping results once uploaded to your board)

const int Pin_ButtonA = 1;  //will appear as BUTTON 1 in joy.cpl
const int Pin_ButtonB = 0;  //will appear as BUTTON 2 in joy.cpl

const int Pin_ButtonX = 2;  //will appear as BUTTON 3 in joy.cpl
const int Pin_ButtonY = 3;  //will appear as BUTTON 4 in joy.cpl

const int Pin_ButtonLB = 4;  //will appear as BUTTON 5 in joy.cpl
const int Pin_ButtonRB = 5;  //will appear as BUTTON 6 in joy.cpl

const int Pin_ButtonBack  = 6;  //will appear as BUTTON 7 in joy.cpl   (also known as back/select/coin)
const int Pin_ButtonStart = 7;  //will appear as BUTTON 8 in joy.cpl   (also known as start/1up)

const int Pin_ButtonL3 = 8;  //will appear as BUTTON 9 in joy.cpl   
const int Pin_ButtonR3 = 9;  //will appear as BUTTON 10 in joy.cpl   

// Trigger Pins 
// Dek 14/2 - digital input assigned for Micro Pro
const int Pin_TriggerL = 16;  //also labelled MOSI will appear as trigger full / off in joy.cpl   (can be used as an extra button in some games)
const int Pin_TriggerR = 10;  //also labelled A10 will appear as trigger full / off  in joy.cpl   (can be used as an extra button in some games)


// Directional Pad Pins - Dpad - (which will be use to emulate left analog)

// Dek 14/2 
// Given the limited number of pins on the Pro Micro,  moved the dpad input pins to where the analog pins are and set them to be digital inputs.
//
// This means you can have a joystick with 8 buttons (upto 10 if you use the L/R triggers) + coin + start
// This brings 12 button as the total number of available buttons.
//
// You can easily remap pins by replacing the numbers above, e.g. you'd prefer to the move the dpad input elsewhere, or you have an existing wire harness to your control panel.  See the Pro Micro pinout diagrams for more information.
// UDLR

const int Pin_DpadUp    = A3; //also labelled pin 21 on Pro Micro Diagrams
const int Pin_DpadDown  = A2; //also labelled pin 20 on Pro Micro Diagrams
const int Pin_DpadLeft  = A1; //also labelled pin 19 on Pro Micro Diagrams
const int Pin_DpadRight = A0; //also labelled pin 18 on Pro Micro Diagrams

void setup() {
   

  // Set all buttons, dpad, triggers as inputs, using internal pull-up resistors (e.g. to a HIGH state unless pressed)
  pinMode(Pin_ButtonA, INPUT_PULLUP);
  pinMode(Pin_ButtonB, INPUT_PULLUP);
  pinMode(Pin_ButtonX, INPUT_PULLUP);
  pinMode(Pin_ButtonY, INPUT_PULLUP);

  pinMode(Pin_ButtonLB, INPUT_PULLUP);
  pinMode(Pin_ButtonRB, INPUT_PULLUP);

  pinMode(Pin_ButtonBack, INPUT_PULLUP);
  pinMode(Pin_ButtonStart, INPUT_PULLUP);

  pinMode(Pin_ButtonL3, INPUT_PULLUP);
  pinMode(Pin_ButtonR3, INPUT_PULLUP);

  pinMode(Pin_TriggerL, INPUT_PULLUP);
  pinMode(Pin_TriggerR, INPUT_PULLUP);

  pinMode(Pin_DpadUp, INPUT_PULLUP);
  pinMode(Pin_DpadDown, INPUT_PULLUP);
  pinMode(Pin_DpadLeft, INPUT_PULLUP);
  pinMode(Pin_DpadRight, INPUT_PULLUP);

  
  XInput.setJoystickRange(0, 1023);  // Set left analog joystick range.

  XInput.setAutoSend(false);  // Wait for all controls before sending (default value)

  XInput.begin();
}

void loop() {
  // Read pin values and store in variables
  // Dek 14/01
  // The code confusingly adds "!" to invert the state, so when the user presses a button, the digital read = LOW, however this is then inverted to become a "1" or HIGH when assigning to a variable, this is likely needed to support the USB communication step)
  // Take note if you need to adapt the code for use in conditional statements.
  
  boolean buttonA = !digitalRead(Pin_ButtonA);
  boolean buttonB = !digitalRead(Pin_ButtonB);
  boolean buttonX = !digitalRead(Pin_ButtonX);
  boolean buttonY = !digitalRead(Pin_ButtonY);

  boolean buttonLB = !digitalRead(Pin_ButtonLB);
  boolean buttonRB = !digitalRead(Pin_ButtonRB);

  boolean buttonBack  = !digitalRead(Pin_ButtonBack);
  boolean buttonStart = !digitalRead(Pin_ButtonStart);

  boolean buttonL3 = !digitalRead(Pin_ButtonL3);
  boolean buttonR3 = !digitalRead(Pin_ButtonR3);

  boolean dpadUp    = !digitalRead(Pin_DpadUp);
  boolean dpadDown  = !digitalRead(Pin_DpadDown);
  boolean dpadLeft  = !digitalRead(Pin_DpadLeft);
  boolean dpadRight = !digitalRead(Pin_DpadRight);

  // Read trigger buttons
  boolean triggerLeft  = !digitalRead(Pin_TriggerL);
  boolean triggerRight = !digitalRead(Pin_TriggerR);

  // Set XInput buttons
  XInput.setButton(BUTTON_A, buttonA); 
  XInput.setButton(BUTTON_B, buttonB); 
  XInput.setButton(BUTTON_X, buttonX);
  XInput.setButton(BUTTON_Y, buttonY);

  XInput.setButton(BUTTON_LB, buttonLB);
  XInput.setButton(BUTTON_RB, buttonRB);

  XInput.setButton(BUTTON_BACK, buttonBack);
  XInput.setButton(BUTTON_START, buttonStart);

  XInput.setButton(BUTTON_L3, buttonL3);
  XInput.setButton(BUTTON_R3, buttonR3);

  // Set XInput trigger values
  XInput.setButton(TRIGGER_LEFT, triggerLeft);
  XInput.setButton(TRIGGER_RIGHT, triggerRight);


  // Set XInput DPAD values
  
  // dek 14/02 - greyed out Setting Dpad 
  // TO-DO: add an input pin and switch that enables user to switch between Dpad mode and left analog stick mode (e.g open = analog mode / closed = dpad mode)
  //
  //ignore sending Dpad input code, as we're going use the dpad to pretend to be a left analog stick with predefined direction values (see left analog code further below).
    //XInput.setDpad(dpadUp, dpadDown, dpadLeft, dpadRight); //ignored
  

  // Set left analog joystick values based Dpad input...
  
  if (UseLeftJoystick == true) {
      int leftJoyX;
      int leftJoyY;

    // Dek 14/02 
    //if a digital microswitch is pressed it will assign an value to mimic the analog direction.
    //It will force the extreme direction e.g. 100% = 1023 (direction), 50% = 511 (for middle/deadzone), 0% = 0 (other direction)


    // UP OR DOWN - tests both pins to determine direction.
     if (dpadUp == HIGH && dpadDown == LOW){
      leftJoyY = 1023; //UP  
    }else if (dpadUp == LOW && dpadDown == HIGH){
      leftJoyY = 0; //DOWN 
    }else {
      leftJoyY = 511; //MIDDLE - eg if no dpad directions selected, return the virtual analog stick to the centre. 
    }

    // LEFT OR RIGHT
    if (dpadLeft == HIGH && dpadRight == LOW) {
      leftJoyX = 1023; //LEFT 
    } else if (dpadLeft == LOW && dpadRight == HIGH) {
      leftJoyX = 0; //RIGHT
    }else{
      leftJoyX = 511; //MIDDLE 
    }
     
  
    //Dek 14/2 - because we are using Dpad as left analog, we don't want it to invert up/down. This is hardcoded to false.
      boolean invert = false;

      XInput.setJoystickX(JOY_LEFT, leftJoyX);
      XInput.setJoystickY(JOY_LEFT, leftJoyY, invert);
    }

    // Send all control data to the computer
    XInput.send();
  }
