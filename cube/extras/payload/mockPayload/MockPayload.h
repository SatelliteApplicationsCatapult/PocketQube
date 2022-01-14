#ifndef MockPayload_h
#define MockPayload_h
//#define LED_PIN 13 //LED on Arduino Uno
#define LED_PIN 17 // for LED on Pro Micro
#include <Payload.h>

class MockPayload : public Payload {
  public:
    MockPayload();
    ~MockPayload();
    void initialise();
    int doing(int mode, char argv[][10]);
    int done();
};

#endif
