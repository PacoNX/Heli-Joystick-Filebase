//Pin Declarations
const int toggle1 = 2;
bool lastToggleState1 = HIGH;

const int three1_UP = 5;
bool lastThreeWayUpState1 = HIGH;
const int three1_DOWN = 6;
bool lastThreeWayDownState1 = HIGH;

const int button1 = 10;
bool lastButtonState1 = HIGH;

const int pot1 = A0;
int lastPotValue1 = -1;


void setup() {
  Serial.begin(115200);

  pinMode(toggle1, INPUT_PULLUP);

  pinMode(three1_UP, INPUT_PULLUP);
  pinMode(three1_DOWN, INPUT_PULLUP);

  pinMode(button1, INPUT_PULLUP);
  
  pinMode(pot1, INPUT_PULLUP);

  analogReadResolution(10);   // 0..1023
  analogReadAveraging(8);     // smoother potentiometer readings
}

void loop() {

  // Toggle Switch
  bool toggleState1 = digitalRead(toggle1);

  if (toggleState1 != lastToggleState1) {

    if (toggleState1 == LOW) {
      Joystick.button(1, 1);
      Serial.println("Toggle1 -> ON");
    }
    else {
      Joystick.button(1, 0);
      Serial.println("Toggle1 -> OFF");
    }

    lastToggleState1 = toggleState1;
  }



  // Push Button
  bool pushButtonState1 = digitalRead(button1);

  if (pushButtonState1 != lastButtonState1) {

    if (pushButtonState1 == LOW) {
      Joystick.button(2, 1);
      Serial.println("Button1 -> PRESSED");
    }
    else {
      Joystick.button(2, 0);
      Serial.println("Button1 -> RELEASED");
    }

    lastButtonState1 = pushButtonState1;
  }



  // Threeway Switch
  bool threeWayUpState1 = digitalRead(three1_UP);
  bool threeWayDownState1 = digitalRead(three1_DOWN);

  if (threeWayUpState1 != lastThreeWayUpState1 ||
      threeWayDownState1 != lastThreeWayDownState1) {

    // Up active
    if (threeWayUpState1 == LOW && threeWayDownState1 == HIGH) {
      Joystick.button(3, 1);
      Joystick.button(4, 0);
      Serial.println("ThreeWay1 -> UP");
    }
    // Down active
    else if (threeWayUpState1 == HIGH && threeWayDownState1 == LOW) {
      Joystick.button(3, 0);
      Joystick.button(4, 1);
      Serial.println("ThreeWay1 -> DOWN");
    }
    // Middle
    else {
      Joystick.button(3, 0);
      Joystick.button(4, 0);
      Serial.println("ThreeWay1 -> MIDDLE");
    }

    lastThreeWayUpState1 = threeWayUpState1;
    lastThreeWayDownState1 = threeWayDownState1;
  }



  // Potentiometer
  int potValue1 = analogRead(pot1);

  if (abs(potValue1 - lastPotValue1) > 3) {   // ignore tiny noise
    Joystick.sliderLeft(potValue1);

    Serial.print("Pot1 -> ");
    Serial.println(potValue1);

    lastPotValue1 = potValue1;
  }

  delay(5);
}