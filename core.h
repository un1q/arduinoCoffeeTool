#ifndef CORE_H_
#define CORE_H_

class Core {
  public:
    virtual void update(char key) = 0;
    virtual void start()          = 0;
};

#endif