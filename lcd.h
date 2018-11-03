#ifndef LCD_H_
#define LCD_H_

class Lcd {
  public:
    struct Info {
      int temp   = 0;
      int time   = 0;
      int weight = 0;
      char* tempAlarm   = "";
      char* timeAlarm   = "";
      char* weightAlarm = "";
    };

    struct Menu {
      char** options  = nullptr;
      int    size     = 0;
      int    selected = -1;
      int SelectNext();
      int SelectPrev();
    };
    
    virtual void setup();
    virtual void print(Info *info) = 0;
    virtual void print(Menu *menu) = 0;
};

#endif
