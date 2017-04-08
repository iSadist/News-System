#ifndef DATABASE_H
#define DATABASE_H

#include "server.h"
#include "article.h"
#include "newsgroup.h"
#include <vector>

class Database{

public:
	virtual std::vector<Newsgroup> list_NG() = 0;
	virtual bool create_NG(std::string title) = 0;
	virtual bool delete_NG(std::string title) = 0;
	virtual std::vector<Article> list_ART() = 0;
	virtual bool create_ART(std::string title) = 0;
	virtual bool delete_ART(std::string title) = 0;
	virtual Article get_ART(std::string title) = 0;
};

#endif