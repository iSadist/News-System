#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include <string>
#include <ctime>
#include <vector>
#include "article.h"

class Newsgroup {
private:
	int id;
	std::string title;
	std::tm *creationDate;
	std::vector<Article> articles;

public:
	Newsgroup (int uniqueId, std::string title);
	int getId();
	std::string getTitle();
	std::string getCreationDate();
	std::vector<Article> getArticles();
	Article getArticle(int art_id);
	void addArticle(Article article);
	bool removeArticle(int art_id);
	virtual ~Newsgroup ();
};

#endif
