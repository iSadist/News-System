#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include <string>
#include <ctime>

class Newsgroup {
private:
  int id;
  std::string title;
  std::tm *creationDate;

public:
  Newsgroup (int uniqueId, std::string title);
  int getId();
  std::string getTitle();
  std::string getCreationDate();

  virtual ~Newsgroup ();
};

#endif
