#ifndef STRING_BUFFER_H_
#define STRING_BUFFER_H_

class StringBuffer {
    static const int bufferSize = 8;
    char buffer[bufferSize];
    
  public:
    static StringBuffer global;
    
    int   nSecondsToString(int secTotal);
    char* secondsToString(int secTotal);
    char* secondsToString(int secTotal, int length);
    char* intToString(int value);
    char* intToString(int value, char* format);
};

#endif