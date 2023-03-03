//*****************************************************************
//*** ゴール探索でのセンサの通信とサーボモータコントロールのプログラム
//*** PSDからの信号を受けるArduinoがH8へ送信し，側面に設置される．車庫入れが終わった後，一回目直線運動
//*** SONICからの信号を受けるArduinoがH8へ送信，正面に設置される．二回目直線運動
//*** YANG(2023/1/27) バージョン1.8
//*****************************************************************

#include <Servo.h>
Servo RC1servo;
Servo RC2servo;

#define PIN_OUTPUT_RC1 9    //腕を挟む用RC1への信号線
#define PIN_OUTPUT_RC2 10   //磁石に作用するRC2への信号線

#define PIN_INPUT_PSD 5     //PSDセンサからのアナログ信号ー入力
#define PIN_OUTPUT_B4 13    //処理したの信号をH8へ送るCN2-33. PSD
#define PIN_OUTPUT_B5 12    //処理したの信号をH8へ送るCN2-34. SONIC

#define PIN_INPUT 7  //H8から起動信号を受ける

#define PIN_TRG_SONIC 2     //SONIC超音波センサのTRG入力
#define PIN_ECHO_SONIC 3    //SONIC超音波センサのECHO出力

//初期値設定
//static int i_PSD = 1;//グローバル変数でPSDの起動
int RC1_pos = 0;
int RC2_pos = 0;
int i_B4 = 0;
int i_B5 = 0;

void setup() {
  // put your setup code here, to run once:

  //SONICのPIN 初期化
  pinMode(PIN_TRG_SONIC, OUTPUT);
  pinMode(PIN_ECHO_SONIC, INPUT);

  //OUTPUT and INPUT 初期化
  pinMode(PIN_OUTPUT_B4, OUTPUT);
  pinMode(PIN_OUTPUT_B5, OUTPUT);
  pinMode(PIN_INPUT, INPUT);
  pinMode(PIN_INPUT_PSD, INPUT);

  //RC1 and RC2　初期化
  pinMode(PIN_OUTPUT_RC1, OUTPUT);
  pinMode(PIN_OUTPUT_RC2, OUTPUT);
  
  RC1servo.attach(PIN_OUTPUT_RC1);
  RC2servo.attach(PIN_OUTPUT_RC2);
  
  Serial.begin(115200); //シリアル通信のボートを開く

  digitalWrite(PIN_TRG_SONIC,LOW);
  digitalWrite(PIN_OUTPUT_B4, LOW);//H8へ0を送る
  digitalWrite(PIN_OUTPUT_B5, LOW);//H8へ0を送る
  
  //RCの角度の初期化
  RC1servo.write(0);
  RC2servo.write(0);
}

void loop(){
  // put your main code here, to run repeatedly:   
    Serial.print("arduino処理開始\n");

    int interval = 0 ;           //pulse
    double distance = 0;        //距離
    int i_s = 0;                //距離判断のため
    int PSD_r_high = 30;        //PSDの閾値の高い
    int PSD_r_low = 15;         //PSDの閾値の低い
    int sonic_r = 13;           //超音波センサの閾値の値，この値によりRC1の運転を停止する.
    int PSD_val = 0;            //PSD値

    int input_1 = 0;  
    int input_2 = 0;
    
    input_1 = Inputread(PIN_INPUT);
    delay(10);//時間を持つ
    input_2 = Inputread(PIN_INPUT);
    delay(10);//時間を持つ

    if( i_B4 == 0){
      digitalWrite(PIN_OUTPUT_B4, LOW);//H8へ0を送る
       Serial.print("B4=0\n");
    }else{
      digitalWrite(PIN_OUTPUT_B4, HIGH);//H8へ1を送る
      Serial.print("B4=1\n");
    }
    
    if( i_B5 == 0){
      digitalWrite(PIN_OUTPUT_B5, LOW);//H8へ0を送る
      Serial.print("B5=0\n");
    }else{
      digitalWrite(PIN_OUTPUT_B5, HIGH);//H8へ1を送る
      Serial.print("B5=1\n");
    }
    
    if( (input_1 == HIGH) && (input_2 == HIGH)  ){
      //PSD処理
      Serial.print("PSDに入った.PSD_val:\n");
      PSD_val = PSDread( PIN_INPUT_PSD );
      Serial.print(PSD_val);
      Serial.print("\n");

      int PSD_d = AnaToCm(PSD_val);
      Serial.print(AnaToCm(PSD_val));
      Serial.println("cm");

      if( (PSD_d <= PSD_r_high ) && ( PSD_d > PSD_r_low ) ){
          digitalWrite(PIN_OUTPUT_B4,HIGH);
          i_B4 = 1;
          Serial.print("B4HIGH");
          }
      if( i_B4 == 1 ){
      //超音波センサ
      // 距離計測
      //trigger pulse output (10us)

      Serial.println("SONICに入った");
      digitalWrite(PIN_TRG_SONIC, HIGH);
      delayMicroseconds(9);
      digitalWrite(PIN_TRG_SONIC, LOW);
      // echo pulse width measure
      
      interval = pulseIn(PIN_ECHO_SONIC, HIGH, 30000);  // 時間計測
      distance = interval * 0.017;  
      
      // 時間=>距離に変換 [cm]340[m/sec]/2 = 0.017[cm/μs]
      distance=SONICread(distance);//distanceの100回平均
      
      // send result
        Serial.print("pulse width =");
        Serial.print(interval);
        Serial.print("[us] distance =");
        Serial.print(distance);
        Serial.print("[cm]\n");
        
        i_s = rc(distance, sonic_r);

        if( i_s == 1 ){//H8へ信号を送る
          i_B5=1;
          digitalWrite(PIN_OUTPUT_B5,HIGH);
          delay(1000);
          
          if( RC1_pos < 100 ){
          RC1servo.write(RC1_pos);
          RC1_pos+=10;        
          Serial.print("B5HIGH");
          Serial.print("RC1回転中\n");
          } 
          
          delay(50);
          
          if( RC1_pos >=100 ){
            Serial.print("RC2回転中\n");
            for(int i=0; RC2_pos<180;RC2_pos+=1 ){
                RC2servo.write(RC2_pos);    
                delay(15);           
               }
            }
        }
        //RCの回転
    }//SONIC実行    
  }//PIN_INPUT
}//loop

int PSDread(int PinNo){ //PSDの読み取り
  long ans=0;
  for(int i=0; i<100; i++){
    ans=ans +analogRead(PinNo);
  }  
  return ans/100;
}
int SONICread(int distance){
  double sum = 0;
  for(int i=0; i<100; i++){
    sum = sum + distance;
  }
  return sum/100.0;
}
int Inputread(int PinNo){
  int sum = 0;
  for(int i=0; i<100; i++){
    sum=sum +digitalRead(PinNo);
  }  
  if(sum < 80) return 0; 
  if(sum >= 80) return 1; 
}

int rc(double distance,int sonic_r){
      if( distance >= sonic_r ){
        Serial.print("直線2運転指令\n");
        return 0;
      }else if(distance == 0){
        return 0;
      }else{
        Serial.print("直線2運運転停止指令\n");        
        return 1;
      }
}

int AnaToCm(int analogValue){ //PSDの距離示す
  if(analogValue >= 470) return(10);
  if(analogValue >= 330) return(15);
  if(analogValue >= 259) return(20);
  if(analogValue >= 214) return(25);
  if(analogValue >= 172) return(30);
  if(analogValue >= 153) return(35);
  if(analogValue >= 134) return(40);
  if(analogValue >= 105) return(50);
  if(analogValue >= 85)  return(60);
  return(-1);
}
