#include "article.h"

Article::Article(int id, std::string title, std::string author, std::string content) : id(id), title(title), author(author), content(content) {
  std::time_t now =  std::time(0);
  creationDate = std::localtime(&now);
}

int Newsgroup::getId() {
  return id;
}

std::string Newsgroup::getTitle() {
  return title;
}

std::string Newsgroup::getCreationDate() {
  std::string date = "";
  date.append(1900 + creationDate->tm_year);
  date.append("-");
  date.append(1 + creationDate->tm_mon);
  date.append("-");
  date.append(1 + creationDate->tm_mday);
  return date;
}

virtual Newsgroup::~Newsgroup() {
  delete creationDate;
}
