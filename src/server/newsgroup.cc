#include "newsgroup.h"

Newsgroup::Newsgroup(int uniqueId, std::string title) : id(uniqueId), title(title) {
	std::time_t now =  std::time(0);
	creationDate = std::localtime(&now);
}

Newsgroup::Newsgroup (int uniqueId, std::string title, std::tm *creation) : id(uniqueId), title(title), creationDate(creation) {}

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

Article Newsgroup::getArticle(int art_id){
	if (articles.size() == 0) return Article(-1,"null","null","null");

	auto itr = articles.begin();
	while (itr != articles.end()){
		if ((*itr).getId() == art_id){
			return *itr;
		}
	itr++;
	}
	return Article(-1,"null","null","null");
}

void Newsgroup::addArticle(Article article){
	articles.push_back(article);
}

bool Newsgroup::removeArticle(int art_id){
	if (articles.size() == 0) return false;

	auto itr = articles.begin();
	while (itr != articles.end()){
		if ((*itr).getId() == art_id){
			articles.erase(itr);
			return true;
		}
	itr++;
	}
	return false;
}

Newsgroup::~Newsgroup() {

}
