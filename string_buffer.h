#ifndef STRING_BUFFER_H_
#define STRING_BUFFER_H_

#include <Arduino.h>

typedef const char* FlashAddr;

#define TempLength 

#define tempStringLength   4
#define weightStringLength 5
#define timeStringLength   6


class StringBuffer {
    int   bufferSize = 15;
    char* buffer;
    
  public:
    static StringBuffer global;
    
    StringBuffer(int size = 15);
    StringBuffer(FlashAddr flashStringAddress);
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
    inline int getSize();
};

inline int StringBuffer::getSize() {
  return bufferSize;
}

#endif