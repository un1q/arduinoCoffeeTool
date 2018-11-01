#include "global_string_buffer.h"

#include <Arduino.h>

char GlobalStringBuffer::buffer[bufferSize];

char* GlobalStringBuffer::secondsToString(int secTotal) {
  char* format = "%d:%02d";
  if (secTotal < 0) {
    format = "-%d:%02d";
    secTotal *= -1;
  }
  int sec = 0;
  int min = 0;
  sec = secTotal % 60;
  min = secTotal / 60;
  snprintf(buffer, bufferSize,format,min,sec);
  return buffer;
}

char* GlobalStringBuffer::intToString(int value, char* format) {
  snprintf(buffer, bufferSize,format,value);
  return buffer;
}

char* GlobalStringBuffer::intToString(int value) {
  return intToString(value, "%d");
}
