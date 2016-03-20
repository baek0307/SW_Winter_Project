/*
	코드자체가 아직 완성단계가 아니지만 
	추후에 구현하고자하는 부분들은 수학적 계산이 필요하거나
	아두이노가 아닌 어플리케이션 개발과 관련됨
	일단은 여기까지 한걸 업로드합니다.
	-20133228 컴퓨터공학과 백장현
*/

#include <Wire.h> //LCD화면에 데이터 출력하기 위한 헤더파일
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

const int delayTime = 5;                      //일시정지 시간
int S = A0; // INPUT PIN
int M_Count = 0;
float time =0;
float c_time[100];
int count=1;


void setup() {
   Serial.begin(115200); // 시리얼 통신 초기화
   
   //마그네틱 센서를 이용하는부분
   
 Serial.println("Arduino Examples - Analog Hall Sensor");
 Serial.println(" http://docs.whiteat.com/?p=1288");
 Serial.println("Count Time  Magnetic   ");
 pinMode(S, INPUT); 
 
 
   //LCD화면에 출력하는부분
  lcd.init();
  lcd.backlight();
  lcd.print("Count Time  Mag");
}


void loop() {
  int save_count;
  //마그네틱 센서를 이용해 측정된 값이 400이상,300이하인 경우만 check
 if((analogRead(S) >=400) || (analogRead(S) <=300))
 {
   c_time[count] = time;

  if(count == 1 )
   {
     //마그네틱 센서로부터 얻은 값을 시리얼 모니터에 출력
     Serial.print(count); Serial.print("  "); Serial.print(c_time[count]); Serial.print("  ");Serial.println(analogRead(S), DEC);
     //LCD화면에 해당 수치를 보여줌
     lcd.setCursor(0,1);
     lcd.print(count); lcd.print("     ");lcd.print(c_time[count]);lcd.print("  ");lcd.print(analogRead(S), DEC);
     
   count++;
   }
  
   else if( c_time[count] - c_time[count-1] >= 0.3)
  { 
    
    Serial.print(count); Serial.print("  "); Serial.print(c_time[count]); Serial.print("  ");Serial.println(analogRead(S), DEC);
     lcd.setCursor(0,1);
    lcd.print(count); lcd.print("     ");lcd.print(c_time[count]);lcd.print("  ");lcd.print(analogRead(S), DEC);
   count++;
  }

    
 }
 time = time+0.1;
 delay(100);

                  
}
