#ifndef LCD_H_
#define LCD_H_

class Lcd {
  public:
    struct Info {
      int temp   = 0;
      int time   = 0;
      int weight = 0;
      char* alarmDesc   = nullptr;
      char* step        = nullptr;
      char* nextStep    = nullptr;
    };

    struct Menu {
      char** options  = nullptr;
      int    size     = 0;
      int    selected = -1;
    };
    
    virtual ~Lcd();
    virtual void setup()           = 0;
    virtual void print(Info *info) = 0;
    virtual void print(Menu *menu) = 0;
    virtual void clear()           = 0;
};

#endif
