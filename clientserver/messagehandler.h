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
  //Server -> Client
  int readNumber(const shared_ptr<Connection>& conn);
  void writeString(const shared_ptr<Connection>& conn, const string& s);

  //Client -> Server
  void writeNumber(const Connection& conn, int value);
  string readString(const Connection& conn);

public:
  MessageHandler ();
  virtual ~MessageHandler ();

  //Server -> Client
  string getMessage(const shared_ptr<Connection>& conn);
  void sendMessage(const shared_ptr<Connection>& conn);

  //Client -> Server
  vector<pair<int, string>> clientListNewsgroups(const Connection& conn) const;
  int clientCreateNewsgroup(const Connection& conn, string title);
  int clientDeleteNewsgroup(const Connection& conn, int ng_id);
  vector<pair<int, string>> clientListArticles(const Connection& conn, int ng_id) const;
  int clientCreateArticle(const Connection& conn, ng_id, string title, string author, string text);
  int clientDeleteArticle(const Connection& conn, ng_id, art_id);
  Article clientGetArticle(const Connection& conn, ng_id, art_id) const;

  void setConnection(const Connection* new_conn);
};

#endif
