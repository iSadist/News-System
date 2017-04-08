#ifndef DATABASE_H
#define DATABASE_H

#include "server.h"
#include "article.h"
#include "newsgroup.h"
#include <vector>

/*Interface class to Memdatabase and Sqldatabase*/

class Database{

public:
	virtual std::vector<Newsgroup> list_NG() = 0;
	virtual bool create_NG(std::string title) = 0;
	virtual bool delete_NG(std::string title) = 0;
	virtual std::vector<Article> list_ART(std::string ng_title) = 0;
	virtual bool create_ART(std::string title, std::string text) = 0;
	virtual bool delete_ART(std::string title) = 0;
	virtual Article get_ART(std::string title) = 0;
};

#endif