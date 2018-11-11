#include "string_buffer.h"

#include <Arduino.h>

char* StringBuffer::secondsToString(int secTotal) {
  nSecondsToString(secTotal);
  return buffer;
}

int StringBuffer::nSecondsToString(int secTotal) {
  char* format = "%d:%02d";
  if (secTotal < 0) {
    format = "-%d:%02d";
    secTotal *= -1;
  }
  int sec = 0;
  int min = 0;
  sec = secTotal % 60;
  min = secTotal / 60;
  return snprintf(buffer, bufferSize,format,min,sec);
}

char* StringBuffer::secondsToString(int secTotal, int length) {
  if (length > bufferSize-1)
    length = bufferSize-1;
  int n = nSecondsToString(secTotal);
  if (n < length && n >= 0) {
    memset(buffer+n, ' ', length-n);
    buffer[length] = '\0';
  }
  return buffer;
}

char* StringBuffer::intToString(int value, char* format) {
  snprintf(buffer, bufferSize,format,value);
  return buffer;
}

char* StringBuffer::intToString(int value) {
  return intToString(value, "%d");
}
