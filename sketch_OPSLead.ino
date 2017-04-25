// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
#define led1 2
#define led2 4
#define led3 6
#define in1 A5
#define in2 A4
#define in3 A3

int previous1 = 0;
int previous2 = 0;
int previous3 = 0;

String playercombo = "";
String gamecombo = "";
  
// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(in3, INPUT);

  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  int read3 = digitalRead(in3);
  int read2 = digitalRead(in2);
  int read1 = digitalRead(in1);
  
  if(read3 == 0 && previous1 == 0){  //farthest in
    digitalWrite(led3, LOW);
    previous1 = 1;
  }
  if(read3 != 0 && previous1 == 1){
    digitalWrite(led3, HIGH);
    previous1 = 0;
    playercombo += "r";
  }
  
  if(read2 == 0 && previous2 == 0){    //middle
    digitalWrite(led2, LOW);
    previous2 = 1;
  }
  if(read2 != 0 && previous2 == 1){
    digitalWrite(led2, HIGH);
    previous2 = 0;
    playercombo += "g";
  }
  
  if(read1 == 0 && previous3 == 0){  //most out
    digitalWrite(led1, LOW);
    previous3 = 1;
  }
  if(read1 != 0 && previous3 == 1){
    digitalWrite(led1, HIGH);
    previous3 = 0;
    playercombo += "b";
  }
  if(playercombo.length() == gamecombo.length() && previous1 == 1 && previous2 == 1 && previous3 == 1)
    checkValid();
}

void nextturn(){
  playercombo = "";

  if(gamecombo.length()==0){
    for(int i = 0; i < 2; i++){
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
  
  int color = random(0,3);
    if(color == 0)
      gamecombo += "r";
    else if(color == 1)
      gamecombo += "g";
    else if(color == 2)
      gamecombo += "b";
    else
      gamecombo += "!";

    for(int i = 0; i < gamecombo.length(); i++){
      if(gamecombo[i] == 'r'){
        digitalWrite(led3, HIGH);
        delay(500);
        digitalWrite(led3, LOW);
        delay(500);
      }
      if(gamecombo[i] == 'g'){
        digitalWrite(led2, HIGH);
        delay(500);
        digitalWrite(led2, LOW);
        delay(500);
      }
      if(gamecombo[i] == 'b'){
        digitalWrite(led1, HIGH);
        delay(500);
        digitalWrite(led1, LOW);
        delay(500);
      }
    }
    Serial.print(";");
    Serial.print(gamecombo);
}

void lose(){
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  delay(500);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  gamecombo="";
  delay(500);
}

void checkValid(){
    for(int i = 0; i < playercombo.length(); i++){
      if(playercombo[i] != gamecombo[i])
        lose();
    }
    delay(1000);
    nextturn();
}


