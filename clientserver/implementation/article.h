#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>
#include <ctime>

class Article {
private:
  int id;
  std::string title;
  std::string author;
  std::string content;
  std::tm *creationDate;

public:
  Article (int id, std::string title, std::string author, std::string content);
  int getId();
  std::string getTitle();
  std::string getAuthor();
  std::string getContent();
  std::string getCreationDate();

  virtual ~Article ();
};

#endif
