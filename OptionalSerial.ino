
//make serial calls optional
boolean use_serial;


void set_up_serial(boolean doit_or_dont)
{
  use_serial = doit_or_dont;
  
  if(use_serial)
  {
   // Open serial communications and wait for port to open:
     //Serial.begin(9600);
     //while (!Serial) 
     //{
      ; // wait for serial port to connect. Needed for Leonardo only
    //}      
  }
  
   
}

void serial_print(String this_string)
{
  if(use_serial)
  {
    //Serial.print(this_string);
  }
}

void serial_println(String this_string)
{
  if(use_serial)
  {
    //Serial.println(this_string);
  }
}

void serial_write(char this_char)
{
  if(use_serial)
  {
    //Serial.write(this_char);
  }
}

