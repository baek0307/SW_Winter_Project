
int position_pin[] = {1,2,3,4};               //4자리 결정 핀
int segment_pin[] = {5,6,7,8,9,10,11,12};     //세그먼트 제어 핀
const int delayTime = 5;                      //일시정지 시간
int S = A0; // INPUT PIN
int M_Count = 0;
float time =0;

//0 ~ 9를 표현하는 세그먼트 값
byte data[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xE6};

void setup() {
   Serial.begin(115200); // 시리얼 통신 초기화
 Serial.println("Arduino Examples - Analog Hall Sensor");
 Serial.println(" http://docs.whiteat.com/?p=1288");
 pinMode(S, INPUT); 
  
 
  //4자리 결정 핀 출력용으로 설정
  for(int i = 0; i < 4; i++) {
     pinMode(position_pin[i], OUTPUT);
  }

  //세그먼트 제어 핀 출력용으로 설정
  for(int i = 0; i < 8; i++) {
    pinMode(segment_pin[i], OUTPUT);
  }
}

void loop() {

  Serial.print("Time ="); Serial.print(time); Serial.print("  ");
  time = time+0.01;
Serial.print("Magnetic="); Serial.println(analogRead(S), DEC);Serial.print("  ");
 if(analogRead(S) >=600 ||analogRead(S) <=450)
 {
   M_Count++;
   Serial.print(M_Count); 
   count_M(M_Count);
   Serial.print("  ");Serial.print("Check");  
 }
 
 delay(10);

  
  //count();                
}

void show(int position, int number) {
  //4자리 중 원하는 자리 선택
  for(int i = 0; i < 4; i++) {
    if(i + 1 == position){
      digitalWrite(position_pin[i], LOW);
    } else {
      digitalWrite(position_pin[i], HIGH);
    }
  }

  //8개 세그먼트를 제어해서 원하는 숫자 출력
  for(int i = 0; i < 8; i++){
     byte segment = (data[number] & (0x01 << i)) >> i;
     if(segment == 1){
       digitalWrite(segment_pin[7 - i], HIGH);
     } else {
       digitalWrite(segment_pin[7 - i], LOW);
     }
  }
}

//M_count 
void count_M(int M_count){
  int i,j,k,l;
  i = (M_count/1000);
  j = (M_count/100)%10;
  k = (M_count/10)%10;
  l = M_count%10;
  
 show(1,i);
  delay(delayTime);
  show(2,j);
  delay(10*delayTime);
  show(3,k);
  delay(10*delayTime);
  show(4,l);
  delay(delayTime);


}


/*
 0001부터 하나씩 카운트하는 함수
*/
void count() {
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      for(int k = 0; k < 10; k++) {
        for(int l = 0; l < 10; l++) {
          show(1,i);
          delay(delayTime);
          show(2,j);
          delay(delayTime);
          show(3,k);
          delay(delayTime);
          show(4,l);
          delay(delayTime);
        }
      }
    }
  }
  delay(500);
}
