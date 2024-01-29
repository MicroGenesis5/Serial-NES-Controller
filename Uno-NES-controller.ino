// Serial NES Controller project: https://falconreach.net/_txt/nes.html

// Arduino NES controller for the game 'The Chessmaster'

int RIGHT = 2;
int LEFT = 3;
int DOWN = 4;
int UP = 5;
int START = 6;
int SELECT = 7;
int B = 8;
int A = 9;

int control = 13;

int btwnBtnPresses = 2500; // delay between different button presses
int buttonRegister = 350; // delay for button to register as a single button press (excluding during Select Menu)
int menuRegister = 120; // delay for a directional (up, downn, left, right) press during Select Menu

void setup() {

  pinMode(RIGHT, OUTPUT);
  pinMode(LEFT, OUTPUT);
  pinMode(DOWN, OUTPUT);
  pinMode(UP, OUTPUT);
  pinMode(START, OUTPUT);
  pinMode(SELECT, OUTPUT);
  pinMode(B, OUTPUT);  
  pinMode(A, OUTPUT);
  
  pinMode(control, OUTPUT);
  Serial.begin(9600);
 
  digitalWrite(RIGHT, HIGH);
  digitalWrite(LEFT, HIGH);
  digitalWrite(DOWN, HIGH);
  digitalWrite(UP, HIGH);
  digitalWrite(START, HIGH);
  digitalWrite(SELECT, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(A, HIGH);

  digitalWrite(control, LOW);

}

void loop() {

  String readString;
  String Q;

  // check serial port
  while (Serial.available()) {
    delay(1);
    if (Serial.available() > 0) {
      char c = Serial.read(); // gets one byte from serial buffer
      if (isControl(c)) {
        break;
      }
      readString += c; // makes the string readString
    }
  }

  Q = readString;

  // check serial read
  if (Q.charAt(0) == 'm') {    
    digitalWrite(control, HIGH);
  }

  if (digitalRead(control) == LOW) {
    delay(200);
  } else {

    delay(2000);
    digitalWrite(control, LOW); // reset control

    switch(Q.charAt(1)) {
      case 's':
        startGame();
        break;
      case 'n':
        newGame();
        break;
      case 'p':
        newGameBlack();
        break;
      case 'i':
        delay(btwnBtnPresses);
        buttonPress(A, buttonRegister);
        break;
      case 'j':
        forceMove();
        break;
      case 'l':
        computerLevel(Q.charAt(2));
        break;
      default:
        moveHand(Q.charAt(1), Q.charAt(2));
        break;
    }
    
  }
   
}

// starts a new game after the NES console is turned on
void startGame() {
      
  // press 'A' to pass intro menu #1
  delay(btwnBtnPresses);
  buttonPress(A, buttonRegister);

  // press 'A' to pass intro menu #2
  delay(btwnBtnPresses);
  buttonPress(A, buttonRegister);

  // wait for the chessboard to appear, press 'A' one more time to kill music
  delay(5000); 
  buttonPress(A, buttonRegister);

  // move hand to 'staging spot' 
  delay(btwnBtnPresses);
  buttonPress(LEFT, 1000);

  delay(3000);
    
}

// starts a new game from the chessboard screen (game has already been turned on)
void newGame() {

  // press 'Select'
  delay(btwnBtnPresses);  
  buttonPress(SELECT, buttonRegister);

  // press 'A' x2
  buttonRepeat(A, buttonRegister, 2);

  // move hand to 'staging spot'
  delay(btwnBtnPresses);
  buttonPress(LEFT, 1000);

  delay(3000);
  
}

// starts a new game from the chessboard screen (game has already been turned on) as black piece, ie player 2
void newGameBlack() {

  newGame();

  delay(4000);

  // press 'Select'
  delay(btwnBtnPresses);
  buttonPress(SELECT, buttonRegister);

  // press 'DOWN' x3
  buttonRepeat(DOWN, menuRegister, 3);

  // press 'A'
  delay(btwnBtnPresses);
  buttonPress(A, buttonRegister);

  delay(4000);

  /* Do the following on the Select Menu so the pointer goes back to the top of the menu 
     This is needed otherwise all commands involving the Select Menu won't work / will break */

  // press 'Select'
  delay(btwnBtnPresses);
  buttonPress(SELECT, buttonRegister);

  // press 'UP' x3
  buttonRepeat(UP, menuRegister, 3);

  // press 'Select'
  delay(btwnBtnPresses);
  buttonPress(SELECT, menuRegister);

  delay(3000);
  
}

// force the AI to move
void forceMove() {

  // press 'Select'
  delay(btwnBtnPresses);
  buttonPress(SELECT, buttonRegister);

  // press 'DOWN' x3 
  buttonRepeat(DOWN, menuRegister, 3);

  // press 'A'
  delay(btwnBtnPresses);
  buttonPress(A, buttonRegister);

  /* Do the following on the Select Menu so the pointer goes back to the top of the menu 
     This is needed otherwise all commands involving the Select Menu won't work and will break */

  // press 'Select'
  delay(btwnBtnPresses);
  buttonPress(SELECT, buttonRegister);

  // press 'UP' x4
  buttonRepeat(UP, menuRegister, 4);

  // press 'Select'
  delay(btwnBtnPresses);
  buttonPress(SELECT, buttonRegister);

  delay(3000);
  
}

// change the AI's level, note that this will start a new game
void computerLevel(char levelChar) {

  newGame();

  int level;

  if ((levelChar - '0' >= 1) && (levelChar - '0' <= 9)) {
    level = levelChar - '0';
  } else {
    switch (levelChar) {
      case 'a':
        level = 10;
        break;
      case 'b':
        level = 11;
        break;
      case 'c':
        level = 12;
        break;
      case 'd':
        level = 13;
        break;
      case 'e':
        level = 14;
        break;
      case 'f':
        level = 15;
        break;
      default:
        level = 0;
        break;
    }
  }

  // press 'Select'
  delay(btwnBtnPresses);
  buttonPress(SELECT, buttonRegister);

  // press 'UP' x7
  buttonRepeat(UP, menuRegister, 7);

  // press 'A' x number of times, depending on the level chosen by the player
  buttonRepeat(A, menuRegister, level);

  /* Do the following on the Select Menu so the pointer goes back to the top of the menu 
     This is needed otherwise all commands involving the Select Menu won't work and will break */

  // press 'DOWN' x7
  buttonRepeat(DOWN, menuRegister, 7);

  // press 'Select'
  delay(btwnBtnPresses);
  buttonPress(SELECT, buttonRegister);
    
}

// simulate a button press
void buttonPress(int button, int pressTime) {
  
  digitalWrite(button, LOW);
  delay(pressTime);
  digitalWrite(button, HIGH);  
  
}

// use when the same button needs to be pushed 
void buttonRepeat(int button, int pressTime, int repeat) {

  for (int i = 0; i < repeat; i++) {
    delay(btwnBtnPresses);
    buttonPress(button, pressTime);
  }
  
}

// moves the 'game hand' to pick up and drop chess pieces
void moveHand(char xCoordinateChar, char yCoordinateChar) {

  int xCoordinate;

  switch(xCoordinateChar) {
    case 'a':
      xCoordinate = 1;
      break;
    case 'b':
      xCoordinate = 2;
      break;
    case 'c':
      xCoordinate = 3;
      break;
    case 'd':
      xCoordinate = 4;
      break;
    case 'e':
      xCoordinate = 5;
      break;
    case 'f':
      xCoordinate = 6;
      break;
    case 'g':
      xCoordinate = 7;
      break;
    case 'h':
      xCoordinate = 8;
      break;
    default:
      xCoordinate = 0;
      break;
  }

  int yCoordinate = yCoordinateChar - '0';

  int delayHorizontal = 0;
  int delayVertical = 0;

  delayHorizontal = (200 * xCoordinate + 40);

  // 1. move hand from 'staging spot' to coordinate
  
  delay(btwnBtnPresses);
  
  buttonPress(RIGHT, delayHorizontal);
  
  delay(btwnBtnPresses);
  
  if ((yCoordinate >= 1) && (yCoordinate <= 4)) {
    delayVertical = 200 * (5 - yCoordinate);
    buttonPress(DOWN, delayVertical);
  } else if ((yCoordinate == 5) || (yCoordinate < 1) || (yCoordinate > 8)) {
    delayVertical = 0; // don't move hand up or down :) 
  } else { // 6 <= yCoordinate <= 8 
    delayVertical = 200 * (yCoordinate - 5);
    buttonPress(UP, delayVertical);
  }

  // 2. pick up or drop piece
  
  delay(btwnBtnPresses);
  
  buttonPress(A, buttonRegister);

  // 3. move hand from coordinate to 'staging spot'
  
  delay(btwnBtnPresses);

  if ((yCoordinate >= 1) && (yCoordinate <= 4)) {
    buttonPress(UP, delayVertical);
  } else if ((yCoordinate == 5) || (yCoordinate < 1) || (yCoordinate > 8)) {
    delayVertical = 0; // don't move hand up or down :)  
  } else { // 6 <= yCoordinate <= 8
    delayVertical = 200 * (yCoordinate - 5);
    buttonPress(DOWN, delayVertical);
  }    

  delay(btwnBtnPresses);
  
  buttonPress(LEFT, delayHorizontal);
  
}
