#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "protocol.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "message.h"
#include "article.h"

#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

class MessageHandler {
private:
  //Server
  int readNumber(const shared_ptr<Connection>& conn);
  string readString(const shared_ptr<Connection>& conn, int char_count);
  void writeString(const shared_ptr<Connection>& conn, const string& s);
  int readCommand(const shared_ptr<Connection>& conn);

  //Client
  void writeNumber(const Connection& conn, int value);
  string readString(const Connection& conn, int char_count);
  void writeString(const Connection& conn, string& s);


public:
  MessageHandler ();
  virtual ~MessageHandler ();

  //Server
  Message getMessage(const shared_ptr<Connection>& conn);
  void sendMessage(const shared_ptr<Connection>& conn);

  //Client
  vector<pair<int, string>> clientListNewsgroups(const Connection& conn) const;
  int clientCreateNewsgroup(const Connection& conn, string title);
  int clientDeleteNewsgroup(const Connection& conn, int ng_id);
  vector<pair<int, string>> clientListArticles(const Connection& conn, int ng_id);
  int clientCreateArticle(const Connection& conn, int ng_id, string title, string author, string text);
  int clientDeleteArticle(const Connection& conn, int ng_id, int art_id);
  Article clientGetArticle(const Connection& conn, int ng_id, int art_id);

  void setConnection(const Connection* new_conn);
};

#endif
