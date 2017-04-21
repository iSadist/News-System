#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "protocol.h"
#include "connection.h"
#include "connectionclosedexception.h"

#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

class MessageHandler {
private:
  Connection* conn;

public:
  MessageHandler (const Connection& conn);
  virtual ~MessageHandler ();

  //Server -> Client
  int readNumber(const shared_ptr<Connection>& conn);
  void writeString(const shared_ptr<Connection>& conn, const string& s);

  //Client -> Server
  void writeNumber(const Connection& conn, int value);
  string readString(const Connection& conn);

  void setConnection(const Connection* new_conn) {
    conn = new_conn;
  }

};

#endif
