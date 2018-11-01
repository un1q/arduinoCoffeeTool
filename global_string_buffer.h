#ifndef GLOBAL_STRING_BUFFER_H_
#define GLOBAL_STRING_BUFFER_H_

class GlobalStringBuffer {
  public:
    const static int bufferSize = 8;
    static char buffer[bufferSize];
    
    static char* secondsToString(int secTotal);
    static char* intToString(int value);
    static char* intToString(int value, char* format);
};

#endif