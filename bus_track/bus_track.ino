#include <LGPS.h>
#include <math.h>

gpsSentenceInfoStruct info;

double location[2];
char buff[256];

static unsigned char getComma(unsigned char num,const char *str)
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

static double getDoubleNumber(const char *s)
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

static double getIntNumber(const char *s)
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
    sprintf(buff, "latitude = %10.4f, longitude = %10.4f", location[0], location[1]);
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
void loop(){
  setLocation(location);
  Serial1.print("AT+DTX=11,\"T");
  Serial1.print(location[0]);
  Serial1.print(location[1]);
  Serial1.println("\"");
  //Serial1.println("AT+DTX=11,\"12345ABCdef\"");
  delay(1000);
  Serial.println("Send GPS over");
  delay(5000);
}
