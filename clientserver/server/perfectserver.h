#ifndef PERFECT_SERVER_H

#define PERFECT_SERVER_H

#include "server.h"
#include "messagehandler.h"

class PerfectServer{
private:
  Server server;
  MessageHandler msg_hand;

public:
  PerfectServer ();
  virtual ~PerfectServer ();

};



#endif
