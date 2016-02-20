const int delayTime = 1;                      //일시정지 시간
int S = A0; // INPUT PIN
int M_Count = 0;
float time =0;
float c_time[100];
int count=1;


void setup() {
   Serial.begin(115200); // 시리얼 통신 초기화
 Serial.println("Arduino Examples - Analog Hall Sensor");
 Serial.println(" http://docs.whiteat.com/?p=1288");
 Serial.println("Count Time  Magnetic   ");
 pinMode(S, INPUT); 
  
}


void loop() {
  int save_count;
  
 if(analogRead(S) >=600 ||analogRead(S) <=450)
 {
   c_time[count] = time;
   
  if(count == 1 )
   {
     Serial.print(count); Serial.print("  "); Serial.print(c_time[count]); Serial.print("  ");Serial.println(analogRead(S), DEC);
   count++;
   }
  
   else if( c_time[count] - c_time[count-1] >= 0.3)
  { 
    Serial.print(count); Serial.print("  "); Serial.print(c_time[count]); Serial.print("  ");Serial.println(analogRead(S), DEC);
   count++;
  }

    
 }
 // I'll write coment in english cause Hangul doesn't present in this program
 // When this magnetic sensor satisfied in this case, count up, and present the time in screen.
 time = time +0.01;
delay(10);


                  
}
