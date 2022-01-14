#ifndef Payload_h
#define Payload_h

/*****************************************************************************
* This class is the abstract data type for payload, for plugin to the platform.
******************************************************************************/
class Payload {
  public:
    virtual void initialise();
    virtual int doing(int mode, char argv[][10]);
    virtual int done();
};

#endif
