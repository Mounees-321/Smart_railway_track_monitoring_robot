// Motor Pins
int ENA = 5;
int IN1 = 8;
int IN2 = 7;

int ENB = 6;
int IN3 = 11;
int IN4 = 12;

// LED for normal/danger
int greenLED = 4;
int redLED = 3;


// Sensors
int trigPin = 9;
int echoPin = 10;
int irPin = A0;
int vibPin = A1;

// ------------------- MOTOR CONTROL -------------------
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

// ------------------- LED CONTROL -------------------
void showNormal() {
  digitalWrite(greenLED, HIGH);  
   digitalWrite(redLED,LOW);  // LED ON
}

void showDanger() {
  digitalWrite(greenLED, LOW); 
   digitalWrite(redLED, HIGH);    // LED OFF
}

// ------------------- ULTRASONIC -------------------
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); 
  int distance = duration * 0.034 / 2;

  return distance;
}

// ------------------- CLASSIFICATION LOGIC -------------------
String classify(int distance, int irValue, int vibration) {

  // High vibration alert
  if (vibration > 700) {
    return "HIGH VIBRATION";
  }

  // IR + Distance ML rules
  if (irValue <= 514) {
    if (distance <= 29) {
      return "OBSTACLE";
    } else {
      return "NORMAL";
    }
  } else {
    if (distance <= 30) {
      return "CRACK+OBS";
    } else {
      return "CRACK";
    }
  }
}

// ------------------- SETUP -------------------
void setup() {

  Serial.begin(9600);

  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

// ------------------- MAIN LOOP -------------------
void loop() {

  int distance = getDistance();
  int irValue = analogRead(irPin);
  int vibration = analogRead(vibPin);

  String status = classify(distance, irValue, vibration);

  // Print everything
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" | IR: ");
  Serial.print(irValue);
  Serial.print(" | VIB: ");
  Serial.print(vibration);
  Serial.print(" | STATUS: ");
  Serial.println(status);

  // Motor + LED logic
  if (status == "NORMAL") {
    showNormal();
    moveForward();
  } 
  else {
    showDanger();
    stopMotors();
  }

  delay(300);
}
