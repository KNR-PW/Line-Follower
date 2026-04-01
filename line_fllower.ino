uint8_t led = 13;

uint8_t sensorL= A0;
uint8_t sensorR = A1;
uint8_t sensorL_Far= A2;
uint8_t sensorR_Far = A3;

uint8_t motorL_pwm = 6;
uint8_t motorL_backward = 7;
uint8_t motorL_forward = 8;

uint8_t motorR_pwm = 3;
uint8_t motorR_backward = 4;
uint8_t motorR_forward = 2;

#define MAX 200
int speed = MAX;

int sensorL_value = 0;
int sensorR_value=0;
int sensorL_Far_value = 0;
int sensorR_Far_value=0;

const int line_threshold = 700;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(sensorL, INPUT);
  pinMode(sensorR, INPUT);

  pinMode(motorL_pwm, OUTPUT);
  pinMode(motorL_backward, OUTPUT);
  pinMode(motorL_forward, OUTPUT);

  pinMode(motorR_pwm, OUTPUT);
  pinMode(motorR_backward, OUTPUT);
  pinMode(motorR_forward, OUTPUT);

  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorL_value = analogRead(sensorL) >= line_threshold;
  sensorR_value = analogRead(sensorR) >= line_threshold;
  sensorL_Far_value = analogRead(sensorL_Far) >= line_threshold;
  sensorR_Far_value = analogRead(sensorR_Far) >= line_threshold;

  if (sensorR_value || sensorL_value)
    digitalWrite(led, HIGH);
  else
    digitalWrite(led, LOW);

  debug();

  if ((sensorL_value && sensorR_value && !sensorL_Far_value && !sensorR_Far_value) || (sensorL_value && sensorR_value && sensorL_Far_value && sensorR_Far_value)){
  //  speed=MAX;
    forward();
  }
  else if((sensorR_value && !sensorL_value) ){
    right();
  }
  
  else if((sensorL_value && !sensorR_value) ){
    left();
  }
  else if (sensorR_Far_value){
 //   speed=MAX*0.7;
    hardright();
  }
  else if (sensorL_Far_value){
  //  speed=MAX*0,7;
    hardleft();
  }
  
  
  else{
    stop();
  }
  
}

void forward(){
  digitalWrite(motorL_backward, LOW);
  digitalWrite(motorL_forward, HIGH);
  analogWrite(motorL_pwm, speed);

  digitalWrite(motorR_backward, LOW);
  digitalWrite(motorR_forward, HIGH);
  analogWrite(motorR_pwm, speed);
}

void left(){
  digitalWrite(motorL_backward, LOW);
  digitalWrite(motorL_forward, HIGH);
  analogWrite(motorL_pwm, speed/1.5);

  digitalWrite(motorR_backward, LOW);
  digitalWrite(motorR_forward, HIGH);
  analogWrite(motorR_pwm, speed);
}

void hardleft(){
  digitalWrite(motorL_backward, HIGH);
  digitalWrite(motorL_forward, LOW);
  analogWrite(motorL_pwm, 60);

  digitalWrite(motorR_backward, LOW);
  digitalWrite(motorR_forward, HIGH);
  analogWrite(motorR_pwm, speed);
}

void right(){
  digitalWrite(motorL_backward, LOW);
  digitalWrite(motorL_forward, HIGH);
  analogWrite(motorL_pwm, speed);

  digitalWrite(motorR_backward, LOW);
  digitalWrite(motorR_forward, HIGH);
  analogWrite(motorR_pwm, speed/1.5);
}

void hardright(){
  digitalWrite(motorL_backward, LOW);
  digitalWrite(motorL_forward, HIGH);
  analogWrite(motorL_pwm, speed);

  digitalWrite(motorR_backward, HIGH);
  digitalWrite(motorR_forward, LOW);
  analogWrite(motorR_pwm, 60);
}

void stop(){
  digitalWrite(motorL_backward, LOW);
  digitalWrite(motorL_forward, LOW);

  digitalWrite(motorR_backward, LOW);
  digitalWrite(motorR_forward, LOW);
}

void debug(){
//  Serial.print("0 ");
  Serial.print(sensorR_value);
  Serial.print(" ");
  Serial.print(sensorL_value);
  Serial.print(" ");
  Serial.print(sensorR_Far_value);
  Serial.print(" ");
  Serial.println(sensorL_Far_value);
}
