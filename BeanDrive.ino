

//Motor A
int AIN1 = 0; //Direction
int AIN2 = 1; //Direction
int PWMA = 2; //Speed control 

int STBY = 3; //standby

//Motor B
int BIN1 = 5; //Direction
int BIN2 = 6; //Direction
int PWMB = 7; //Speed control

int motor;
int command;
int motor1_speed;
int motor1_direction;
int motor2_speed;
int motor2_direction;

void setup(){
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

 Serial.begin(57600);
 Serial.setTimeout(5);
 
 motor1_speed = 0;
 motor1_direction = 0;

 motor2_speed = 0;
 motor2_direction = 0;

}

void loop(){

 //Buffer that receives serial commands from the App
 char rec_buffer[64];
 size_t rec_length = 64;
 
 //Set the length to number of bytes recieved
 rec_length = Serial.readBytes(rec_buffer, rec_length);
 
 if ( rec_length > 0 )
 {
   Bean.setLed(255,255,255);
   // Byte[0] : Commmand Type (0 - Speed, 1 - Direction, 2 - Stop)
   // Byte[1] : Motor Number
   // Byte[2] : Value (Speed [0-255], Direction [0 - Clockwise, 1 - Counter-Clockwise])
   
   command = rec_buffer[0];
   motor = rec_buffer[1];

   if (command == 0) {
     if (motor == 1) {
       motor1_speed = rec_buffer[2];
       move(motor, motor1_speed, motor1_direction);
     } else {
       motor2_speed = rec_buffer[2];
       move(motor, motor2_speed, motor2_direction);
    }
   
   } else if (command == 1) {
     if (motor == 1) {
       motor1_direction = rec_buffer[2];
       move(motor, motor1_speed, motor1_direction);
     } else {
       motor2_direction = rec_buffer[2];
       move(motor, motor2_speed, motor2_direction);
    }
   } else {
    stop();
   }
   
 }
 else{
   Bean.setLed(0,0,0);
 }  
}


void move(int motor, int speed, int direction){

//Move specific motor at speed and direction
//motor: 1 for A 2 for B
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop(){
  digitalWrite(STBY, LOW); 
}
