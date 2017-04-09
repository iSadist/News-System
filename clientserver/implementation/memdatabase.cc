#include "memdatabase.h"
#include <string>
#include <algorithm>
#include <iostream>

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
	Newsgroup ng(++ng_counter, title);
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
	Article art(++art_counter, title, author, text);
	if (newsgroups.size() == 0) return false;
	auto itr = newsgroups.begin();
	while (itr != newsgroups.end()){
		if ((*itr).getId() == ng_id){
			newsgroups.at(itr - newsgroups.begin()).addArticle(art);
			return true;
		}
	itr++;
	}
	return false;
}

bool Memdatabase::delete_ART(int ng_id, int art_id){
	if (newsgroups.size() == 0) return false;
	auto it = get_NG_iterator(ng_id);
	if (it != newsgroups.end()){
		newsgroups.at(it - newsgroups.begin()).removeArticle(art_id);
		return true;
	}
	return false;
}

Article Memdatabase::get_ART(int ng_id, int art_id){
	auto it = get_NG_iterator(ng_id);
	if (it != newsgroups.end()){
		return newsgroups.at(it - newsgroups.begin()).getArticle(art_id);
	}
	return Article(-1,"null","null","null");
}

__gnu_cxx::__normal_iterator<Newsgroup*, std::vector<Newsgroup, std::allocator<Newsgroup> > >
Memdatabase::get_NG_iterator(int ng_id){
	auto lambda = [ng_id](Newsgroup newsgroup) { return newsgroup.getId() == ng_id; };
	auto it = std::find_if(newsgroups.begin(), newsgroups.end(), lambda);
	return it;
}



