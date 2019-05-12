#define SETP_RATE 10

int INA = 4;
int INB = 5;
int INC = 6;
int IND = 7;

int LED_PIN = 13;

static byte _step = 0;
static byte *_pStep;

void WaveStepDrive(byte* step)
{
  byte myStep = *_pStep;

  switch(myStep)
  {
    case 0: 
      digitalWrite(INA, HIGH);
      digitalWrite(INB, LOW);
      digitalWrite(INC, LOW);
      digitalWrite(IND, LOW);
      break;
    case 1: 
      digitalWrite(INA, LOW);
      digitalWrite(INB, HIGH);
      digitalWrite(INC, LOW);
      digitalWrite(IND, LOW);
      break;
    case 2: 
      digitalWrite(INA, LOW);
      digitalWrite(INB, LOW);
      digitalWrite(INC, HIGH);
      digitalWrite(IND, LOW);
      break;
    case 3: 
      digitalWrite(INA, LOW);
      digitalWrite(INB, LOW);
      digitalWrite(INC, LOW);
      digitalWrite(IND, HIGH);
      break;
    default:
      break;  
  }
}

void PlayForward(int count)
{
  for (int i=0; i<count; ++i)
  {
    _pStep = &_step;
    *_pStep += 1;
    *_pStep &= 0x03;
    WaveStepDrive(&_step);
    delay(500);
  }
}

void BlinkLED(int count) {
  for (int i=0; i< count; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
  } 
}

void setup() 
{
  Serial.begin( 9600 );    // 9600 is the default baud rate for the serial Bluetooth module
  Serial.println("hello! ^_^");

  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(INC, OUTPUT);
  pinMode(IND, OUTPUT);

  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);
  digitalWrite(INC, LOW);
  digitalWrite(IND, LOW);

  pinMode(LED_PIN, OUTPUT);
  BlinkLED(3);
}

void loop() 
{
  // listen for the data
  if ( Serial.available() > 0 ) {
    
    // read a numbers from serial port
    int code = Serial.parseInt();
    Serial.print("You have input: ");
    Serial.println(String(code));
        
    if (code/100 == 1) 
    {
      int count = code % 100;
      BlinkLED(count);
    }
    else if (code/100 == 2) 
    {
      int count = code % 200;
      PlayForward(count);
    }
  }
}
