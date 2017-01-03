 #include <Arduino_FreeRTOS.h>

void TaskUltrasonicSensor_1 (void *pvParameters);
int trigPin1 = 12, echoPin1 = 13;
int distance1=0,duration1=0;

void TaskUltrasonicSensor_2 (void *pvParameters);
int trigPin2 = 7, echoPin2 = 8;
int distance2=0,duration2=0;

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
  xTaskCreate( TaskUltrasonicSensor_1, (const portCHAR *)"UltrasonicSensor_1", 128, NULL, 1, NULL );
  xTaskCreate( TaskUltrasonicSensor_2, (const portCHAR *)"UltrasonicSensor_2", 128, NULL, 1, NULL );
}

void TaskUltrasonicSensor_1(void *pvParameters) {
  (void) pvParameters;
  //Serial.print("inU");
  digitalWrite(trigPin1, LOW); // Clears the trigPin
  delayMicroseconds(2);
   /* Sets the trigPin on HIGH state for 10ms */
  digitalWrite(trigPin1, HIGH);    delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
   /* Reads Echo pin, returns sound travel time in ms */
  duration1 = pulseIn(echoPin1, HIGH);
   /* Calculating the distance */
  distance1 = duration1*0.034/2;
  Serial.print("\n distance1=");
  Serial.print(distance1);
  delay(2500);
}
void TaskUltrasonicSensor_2(void *pvParameters) {
  (void) pvParameters;
  //Serial.print("inU");
  digitalWrite(trigPin2, LOW); // Clears the trigPin
  delayMicroseconds(2);
   /* Sets the trigPin on HIGH state for 10ms */
  digitalWrite(trigPin2, HIGH);    delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
   /* Reads Echo pin, returns sound travel time in ms */
  duration2 = pulseIn(echoPin2, HIGH);
   /* Calculating the distance */
  distance2 = duration2*0.034/2;
  Serial.print("\n distance2=");
  Serial.print(distance2);
  delay(2500);
}
void loop() {
  // put your main code here, to run repeatedly:


}
