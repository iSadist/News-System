#ifndef MESSAGE_H
#define MESSAGE_H

#include <vector>
#include <string>

/*Interface class to Memdatabase and Sqldatabase*/

class Message{

public:
	int type;
	std::vector<std::string> contents;

};

#endif
