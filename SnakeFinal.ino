#include <LedControl.h>
#include <math.h>
#include <stdlib.h>
 
LedControl lc=LedControl(12,11,10,1); //LedControl(int dataPin, int clkPin, int csPin, int numDevices);
   
  int numbers[11][8][8] = {{
  {0,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {
  {0,0,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,1,1,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,1,1,1,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {
 
  {0,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,1,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {
 
  {0,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,1,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {
 
  {0,0,0,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  },
  {
 
  {0,0,0,0,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {
  
  {0,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,1,1,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {
 
  {0,0,0,0,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {0,1,0,0,0,0,0,0},
  {0,1,0,0,0,0,0,0},
  {0,1,0,0,0,0,0,0},
  {0,1,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {
 
  {0,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {
 
  {0,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,1,1,0,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {
 
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  }}; 
 
 
const int LRin = A0;
const int UDin = A1;
 
bool blinkFruit = true; //switch every loop to blink fruit.
unsigned moveDir = 0; //0 = right, 1 = up, 2 = left, 3 = down.
unsigned currMoveDir = 0;//Used to keep track of actual current direction, not just last set during a cycle
int length = 1;  //Starting length.
int last[64][2]; //the matrix
int x = 3; //Start position
int y = 2; //start position
int lastId = 0; //The position of the snake in the previous step.
bool collision = false; //Set to true if collision.
bool incLength = false;
int fruitPos[2];  //Holds the position of the fruit. 
long timer = 0;// Check for user input every cycle
bool fruitOnScreen = false;
int looper = 0;
int speed = 300;
long time;
long timeFruit;
void setup() {
  
  for (int i = 0; i < 64; i++){ //set all positions outside the screen - for checking collisions after
    last[i][0] = -1;
    last[i][1] = -1; 
  }
   
  //Set up display
  for (int i = 0; i < 1; i++)
  {
    lc.shutdown(i,false);
    // Set the brightness to medium values
    lc.setIntensity(i,10);
    // and clear the display 
    lc.clearDisplay(i);
  }
 
}
 
void loop() { 

  time = millis();
  looper++;
  looper = looper % speed;
  checkMove();
  if (looper == 0) doMove();
  if (looper == 0) checkCollision();
  if (collision) 
  { 
    gameOver();
  }
  
  fruitCollision(); //Check if fruit has been eaten
 
  while (!fruitOnScreen) createFruit(); //randomize new fruit position until a valid position is set
   
  if (looper % 100 == 0)fruitBlink();
  delay(1);
}
 
void gameOver()
{
  while (true)
  {
    lc.clearDisplay(0);//clear display 
    speed=300;
    delay(100);
    printScore(length-1);
    delay(500);
  } 
}
 
void printScore(int x)
{
  unsigned a,b;
  if (x > 10)//if the score has 2 digits, construct those digits
  {
    a = x/10;
    b = x-(a*10); 
  }
  else if (x == 10){
    a = 1;
    b = 0;
  }
  else{//when score between 0 and 9, show it in the middle of the matrix - it has only one digit
    digit(x,2);
    return;
 
  }
  digit(b,0);//when the score has 2 digits, print those separately
  digit(a,4);
}
  

void digit(int nr, int offset)//Print a digit on the display
{
    for (int x = 0; x < 8; x++)
    {
      for (int y = 0; y < 8; y++)
      {
        if(numbers[nr][x][y] == 1) lc.setLed(0,y+offset,7-x,true); 
    } 
  }
}

void fruitBlink()//Blink the fruit
{
  if (blinkFruit) 
    lc.setLed(0,fruitPos[0],fruitPos[1],true);
  else 
    lc.setLed(0,fruitPos[0],fruitPos[1],false);
  if (blinkFruit == true)
    blinkFruit = false;
  else 
    blinkFruit = true;
}
 
void led(int x, int y){//Turn on led at position (x,y)
  if (!incLength)
  {
    //Turn off the last light at the tail and re-arrange array 
    lc.setLed(0,last[0][0], last[0][1],false); 
    for (int i = 0; i < length; i++)
    {
      last[i][0] = last[i+1][0];
      last[i][1] = last[i+1][1];
    }
  }
  else
  { 
    length++;
    incLength = false;
  }
 
  last[length][0] = x;
  last[length][1] = y;
  lc.setLed(0,last[length][0],last[length][1],true); // turn on led for the next position of the head
 
}
 
void checkMove(){//function that reads input from joystick
    
  int lr = analogRead(LRin);
  int ud = analogRead(UDin);
 
  if(lr > 800 && currMoveDir != 0) moveDir = 2; //Go right
  if(lr < 100 && currMoveDir != 2) moveDir = 0; //Go left
  if(ud > 800 && currMoveDir != 1) moveDir = 3; //Go up
  if(ud < 100 && currMoveDir != 3)  moveDir = 1; //Go down

  if (time % 500 == 0) 
   if (time - timeFruit >= 8000)
   {
    lc.setLed(0, fruitPos[0],fruitPos[1],false);
    createFruit();
    }
}
 
void doMove()//Move snake based on currentMoveDir
{
  currMoveDir = moveDir;
  
  if(moveDir == 0) x--;//Move snake to the left
  if(moveDir == 1) y++;//Move snake down
  if(moveDir == 2) x++;//Move snake to the right
  if(moveDir == 3) y--;//Move snake up
  
  led(x,y); 
}
 

void incrementLength()//increment length
{
  incLength = true; 
}
 
void createFruit()//create fruit
{
  timeFruit = millis();
  int xR = rand() % 8;
  int yR = rand() % 8;
 
  for (int i = 0; i <= length; i++)//checks if the random value for the candy is ok - not occupied by the snake
  {
    if (xR == last[i][0] && yR == last[i][1])
    {
      fruitOnScreen = false; 
      return;
    }
  }
  fruitPos[0] = xR;
  fruitPos[1] = yR;
  fruitOnScreen = true;
  lc.setLed(0,xR,yR,true);
}
 
void fruitCollision()//Check for collision with candy
{
  if(last[length][0] == fruitPos[0] && last[length][1] == fruitPos[1])
  {
    fruitOnScreen = false;//the fruit dissapears
    incrementLength();//the size of the snake increases

    if(speed > 50) speed = speed-30;
  }
}
 

void checkCollision()//Checks collision with snake and wall.
{
  int xP = last[length][0];
  int yP = last[length][1];
 
  if (xP == -1 || xP == 8 || yP == -1 || yP == 8)
  {
    collision = true;
    return;
  }
  else{
    for (int i = 0; i < length; i++)
    {
      if (last[i][0] == xP && last[i][1] == yP)
      {
        collision = true;
        return;
      }
    }
  }
}
