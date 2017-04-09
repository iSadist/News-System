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
	bool delete_NG(int ng_id);
	std::vector<Article> list_ART(int ng_id);
	bool create_ART(int ng_id, std::string title, std::string author, std::string text);
	bool delete_ART(int ng_id, int art_id);
	Article get_ART(int ng_id, int art_id);

private:
	std::vector<Newsgroup> newsgroups;
	int ng_counter;
	int art_counter;
	__gnu_cxx::__normal_iterator<Newsgroup*, std::vector<Newsgroup, std::allocator<Newsgroup> > >
	get_NG_iterator(int ng_id);
};

#endif