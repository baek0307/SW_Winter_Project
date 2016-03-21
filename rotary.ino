/*
  로터리 인코더를 사용하여 휠체어의 바퀴가 회전중인지를 확인하는코드
*/

int totalCount = 0;
int S = 2; // Switch
int pinA = 3;
int pinB = 4;
 
// 프로그램 시작 - 초기화 작업
void setup()
{
 Serial.begin(115200); // 시리얼 통신 초기화
 pinMode(S, INPUT);
 pinMode(pinA, INPUT);
 pinMode(pinB, INPUT);
 digitalWrite(S, HIGH);
}
 
int nowCnt = 0;
void loop()
{
 if (LOW == digitalRead(S))
 {
 Serial.println("Clear"); // 감지
 delay(200);
 totalCount = 0;
 }
 else
 {
 //Serial.print("."); // 없음
 }
 
 nowCnt = getValue();
 
 if (nowCnt != 0)
 {
 totalCount += nowCnt;
 Serial.println(totalCount);
 }
 
}
 
int oldA = LOW;
int oldB = LOW;
 
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

