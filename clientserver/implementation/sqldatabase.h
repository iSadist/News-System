#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include "database.h"
#include <sqlite3.h>

class Sqldatabase : public Database {

private:
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	const char* data = "Callback function called";

public:
	Sqldatabase();
	virtual ~Sqldatabase();

	void open_connection();
	void close_connection();

	bool create_NG(std::string title);
	bool delete_NG(int ng_id);
	std::vector<Article> list_ART(int ng_id);
	bool create_ART(int ng_id, std::string title, std::string author, std::string text);
	bool delete_ART(int ng_id, int art_id);
	Article get_ART(int ng_id, int art_id);
};

#endif
