String playercombo = "";     //creating variables used for storing color combos and sensing rising edges in input pins
String gamecombo = "";

int previousButtonMode1 = 0;
int currentButtonMode1 = 0;
int previousButtonMode2 = 0;
int currentButtonMode2 = 0;
int previousButtonMode3 = 0;
int currentButtonMode3 = 0;

void setup() {
  DDRD |= 0b01010100;       //defining the output pins
  PORTD &= ~(0b01010100);   //setting output pins to start at low

  DDRC &= ~(0b00111000);    //defining the input pins
  
  Serial.begin(9600);       //for debugging purposes
}

void loop() {
  // put your main code here, to run repeatedly:

  previousButtonMode1 = currentButtonMode1;       //reassign previous and current
  previousButtonMode2 = currentButtonMode2;
  previousButtonMode3 = currentButtonMode3;
  
  currentButtonMode1 = (PINC & (1<<5));           //take in readings for each input pin
  currentButtonMode2 = (PINC & (1<<4));
  currentButtonMode3 = (PINC & (1<<3));

  if(currentButtonMode1 != previousButtonMode1){  //rising edge detection for red
    if(currentButtonMode1 != 0){                  //if currentButtonModel is not 0, then it is receiving a HIGH voltage 
      PORTD |= (1<<2);                            //write HIGH to output pin D2
      playercombo += "b";                         //add to player's string
    }
    else{
      PORTD &= ~(1<<2);                           //write LOW to output pin D2
    }
  }

  if(currentButtonMode2 != previousButtonMode2){  //rising edge detection for green
    if(currentButtonMode2 != 0){
      PORTD |= (1<<4);
      playercombo += "g";
    }
    else{
      PORTD &= ~(1<<4);
    }
  }

  if(currentButtonMode3 != previousButtonMode3){  //rising edge detection for blue
    if(currentButtonMode3 != 0){
      PORTD |= (1<<6);
      playercombo += "r";
    }
    else{
      PORTD &= ~(1<<6);
    }
  }

  if(playercombo.length() == gamecombo.length()){
    checkValid();
  }
}

void nextturn(){      //function for adding a new color to gamecombo and flashing lights in the right order
  
  playercombo = "";   //reset playercode to 0 for the next "turn"

  if(gamecombo.length()==0){        //if the game is starting on the first turn, gamecode will be length 0
    for(int i = 0; i < 2; i++){     //loop for adding 2 colors to gamecombo so that the game starts with at least 3 colors
    int color = random(0,3);
    if(color == 0)
      gamecombo += "r";
    else if(color == 1)
      gamecombo += "g";
    else if(color == 2)
      gamecombo += "b";
    else
      gamecombo += "!";
    }
  }
  
  int color = random(0,3);          //add new color to gamecombo
    if(color == 0)
      gamecombo += "r";
    else if(color == 1)
      gamecombo += "g";
    else if(color == 2)
      gamecombo += "b";
    else
      gamecombo += "!";

    for(int i = 0; i < gamecombo.length(); i++){  //flash colors for the player to see
      if(gamecombo[i] == 'r'){
        PORTD |= (1<<6);
        delay(500);
        PORTD &= ~(1<<6);
        delay(500);
      }
      if(gamecombo[i] == 'g'){
        PORTD |= (1<<4);
        delay(500);
        PORTD &= ~(1<<4);
        delay(500);
      }
      if(gamecombo[i] == 'b'){
        PORTD |= (1<<2);
        delay(500);
        PORTD &= ~(1<<2);
        delay(500);
      }
    }
}

void lose(){        //flash red then reset gamecombo to 0
  PORTD |= (1<<2);
  PORTD |= (1<<4);
  PORTD |= (1<<6);
  delay(500);
  PORTD |= (1<<2);
  PORTD |= (1<<4);
  PORTD |= (1<<6);
  playercombo="";
  gamecombo="";
  delay(500);
}

void checkValid(){    //checks whether the player's combo matches with the correct combo
    for(int i = 0; i < playercombo.length(); i++){
      if(playercombo[i] != gamecombo[i])
        lose();
    }
    delay(1000);
    nextturn();
}
