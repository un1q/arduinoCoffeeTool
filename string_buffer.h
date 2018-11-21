#ifndef STRING_BUFFER_H_
#define STRING_BUFFER_H_

#include <Arduino.h>

typedef const char* FlashAddr;

class StringBuffer {
    int   bufferSize = 15;
    char* buffer;
    
  public:
    static StringBuffer global;
    
    StringBuffer(int size = 15);
    ~StringBuffer();
    
    int   nSecondsToString(int secTotal);
    char* secondsToString(int secTotal);
    char* secondsToString(int secTotal, int length);
    char* intToString(int value);
    char* intToString(int value, const char* format);
    char* flashToString(FlashAddr flashAddr);
    char* flashToString(const __FlashStringHelper *flashAddr);
    char* tempToString(int temp);
    char* weightToString(int weight);
    char* emptyString();
    char* get();
    //char* center();
};

#endif