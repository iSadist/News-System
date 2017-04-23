#include "messagehandler.h"

using namespace std;


MessageHandler::MessageHandler() {
}

MessageHandler::~MessageHandler() {
}

//Server -> Client

int MessageHandler::readCommand(const Connection& conn) {
	unsigned char byte1 = conn.read();
	return byte1;
}

void MessageHandler::writeCommand(const Connection& conn, unsigned int byte) {
	conn.write(byte);
}

int MessageHandler::readNumber(const Connection& conn) {
	unsigned char byte1 = conn.read();
	unsigned char byte2 = conn.read();
	unsigned char byte3 = conn.read();
	unsigned char byte4 = conn.read();
	return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

void MessageHandler::writeNumber(const Connection& conn, int value) {
	conn.write(Protocol::PAR_NUM);

	conn.write((value >> 24) & 0xFF);
	conn.write((value >> 16) & 0xFF);
	conn.write((value >> 8)	 & 0xFF);
	conn.write(value & 0xFF);
}

string MessageHandler::readString(const Connection& conn, int char_count) {
	string s;
	char ch;
	while (char_count > 0) {
		ch = conn.read();
		s += ch;
		char_count--;
	}
	return s;
}

void MessageHandler::writeString(const Connection& conn, string& s) {
	conn.write(Protocol::PAR_STRING);
	int value = s.size();

	conn.write((value >> 24) & 0xFF);
	conn.write((value >> 16) & 0xFF);
	conn.write((value >> 8)	 & 0xFF);
	conn.write(value & 0xFF);

	for (char c : s) {
		conn.write(c);
	}
}

Message MessageHandler::getMessage(const Connection& conn){
	Message msg;
	switch (readCommand(conn)) {
		case Protocol::COM_LIST_NG:
			if (readCommand(conn) == Protocol::COM_END){
				msg.type = Protocol::COM_LIST_NG;
			}
			break;
		case Protocol::COM_CREATE_NG:
			if (readCommand(conn) == Protocol::PAR_STRING){
				int char_count = readNumber(conn);
				string ng_name = readString(conn, char_count);
				if (readCommand(conn) == Protocol::COM_END){
					msg.type = Protocol::COM_CREATE_NG;
					msg.contents.push_back(ng_name);
				}
			}
			break;
		case Protocol::COM_DELETE_NG:
			if (readCommand(conn) == Protocol::PAR_NUM){
				int ng_id = readNumber(conn);
				if (readCommand(conn) == Protocol::COM_END){
					msg.type = Protocol::COM_DELETE_NG;
					msg.contents.push_back(to_string(ng_id));
				}
			}
			break;
		case Protocol::COM_LIST_ART:
			if (readCommand(conn) == Protocol::PAR_NUM){
				int ng_id = readNumber(conn);
				if (readCommand(conn) == Protocol::COM_END){
					msg.type = Protocol::COM_LIST_ART;
					msg.contents.push_back(to_string(ng_id));
				}
			}
			break;
		case Protocol::COM_CREATE_ART:
			if (readCommand(conn) == Protocol::PAR_NUM){
				int ng_id = readNumber(conn);
				msg.contents.push_back(to_string(ng_id));
				int char_count;
				string art_name;
				bool pass = true;
				for (int k = 0; k < 3; k++){
					if (readCommand(conn) == Protocol::PAR_STRING){
						char_count = readNumber(conn);
						art_name = readString(conn, char_count);
						msg.contents.push_back(art_name);
					}else{
						pass = false;
						break;
					}
				}
				if (pass && readCommand(conn) == Protocol::COM_END)
					msg.type = Protocol::COM_CREATE_ART;
			}
			break;
		case Protocol::COM_DELETE_ART:
			if (readCommand(conn) == Protocol::PAR_NUM){
				int ng_id = readNumber(conn);
				if (readCommand(conn) == Protocol::PAR_NUM){
					int art_id = readNumber(conn);
					if (readCommand(conn) == Protocol::COM_END){
						msg.type = Protocol::COM_DELETE_ART;
						msg.contents.push_back(to_string(ng_id));
						msg.contents.push_back(to_string(art_id));
					}
				}
			}
			break;
		case Protocol::COM_GET_ART:
			if (readCommand(conn) == Protocol::PAR_NUM){
				int ng_id = readNumber(conn);
				if (readCommand(conn) == Protocol::PAR_NUM){
					int art_id = readNumber(conn);
					if (readCommand(conn) == Protocol::COM_END){
						msg.type = Protocol::COM_GET_ART;
						msg.contents.push_back(to_string(ng_id));
						msg.contents.push_back(to_string(art_id));
					}
				}
			}
			break;
	}
	return msg;
}

//Client -> Server

vector<pair<int, string>> MessageHandler::clientListNewsgroups(const Connection& conn) {
	//Send request to server
	writeCommand(conn, Protocol::COM_LIST_NG);
	writeCommand(conn, Protocol::COM_END);

	//Receive result from server
	vector<pair<int,string>> newsgroups;

	if (readCommand(conn) == Protocol::ANS_LIST_NG && readCommand(conn) == Protocol::PAR_NUM) {
		int list_size = readNumber(conn);

		for (size_t i = 0; i < list_size; i++) {
			int number;
			string title;
			int command = readCommand(conn);

			if (command != Protocol::ANS_END) {
				if (command == Protocol::PAR_NUM) {
					number = readNumber(conn);
					command = readCommand(conn);
				}
				if (command == Protocol::PAR_STRING) {
					int size = readNumber(conn);
					title = readString(conn, size);
				}
			}

			pair<int,string> group = make_pair(number, title);
			newsgroups.push_back(group);
		}

		if (readCommand(conn) != Protocol::ANS_END) {
			return vector<pair<int,string>>();
		}
	}

	if (readCommand(conn) != Protocol::ANS_END) {
		std::cout << "Problem with message... terminating" << '\n';
		exit(1);
	}

	return newsgroups;
}

void MessageHandler::clientCreateNewsgroup(const Connection& conn, string title) {
	//Send request to server
	writeCommand(conn, Protocol::COM_CREATE_NG);
	writeString(conn, title);
	writeCommand(conn, Protocol::COM_END);

	//Receive result from server
	if (readCommand(conn) == Protocol::ANS_CREATE_NG) {
		int result = readCommand(conn);
		if(result == Protocol::ANS_ACK) {
	    std::cout << "Newsgroup created successfully!" << '\n';
	  } else if (result == Protocol::ANS_NAK) {
			if (readCommand(conn) == Protocol::ERR_NG_ALREADY_EXISTS) {
				std::cout << "Failed... A Newsgroup with that title already exists!" << '\n';
			}
	  } else {
	    std::cout << "Failed to created Newsgroup " << title << '\n';
	  }
	} else {
		exit(1);
	}
	if (readCommand(conn) != Protocol::ANS_END) {
		std::cout << "Problem with message... terminating" << '\n';
		exit(1);
	}
}

void MessageHandler::clientDeleteNewsgroup(const Connection& conn, int ng_id) {
	//Send request to server
	writeCommand(conn, Protocol::COM_DELETE_NG);
	writeNumber(conn, ng_id);
	writeCommand(conn, Protocol::COM_END);

	//Receive result from server
	if (readCommand(conn) == Protocol::ANS_DELETE_NG) {
		int result = readCommand(conn);
		if(result == Protocol::ANS_ACK) {
	    std::cout << "Newsgroup deleted successfully!" << '\n';
	  } else if (result == Protocol::ANS_NAK) {
			if (readCommand(conn) == Protocol::ERR_NG_ALREADY_EXISTS) {
				std::cout << "Failed... No Newsgroup with that ID exists!" << '\n';
			}
	  } else {
	    std::cout << "Failed to delete Newsgroup Nr." << ng_id << '\n';
	  }
	} else {
		exit(1);
	}
	if (readCommand(conn) != Protocol::ANS_END) {
		std::cout << "Problem with message... terminating" << '\n';
		exit(1);
	}
}

vector<pair<int, string>> MessageHandler::clientListArticles(const Connection& conn, int ng_id){
	//Send request to server
	writeCommand(conn, Protocol::COM_LIST_ART);
	writeNumber(conn, ng_id);
	writeCommand(conn, Protocol::COM_END);

	//Receive result from server

	vector<pair<int,string>> articles;

	int command = readCommand(conn);

	if (command == Protocol::ANS_LIST_ART) {
		while (command != Protocol::ANS_END) {
			command = readCommand(conn);
			if (command == Protocol::ANS_ACK) {
				command = readCommand(conn);
				if (command == Protocol::PAR_NUM) {
					int size = readNumber(conn);
					for (size_t i = 0; i < size; i++) {
						int number;
						string title;

						if (readCommand(conn) == Protocol::PAR_NUM) {
							number = readNumber(conn);
						}

						if (readCommand(conn) == Protocol::PAR_STRING) {
							int title_size = readNumber(conn);
							title = readString(conn, title_size);
						}

						articles.push_back(make_pair(number, title));
					}
				}
			} else {
				command = readCommand(conn);
				if (command == Protocol::ERR_NG_DOES_NOT_EXIST) {
					std::cout << "Failed... No Newsgroup with that ID!" << '\n';
					return vector<pair<int,string>>();
				} else {
					std::cout << "Unknown error. Terminating..." << '\n';
					return vector<pair<int,string>>();
				}
			}
		}
	}

	return articles;
}

void MessageHandler::clientCreateArticle(const Connection& conn, int ng_id, string title, string author, string text) {
	//Send request to server
	writeCommand(conn, Protocol::COM_CREATE_ART);
	writeNumber(conn, ng_id);
	writeString(conn, title);
	writeString(conn, author);
	writeString(conn, text);
	writeCommand(conn, Protocol::COM_END);

	//Receive result from server
	if (readCommand(conn) == Protocol::ANS_CREATE_ART) {
		int result = readCommand(conn);
		if(result == Protocol::ANS_ACK) {
	    std::cout << "Article created successfully!" << '\n';
	  } else if (result == Protocol::ANS_NAK) {
			if (readCommand(conn) == Protocol::ERR_NG_DOES_NOT_EXIST) {
				std::cout << "Failed... No Newsgroup with that ID exists!" << '\n';
			}
	  } else {
	    std::cout << "Failed to create Article" << '\n';
	  }
	} else {
		exit(1);
	}

	if (readCommand(conn) != Protocol::ANS_END) {
		std::cout << "Problem with message... terminating" << '\n';
		exit(1);
	}
}

void MessageHandler::clientDeleteArticle(const Connection& conn, int ng_id, int art_id) {
	//Send request to server
	writeCommand(conn, Protocol::COM_DELETE_ART);
	writeNumber(conn, ng_id);
	writeNumber(conn, art_id);
	writeCommand(conn, Protocol::COM_END);

	//Receive result from server
	if (readCommand(conn) == Protocol::ANS_DELETE_ART) {
		int result = readCommand(conn);
		if(result == Protocol::ANS_ACK) {
	    std::cout << "Article deleted successfully!" << '\n';
	  } else if (result == Protocol::ANS_NAK) {
			result = readCommand(conn);
			if (result == Protocol::ERR_NG_DOES_NOT_EXIST) {
				std::cout << "Failed... No Newsgroup with that ID exists!" << '\n';
			} else if (result == Protocol::ERR_ART_DOES_NOT_EXIST){
				std::cout << "Failed... No Article with that ID exists!" << '\n';
			}
	  } else {
	    std::cout << "Failed to delete Article" << '\n';
	  }
	} else {
		exit(1);
	}

	if (readCommand(conn) != Protocol::ANS_END) {
		std::cout << "Problem with message... terminating" << '\n';
		exit(1);
	}
}

Article MessageHandler::clientGetArticle(const Connection& conn, int ng_id, int art_id){
	//Send request to server
	writeCommand(conn, Protocol::COM_GET_ART);
	writeNumber(conn, ng_id);
	writeNumber(conn, art_id);
	writeCommand(conn, Protocol::COM_END);

	//Receive result from server

	int id;
	string title;
	string author;
	string content;

	if (readCommand(conn) == Protocol::ANS_GET_ART) {
		id = 0;
		int command = readCommand(conn);
		if (command == Protocol::ANS_ACK) {
			int size = readNumber(conn);
			title = readString(conn, size);
			size = readNumber(conn);
			author = readString(conn, size);
			size = readNumber(conn);
			content = readString(conn, size);

		} else if (command == Protocol::ANS_NAK) {
			command = readCommand(conn);
			if (command == Protocol::ERR_NG_DOES_NOT_EXIST) {
				std::cout << "Failed... No Newsgroup with that ID exists!" << '\n';
			} else if(command == Protocol::ERR_ART_DOES_NOT_EXIST) {
				std::cout << "Failed... No Article with that ID exists!" << '\n';
			}
		}
		if (readCommand(conn) == Protocol::ANS_END) {
				std::cout << "Problem with message... terminating" << '\n';
				return Article(id, title, author, content);
		}
	}
	id = -1;
	return Article(id, title, author, content);
}



void MessageHandler::server_send_ng_list(const Connection& conn, vector<Newsgroup> ng_list){
	writeCommand(conn, Protocol::ANS_LIST_NG);
	writeNumber(conn, ng_list.size());
	for (Newsgroup ng : ng_list){
		writeNumber(conn, ng.getId());
		string ng_id = ng.getTitle();
		writeString(conn, ng_id);
	}
	writeCommand(conn, Protocol::ANS_END);
}

void MessageHandler::server_send_ng_create_response(const Connection& conn, bool success){
	writeCommand(conn, Protocol::ANS_CREATE_NG);
	if (success){
		writeCommand(conn, Protocol::ANS_ACK);
	} else {
		writeCommand(conn, Protocol::ANS_NAK);
		writeCommand(conn, Protocol::ERR_NG_ALREADY_EXISTS);
	}
	writeCommand(conn, Protocol::ANS_END);
}

void MessageHandler::server_send_ng_delete_response(const Connection& conn, bool success){
	writeCommand(conn, Protocol::ANS_DELETE_NG);
	if (success){
		writeCommand(conn, Protocol::ANS_ACK);
	} else {
		writeCommand(conn, Protocol::ANS_NAK);
		writeCommand(conn, Protocol::ERR_NG_DOES_NOT_EXIST);
	}
	writeCommand(conn, Protocol::ANS_END);
}

void MessageHandler::server_send_ng_art_list(const Connection& conn, vector<Article> art_list){
	writeCommand(conn, Protocol::ANS_LIST_ART);
	if (art_list.size() == 1 && art_list[0].getId() == 0){
		writeCommand(conn, Protocol::ANS_NAK);
		writeCommand(conn, Protocol::ERR_NG_DOES_NOT_EXIST);
	} else {
		writeCommand(conn, Protocol::ANS_ACK);
		writeNumber(conn, art_list.size());
		for (Article art : art_list){
			writeNumber(conn, art.getId());
			string art_id = art.getTitle();
			writeString(conn, art_id);
		}
	}
	writeCommand(conn, Protocol::ANS_END);
}

void MessageHandler::server_send_art_create_response(const Connection& conn, bool success){
	writeCommand(conn, Protocol::ANS_CREATE_ART);
	if (success){
		writeCommand(conn, Protocol::ANS_ACK);
	} else {
		writeCommand(conn, Protocol::ANS_NAK);
		writeCommand(conn, Protocol::ERR_NG_DOES_NOT_EXIST);
	}
	writeCommand(conn, Protocol::ANS_END);
}

void MessageHandler::server_send_art_delete_response(const Connection& conn, int success){
	writeCommand(conn, Protocol::ANS_DELETE_ART);
	if (success == 1) {
		writeCommand(conn, Protocol::ANS_ACK);
	} else if (success == 0) {
		writeCommand(conn, Protocol::ANS_NAK);
		writeCommand(conn, Protocol::ERR_NG_DOES_NOT_EXIST);
	} else if (success == -1) {
		writeCommand(conn, Protocol::ANS_NAK);
		writeCommand(conn, Protocol::ERR_ART_DOES_NOT_EXIST);
	}
	writeCommand(conn, Protocol::ANS_END);
}

void MessageHandler::server_send_article(const Connection& conn, Article art){
	writeCommand(conn, Protocol::ANS_GET_ART);
	if (art.getId() == 0) {
		writeCommand(conn, Protocol::ANS_NAK);
		writeCommand(conn, Protocol::ERR_NG_DOES_NOT_EXIST);
	} else if (art.getId() == -1) {
		writeCommand(conn, Protocol::ANS_NAK);
		writeCommand(conn, Protocol::ERR_ART_DOES_NOT_EXIST);
	} else {
		writeCommand(conn, Protocol::ANS_ACK);
		string title = art.getTitle();
		string author = art.getAuthor();
		string text = art.getContent();
		writeString(conn, title);
		writeString(conn, author);
		writeString(conn, text);
	}
	writeCommand(conn, Protocol::ANS_END);
}