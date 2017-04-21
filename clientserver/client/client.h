#ifndef CLIENT_H
#define CLIENT_H

#include "connection.h"
#include "messagehandler.h"

#include <string>

class Client {
private:
  Connection* conn;
  Server* server;
  int current_newsgroup;

  void print_newsgroup_menu(int newsgroup_id);
  void newsgroup_options(int newsgroup_id);

public:
  Client (const char* host, int port);
  Client ();
  virtual ~Client ();

  int scanInputInteger();
  std::string scanInputString();

  void changeToNewsgroup();
  void listNewsgroups();
  void createNewsgroup();
  void deleteNewsgroup();

  void listArticles(int newsgroup_id);

  void readArticle(int newsgroup_id);
  void writeArticle(int newsgroup_id);
  void deleteArticle(int newsgroup_id);

  void switchServer();

};

#endif
