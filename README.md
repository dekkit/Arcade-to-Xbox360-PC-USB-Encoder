# Arcade-to-Xbox360-PC-USB-Encoder
This is a modification of the examples provided within the fantastic ArduinoXinput project (see https://github.com/dmadison/ArduinoXInput).

This project will enable you to wire your arcade / fighting stick to an arduino micro pro - it will appear within your windows pc as an 'Xbox 360 for Windows' usb device.   This is useful for many games that expect a windows gamepad without the need for additional software to emulate xbox gamepads.


Key modifications
- I've adapted the code to be better aligned with the Pro Micro and for use with building your own DIY Arcade Joysticks and control panels.
- I've changed directional pad (up,down,left,right) to output as the left analog stick (using pre-defined values).   I found a few  arcade ports in steam that were relying on the player using the left analog stick. I've left the dpad code in, in case anyone needs revert it.
- Moved the pin assignments around to better fit the pro micro layout (see pinout / wiring diagram below).
- Removed some of the 'inverse' logic as it is no longer using analog sticks as inputs.
- Included additional notes in case you'd like to make your own code changes.

## Wiring Diagram
Note this is specific to an Arduino Pro Micro, if using other arduino models make sure you check pin numbering as they do vary between models.

<img width="709" height="654" alt="image" src="https://github.com/user-attachments/assets/d3e4c7ec-b9d7-451e-aa7e-f613693880ce" />

## Background
See the original project here: https://github.com/dmadison/ArduinoXInput for more details about Xinput.
This library lets you easily emulate an Xbox 360 controller using a USB-capable Arduino microcontroller.  There are many examples if you'd like to experiment with the code and make your own custom gamepads/ arcade projects.

## Hardware - Pro Micro
- I used a cheap clone Pro Micro  5v, running at 16Mhz

## Installing Boards / Libraries
Before you install the .ino file provided in this github,  you must add an 'Xinput' edition of the Pro Mico board to the Arduino IDE.   While the original github explains the reasons for this. if you don't do this, it simply will not appear as an xbox for windows device.

- **Install a compatible boards package** for Pro Micro (more info: https://github.com/dmadison/ArduinoXInput#compatible-boards) - please note that the Pro Micro appears under both 'Arduino AVR Core Boards' AND 'SparkFun AVR Boards' and both worked for my cheap clone Pro Micro board... it should look something like this:
	<img width="662" height="362" alt="image" src="https://github.com/user-attachments/assets/0be76047-36df-4ff7-88c7-2d871df429aa" />
	- type in 'Xinput' and select the latest versions to install.
	<img width="786" height="443" alt="image" src="https://github.com/user-attachments/assets/d460783d-729e-44d4-a08d-361989626ea8" />
- if you cannot see Xinput listed, refer back to the instructions linked above to ensure the boards will appear in your list or in case i've missed a step.
- **Install the Xinput library**  (further info about installing libraries can be found here - https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries/ ) ... it should look something like this
  
	<img width="430" height="321" alt="image" src="https://github.com/user-attachments/assets/0649e375-f13c-4e81-9728-5d4597be3df8" />

	<img width="786" height="443" alt="image" src="https://github.com/user-attachments/assets/6bba038f-0f84-484d-9a20-b591313c0ec0" />

- Install the library and you should now be good to use the .ino file provided in this repository.

## Installing project on Pro Micro
- Connect your arduino to pc
- Open the .ino file within this respository in Arduino IDE (**download ino file from here:** [Arcade to Xbox360 PC USB Encoder](https://github.com/dekkit/Arcade-to-Xbox360-PC-USB-Encoder/tree/master/Arcade%20to%20Xbox360%20PC%20USB%20Encoder))
- Under Tools > Board:  select the Pro Micro with Xinput  (if using the Sparkfun - check to make sure 5v, 16MHZ is selected) AND  make sure the correct port number is selected.
  	<img width="830" height="363" alt="image" src="https://github.com/user-attachments/assets/124244ee-bf2b-4f1a-88f4-b721e490fca6" />
	
- Under Sketch > select 'Upload'

Once the pro micro has been programmed, it will no longer be recognised by the Ardunio IDE.   You can now test the device, by  using Windows + R (run window) and typing "joy.cpl"
## Testing encoder
Connecting each input pin to ground will activate the button or direction - this will help ensure that you have wired your buttons / joystick correctly.

<img width="400" height="455" alt="image" src="https://github.com/user-attachments/assets/7d061b66-fd37-4e82-9c5d-d5e1e665a61b" />



## Oops! - how do i reprogram the Pro Micro?
if the steps don't work or you need to re-program on the arduinio, you'll need to perform a hardware reset.
- this is achieved by joining the **RST pin** and the **GND pin**
- once done, it will temporarily be seen by the Arduino IDE (you have about 8 seconds to  upload a new sketch).
- If you keep running  of time, you can create a new blank sketch and upload that to the arduino
- To do this successfully, in the board settings, i select the Arduino Micro as follows (note i select a board edition without Xinput), then upload a blank new sketch.
- This will stop the board disconnecting after 8 seconds and enable you to upload any sketch.

  <img width="758" height="423" alt="image" src="https://github.com/user-attachments/assets/d1121514-f679-4549-9ba7-e909722fdb2b" />
