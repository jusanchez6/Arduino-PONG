# Arduino-PONG
One day I was bored in my summer vacations and I just did this, it could be upgrade of many ways but I think it is a good start. 

the first version published as "V1.0" contains the base game with very essencial functions

Things done:
1. Start screen and butom
2. score limit and Winner screen
3. Two players mode

however I found a problem with my screen resolution and I change the values of the Width and Heght, this values could be change
easily just adjusting the definition of SCREEN_WIDHT and SCREEN_HEIGHT. The previous definition could be find in the very top of
code.

The screen uses an I2C communication protocol, it means in Arduino nano goes connected:

SDA-------> A4

SCL-------> 45

GND-------> GND

Vcc-------> 5v

I did not taste, but it could run on Arduino Uno, if this is your case check the pin out for the conection of the I2C
oled screen in the follow page: https://docs.arduino.cc/hardware/uno-rev3
The configuration used in the star butom was a pull-dowm resistence on pin 5.

And for the movement of the paddles it could be use two potenciometers connected in pin A0 for player 1, and
pin A1 for player 2


Things I would like to do:
1. Sound
2. mode select screen
3. vs pc game mode
4. adjustable velocity in a menu
5. fix the oled screen resolution
6. effect in paddles-ball bounce


Some functions has been taken from the DANNI FR project, you can take a look to his project in the follow page:
https://www.instructables.com/PONG-con-Arduino/
Thaks to him :) 



