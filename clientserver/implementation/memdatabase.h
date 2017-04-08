#ifndef MEMDATABASE_H
#define MEMDATABASE_H

#include "database.h"

/*Implementation of Database.h interface*/

class Memdatabase : Database{

public:
	Memdatabase();
	virtual ~Memdatabase();
	std::vector<Newsgroup> list_NG();
	bool create_NG(std::string title);
	bool delete_NG(std::string title);
	std::vector<Article> list_ART(std::string ng_title);
	bool create_ART(std::string title, std::string text);
	bool delete_ART(std::string title);
	Article get_ART(std::string title);

private:
	std::vector<Newsgroup> newsgroups;
};

#endif