#include "memdatabase.h"
#include <string>

Memdatabase::Memdatabase(){

}

Memdatabase::~Memdatabase(){

}

std::vector<Newsgroup> Memdatabase::list_NG(){
	return newsgroups;
}

bool Memdatabase::create_NG(std::string title){
	return true;
}

bool Memdatabase::delete_NG(std::string title){
	if (newsgroups.size() == 0) return false;
	return true;
}

/*Searches for the newsgroup with ng_title in newsgroup list and
	returns its article list*/
std::vector<Article> Memdatabase::list_ART(std::string ng_title){
	return newsgroups[0].getArticles();
}

bool Memdatabase::create_ART(std::string title, std::string text){
	return true;
}

bool Memdatabase::delete_ART(std::string title){
	if (newsgroups.size() == 0) return false;
	return true;
}

Article Memdatabase::get_ART(std::string title){
	return newsgroups[0].getArticles()[0];
}