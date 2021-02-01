#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "Your WiFi Name";         
const char* password = "Your WiFi Password";
long duration;
long cm;
const int echo = D1;
const int trig = D2;
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = ""; //For the Web Server
String page2="";  //For updating Status of motor 1
String page3="";  //For updating status of motor 2
void setup(void)
{
  //the HTML of the web page
  page = "<center><h1>RC CAR CONTROL</h1><body><p><a href =\"Forward_slow\"><button>Forward Slow</button></a>&nbsp;<a href=\"Forward_medium\"><button>Forward Medium</button></a><a href=\"Forward\"><button>Forward Fast</button></a></p><p><a href =\"Backward_slow\"><button>Backward Slow</button></a>&nbsp;<a href=\"Backward_medium\"><button>Backward Medium</button></a><a href=\"Backward\"><button>Backward Fast</button></a></p><p><a href =\"Left_slow\"><button>Left Slow</button></a>&nbsp;<a href=\"Left_medium\"><button>Left Medium</button></a><a href=\"Left\"><button>Left Fast</button></a></p><p><a href =\"Right_slow\"><button>Right Slow</button></a>&nbsp;<a href=\"Right_medium\"><button>Right Medium</button></a><a href=\"Right\"><button>Right Fast</button></a></p><p><a href=\"Stop\"><button>Stop</button></a><a href=\"Auto\"><button>Auto</button></a></p></body></center>";
  pinMode(D5, OUTPUT);   // inputs for motor 1
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);    // inputs for motor 2 
  pinMode(D8,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);  // For status of WiFi connection
  delay(1000);
  Serial.begin(115200);     
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  digitalWrite(LED_BUILTIN,HIGH);     // when connected turns high
  Serial.println("");
  Serial.print("Connected to ");   
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());   //provides IP address
   server.on("/", [](){
    server.send(200, "text/html", page+page2);
  });
  server.on("/Forward_slow",Forward_slow);
  server.on("/Forward_medium",Forward_medium);
  server.on("/Forward",Forward);
 
  server.on("/Backward_slow",Backward_slow);
  server.on("/Backward_medium",Backward_medium);
  server.on("/Backward",Backward);
  
  server.on("/Left_slow",Left_slow);
  server.on("/Left_medium",Left_medium);
  server.on("/Left",Left);

  server.on("/Right_slow",Right_slow);
  server.on("/Right_medium",Right_medium);
  server.on("/Right",Right);


  server.on("/Stop",[](){                              // turns all the motor input pins low

  server.send(200,"text/html",page+page2+page3);
    digitalWrite(D5,LOW);
    digitalWrite(D6,LOW);
    digitalWrite(D7,LOW);
    digitalWrite(D8,LOW);
    delay(200);
  });

        server.on("/Auto",[](){
        server.send(200, "text/html",page+page2+page3);
        digitalWrite(trig,LOW);
        delayMicroseconds(5);
        digitalWrite(trig,HIGH);  
        delayMicroseconds(10);    
        digitalWrite(trig,LOW);  

        duration = pulseIn(echo,HIGH);

        cm = (duration/2)/29.1;
        if(cm<50){
        analogWrite(D5,700);
        digitalWrite(D6,LOW);
        digitalWrite(D7,LOW);
        analogWrite(D8,700);         
          }else{
        analogWrite(D5,700);
        digitalWrite(D6,LOW);
        analogWrite(D7,700);
        digitalWrite(D8,LOW);            
            }
        delay(1);       
        }); 
  
  server.begin();
  Serial.println("Web server started!");
}
void loop(void)
{  
     server.handleClient();
}

 void Forward() 
 {
        digitalWrite(D5,HIGH);
        digitalWrite(D6,LOW);
        digitalWrite(D7,HIGH);
        digitalWrite(D8,LOW);
    page2="<center><p> motor Status : Forward Fast </p></center>";
    server.send(200,"text/html", page+page2+page3);
    delay(200);
  }
  void Left()
  {
    page3="<center><p> motor Status : Left Fast </p></center>";
    server.send(200,"text/html",page+page2+page3);
        digitalWrite(D5,HIGH);
        digitalWrite(D6,LOW);
        digitalWrite(D7,LOW);
        digitalWrite(D8,HIGH);
    delay(200);
  }
  void Right()
   { 
    page3="<center><p> motor Status : Right Fast </p></center>";
    server.send(200,"text/html",page+page2+page3);
        digitalWrite(D5,LOW);
        digitalWrite(D6,HIGH);
        digitalWrite(D7,HIGH);
        digitalWrite(D8,LOW);
    delay(200);
  }
   void Backward()
  {
    page2="<center><p> motor Status : Backward Fast </p></center>";
    server.send(200, "text/html", page+page2+page3);
        digitalWrite(D5,LOW);
        digitalWrite(D6,HIGH);
        digitalWrite(D7,LOW);
        digitalWrite(D8,HIGH);
    delay(200); 
  }




  //-------------------------------

   void Forward_medium() 
 {
        analogWrite(D5,900);
        digitalWrite(D6,LOW);
        analogWrite(D7,900);
        digitalWrite(D8,LOW);
    page2="<center><p> motor Status : Forward Medium </p></center>";
    server.send(200,"text/html", page+page2+page3);
    delay(200);
  }
  void Left_medium()
  {
    page3="<center><p> motor Status : Left Medium</p></center>";
    server.send(200,"text/html",page+page2+page3);
        analogWrite(D5,900);
        digitalWrite(D6,LOW);
        digitalWrite(D7,LOW);
        analogWrite(D8,900);
    delay(200);
  }
  void Right_medium()
   { 
    page3="<center><p> motor Status : Right Medium</p></center>";
    server.send(200,"text/html",page+page2+page3);
        digitalWrite(D5,LOW);
        analogWrite(D6,900);
        analogWrite(D7,900);
        digitalWrite(D8,LOW);
    delay(200);
  }
   void Backward_medium()
  {
    page2="<center><p> motor Status : Backward Medium</p></center>";
    server.send(200, "text/html", page+page2+page3);
        digitalWrite(D5,LOW);
        analogWrite(D6,900);
        digitalWrite(D7,LOW);
        analogWrite(D8,900);
    delay(200); 
  }

  //-----------------------------------------


   void Forward_slow() 
 {
        analogWrite(D5,700);
        digitalWrite(D6,LOW);
        analogWrite(D7,700);
        digitalWrite(D8,LOW);
    page2="<center><p> motor Status : Forward Slow </p></center>";
    server.send(200,"text/html", page+page2+page3);
    delay(200);
  }
  void Left_slow()
  {
    page3="<center><p> motor Status : Left Slow </p></center>";
    server.send(200,"text/html",page+page2+page3);
        analogWrite(D5,700);
        digitalWrite(D6,LOW);
        digitalWrite(D7,LOW);
        analogWrite(D8,700);
    delay(200);
  }
  void Right_slow()
   { 
    page3="<center><p> motor Status : Right Slow </p></center>";
    server.send(200,"text/html",page+page2+page3);
        digitalWrite(D5,LOW);
        analogWrite(D6,700);
        analogWrite(D7,700);
        digitalWrite(D8,LOW);
    delay(200);
  }
   void Backward_slow()
  {
    page2="<center><p> motor Status : Backward Slow</p></center>";
    server.send(200, "text/html", page+page2+page3);
        digitalWrite(D5,LOW);
        analogWrite(D6,700);
        digitalWrite(D7,LOW);
        analogWrite(D8,700);
    delay(200); 
  }
