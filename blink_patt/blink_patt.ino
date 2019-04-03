int state;
long count;
long t;
void setup() {
  Serial.begin(9600);
  DDRB |= B00110000;
  // put your setup code here, to run once:
  state = 1;
  count = 0;
  t = 20000;
  PORTB &=B11011111;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(state == 1 && count < 6*t) {
    count++;
  }
  else if(state == 1) {
    state = 2;
    //digitalWrite(12,HIGH);
    PORTB |=B00100000;
    count = 0;
  }

  if(state == 2 && count < t) {
    count++;
  }
  else if(state == 2) {
    state = 3;
    //digitalWrite(12,LOW);
    PORTB &=B11011111;
    count = 0;
  }

  if(state == 3 && count < t) {
    count++;
  }
  else if(state == 3) {
    state = 4;
    //digitalWrite(12,HIGH);
    PORTB |=B00100000;
    count = 0;
  }

  if(state == 4 && count < t) {
    count++;
  }
  else if(state == 4) {
    state = 1;
   // digitalWrite(12,LOW);
   PORTB &=B11011111;
    count = 0;
  }
}
