#include <SoftwareSerial.h> 
#include <string.h>
#include "LowPower.h"
#include <avr/wdt.h>
#define _CRT_SECURE_NO_WARNINGS
#define LED 7
#define TX 2
#define RX 3
//distance = 10 ^ ((POWER-RSSI) / 10n)
SoftwareSerial BTSerial(TX, RX);
byte bt_in;
char bf;
byte data;
char buff[200];
unsigned char buff_idx = 0;
unsigned char isParse = 0;
char *uuid= "2E234454CF6D4A0FADF2F4911BA9FFA6";
int count=0,t_count=0,f_count=0,maxi=99,inter=10;
void setup() {
   pinMode(LED,OUTPUT);
   Serial.begin(9600);
   BTSerial.begin(9600);
   Serial.println("booting");
}

void loop(){
  if (millis()%inter== 0) {
    BTSerial.println("AT+DISI?");
    if(count<maxi){
      if(BTSerial.available()) {
        char c = BTSerial.read();
        //Serial.println(micros());
        //Serial.print(c);
        buff[buff_idx++] = c;
        if (c == '\n') {
          buff[buff_idx++] = '\0';
          buffParse();   
            }
          t_count++;
         }else{
           f_count++;
          }
       count++;
    }
    else if(count==maxi){
      Serial.print("true : ");
      Serial.println(t_count);
      Serial.print("false : ");
      Serial.println(f_count);
      delay(10000);
        }
    }
  }

void buffParse() {
  char *ptr;
  unsigned char idx;
  ptr = strtok(buff, "+");
  ptr += strlen(ptr) + 1;
  if (!strncmp(ptr, "DISCE", 5)) {
  }
  else if (!strncmp(ptr, "DISC", 4)) {
    ptr = strtok(ptr, ":");
    while (ptr != NULL) {
      if (strlen(ptr) == 32) {
       Serial.println(ptr);
       int com = strcmp(ptr,uuid);
       if(com == 0){      
        //digitalWrite(LED,HIGH);
          }
        else{     
        //digitalWrite(LED,LOW);
           }
      }
      ptr = strtok(NULL, ":");     
    }
  }
  buff_idx = 0;
}
