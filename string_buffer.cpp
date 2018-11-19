#include "string_buffer.h"

#include <Arduino.h>

StringBuffer StringBuffer::global;

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

char* StringBuffer::intToString(int value, const char* format) {
  snprintf(buffer, bufferSize,format,value);
  return buffer;
}

char* StringBuffer::intToString(int value) {
  return intToString(value, "%d");
}

char* StringBuffer::flashToString(FlashAddr flashAddr) {
  strncpy_P(buffer, flashAddr, bufferSize);
  //memcpy_P(buffer, flashAddr, bufferSize);
  buffer[bufferSize-1] = '\0'; //just in case buffer is to small: I'd rather get truncated string, then trash
  return buffer;
}

char* StringBuffer::flashToString(const __FlashStringHelper *flashAddr) {
  strncpy_P(buffer, (PGM_P)flashAddr, bufferSize);
  //memcpy_P(buffer, flashAddr, bufferSize);
  buffer[bufferSize-1] = '\0'; //just in case buffer is to small: I'd rather get truncated string, then trash
  return buffer;
}

char* StringBuffer::tempToString(int temp) {
  return intToString(temp < -99 ? -99 : temp, "%03dC");
}

char* StringBuffer::weightToString(int weight) {
  return intToString(weight, "%03dg");
}

char* StringBuffer::emptyString() {
  buffer[0]='\0';
  return buffer;
}

char* StringBuffer::get() {
  return buffer;
}