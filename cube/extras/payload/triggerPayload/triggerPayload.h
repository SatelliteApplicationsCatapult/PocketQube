#ifndef triggerPayload_h
#define triggerPayload_h

#include <Cube.h>
#include <RH_RF22.h>
//#include <SD.h>
//#include <Adafruit_VC0706.h>

class triggerPayload : public Payload {
  public:
    triggerPayload();
    ~triggerPayload();
    void initialise();
    int doing();
    int done();
};

#endif
