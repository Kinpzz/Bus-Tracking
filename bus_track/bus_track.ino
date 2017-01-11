#include <LGPS.h>
#include <math.h>

gpsSentenceInfoStruct info;

double location[2];
char buff[256];

unsigned char getComma(unsigned char num,const char *str)
{
  unsigned char i,j = 0;
  int len=strlen(str);
  for(i = 0;i < len;i ++)
  {
     if(str[i] == ',')
      j++;
     if(j == num)
      return i + 1; 
  }
  return 0; 
}

double getDoubleNumber(const char *s)
{
  char buf[10];
  unsigned char i;
  double rev;
  
  i=getComma(1, s);
  i = i - 1;
  strncpy(buf, s, i);
  buf[i] = 0;
  rev=atof(buf);
  return rev; 
}

double getIntNumber(const char *s)
{
  char buf[10];
  unsigned char i;
  double rev;
  
  i=getComma(1, s);
  i = i - 1;
  strncpy(buf, s, i);
  buf[i] = 0;
  rev=atoi(buf);
  return rev; 
}

void setLocation(double *location) {
  LGPS.getData(&info);
  Serial.println((char*)info.GPGGA);
  const char* GPGGAstr = (const char*)info.GPGGA;
  int tmp, num;
  if(GPGGAstr[0] == '$') {
    tmp = getComma(2, GPGGAstr);
    // latitude
    location[0] = getDoubleNumber(&GPGGAstr[tmp]);
    tmp = getComma(4, GPGGAstr);
    // longitude
    location[1] = getDoubleNumber(&GPGGAstr[tmp]);
    sprintf(buff, "latitude = %.4f, longitude = %.4f", location[0], location[1]);
    Serial.println(buff);
    tmp = getComma(7, GPGGAstr);
    num = getIntNumber(&GPGGAstr[tmp]);
    sprintf(buff, "satellites number = %d", num);
    Serial.println(buff); 
  } else {
    Serial.println("Not get data");
  }
}

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
  LGPS.powerOn();
  Serial.println("LGPS Power on, and waiting ...");
  delay(3000);
  setLocation(location);
}  

char buf[80];
int size;

void loop(){

//  Serial1.println()
//  Serial1.println("AT+DTX=16,\"8600.0000,0.0000\"");
  setLocation(location);
  
  memset(buf, 80,'\0');
  sprintf(buf, "A%.4f\0", location[0]);
  size = strlen(buf);
//  Serial.println(buf);
//  Serial.println(size);
  
  Serial1.print("AT+DTX=");
  Serial1.print(size);
  Serial1.print(",\"");
  Serial1.print(buf);
  Serial1.println("\"");

  delay(5000); // the latency for lora module

  memset(buf, 80,'\0');
  sprintf(buf, "L%.4f\0", location[1]);
  size = strlen(buf);
  Serial.println(buf);
  Serial.println(size);
  
  Serial1.print("AT+DTX=");
  Serial1.print(size);
  Serial1.print(",\"");
  Serial1.print(buf);
  Serial1.println("\"");

  delay(1000);
  Serial.println("Send GPS over");
  delay(5000);
}
