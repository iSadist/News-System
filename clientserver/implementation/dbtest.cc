#include "memdatabase.h"

#include <memory>
#include <iostream>
#include <string>

using namespace std;

Memdatabase db;

int main(int argc, char* argv[]){
	db = Memdatabase();

	db.list_NG();
	db.delete_ART(44, 22);
	db.get_ART(22, 44);
	db.list_ART(3);

	db.create_NG("Good News Group");
	db.list_NG();
	db.create_ART(1, "Today", "Marcel", "Sunday afternoon is pretty chill");
	db.list_ART(1);
	db.get_ART(1, 1);
	db.delete_ART(1, 1);
	std::cout << "No crashes while testing memory database, newsgroups and article classes" << std::endl;

}
