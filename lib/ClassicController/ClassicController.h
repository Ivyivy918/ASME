#ifndef ClassicController_h
#define ClassicController_h
#include <Arduino.h>

#define WII_PLAYER_1 0x52

class ClassicController {
public:
    void begin(uint8_t player);
    void update();
    bool joy_left_left();
    bool joy_left_right();
    bool joy_left_up();
    bool joy_left_down();
    bool joy_right_left();
    bool joy_right_right();
    bool joy_right_up();
    bool joy_right_down();
    bool button_a();
    bool button_b();
    bool button_home();
    int shoulder_left();
    int shoulder_right();
    void joy_left_set_scaled_min_max(int x1, int x2, int y1, int y2);
    void joy_right_set_scaled_min_max(int x1, int x2, int y1, int y2);

private:
    uint8_t _address;
    uint8_t _data[6];
    void _send_request();
};
#endif