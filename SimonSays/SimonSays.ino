//BUTTON VAR

const int buttonA = 2;
const int buttonB = 3;
const int buttonC = 4;
const int buttonD = 5;

//STATE VAR

int stateA = 0;
int stateB = 0;
int stateC = 0;
int stateD = 0;

//LIGHT VAR

const int lightA = 8;
const int lightB = 9;
const int lightC = 10;
const int lightD = 11;

//GAME VAR

int game = 0;
const int maxGame = 10;
int simonSaysArray[maxGame];
int level = 0;
int reactInt = 0;
int reacted;
int curr = 0;
int maxReact = 20;
int playerRestartArray[4];
int restartArray[4] = {0,1,2,3};

//READ INPUT

void readInput(){
  stateA = digitalRead(buttonA);
  stateB = digitalRead(buttonB);
  stateC = digitalRead(buttonC);
  stateD = digitalRead(buttonD);
}

void  delayedReadInput(int rec){
  for(int i = 0; i<rec ; i++){
    readInput();
    if(checkPressed()) return;
    delay(10);
  }
}


// Check if anything is pressed

bool checkPressed(){
  if(stateA == 1 || stateB == 1 || stateC == 1 || stateD == 1)
  return true;
  return false;
}

//NATURAL Mode

void natural(){
  digitalWrite(lightA, HIGH);
  digitalWrite(lightB, LOW);
  digitalWrite(lightC, LOW);
  digitalWrite(lightD, LOW);

  //Loops forwards to see if anything has been pressed
  int pin;
  const int delayTime = 150;
  delay(delayTime);
  for(int i =0; i<4;i++){
    pin = i + 8;
    digitalWrite(pin, HIGH);
    if(pin != 8 || pin != 11) delay(delayTime);
    digitalWrite(pin, LOW);
    readInput();
    if(checkPressed()) return;
  }

  //Loops backwards
  for(int i = 4; i> 0;i--){
    pin = 7 + i;
    digitalWrite(pin, HIGH);
    if(pin != 11 || pin != 8) delay(delayTime);
    digitalWrite(pin, LOW);
    readInput();
    if(checkPressed()) return;
  }
}

//BLINK animation

void blinking(){
  int pin;
  for(int i = 0; i<3 ; i++){
    for(int j = 0; j < 4; j++){
      pin = j + 8;
      digitalWrite(pin,HIGH);
    }
    delay(200);
    for(int j = 0; j < 4; j++){
      pin = j + 8;
      digitalWrite(pin,LOW);
    }
    delay(200);
  }
}

//GAMES

void newGame(){
  level = 0;
}

void add(){
  level++;
}

//SHOW BUTTONS LIGHT

void lightUp(int time){

  int pin;

  if(game == 1){
   pin = simonSaysArray[curr];
  }else if(game == 2){
    pin = reactInt;
  }
  switch(pin){
    case 0: digitalWrite(lightA, HIGH);
            delay(time);
            digitalWrite(lightA, LOW);
            break;
    case 1: digitalWrite(lightB, HIGH);
            delay(time);
            digitalWrite(lightB, LOW);
            break;
    case 2: digitalWrite(lightC, HIGH);
            delay(time);
            digitalWrite(lightC, LOW);
            break;
    case 3: digitalWrite(lightD, HIGH);
            delay(time);
            digitalWrite(lightD, LOW);
            break;
    defult:break;        
  }

  digitalWrite(lightA, LOW);
  digitalWrite(lightB, LOW);
  digitalWrite(lightC, LOW);
  digitalWrite(lightD, LOW);

  delay(500);

}

//TEST

void test(){
  for(int i = 0 ; i < maxGame ; i++){
    add();
  }
  for(curr = 0 ; curr < maxGame ; curr++){
    lightUp(500);
  }
  blinking();
  game = 2;
  level = 0;
}

//SIMON RANDOM

void randomize(){

  if(game == 1){
    for(int i = 0; i < maxGame; i++){
      simonSaysArray[i] = random(0,4);
    }
  }
  if(game == 2){
    reactInt = random(0,4);
  }

  if(game == 3){

  }
}

//SIMON GAME

void simonSays(){

  int gameState = 0;
  level = 0;
  randomize();

  while(true){
    if(gameState == 0){

      add();
      for(curr = 0 ; curr < level ; curr++){
      lightUp(500);
      }
      gameState = 1;
    }

    if(gameState == 1){
      for(curr = 0; curr < level; curr++){
        delayedReadInput(500);
        if(lightButton(300) != simonSaysArray[curr]){
          fail();
          return;
        }
      }
    }
    delay(500);
    gameState = 0;

    if(level == maxGame){
      win();
      return;
    }
  }
}

//WIN AND FAIL

void fail(){
  blinking();
  game = 0;
  level = 0;
  randomize();
}

void win(){
  blinking();
  game = 5;
  level = 0;
  randomize();
}

void permaLight(){
  int pin = reactInt;

  switch(pin){
    case 0: digitalWrite(lightA, HIGH);
            return;
    case 1: digitalWrite(lightB, HIGH);
            return;        
    case 2: digitalWrite(lightC, HIGH);
            return;
    case 3: digitalWrite(lightD, HIGH);
            return;
    default:return ;
  }
}

//WHAC-A-MOLE

void reactGame(){

  int reactTime;
  while(true){
    randomize();
    permaLight();
    reactTime = 150 - 5*level; 
    delayedReadInput(reactTime);
    if(lightButton(reactTime) != reactInt){
      fail();
      return;
    }else if(level == maxReact-1){
      win();
      return;
    }
    add();
    delay(reactTime + 2*level);

  }
}

//BUTTON SELECT

int lightButton(int del){
  while(true){
    readInput();
    if(stateA == HIGH){
      digitalWrite(lightA, HIGH);
      delay(del);
      digitalWrite(lightA, LOW);
      stateA = 0;
      return 0;
    }
    if(stateB == HIGH){
      digitalWrite(lightB, HIGH);
      delay(del);
      digitalWrite(lightB, LOW);
      stateB = 0;
      return 1;
    }
    if(stateC == HIGH){
      digitalWrite(lightC, HIGH);
      delay(del);
      digitalWrite(lightC, LOW);
      stateC = 0;
      return 2;
    }
    if(stateD == HIGH){
      digitalWrite(lightD, HIGH);
      delay(del);
      digitalWrite(lightD, LOW);
      stateD = 0;
      return 3;
    }
    return 9;
  }
}

void gameRestart(){
  curr =0;
  while(true){
    delayedReadInput(500);
    int pin = lightButton(200);
   if(restartArray[curr] != pin){
      curr = 0;
    }else curr++;
    if(curr == 4){
      curr = 0;
      game = 0;
      return;
   }
  }
}

//RUN

void setup() {
 
  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  pinMode(buttonC, INPUT);
  pinMode(buttonD, INPUT);

  pinMode(lightA, OUTPUT);
  pinMode(lightB, OUTPUT);
  pinMode(lightC, OUTPUT);
  pinMode(lightD, OUTPUT);

  randomize();

  game = 0;

}

void loop() {

  randomize();

  if(checkPressed() && game == 0){
    if(lightButton(300) == 0){ 
      game = 1;
      blinking();
    }
    else if(lightButton(300) == 1){ 
      game = 2;
      blinking();
    }
    stateA = 0;
    stateB = 0;
    stateC = 0;
    stateD = 0;
    
  }

  if(game == 1){
    simonSays();
  }
  if(game == 2){
    reactGame();
  }

  if(game == 5){
    gameRestart();
  }


  if(game == 0){
    natural();
  }
}
