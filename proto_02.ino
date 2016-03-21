
#include <Wire.h> //LCD화면에 데이터 출력하기 위한 헤더파일
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

const int delayTime = 5;                      //일시정지 시간

//홀마그네틱센서관련 변수
int S = A0; // INPUT PIN
int M_Count = 0;
float time =0;
int count=1;
//로터리 인코더 관련 변수
int rotary_Count = 0;
int R = 2; // 로터리 인코더의 스위치
int pinA = 3;//로터리 인코더 핀A와 핀B
int pinB = 4;//
int nowCnt = 0;


void setup() {
   Serial.begin(115200); // 시리얼 통신 초기화
   
   //마그네틱 센서를 이용하는부분
  
   Serial.println("Count Time  Magnetic   ");
   pinMode(S, INPUT); 
 
   //로터리 인코더를 이용하는부분
   pinMode(R, INPUT);
   pinMode(pinA, INPUT);
   pinMode(pinB, INPUT);
   digitalWrite(R, HIGH);
 
   //LCD화면에 출력하는부분
  lcd.init();
  lcd.backlight();
  lcd.print("Count Time  Mag");
}


void loop() {
  int save_count;
  
  
  
  //로터리 카운터의 스위치값이 0가 되는경우(다감아진경우) 새로운 데이터입력을 위해
  if (LOW == digitalRead(R))
   {
     Serial.println("Clear"); // 감지
     delay(200);
     rotary_Count = 0;
   }
 
 
   nowCnt = getValue();//바퀴가 앞으로 돌때는 일정 각도마다 +1, 뒤로돌때는 -1
 
   //바퀴가 회전하고 있다는의미
   if (nowCnt != 0)
   {
     rotary_Count += nowCnt;
     Serial.println(rotary_Count);
      
      //마그네틱 센서를 이용해 측정된 값이 400이상,300이하인 경우만 check
      if((analogRead(S) >=400) || (analogRead(S) <=300))
      {
        {
           //마그네틱 센서로부터 얻은 값을 시리얼 모니터에 출력
           Serial.print(count); Serial.print("  "); Serial.print(time); Serial.print("  ");Serial.println(analogRead(S), DEC);
           //LCD화면에 해당 수치를 보여줌
            lcd.setCursor(0,1);
            lcd.print(count); lcd.print("     ");lcd.print(time);lcd.print("  ");lcd.print(analogRead(S), DEC);
     
           count++;
         }
    
     }   
     
   }
   
 //loop문은 0.3초마다 돌아감
 time = time+0.3;
 delay(300);              
}


  int oldA = LOW;
  int oldB = LOW;
 
 //로터리 인코더작동관련 함수
 /*  현재 코드에서는 단순 휠체어가 이동중인지를 판별하면 되므로 크게 중요하지 않지만
    추후 환자가 앞으로 가는지 뒤로가는지, 어느정도만큼의 호를 그리며 좌/우회전하는지를 판별할수있게함
    바퀴가 앞으로 돌때는 10도마다 +1, 뒤로돌때는 -1
 */
int getValue()
{
   int rValue = 0;
   int A = digitalRead(pinA);
   int B = digitalRead(pinB);
 
   if (A != oldA || B != oldB)
   {
     if (oldA == LOW && A == HIGH)
     {
       if (oldB == HIGH) rValue = 1;
       else rValue = -1;
     }
   }
   oldA = A;
   oldB = B;
   return rValue;
}




