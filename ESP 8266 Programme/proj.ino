#include<ESP8266WiFi.h>
WiFiClient client;
#include"ThingSpeak.h"
void setup(){
  pinMode(10,INPUT);
  pinMode(3,OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin("S","000000000");
  Serial.begin(9600);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print("....");
  delay(100);
}
Serial.println(WiFi.localIP());
}
void loop()
{
  ThingSpeak.begin(client);
  int manual;
  String H;
  while((manual=ThingSpeak.readIntField(299485,1,"OMGZO12A66A4SUUC"))==0)
  {
    String S=digitalRead(10);
    if(S==HIGH)
    {
      digitalWrite(3,HIGH);
      ThingSpeak.writeField(299485,2,1,"C6BZX6UAS8AW9KET");
      }
    else if(S==LOW)
    {
      digitalWrite(3,LOW);
      ThingSpeak.writeField(299485,2,0,"C6BZX6UAS8AW9KET");
      }
  client.print(S);
  client.stop();
  
  }
  int control=ThingSpeak.readIntField(299485,3,"OMGZO12A66A4SUUC");
  if(control==1)
    {
      H=HIGH;
      digitalWrite(3,HIGH);
      ThingSpeak.writeField(299485,2,1,"C6BZX6UAS8AW9KET");
      }
 else if(control==0)
    {
      H=LOW;
      digitalWrite(3,LOW);
      ThingSpeak.writeField(299485,2,0,"C6BZX6UAS8AW9KET");
      }
  Serial.println(H);
}

