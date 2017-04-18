#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include "database.h"
#include <sqlite3.h>

class Sqldatabase : public Database {

private:
	sqlite3 *db;
	int article_counter;
	bool prepareStatement(std::string sql);

public:
	Sqldatabase();
	virtual ~Sqldatabase();

	bool open_connection(const std::string& filepath);
	void close_connection();

	std::vector<Newsgroup> list_NG();
	bool create_NG(std::string title);
	bool delete_NG(int ng_id);
	std::vector<Article> list_ART(int ng_id);
	bool create_ART(int ng_id, std::string title, std::string author, std::string text);
	bool delete_ART(int ng_id, int art_id);
	Article get_ART(int ng_id, int art_id);
};

#endif
