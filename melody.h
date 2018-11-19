#ifndef MELODY_H_
#define MELODY_H_

// Plays melody.
// Be aware, it's not async and it starves main thread

class Melody {
    static int buzzPin;
    int notesCount = 0;
    int *notes; //example: {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4} (include pitches.h)
    int *notesDuration; // note durations: 4 = quarter note, 8 = eighth note, etc.:

  public:
    static void setPin(int buzzPin);
    static void playNote(int note, int noteDuration); //note duration: 4 = quarter note, 8 = eighth note, etc.:
    static void playTone(int freq, int duration);     //duration in ms
    
    Melody::Melody(int* notes, int* notesDuration, int notesCount);
    ~Melody();
    void play();
};


#endif