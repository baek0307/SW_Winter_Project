//샐굼맿블뤁툿몯듈젣댈작동한늕확읺학윟한콛입닏

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
  byte data;
  data = Serial.read();
  //슴맡틒폰을롭붙a란묹잘입력받은경앋둥인uno13번led불들엉옵ㅂㅂ닏
  if(data =='a'){
    digitalWrite(13,HIGH);
  }
  //b입격된는경불껒집닏
  if(data =='b'){
    digitalWrite(13,LOW);
  }
  }

}
