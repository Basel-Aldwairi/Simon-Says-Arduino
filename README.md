# Simon Says Arduino
Simon says and a reaction time game on an Arduino Uno

Basel Al-Dwairi

Use the code written in the SimonSays.ino and build the circuit like the one in diagram.json

In order to see how the diagram looks, copy the contents into Wokwi 
(https://wokwi.com/projects/new/arduino-uno )

Simon says: long press the green button when in natural mode(the lights flicker). Copy the moves of the lights. If you fail, the light animation will play ( all lights will flicker 3 times ) and the board will go to natural mode. If you win, the light animation will play and then all of the lights will turn off.

Whac-A-Mole: long press the yellow button when in natural mode. Press the lights as soon as they are seen, if you are too slow, the light animation will play and the board will go back to natural mode. If you win, the animation will play and all lights will turn off.

When all lights are off, enter the code [green, yellow, blue, red], and the board will go back to natural mode. 