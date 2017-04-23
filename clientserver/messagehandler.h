#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "protocol.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "message.h"
#include "article.h"
#include "newsgroup.h"

#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

class MessageHandler {

private:
  //Shared internal functions
  int readCommand(const Connection& conn);
  void writeCommand(const Connection& conn, unsigned char byte);

  int readNumber(const Connection& conn);
  void writeNumber(const Connection& conn, int value);

  string readString(const Connection& conn, int char_count);
  void writeString(const Connection& conn, const string& s);
  void writeString(const Connection& conn, string& s);

public:
  MessageHandler ();
  virtual ~MessageHandler ();

  //Shared
  Message getMessage(const Connection& conn);
  void sendMessage(const Connection& conn);

  //Client
  vector<pair<int, string>> clientListNewsgroups(const Connection& conn);
  void clientCreateNewsgroup(const Connection& conn, string title);
  void clientDeleteNewsgroup(const Connection& conn, int ng_id);
  vector<pair<int, string>> clientListArticles(const Connection& conn, int ng_id);
  void clientCreateArticle(const Connection& conn, int ng_id, string title, string author, string text);
  void clientDeleteArticle(const Connection& conn, int ng_id, int art_id);
  Article clientGetArticle(const Connection& conn, int ng_id, int art_id);

  //Server
  void server_send_ng_list(const Connection& conn, vector<Newsgroup> ng_list);
  void server_send_ng_create_response(const Connection& conn, bool success);
  void server_send_ng_delete_response(const Connection& conn, bool success);
  void server_send_ng_art_list(const Connection& conn, vector<Article> art_list);
  void server_send_art_create_response(const Connection& conn, bool success);
  void server_send_art_delete_response(const Connection& conn, bool success);
  void server_send_article(const Connection& conn, Article art);

};

#endif
