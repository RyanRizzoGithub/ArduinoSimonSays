
// Initialize global variables
int currState = 0;
int level = 1;
int answers[40];
int sequence[40];
int selected;
boolean correct = false;
boolean winning = false;

// Create variables for leds
int n1 = 2;
int n2 = 3;
int n3 = 4;
int n4 = 5;
int n5 = 10;

// Create variables for buzzer
int p1 = A0;
int c = 200;
int d = 1200;
int e = 2500;
int f = 6000;
int g = 12000;
  
// Create variables for buttons
int s1 = 6;
int s2 = 7;
int s3 = 8;
int s4 = 9;
int s5 = 11;

int startTune[] = {c, e, g};
int winTune[] = {c, d, e, f, g};

void setup() {
  // Initialize serial
  Serial.begin(9600);
  // Set leds as input
  pinMode(n1, INPUT);
  pinMode(n2, INPUT);
  pinMode(n3, INPUT);
  pinMode(n4, INPUT);
  pinMode(n5, INPUT);
  
  // Set buzzer as input
  pinMode(p1, INPUT);
  
  // Set buttons as output
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s4, OUTPUT);
  pinMode(s5, OUTPUT);
}

void loop() {
  // Wait for system boot
  if (currState == 0) {
    turnOnSystem();
    currState = 1;
  }
  // Create the random pattern
  if (currState == 1){
    generateRandomPattern();
    currState = 2;
  }
  // Set the level back to 1
  else if (currState == 2) {
    resetLevel();
    currState = 3;
  }
  // Display the current pattern
  else if (currState == 3) {
    displayCurrentPattern();
    currState = 4;
  }
  // Read the users input
  else if (currState == 4) {
    readUserInput();
    currState = 5;
  }
  // Check if user input is correct
  else if (currState == 5) {
    correct = checkUserInput();
    currState = 6;
  }
  // Check if game is over
  else if (currState == 6){
     if (correct == true) {
        checkWinCon();
        currState = 8;
     } else {
       currState = 7;
     }
  }
  // Display game loss sequence
  else if (currState == 7) {
    lossTuneFunction();
    displayLoss();
    level = 1;
    currState = 1;
  }
  // Level up
  else if (currState == 8){
    level++;
    currState = 3;
  }
  
}
/*  This function is responsible for turning on
 *  the game. It waits for the user to press 
 *  s5.
 */
void turnOnSystem(){
    digitalWrite(n5, LOW);
    while (digitalRead(s5) == LOW) {
    }
    // Turn on white led
    digitalWrite(n5, HIGH);
    // Play the start sequence
    playTune(startTune, 3);
    delay(500);
}

/*  This function creates the random pattern which
 *  the game uses. This function only needs to run
 *  once each iteration.
 */
void generateRandomPattern(){
  // Generate random sequence
  Serial.println("Sequence");
  for (int i=0; i<40; i++){
    sequence[i] = random(2, 6);
    Serial.print(sequence[i]);
    Serial.print(", ");
  }
  Serial.println(" ");
}

/*  This function resets the level to 1 */
void resetLevel() {
  level = 1;
}

/*  This function displays one step of the sequence, per
 *  level the user has achieved
 */
void displayCurrentPattern() {
  Serial.println("Sequence Display");
  for (int i=0; i < level; i++) {
     digitalWrite(sequence[i], HIGH);
     playTone(sequence[i]);
     delay(750);
     digitalWrite(sequence[i], LOW);
     delay(250);
    Serial.print(sequence[i]);
    Serial.print(", ");
  }
  Serial.println("");
}

/*  This function is used to determine which button the
 *  user selected.
 */
void readUserInput() {
  for (int i=0; i < level; i++) {
    // Wait for input
    while (digitalRead(s1) == LOW && 
      digitalRead(s2) == LOW &&
      digitalRead(s3) == LOW &&
      digitalRead(s4) == LOW) {
      delay(10);
      }
    // Determine which button was selected
    if (digitalRead(s1) == HIGH) {
          while (digitalRead(s1) == HIGH){
          }
          answers[i] = n1;
          selected = n1;
    }
    else if (digitalRead(s2) == HIGH) {
          while (digitalRead(s2) == HIGH) {
          }
          answers[i] = n2;
          selected = n2;
    }
    else if (digitalRead(s3) == HIGH) {
          while (digitalRead(s3) == HIGH) {
          }
          answers[i] = n3;
          selected = n3;
      }
      else if (digitalRead(s4) == HIGH) {
          while (digitalRead(s4) == HIGH) {
          }
          // update the arrayl
          answers[i] = n4;
            selected = n4;
      }
    Serial.print("User selected ");
    Serial.println(selected);
  }
}

/*   This function is used to determine is the button
 *   the user selected corrolates to the correct part
 *   in the sequence
 */
boolean checkUserInput(){
  for (int i=0; i<level; i++){
      if (sequence[i] != answers[i]) {
          Serial.println("Incorrect Choice");
          Serial.print("sequence[i] = ");
          Serial.println(sequence[i]);
          Serial.print("answers[i] = ");
          Serial.println(answers[i]);
          return false;
      }
    } 
    Serial.println("Correct Answer");
    return true;
}

/*   This function determines if the win condition
 *   has been met. In this case, the win condition
 *   is completion of level 40, good luck.
 */
void checkWinCon(){
    if (level == 40) {
      playTune(winTune, 5);
      displayWin();
      level = 0;
    }
    currState = 3;
}

/*  This function displays the winning sequence */
void displayWin() {
    digitalWrite(n1, HIGH);
    delay(250);
    digitalWrite(n2, HIGH);
    delay(250);
    digitalWrite(n1, LOW);
    digitalWrite(n3, HIGH);
    delay(250);
    digitalWrite(n2, LOW);
    digitalWrite(n4, HIGH);
    delay(250);
    digitalWrite(n3, LOW);
    digitalWrite(n1, HIGH);
    delay(250);
    digitalWrite(n4, LOW);
    digitalWrite(n2, HIGH);
    delay(250);
    digitalWrite(n1, LOW);
    digitalWrite(n3, HIGH);
    delay(250);
    digitalWrite(n2, LOW);
    digitalWrite(n4, HIGH);
    delay(250);
    digitalWrite(n3, LOW);
    digitalWrite(n1, HIGH);
    delay(250);
    digitalWrite(n4, LOW);
    digitalWrite(n2, HIGH);
    delay(250);
    digitalWrite(n1, LOW);
    digitalWrite(n3, HIGH);
    delay(250);
    digitalWrite(n2, LOW);
    digitalWrite(n4, HIGH);
    delay(250);
    digitalWrite(n3, LOW);
    digitalWrite(n1, HIGH);
    delay(250);
    digitalWrite(n4, LOW);
    digitalWrite(n2, HIGH);
    delay(250);
    digitalWrite(n1, LOW);
    digitalWrite(n3, HIGH);
    delay(250);
    digitalWrite(n2, LOW);
    digitalWrite(n4, HIGH);
    delay(250);
    digitalWrite(n3, LOW);
    digitalWrite(n1, HIGH);
    delay(250);
    digitalWrite(n4, LOW);
    delay(250);
    digitalWrite(n1, LOW);
}

/* This function displays the losing dequence */
void displayLoss(){
    digitalWrite(n1, HIGH);
    digitalWrite(n2, HIGH);
    digitalWrite(n3, HIGH);
    digitalWrite(n4, HIGH);
    delay(500);
  
    digitalWrite(n1, LOW);
    digitalWrite(n2, LOW);
    digitalWrite(n3, LOW);
    digitalWrite(n4, LOW);
    delay(500);
  
    digitalWrite(n1, HIGH);
    digitalWrite(n2, HIGH);
    digitalWrite(n3, HIGH);
    digitalWrite(n4, HIGH);
    delay(500);
  
    digitalWrite(n1, LOW);
    digitalWrite(n2, LOW);
    digitalWrite(n3, LOW);
    digitalWrite(n4, LOW);
    delay(500);
    
    digitalWrite(n1, HIGH);
    digitalWrite(n2, HIGH);
    digitalWrite(n3, HIGH);
    digitalWrite(n4, HIGH);
    delay(500);
  
    digitalWrite(n1, LOW);
    digitalWrite(n2, LOW);
    digitalWrite(n3, LOW);
    digitalWrite(n4, LOW);
    delay(500);
}

/* Given a pin, this function will play the note which correlates
 *  to it
 */
void playTone(int pin) {
  if (pin == 2) {
    tone(p1, c, 10);
  }
  if (pin == 3) {
    tone(p1, d, 10);
  }
  if (pin == 4) {
    tone(p1, e, 10);
  }
  if (pin == 5) {
    tone(p1, f, 10);
  }
}

/*  Given an array and its size, where each element in the
 *  array is a note, this function plays each note
 */
void playTune(int tune[], int size){
  int i = 0;
  delay(200);
  for (int i = 0; i <= size; i++) {
    Serial.print(tune[0]);
    tone(p1, tune[i], 10);
    delay(500);
  }
}
/*  This function plays the losing song. This could not be
 *   played with the playTune function because of its 
 *   functionality.
 */
void lossTuneFunction(){
  for (int i=4000; i>2000; i--) {
    tone(p1, i);
    delay(1);
    noTone(p1);
  }
}
