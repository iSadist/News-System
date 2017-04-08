#include "newsgroup.h"

Newsgroup::Newsgroup(int uniqueId, std::string title) : id(uniqueId), title(title) {
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
	date.append(std::to_string(1900 + creationDate->tm_year));
	date.append("-");
	date.append(std::to_string(1 + creationDate->tm_mon));
	date.append("-");
	date.append(std::to_string(1 + creationDate->tm_mday));
	return date;
}

std::vector<Article> Newsgroup::getArticles(){
	return articles;
}

/*Checks name and adds articles or replaces text and creation date if article exists*/
void Newsgroup::addArticle(Article article){

}

Newsgroup::~Newsgroup() {
	delete creationDate;
}
