#include "memdatabase.h"
#include <string>

Memdatabase::Memdatabase() : ng_counter(0), art_counter(0){

}

Memdatabase::~Memdatabase(){

}

std::vector<Newsgroup> Memdatabase::list_NG(){
	return newsgroups;
}

bool Memdatabase::create_NG(std::string title){
	for (Newsgroup newsgroup : newsgroups){
		if (newsgroup.getTitle() == title){
			return false;
		}
	}
	Newsgroup ng(ng_counter++, title);
	newsgroups.push_back(ng);
	return true;
}

bool Memdatabase::delete_NG(int ng_id){
	if (newsgroups.size() == 0) return false;
	auto itr = newsgroups.begin();
	while (itr != newsgroups.end()){
		if ((*itr).getId() == ng_id){
			newsgroups.erase(itr);
			return true;
		}
	itr++;
	}
	return false;
}

std::vector<Article> Memdatabase::list_ART(int ng_id){
	for (auto newsgroup : newsgroups){
		if (newsgroup.getId() == ng_id){
			return newsgroup.getArticles();
		}
	}
	return std::vector<Article>();
}

bool Memdatabase::create_ART(int ng_id, std::string title, std::string author, std::string text){
	Article art(art_counter++, title, author, text);
	if (newsgroups.size() == 0) return false;
	auto itr = newsgroups.begin();
	while (itr != newsgroups.end()){
		if ((*itr).getId() == ng_id){
			newsgroups.at(newsgroups.end() - itr).addArticle(art);
			return true;
		}
	itr++;
	}
	return false;
}

bool Memdatabase::delete_ART(int ng_id, int art_id){
	if (newsgroups.size() == 0) return false;
	return true;
}

Article Memdatabase::get_ART(int ng_id, int art_id){
	return newsgroups[0].getArticles()[0];
}