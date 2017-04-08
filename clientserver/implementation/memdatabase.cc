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
	return true;
}

std::vector<Article> Memdatabase::list_ART(){
	return articles;
}

bool Memdatabase::create_ART(std::string title){
	return true;
}

bool Memdatabase::delete_ART(std::string title){
	return true;
}

Article Memdatabase::get_ART(std::string title){
	return articles[0];
}