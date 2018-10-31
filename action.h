#ifndef ACTION_H_
#define ACTION_H_

//abstract
class Action {
  public:
    virtual void doIt() = 0;
    virtual ~Action();
};

#endif