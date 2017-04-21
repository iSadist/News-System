#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

class MessageHandler {
private:
  Connection* conn;

public:
  MessageHandler ();
  virtual ~MessageHandler ();

};

#endif
