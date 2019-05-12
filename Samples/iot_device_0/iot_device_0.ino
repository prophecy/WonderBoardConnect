int ledPin = 13;

int buttonState[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int buttonStatePrev[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

void blinkLED(int count) 
{
  for (int i=0; i< count; i++) {
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    delay(50);
  } 
}

void OnButtonPush(int index)
{
  // Send data with bluetooth
  int message = 0;
  
  if (index < 4)
    message = 100 + index + 1;
  else
    message = 200 + index - 3;
    
  Serial.println(message);
  
  // Blink
  int blinkCount = index + 1;
  blinkLED(blinkCount);
}

void setup() {
  Serial.begin( 9600 );    // 9600 is the default baud rate for the serial Bluetooth module
  Serial.println("hello! ^_^");

  for (int i=0; i<8; ++i)
    pinMode(i+2, INPUT);

  pinMode(ledPin, OUTPUT);
  blinkLED(3);
}

void loop() {

  for (int i=0; i<8; ++i)
    buttonState[i] = digitalRead(i+2);

  for (int i=0; i<8; ++i)
  {
    if (buttonState[i] != buttonStatePrev[i])
    {
      if (buttonState[i] == LOW)
        OnButtonPush(i);
            
      buttonStatePrev[i] = buttonState[i];      
    }
  }
}
