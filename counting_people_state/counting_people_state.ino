int trigPin1 = 7, echoPin1 = 8;
int distance1=0, duration1=0;

int trigPin2 = 12, echoPin2 = 13;
int distance2=0, duration2=0;

int counter = 0;
int timer = 0;
char count_buffer[3];
int state = 1;
int iter = 0;

const int max_wait = 50; // counter for reset
const int side_threshold = 50;
const int up_threshold = 70;
void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  Serial1.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  counter = 0;
}

void loop() {
  digitalWrite(trigPin1, LOW); // Clears the trigPin
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  
  digitalWrite(trigPin2, LOW); // Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  
  distance1 = duration1*0.034/2;
  distance2 = duration2*0.034/2;

  if (distance1 >= up_threshold || distance2 >= side_threshold) {
    switch(state) {
      case 1 : 
        if (distance1 < up_threshold) {
          state = 2;
        }
        if (distance2 < side_threshold) {
          state = 3;
        }
        break;
      case 2 :
        if (distance2 < side_threshold) {
          state = 4;
        }
        iter++;
        if (iter > max_wait) {
          //Serial.println("no wait");
          iter = 0;
          state = 1;
        }
        break;
      case 3 :
        if (distance1 < up_threshold) {
          state = 5;
        }
        iter++;
        if (iter > max_wait) {
          //Serial.println("no wait");
          iter = 0;
          state = 1;
        }
        break;
      case 4 :
        //Serial.println("State4 in");
        counter++;
        //Serial.println(counter);
        iter = 0;
        state = 1;
        delay(50);
        break;
      case 5 :
        //Serial.println("State5 out");
        counter--;
        //Serial.println(counter);
        iter = 0;
        state = 1;
        delay(50);
        break;
    }
  }
  if (counter < 0) counter = 0;

  timer++;
  if (timer > 500) {
    timer = 0;
    sprintf(count_buffer, "%d\0", counter);
    Serial1.print("AT+DTX=");
    Serial1.print(strlen(count_buffer));
    Serial1.print(",\"");
    Serial1.print(count_buffer);
    Serial1.println("\"");
    
    //Serial.print(count_buffer);
    //Serial.println("Send count");
  }
}



