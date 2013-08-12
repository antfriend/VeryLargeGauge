/*
Very Large Gauge by Dan Ray

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * servo attached to pin 9

 modified Web Server example:
 Web Server created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 */

#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h> 

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  
/////////////////////////////////////////////////////////////////////
///////////// IPAddress /////////////////////////////////////////////
IPAddress ip(192,168,0,3);  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
int milliseconds_of_delay = 100;
// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
int myservo_pin = 9;
int pos = 0;    // variable to store the servo position 
int loop_count = 0;

void setup() {
  set_up_serial(false);//set to "true" for debugging

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  serial_print("server is at ");
  serial_println(String(Ethernet.localIP()));
  
  myservo.attach(myservo_pin);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  String theCurrentLine;
  if (client) 
  {
    loop_count = 0;
    serial_println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    String theCurrentLine = String("");
    String p = "0";
    while (client.connected()) {
      if (client.available())//===============================================
      {
          char c = client.read();         
          //serial_write(c);//ssssssssssssssssssssss
                
          // if you've gotten to the end of the line (received a newline
          // character) and the line is blank, the http request has ended,
          // so you can send a reply
          if (c == '\n' && currentLineIsBlank) 
          {
            //theCurrentLine = String("");
            //parse_theCurrentLine("end:" + theCurrentLine);
            theCurrentLine = String("");
            write_webpage(client, p);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            break;
          }
          if (c == '\n') 
          {
            // you're starting a new line
            currentLineIsBlank = true;
            p = parse_theCurrentLine(theCurrentLine);
            if(p != "0")
            {
              
              set_servo(p);
              delay(milliseconds_of_delay);
              write_webpage(client, p);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!             
              break;              
            }
            theCurrentLine = String("");
          } 
          else if (c != '\r') 
          {
            // you've gotten a character on the current line
            currentLineIsBlank = false;
            theCurrentLine =  String(theCurrentLine + c);
          }
      }//=====================================================================
    }
    // close the connection:
    client.stop();
    serial_println("client disonnected");
    delay(milliseconds_of_delay);
  }else
  {
     //no client
     loop_count++;
     if(loop_count > 300)
     {
       loop_count = 0;
       if(myservo.attached())
       {
         myservo.detach();
       }
     }
  }
}

void set_servo(String one_to_180)
{
  int the_length = one_to_180.length() + 1;//+1 includes the null terminating character
  char Str1to180[the_length];
  one_to_180.toCharArray(Str1to180, the_length);
  int the_int = atoi(Str1to180);
  the_int = constrain(the_int, 1, 100);
  int reverse_mapped = map(the_int, 1,100,170,1);
  if(myservo.attached() == false)
  {
    myservo.attach(myservo_pin);
  }
  myservo.write(reverse_mapped);
}

String parse_theCurrentLine(String theCurrentLine)
{
  /*
    GET /?p=10 HTTP/1.1
    Host: 192.168.0.3
    Connection: keep-alive
    Cache-Control: max-age=0
    Accept: text/html,application/xhtml+xml,application/xml;q=0.9,**;q=0.8
    User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/28.0.1500.95 Safari/537.36
    Referer: http://192.168.0.3/?p=10
    Accept-Encoding: gzip,deflate,sdch
    Accept-Language: en-US,en;q=0.8
  */ 
  
  //find GET / ?p=...[space]
    
  String p = "0";
  //int secondClosingBracket = stringOne.indexOf('>', firstClosingBracket + 1 );
  //if (stringOne.substring(14,18) == "text") {
  //string.substring(from, to)
  
  // "?... "
  int start_of_p = theCurrentLine.indexOf('?');
  if(start_of_p != -1)
  {
    int end_of_p = theCurrentLine.indexOf(' ', start_of_p);
    if (theCurrentLine.substring(start_of_p,start_of_p + 3) == "?p=")
    {
      p = theCurrentLine.substring(start_of_p + 3, end_of_p);
      
    }
  }
  
  
   serial_println("read:" + theCurrentLine);
   serial_println("p=" + p);
   return p;
}

void write_webpage(EthernetClient client, String p)
{
  // send a standard http response header
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");  // the connection will be closed after completion of the response
  //client.println("Refresh: 5");  // refresh the page automatically every 5 sec
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<br />");
  client.println("You sent p=" + p + "<br />");
  client.println("<br />");
  // output the value of each analog input pin
  for (int analogChannel = 0; analogChannel < 3; analogChannel++) {
    int sensorReading = analogRead(analogChannel);
    client.print("analog input ");
    client.print(analogChannel);
    client.print(" is ");
    client.print(sensorReading);
    client.println("<br />");       
  }
  client.println("</html>");  
  // give the web browser time to receive the data
  delay(milliseconds_of_delay);
}
