#ifndef CLIENT_H
#define CLIENT_H

#include "../connection.h"
#include <string>

class Client {
private:
  Connection* conn;
  Server* server;
  int current_newsgroup;

public:
  Client (); //Connect to server?
  virtual ~Client ();

  void changeToNewsgroup(int newsgroupId);

  void listNewsgroups();
  void createNewsgroup(std::string title);
  void deleteNewsgroup(std::string title);

  void listArticles();

  void readArticle();
  void writeArticle();
  void deleteArticle();

  void switchServer();

};

#endif
