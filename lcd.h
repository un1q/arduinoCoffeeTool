#ifndef LCD_H_
#define LCD_H_

// Everything LCD dependent should go here
//(if you want to use different resolution, you need to change this class and nothing more)

#include <LiquidCrystal_I2C.h>

typedef int* Position;

class Lcd {
    LiquidCrystal_I2C *lcd;
    const static int startPosition = 3;
    int selectedPosition  = startPosition;
    
    void setSelectedPosition(int position);
  public:
    int positions[8][2] = {
      {01,1},
      {06,1},
      {11,1},
      {01,0},
      {07,0},
      {12,0},
      {01,1},
      {10,1}
    };
    const int POS_TEMP          = 0;
    const int POS_WEIGHT        = 1;
    const int POS_TIMER         = 2;
    const int POS_ALARM_TEMP    = 3;
    const int POS_ALARM_WEIGHT  = 4;
    const int POS_ALARM_TIMER   = 5;
    const int POS_PRESET_OPTION = 6;
    const int POS_BACK_OPTION   = 7;
    
    Lcd();
    ~Lcd();
    void setup();
    void clear();
    void print(Position position, char* text);
    void print(int x, int y, char* text);
    void print(int positionIndex, char* text);
    void selectUp();
    void selectDown();
    void selectLeft();
    void selectRight();
    int  getSelectedPosition();
    void startSelection();
};

#endif
