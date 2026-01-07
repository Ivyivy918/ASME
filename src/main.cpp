#include <Arduino.h>
#include <Servo.h>

// 定義馬達物件
Servo base, shoulder, elbow, gripper;

// 定義腳位
const int pins[] = {3, 5, 6, 9};
Servo* servos[] = {&base, &shoulder, &elbow, &gripper};
const char* names[] = {"Base (Pin 3)", "Shoulder (Pin 5)", "Elbow (Pin 6)", "Gripper (Pin 9)"};

void testServo(int index) {
    Serial.print("正在測試: ");
    Serial.println(names[index]);
    
    servos[index]->attach(pins[index]); // 連接馬達
    
    // 0 -> 180 度
    for (int pos = 0; pos <= 180; pos += 2) {
        servos[index]->write(pos);
        delay(15);
    }
    // 180 -> 0 度
    for (int pos = 180; pos >= 0; pos -= 2) {
        servos[index]->write(pos);
        delay(15);
    }
    
    servos[index]->detach(); // 測試完斷開，省電也避免干擾
    Serial.println("測試完成。");
}

void setup() {
    Serial.begin(9600);
    Serial.println("--- meArm 馬達逐一測試程式 ---");
    Serial.println("請輸入數字來測試對應馬達:");
    Serial.println("1: 底座 (Pin 3)");
    Serial.println("2: 肩部 (Pin 5)");
    Serial.println("3: 肘部 (Pin 6)");
    Serial.println("4: 夾爪 (Pin 9)");
}

void loop() {
    if (Serial.available() > 0) {
        char input = Serial.read();
        int choice = input - '1'; 

        if (choice >= 0 && choice <= 3) {
            testServo(choice);
        } else if (input != '\n' && input != '\r') {
            Serial.println("無效輸入，請輸入 1, 2, 3 或 4");
        }
    }
}