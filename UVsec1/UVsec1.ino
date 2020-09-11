#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 5, en1 = 6, d4 = 7, d5 = 8, d6 = 9, d7 = 10;
#define inputCLK 15
#define inputDT 14
#define but 16
#define sw 3
LiquidCrystal lcd(rs, en1, d4, d5, d6, d7);
uint8_t ss = 0, en = 0;
uint32_t lastTime;
uint16_t tim = 0, counter = 0;
uint8_t rly = 2;
int currentStateCLK;
int previousStateCLK;
void setup()
{
  _delay_ms(1500);
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(rly, OUTPUT);
  digitalWrite(rly, LOW);
  pinMode(inputCLK, INPUT);
  pinMode(inputDT, INPUT);
  pinMode(sw, INPUT_PULLUP);
  pinMode(but, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  // put your setup code here, to run once:
  Serial.println("Jash ");
  lcd.print("   Welcome ");
  digitalWrite(13, HIGH);
  _delay_ms(1500);
  digitalWrite(13, LOW);
  _delay_ms(1500);
  digitalWrite(13, HIGH);
  _delay_ms(1500);
  digitalWrite(13, LOW);
  lastTime = millis();
}

void loop() {
  currentStateCLK = digitalRead(inputCLK);

  // If the previous and the current state of the inputCLK are different then a pulse has occured
  if (currentStateCLK != previousStateCLK && en == 0) {

    // If the inputDT state is different than the inputCLK state then
    // the encoder is rotating counterclockwise
    if (digitalRead(inputDT) != currentStateCLK)
    {
      lcd.clear();
      if (tim != 0)
      {
        counter--;
        tim = counter / 2;
        // tim = counter / 6;
        //tim--;
      }
    }
    else
    {
      // Encoder is rotating clockwi
      counter ++;
      tim = counter / 2;
      //
      //tim = counter;
    }
    //
    lcd.setCursor(0, 0);
    lcd.print("   Timer :");
    lcd.setCursor(0, 1);
    lcd.print(tim);
    Serial.print(" -- Value: ");
    Serial.println(tim);
  }
  // Update previousStateCLK with the current state
  previousStateCLK = currentStateCLK;
  //  if (Serial.available() > 0 | digitalRead(but) == LOW &&en==0)
  //  {
  if (digitalRead(but) == LOW && en == 0)
  {
    Serial.println("In input ");
    // tim = (Serial.readStringUntil('\n')).toInt();
    if (tim != 0)
    {
      Serial.print("Timer set for ");
      Serial.print("\t");
      Serial.print(tim);
      Serial.print("  seconds");
      Serial.println();
      en = 1;
      //delay(2000);
      lastTime = millis();
      digitalWrite(rly, HIGH);
    }
  }
  if (digitalRead(sw) == HIGH)
  {
    //Serial.println("HIGH");
    ss = 1;
  }
  if (digitalRead(sw) == LOW)
  {
    delay(85);
    if (digitalRead(sw) == LOW)
    {
      while (digitalRead(sw) == LOW)
      {
        digitalWrite(13, LOW);
        digitalWrite(rly, LOW);
        //Serial.println("Paused ");
        delay(100);
      }
      lastTime = millis();
      //tim++;
    }
  }
  //Serial.println(en);
  // put your main code here, to run repeatedly:
  if (ss == 1 && en == 1)
  {
    digitalWrite(13, HIGH);
    if ((millis() - lastTime >= 1000) && ss == 1)
    {
      lcd.clear();
      _delay_ms(5);
      tim--;
      lastTime += 1000;
      //tim -= ( millis() - lastTime );
      lcd.setCursor(0, 0);
      lcd.print("  Time Left :");
      lcd.setCursor(0, 1);
      lcd.print(tim);
      digitalWrite(rly, HIGH);
      Serial.println(tim);
      if (tim == 0)
      {
        lcd.clear();
        en = 0;
        digitalWrite(rly, LOW);
        digitalWrite(13, LOW);
        counter = 0;
        lcd.setCursor(0, 0);
        lcd.print("Timer End");

        Serial.println("Timer End");
        _delay_ms(2500);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("   Timer :");


      }
    }
  }
  //lastTime = millis();
}
