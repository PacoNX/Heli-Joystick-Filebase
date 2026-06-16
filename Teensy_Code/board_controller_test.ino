const int switchPin = 2;

void setup() {
  pinMode(switchPin, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {

  if (digitalRead(switchPin) == LOW)
    Serial.println("Switch ON");
  else
    Serial.println("Switch OFF");

  delay(200);

}