String strstuff = "G23 X42 Y54.245   Z4; E31; ";
String G;
double x; //end result of what comes after x
double y; //end result of what comes after y
int i;
int lengthstr;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  while (!Serial){
    
  }

  

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(strstuff[0]);
  if (Serial.available()){
    //now you run code after you've entered that dumb string.
    lengthstr = strstuff.length();
    i = 0;
    x = 0;
    y = 0;
    
    while (i<=lengthstr){
      if (strstuff[i] == 'G'){
        
        if (isDigit(strstuff[i + 1])){
          
        }
        else{
          i++;
        }
        
      }
      else if (strstuff[i] == 'X'){
        if (isDigit(strstuff[i + 1])){
          
        }
      }
      else if (strstuff[i] == 'Y'){
        
      }
      
      
      
    }
  }
  

}
