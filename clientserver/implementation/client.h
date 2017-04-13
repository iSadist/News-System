#ifndef CLIENT_H
#define CLIENT_H

#include "newsgroup.h"
#include "article.h"
#include "connection.h"
#include "database.h"
#include "memdatabase.h"
#include <string>

class Client {
private:
  Newsgroup* currentNewsgroup;
  Connection* conn;
  Server* server;

public:
  Client (); //Connect to server?
  virtual ~Client ();

  void changeToNewsgroup(int newsgroupId);

  void listNewsgroups();
  void createNewsgroup(std::string title);
  void deleteNewsgroup(std::string title);

  void listArticles(Newsgroup group);

  void readArticle(Newsgroup group, Article article);
  void writeArticle(Newsgroup group, std::string text);
  void deleteArticle(Newsgroup group, Article article);

  void switchServer();

};

#endif
