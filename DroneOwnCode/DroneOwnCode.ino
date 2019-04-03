//-----This code is only for testing the transmitter and receiver
//First Version of flight controller for receiving transmitter signals
//Connect receiver to pins d8,9,10,11-yaw,throttle,pitch,roll respectively
byte read_channel1,read_channel2,read_channel3,read_channel4; //these are boolean which are set according to transmitter inputs
unsigned long current_time,timer_1,timer_2,timer_3,timer_4;
int receiver_input[5];

void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
PCICR  |=(1 << PCIE0);
PCMSK0 |=(1 << PCINT0);
PCMSK0 |=(1 << PCINT1);
PCMSK0 |=(1 << PCINT2);
PCMSK0 |=(1 << PCINT3);

}

ISR(PCINT0_vect){
  current_time=micros();  //Time from which program enterd ISR(This will occur at any rising edge falling edge of pins from pcint0-pcint7
  //for channel_1
  if(PINB & B00000001){
    if(read_channel1 ==0){
      read_channel1=1;
      timer_1=current_time;
    }
  }else if(read_channel1 == 1){
    read_channel1=0;
    receiver_input[1]=current_time-timer_1;
  }

  //for channel_2
    if(PINB & B00000010){
    if(read_channel2 ==0){
      read_channel2=1;
      timer_2=current_time;
    }
  }else if(read_channel2 == 1){
    read_channel2=0;
    receiver_input[2]=current_time-timer_2;
  }

  //for channel 3
    if(PINB & B00000100){
    if(read_channel3 ==0){
      read_channel3=1;
      timer_3=current_time;
    }
  }else if(read_channel3 == 1){
    read_channel3=0;
    receiver_input[3]=current_time-timer_3;
  }

  //for channel 4
    if(PINB & B00001000){
    if(read_channel4 ==0){
      read_channel4=1;
      timer_4=current_time;
    }
  }else if(read_channel4 == 1){
    read_channel4=0;
    receiver_input[4]=current_time-timer_4;
  }

  
}

void loop() {
  // put your main code here, to run repeatedly:
print_signals();
delay(500);
}

void print_signals(){
  Serial.print(" Yaw");
  if(receiver_input[1]<1430)Serial.print(">>>"); //Should be 1480-1520
  else if(receiver_input[1]>1560)Serial.print("<<<");
  else Serial.print("-*-");
  Serial.print(receiver_input[1]);

  Serial.print(" Throttle");
  if(receiver_input[2]<1480)Serial.print("<<<");//Should be 1480-1520
  else if(receiver_input[2]>1520)Serial.print(">>>");
  else Serial.print("-*-");
  Serial.print(receiver_input[2]);

  Serial.print(" Pitch");
  if(receiver_input[3]<1430)Serial.print("<<<");//Should be 1480-1520
  else if(receiver_input[3]>1560)Serial.print(">>>");
  else Serial.print("-*-");
  Serial.print(receiver_input[3]);

  Serial.print(" Roll");
  if(receiver_input[4]<1370)Serial.print("<<<");//Should be 1480-1520
  else if(receiver_input[4]>1560)Serial.print(">>>");
  else Serial.print("-*-");
  Serial.println(receiver_input[4]);
  
}


