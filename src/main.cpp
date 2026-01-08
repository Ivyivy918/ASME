#include <Arduino.h>
#include <Servo.h>

// 定義馬達
Servo sBase, sShoulder, sElbow, sGripper;

// --- 360度馬達 靜止點 (請依據實際測試微調 90-93) ---
int stopBase = 90;
int stopShoulder = 90;
int stopElbow = 92; 

// --- 180度前爪 參數 (保留你的修改) ---
int gripAngle = 120; 
int gripStep = 10;   

// --- 速度與時間設定 ---
int speedOffset = 20;    // 轉動速度
int moveDuration = 150;  // 每個按鍵字元觸發轉動的時間 (毫秒)

void setup() {
    Serial.begin(9600);
    
    sBase.attach(3);
    sShoulder.attach(5);
    sElbow.attach(6);
    sGripper.attach(9);

    // 初始停止狀態
    sBase.write(stopBase);
    sShoulder.write(stopShoulder);
    sElbow.write(stopElbow);
    sGripper.write(gripAngle); 

    Serial.println("--- 時間模擬角度控制模式 ---");
    Serial.println("輸入 w/s, a/d, e/q 多個字母並按 Enter (例如: www)");
    Serial.println("空白鍵 或 x：緊急停止所有馬達");
}

// 輔助函式：讓馬達轉動一小段時間後停止
void moveContinuous(Servo &s, int speed, int stopPoint) {
    s.write(speed);
    delay(moveDuration); // 按下一次移動的時間
    s.write(stopPoint);  // 移動完畢自動停止
}

void stopAll() {
    sBase.write(stopBase);
    sShoulder.write(stopShoulder);
    sElbow.write(stopElbow);
}

void loop() {
    if (Serial.available() > 0) {
        char cmd = Serial.read();

        switch (cmd) {
            // --- Base (Pin 3) ---
            case 'a': moveContinuous(sBase, stopBase + speedOffset, stopBase); break;
            case 'd': moveContinuous(sBase, stopBase - speedOffset, stopBase); break;

            // --- Shoulder (Pin 5) ---
            case 'w': moveContinuous(sShoulder, stopShoulder + speedOffset, stopShoulder); break;
            case 's': moveContinuous(sShoulder, stopShoulder - speedOffset, stopShoulder); break;

            // --- Elbow (Pin 6) ---
            case 'q': moveContinuous(sElbow, stopElbow - speedOffset, stopElbow); break;
            case 'e': moveContinuous(sElbow, stopElbow + speedOffset, stopElbow); break;

            // --- Gripper (Pin 9) 保留你的 120-140 度邏輯 ---
            case 'r': 
                gripAngle = constrain(gripAngle - gripStep, 120, 140); 
                sGripper.write(gripAngle);
                break; 
            case 'f': 
                gripAngle = constrain(gripAngle + gripStep, 120, 140); 
                sGripper.write(gripAngle);
                break;

            // --- 空白鍵或 x：緊急停止 ---
            case ' ':
            case 'x':
                stopAll();
                Serial.println("!!! EMERGENCY STOP !!!");
                break;
        }
    }
}