unsigned long counters = 0;
long rem = 0;
long due = 0;
unsigned long currentMillis = 0;
/*
  Rotary Encoder Demo
  rot-encode-demo.ino
  Demonstrates operation of Rotary Encoder
  Displays results on Serial Monitor
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/

// Rotary Encoder Inputs
#define inputCLK 10
#define inputDT 9
#define but 11
#define rlypin 7

// LED Outputs
#define ledCW 3
#define ledCCW 2

int counter, tim = 0;
int ss = 0;
int currentStateCLK;
int previousStateCLK;

String encdir = "";

void setup() {

  // Set encoder pins as inputs
  pinMode (inputCLK, INPUT);
  pinMode (inputDT, INPUT);

  // Set LED pins as outputs
  pinMode (but, INPUT_PULLUP);
  pinMode (rlypin, OUTPUT);

  // Setup Serial Monitor
  Serial.begin (9600);

  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  previousStateCLK = digitalRead(inputCLK);

}

void loop() {

  // Read the current state of inputCLK
  currentStateCLK = digitalRead(inputCLK);

  // If the previous and the current state of the inputCLK are different then a pulse has occured
  if (currentStateCLK != previousStateCLK) {

    // If the inputDT state is different than the inputCLK state then
    // the encoder is rotating counterclockwise
    if (digitalRead(inputDT) != currentStateCLK)
    {
      if (counter != 0)
      {
        counter --;
        tim = counter / 6;
        //tim--;
      }
    }
    else
    {
      // Encoder is rotating clockwi
      counter ++;
      tim = counter / 6;
    }
    //
    Serial.print(" -- Value: ");
    Serial.println(tim);
  }
  // Update previousStateCLK with the current state
  previousStateCLK = currentStateCLK;
  if (digitalRead(but) == LOW)
  {
    delay(10);
    if (digitalRead(but) == LOW)
    {
      if (tim != 0)
      {
        Serial.print("Timer set for ");
        Serial.print("\t");
        Serial.print(tim);
        Serial.print("  minutes");
        counters = millis();
        due = counters + (60000 * tim);
        //Serial.println(counters);
       // Serial.println("-----------------------------------------------");
        //Serial.println(due);
        ss = 1;
        delay(2000);
      }
    }
  }
  if (digitalRead(but) == HIGH && ss == 1)
  {
    //int a = 1;
    Serial.println("Relay ONN");
    while (currentMillis <= due)
    {
      if ((int)((due - currentMillis) / 60000) == 0)
      {
        Serial.println("Less than 1 minute left ");
      }
      else
      {
        Serial.print("Time left : ");
        Serial.print("\t");
        Serial.print((int)((due - currentMillis) / 60000));
        Serial.print("  minute/s");
        Serial.println();
      }
      currentMillis = millis();
      // Serial.println(currentMillis);
      // delay(100);
    }
    Serial.println("Relay oFF");
    ss = 0;
    tim, counter = 0;
  }
}
