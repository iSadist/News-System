#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "protocol.h"

using namespace std;

class MessageHandler {
private:
  Connection* conn;

public:
  MessageHandler ();
  virtual ~MessageHandler ();

  //Server -> Client
  int readNumber(const shared_ptr<Connection>& conn);
  void writeString(const shared_ptr<Connection>& conn, const string& s);

  //Client -> Server

  void writeNumber(const Connection& conn, int value);
  string readString(const Connection& conn);

};

#endif
