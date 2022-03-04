/*
Arduino bull tracker
it uses arduino pro mini, neo 6m, sim800l to navigate the bull's location.
when we call the gsm module it cut the call and send the coordinates as sms to the users listed below.
*/ 
#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial mySerial(10,11);
SoftwareSerial gpsSerial(12,13);
boolean stringComplete = false;
String inputString = "";
String fromGSM="";
float lat,lon;
float flat_store = 0.0;
float flon_store = 0.0;
TinyGPS gps;


void setup()  
{
  delay(20000);
  Serial.begin(9600);
  gpsSerial.begin(9600);
  mySerial.begin(9600);
  
  delay(100);
  Serial.println("Serial Connected");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  //reserve some buffer space
  inputString.reserve(200);
  fromGSM.reserve(200);

  mySerial.println("AT+CLIP=1\r\n");//new
  delay(2000);                      //new
 // mySerial.println("AT+CSCLK=2\r\n");//new
  
  //Turn off echo from GSM
  mySerial.print("ATE0");
  mySerial.print("\r");
  delay(300);

}


void loop() // run over and over
{

  //listen from GSM Module
  if (mySerial.available()){
   char inChar = mySerial.read();
    
    if (inChar == '\n') {
      
       //check the state 

        if(fromGSM == "RING\r"){
          Serial.println("---------ON-------");
          delay(1000);
          mySerial.print("ATH\r");
   

         TAKEGPSDATA();
         delay(5000);

          mySerial.println("AT+CMGF=1");
          delay(1000);
          mySerial.println("AT+CMGS=\"+919080967144\"\r"); // Replace x with mobile number
          delay(1000);
          mySerial.print("https://www.google.co.in/search?q=");         
          mySerial.print(lat,7);
          mySerial.print(",");
          mySerial.print(lon,7);
          delay(100);
          mySerial.print((char)26);// ASCII code of CTRL+Z
          delay(1000);

          mySerial.println("AT+CMGF=1");
          delay(1000);
          mySerial.println("AT+CMGS=\"+919943460032\"\r"); // Replace x with mobile number
          delay(1000);
          mySerial.print("https://www.google.co.in/search?q=");         
          mySerial.print(lat,7);
          mySerial.print(",");
          mySerial.print(lon,7);
          delay(100);
          mySerial.print((char)26);// ASCII code of CTRL+Z
          delay(1000);

          mySerial.println("AT+CMGF=1");
          delay(1000);
          mySerial.println("AT+CMGS=\"+918825615807\"\r"); // Replace x with mobile number
          delay(1000);
          mySerial.print("https://www.google.co.in/search?q=");         
          mySerial.print(lat,7);
          mySerial.print(",");
          mySerial.print(lon,7);
          delay(100);
          mySerial.print((char)26);// ASCII code of CTRL+Z
          delay(1000);

          mySerial.println("AT+CMGF=1");
          delay(1000);
          mySerial.println("AT+CMGS=\"+919943437587\"\r"); // Replace x with mobile number
          delay(1000);
          mySerial.print("https://www.google.co.in/search?q=");         
          mySerial.print(lat,7);
          mySerial.print(",");
          mySerial.print(lon,7);
          delay(100);
          mySerial.print((char)26);// ASCII code of CTRL+Z
          delay(1000);

          mySerial.println("AT+CMGF=1");
          delay(1000);
          mySerial.println("AT+CMGS=\"+919094542118\"\r"); // Replace x with mobile number
          delay(1000);
          mySerial.print("https://www.google.co.in/search?q=");         
          mySerial.print(lat,7);
          mySerial.print(",");
          mySerial.print(lon,7);
          delay(100);
          mySerial.print((char)26);// ASCII code of CTRL+Z
          delay(1000);
          
        }
        
      //write the actual response
      Serial.println(fromGSM);
      //clear the buffer
      fromGSM = "";
        
    }else {
         fromGSM+=inChar;
    }
    }

}



void printGPSDATA(){
  gps.f_get_position(&lat, &lon);

  if( lat > 0.0 )
    flat_store = lat;

  if( lon > 0.0 )
    flon_store = lon;


}

void TAKEGPSDATA(){
  //Serial.println("---->TAKEGPSDATA");
  boolean gps_valid = false;
  gpsSerial.listen();
  delay(1000);
 
 
  for(int i =0 ; i < 200 ; i++)
  {
    if(!gps_valid)
    {
      while (gpsSerial.available())
      {
        char c = gpsSerial.read();
        if (gps.encode(c)) // Did a new valid sentence come in?
        {
          printGPSDATA();
          gps_valid = true;
          break;
        }
      }
      delay(5);
    }
  }
 
  mySerial.listen();
  delay(1000);
  //Serial.println("<----TAKEGPSDATA");
 
}

