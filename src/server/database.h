#ifndef DATABASE_H
#define DATABASE_H

#include "server.h"
#include "article.h"
#include "newsgroup.h"
#include <vector>

/*Interface class to Memdatabase and Sqldatabase*/

class Database{

public:
	/*Returns a vector containing all newsgroups*/
	virtual std::vector<Newsgroup> list_NG() = 0;

	/*creates a newsgroup in the database,
	returns true upon success*/
	virtual bool create_NG(std::string title) = 0;

	/*deletes the specified newsgroup from the database,
	returns true if succesfull,*/
	virtual bool delete_NG(int ng_id) = 0;

	/*returns a vector containing all the article objects
	in the specified newsgroup*/
	virtual std::vector<Article> list_ART(int ng_id) = 0;

	/*creates an article in the specified newsgroup
	from the given newsgroup id and article info
	returns true on success*/
	virtual bool create_ART(int ng_id, std::string title, std::string author, std::string text) = 0;

	/*deletes the specified article from the database
	returns 1 for success, 0 for ng not found and -1 for art not found*/
	virtual int delete_ART(int ng_id, int art_id) = 0;

	/*retrieves the specified article from the database
	article id should be 0 for ng not found and -1 for art not found*/
	virtual Article get_ART(int ng_id, int art_id) = 0;
};

#endif
