// Pin definitions
const int loadPin = 2;   // PL (parallel load)
const int clockPin = 1; // CP (clock)
const int dataPin = 3;  // Q7 (data output)

byte incoming;

void setup() {
  Serial.begin(9600);

  pinMode(loadPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, INPUT);
}

void loop() {

  // Load parallel inputs into register
  digitalWrite(loadPin, LOW);
  delayMicroseconds(5);
  digitalWrite(loadPin, HIGH);

 byte incoming = shiftIn(dataPin, clockPin, MSBFIRST);

  for (int i = 7; i >= 0; i--) {
    Serial.print(bitRead(incoming, i));
  }

Serial.println();

  delay(500);
}