# Simon Says Arduino

___

Basel Al-Dwairi

Simon Says and Wach-A-Mole on an Arduino Uno


Use the code in SimonSays.ino, and Build the circuit shown on [Wokwi][1] when using the provided diagram.json 

___

### Games :

1. Simon says:
   - Copy the pattern of the lights. 
   - Long press the Green button to start when in Natural mode
2. Whac-A-Mole:
   - Press the Buttons as soon as their corresponding Lights turn on.
   - Long press the Yellow button to start when in Natural mode.
___

### Modes :

1. Natural : 
   - Lights flicker from one side to the other, used when no games are played
2. Win / Lose : 
   - All Lights flicker 3 times:
   - Win : Goes to Finished
   - Lose : Goes to Natural
3. Finished : 
   - All lights turn off
   - To go back to Natural, enter the code (green, yellow, blue, red)


[1]: https://wokwi.com/projects/new/arduino-uno 'Wokwi'