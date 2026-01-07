#include <Wire.h>
#include "ClassicController.h"

void ClassicController::begin(uint8_t player) {
    _address = player;
    Wire.begin();
    Wire.beginTransmission(_address);
    Wire.write(0x40);
    Wire.write(0x00);
    Wire.endTransmission();
}

void ClassicController::update() {
    Wire.requestFrom(_address, (uint8_t)6);
    int i = 0;
    while (Wire.available()) {
        _data[i++] = (Wire.read() ^ 0x17) + 0x17;
    }
    _send_request();
}

void ClassicController::_send_request() {
    Wire.beginTransmission(_address);
    Wire.write(0x00);
    Wire.endTransmission();
}

// 實作程式碼中使用的判斷邏輯
bool ClassicController::joy_left_left() { return (_data[0] & 0x3F) < 20; }
bool ClassicController::joy_left_right() { return (_data[0] & 0x3F) > 44; }
bool ClassicController::joy_left_up() { return (_data[1] & 0x3F) > 44; }
bool ClassicController::joy_left_down() { return (_data[1] & 0x3F) < 20; }
bool ClassicController::joy_right_left() { return (_data[2] >> 7 | _data[1] >> 6 << 1 | _data[0] >> 6 << 2) < 2; }
bool ClassicController::joy_right_right() { return (_data[2] >> 7 | _data[1] >> 6 << 1 | _data[0] >> 6 << 2) > 28; }
bool ClassicController::joy_right_up() { return (_data[2] & 0x1F) > 28; }
bool ClassicController::joy_right_down() { return (_data[2] & 0x1F) < 2; }
bool ClassicController::button_a() { return !(_data[5] & 0x10); }
bool ClassicController::button_b() { return !(_data[5] & 0x40); }
bool ClassicController::button_home() { return !(_data[4] & 0x08); }
int ClassicController::shoulder_left() { return (_data[2] >> 2 | _data[3] >> 5 << 3); }
int ClassicController::shoulder_right() { return (_data[3] & 0x1F); }
void ClassicController::joy_left_set_scaled_min_max(int x1, int x2, int y1, int y2) {}
void ClassicController::joy_right_set_scaled_min_max(int x1, int x2, int y1, int y2) {}