// LED Chaser Game with 555 Timer & 4017 Counter

// LED pins connected to 4017 outputs
const int LED_PINS[] = {4, 7, 5, 3, 13, 8};  // Blue, Red, Yellow, Blue, Red, Yellow
const int LED_COUNT = 6;

// RGB LED pins (Common Anode)
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

// Game controls
const int BUTTON_PIN = 2;

// Game state
int score = 0;
int targetColor = 0;  // 1=blue, 2=red, 3=yellow
int currentLed = 0;
bool buttonWasPressed = false;

// Color definitions
const String COLORS[] = {"blue", "red", "yellow"};

void setup() {
  Serial.begin(9600);
  
  // Configure LED input pins
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], INPUT);
  }
  
  // Configure RGB outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  
  // Configure button
  pinMode(BUTTON_PIN, INPUT);
  
  // Initialize game
  welcomeMessage();
  randomSeed(analogRead(0));
  pickNewColor();
}

void loop() {
  // Detect currently lit LED
  detectActiveLED();
  
  // Handle button press
  handleButton();
}

void detectActiveLED() {
  for (int i = 0; i < LED_COUNT; i++) {
    if (digitalRead(LED_PINS[i]) {
      currentLed = i;
      break;
    }
  }
}

void handleButton() {
  int buttonState = digitalRead(BUTTON_PIN);
  
  if (buttonState == HIGH && !buttonWasPressed) {
    buttonWasPressed = true;
    processGuess();
  }
  
  if (buttonState == LOW) {
    buttonWasPressed = false;
  }
}

void processGuess() {
  String currentColor = getColorFromIndex(currentLed);
  String target = COLORS[targetColor - 1];
  
  // Check if correct
  if (currentColor == target) {
    score++;
    Serial.println("Correct! +1");
  } else {
    score--;
    Serial.println("Wrong! -1");
  }
  
  Serial.print("Score: ");
  Serial.println(score);
  
  // Check win/lose conditions
  if (score == 5 || score == -5) {
    Serial.println(score == 5 ? "You Win! " : "You Lose! ");
    Serial.println("Game resetting...");
    resetGame();
  } else {
    pickNewColor();
  }
}

void setColor(String color) {
  // Common anode: LOW = ON, HIGH = OFF
  if (color == "blue") {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);
  } 
  else if (color == "red") {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, HIGH);
  } 
  else if (color == "yellow") {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);  // Adjusted for better yellow
    digitalWrite(BLUE_PIN, HIGH);
  }
  else {
    // Turn off all
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, HIGH);
  }
}

void pickNewColor() {
  targetColor = random(1, 4);  // 1-3
  setColor(COLORS[targetColor - 1]);
  
  Serial.print("Target Color: ");
  Serial.println(COLORS[targetColor - 1]);
  Serial.println("Press button when matching LED lights up!\n");
}

String getColorFromIndex(int index) {
  // LEDs: 0/3=blue, 1/4=red, 2/5=yellow
  return COLORS[index % 3];
}

void resetGame() {
  score = 0;
  delay(1500);  // Pause before restart
  Serial.println("Score reset. New round starting...\n");
  pickNewColor();
}

void welcomeMessage() {
  Serial.println("=== LED CHASER GAME ===");
  Serial.println("Match the RGB color with the");
  Serial.println("lit LED and press the button");
  Serial.println("+1 point for correct match");
  Serial.println("-1 point for wrong match");
  Serial.println("First to 5 points wins!");
  Serial.println("=======================\n");
}
