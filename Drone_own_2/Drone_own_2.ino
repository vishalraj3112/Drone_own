//-----This code consists of transmitter with ESCs
//Second Version of flight controller for receiving transmitter signals
//Connect receiver to pins d8,9,10,11-yaw,throttle,pitch,roll respectively
byte last_channel1,last_channel2,last_channel3,last_channel4; //these are boolean which are set according to transmitter inputs
unsigned long current_time,timer_1,timer_2,timer_3,timer_4;
unsigned long timer_loop_1,timer_loop_2,timer_loop_3,timer_loop_4,zero_timer,esc_loop_timer;
int receiver_input_channel1,receiver_input_channel2,receiver_input_channel3,receiver_input_channel4;
int start;
void setup() {
Serial.begin(9600);
DDRD |= B11110000; //Delcare pins d4,d5,d6,d7 as output(for ESCs)
DDRB |= B00010000; //Declare pins d12 as output

  
//This is for transmitter  
PCICR  |=(1 << PCIE0);
PCMSK0 |=(1 << PCINT0);
PCMSK0 |=(1 << PCINT1);
PCMSK0 |=(1 << PCINT2);
PCMSK0 |=(1 << PCINT3);
//for safety so that throttle and Yaw is not more than 1020 and less that 1400 respectively
while(receiver_input_channel4 <990 || receiver_input_channel4 >1200){
start++;

PORTD |=B11110000;
delayMicroseconds(1000);
  PORTD &=B00001111;
  delay(3);
  if(start==125){
    digitalWrite(12,!digitalRead(12));
    start=0;
  }
}
start=0;
digitalWrite(12,LOW);
zero_timer=micros();

}


void loop() {
 // 250hz operation according to throttle input from channel 2 PWM signal is generated.
  while(zero_timer+4000>micros());//Dealock for the first case for 4000us
  zero_timer=micros();
PORTD |= B11110000;

timer_loop_1=receiver_input_channel4 +zero_timer;
timer_loop_2=receiver_input_channel4+zero_timer;
timer_loop_3=receiver_input_channel4+zero_timer;
timer_loop_4=receiver_input_channel4+zero_timer;

while(PORTD>=16){
  esc_loop_timer=micros();
  if(esc_loop_timer>=timer_loop_1)PORTD &= B11101111;
  if(esc_loop_timer>=timer_loop_2)PORTD &=B11011111;
  if(esc_loop_timer>=timer_loop_3)PORTD &=B10111111;
  if(esc_loop_timer>=timer_loop_4)PORTD &=B01111111;
}

  
print_signals();
delay(500);
}

void print_signals(){
  Serial.print(" Yaw");
  if(receiver_input_channel1<1430)Serial.print(">>>"); //Should be 1480-1520
  else if(receiver_input_channel1>1560)Serial.print("<<<");
  else Serial.print("-*-");
  Serial.print(receiver_input_channel1);

  Serial.print(" Throttle");
  if(receiver_input_channel2<1480)Serial.print("<<<");//Should be 1480-1520
  else if(receiver_input_channel2>1520)Serial.print(">>>");
  else Serial.print("-*-");
  Serial.print(receiver_input_channel2);

  Serial.print(" Pitch");
  if(receiver_input_channel3<1430)Serial.print("<<<");//Should be 1480-1520
  else if(receiver_input_channel3>1560)Serial.print(">>>");
  else Serial.print("-*-");
  Serial.print(receiver_input_channel3);

  Serial.print(" Roll");
  if(receiver_input_channel4<1370)Serial.print("<<<");//Should be 1480-1520
  else if(receiver_input_channel4>1560)Serial.print(">>>");
  else Serial.print("-*-");
  Serial.println(receiver_input_channel4);
  
}

//Intruppt Service Routine
ISR(PCINT0_vect){
  current_time=micros();  //Time from which program enterd ISR(This will occur at any rising edge falling edge of pins from pcint0-pcint7
  //for channel_1(YAW)
  if(PINB & B00000001){
    if(last_channel1 ==0){
      last_channel1=1;
      timer_1=current_time;
    }
  }else if(last_channel1 == 1){
    last_channel1=0;
    receiver_input_channel1=current_time-timer_1;
  }

  //for channel_2(throttle)
    if(PINB & B00000010){
    if(last_channel2 ==0){
      last_channel2=1;
      timer_2=current_time;
    }
  }else if(last_channel2 == 1){
    last_channel2=0;
    receiver_input_channel2=current_time-timer_2;
  }

  //for channel 3
    if(PINB & B00000100){
    if(last_channel3 ==0){
      last_channel3=1;
      timer_3=current_time;
    }
  }else if(last_channel3 == 1){
    last_channel3=0;
    receiver_input_channel3=current_time-timer_3;
  }

  //for channel 4
    if(PINB & B00001000){
    if(last_channel4 ==0){
      last_channel4=1;
      timer_4=current_time;
    }
  }else if(last_channel4 == 1){
    last_channel4=0;
   receiver_input_channel4=current_time-timer_4;
  }

  
}



