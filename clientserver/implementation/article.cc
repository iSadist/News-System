#include "article.h"

Article::Article(int id, std::string title, std::string author, std::string content) : id(id), title(title), author(author), content(content) {
  std::time_t now =  std::time(0);
  creationDate = std::localtime(&now);
}

int Article::getId() {
  return id;
}

std::string Article::getTitle() {
  return title;
}

std::string Article::getCreationDate() {
  std::string date = "";
  date.append(std::to_string(1900 + creationDate->tm_year));
  date.append("-");
  date.append(std::to_string(1 + creationDate->tm_mon));
  date.append("-");
  date.append(std::to_string(1 + creationDate->tm_mday));
  return date;
}

Article::~Article() {

}
