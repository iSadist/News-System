#include "memdatabase.h"
#include "sqldatabase.h"
#include "article.h"

#include <memory>
#include <iostream>
#include <string>

using namespace std;

Sqldatabase db;

int main(){
	std::cout << "-----Test of Memdatabase, Newsgroup and Article classes-----" << std::endl;
	// db = Memdatabase();
	db = Sqldatabase();

	std::cout << "Listing newsgroups: " << std::endl;
	std::vector<Newsgroup> ngs = db.list_NG();
	for (auto ng : ngs){
		std::cout << ng.getTitle() << std::endl;
	}

	std::cout << "Retrieving id of article (NG 22, id 44): " << db.get_ART(22, 44).getId() << std::endl;

	std::cout << "Listing articles in non-existing newsgroup (NG 3): " << std::endl;
	std::vector<Article> arts = db.list_ART(3);
	for (auto art : arts){
		std::cout << art.getTitle() << std::endl;
	}

	std::cout << "Creating two newsgroups (Good and Bad newsgroups) " << std::endl;
	db.create_NG("Good News Group");
	db.create_NG("Bad News Group");

	std::cout << "Newsgroups in database: " << std::endl;
	ngs = db.list_NG();
	for (auto ng : ngs){
		std::cout << ng.getTitle() << std::endl;
	}

	std::cout << "Creating article Today in Good News and Tomorrow in Bad News: " << std::endl;
	bool success = db.create_ART(1, "Today", "Marcel", "Sunday afternoon is pretty chill");
	bool success2 = db.create_ART(2, "Tomorrow", "Lecram", "Monday morning sucks");
	std::cout << success << success2 << '\n';

	arts = db.list_ART(1);

	std::cout << "Listing articles in newsgroup 1 (Good News Group) " << std::endl;
	for (auto art : arts){
		std::cout << art.getTitle() << std::endl;
	}

	std::cout << "Retrieving article (NG 1, id 1): " << std::endl;
	Article art = db.get_ART(1, 1);
	std::cout << "Article: " << art.getId() << " " << art.getTitle() << " " << art.getAuthor()
	<< " " << art.getContent() << " " << art.getCreationDate() << std::endl;

	std::cout << "Retrieving article (NG 2, id 2): " << std::endl;
	art = db.get_ART(2, 2);
	std::cout << "Article: " << art.getId() << " " << art.getTitle() << " " << art.getAuthor()
	<< " " << art.getContent() << " " << art.getCreationDate() << std::endl;

	std::cout <<  "deleting article (NG 1, id 1): "<< std::boolalpha << db.delete_ART(1, 1) << std::endl;
	std::cout << "Retrieving deleted article (NG 1, id 1): " << std::endl;
	art = db.get_ART(1, 1);
	std::cout << "Article: " << art.getId() << " " << art.getTitle() << " " << art.getAuthor()
	<< " " << art.getContent() << " " << art.getCreationDate() << std::endl;

	db.close_connection();
	std::cout << "-----Test of Memdatabase, Newsgroup and Article classes completed-----" << std::endl;

}
