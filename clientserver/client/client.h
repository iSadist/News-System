#ifndef CLIENT_H
#define CLIENT_H

#include "../connection.h"
#include "../implementation/messagehandler.h"

#include <string>

class Client {
private:
  Connection* conn;
  Server* server;
  int current_newsgroup;

  void print_newsgroup_menu(int newsgroup_id);
  void newsgroup_options(int newsgroup_id);
  int scanInputInteger();

public:
  Client (const char* host, int port);
  Client ();
  virtual ~Client ();

  void changeToNewsgroup();

  void listNewsgroups();
  void createNewsgroup();
  void deleteNewsgroup();

  void listArticles(int newsgroup_id);

  void readArticle();
  void writeArticle();
  void deleteArticle();

  void switchServer();

};

#endif
