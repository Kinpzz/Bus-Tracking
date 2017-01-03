int trigPin1 = 7, echoPin1 = 8;
int distance1=0,duration1=0;

int trigPin2 = 12, echoPin2 = 13;
int distance2=0,duration2=0;

bool flag1 = false;
bool flag2 = false;
bool inside = false;
bool outside = false;
bool in_process = false;
bool out_process = false;

int max_wait = 0; // counter for reset
int counter = 0;

const int side_threshold = 50;
const int up_threshold = 70;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  counter = 0;
}

void reset() {
    inside = false;
    outside = false;
    in_process = false;
    out_process = false;
    flag1 = false;
    flag2 = false;
    max_wait = 0;
}

void loop() {
  flag1 = false;
  flag2 = false;
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

  //Serial.print("\n distance1=");
  //Serial.print(distance1);

  //Serial.print("\n distance2=");
  //Serial.print(distance2);
  
  if (distance1 < up_threshold) {
    //Serial.println("outside_up");
    flag1 = true;
  }
  if (distance2 < side_threshold) {
    //Serial.println("inside_side");
    flag2 = true;
  }
  if (flag1 == true && flag2 == false) {
    outside = true;
    if (in_process == false && out_process == false) {
      in_process = true;
    }
  } else if (flag1 == false && flag2 == true) {
    inside = true;
    if (in_process == false && out_process == false) {
      out_process = true;
    }
  }

  if (in_process == true && out_process == false) {
    max_wait++;
    //Serial.println("still wait to in");
    if (inside == true) {
      Serial.println("in");
      ++counter;
      Serial.println(counter);
      reset();
    }
  } else if (out_process == true && in_process == false) {
    max_wait++;
    //Serial.println("still wait to out");
    if (outside == true) {
      Serial.println("out");
      --counter;
      Serial.println(counter);
      reset();
    }
  }
  
  if (max_wait > 25) {
    Serial.println("no wait");
    reset();
  }
  
  if (counter < 0) counter = 0;
  delay(100);
}



