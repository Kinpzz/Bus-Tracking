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
bool in = false;
bool out = false;
int max_wait = 0; // counter for reset
int counter = 0;

const int side_threshold = 30;
const int up_threshold = 20;
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
    Serial.println("outside_up");
    flag1 = true;
  }
  if (distance2 < side_threshold) {
    Serial.println("inside_side");
    flag2 = true;
  }
  if (flag1 == true && flag2 == false && in_process == false && out_process == false) {
    Serial.println("wait to in");
    outside = true;
    in_process = true;
  }
  if (flag1 == false && flag2 == true && out_process == false && in_process == false) {
    Serial.println("wait to out");
    inside = true;
    out_process = true;
  }

  if (in_process == true && out_process == false) {
    max_wait++;
    if (inside == true) {
      Serial.println("in");
      Serial.println(counter++);
    }
  }
  if (out_process == true && in_process == false) {
    max_wait++;
    if (outside == true) {
      Serial.println("out");
      Serial.println(counter--);
    }
  }
  if (max_wait > 10) {
    inside = false;
    outside = false;
    in_process = false;
    out_process = false;
    max_wait = 0;
  }
  
  delay(100);
}
