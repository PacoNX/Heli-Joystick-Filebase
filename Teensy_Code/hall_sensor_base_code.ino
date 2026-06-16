#define PackageSize 16

const int latch = 5;
const int _clock = 3;
const int _data = 1;

const int pedals = A1;
int pedalsValue = 0;
int pedalsMin = 1070;
int pedalsMax = 3150;

void setup()
{
 
  // Setup Serial Monitor
  Serial.begin(9600);
  analogReadResolution(12);
  // Setup 74HC165 connections
  pinMode(_clock, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(_data, INPUT);
  
  
  digitalWrite(_clock, LOW);
  digitalWrite(latch, HIGH); //Load all pins basic state
}
 
void loop()
{
  int data[PackageSize];

  digitalWrite(latch, LOW); //Load Pins
  delay(5); //Wait to load all pins
  digitalWrite(latch,HIGH); //Switch to Shift Mode! ---> Time for the Clock
      
  for (int i=0; i<PackageSize; i++) {
    int currentState = digitalRead(_data);

    if (currentState != data[i]) {
      Joystick.button(i+1, currentState);
    }
    data[i] = currentState; //Read Pin Data and write to data[i]
    digitalWrite(_clock,HIGH); //Activate Pin Data
    digitalWrite(_clock, LOW);
  }
  Serial.println();

  for (int j=0; j<PackageSize; j++) {
    Serial.print(data[j]);
  }
  Serial.println();

  ///////////////////////////////////////////////////////////////////////////////////////////

  pedalsValue = analogRead(pedals);
  Serial.println(pedalsValue);
  int pedalsValue_JOY = map(pedalsValue, pedalsMin, pedalsMax, 0, 1023);
  pedalsValue_JOY = constrain(pedalsValue_JOY, 0, 1023);
  Serial.println(pedalsValue_JOY);

  Joystick.X(pedalsValue_JOY);


  delay(200);
}