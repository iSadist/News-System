#include "memdatabase.h"
#include "article.h"

#include <memory>
#include <iostream>
#include <string>

using namespace std;

Memdatabase db;

int main(int argc, char* argv[]){
	db = Memdatabase();

	db.list_NG();
	std::cout << "deleting article: " << db.get_ART(22, 44).getId() << std::endl;

	db.list_ART(3);

	db.create_NG("Good News Group");
	db.create_NG("Bad News Group");
	std::vector<Newsgroup> ngs = db.list_NG();
	for (auto ng : ngs){
		std::cout << ng.getTitle() << std::endl;
	}
	db.create_ART(1, "Today", "Marcel", "Sunday afternoon is pretty chill");
	db.create_ART(2, "Tomorrow", "Lecram", "Monday morning sucks");
	std::vector<Article> arts = db.list_ART(1);;
	for (auto art : arts){
		std::cout << art.getTitle() << std::endl;
	}

	Article art = db.get_ART(1, 1);
	std::cout << art.getId() << " " << art.getTitle() << " " << art.getAuthor()
	<< " " << art.getContent() << std::endl;

	art = db.get_ART(2, 2);
	std::cout << art.getId() << " " << art.getTitle() << " " << art.getAuthor()
	<< " " << art.getContent() << std::endl;

	std::cout << "deleting article: "<< db.delete_ART(1, 1) << std::endl;

	std::cout << "No crashes while testing memory database, newsgroups and article classes" << std::endl;

}
