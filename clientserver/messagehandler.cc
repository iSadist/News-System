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

void MessageHandler::writeCommand(const Connection& conn, unsigned char byte) {
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

	writeNumber(conn, s.size());
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

void MessageHandler::sendMessage(const Connection& conn){

}

//Client -> Server

vector<pair<int, string>> MessageHandler::clientListNewsgroups(const Connection& conn) {
	//Send request to server
	writeCommand(conn, Protocol::COM_LIST_NG);
	writeCommand(conn, Protocol::COM_END);

	//Receive result from server
	vector<pair<int,string>> newsgroups;

	// for(int k=0; k<1; k++) {
	// 	pair<int,string> group = make_pair(id,title);
	// 	newsgroups.push_back(group);
	// }

	return newsgroups;
}

int MessageHandler::clientCreateNewsgroup(const Connection& conn, string title) {
	//Send request to server
	writeCommand(conn, Protocol::COM_CREATE_NG);
	writeString(conn, title);
	writeCommand(conn, Protocol::COM_END);

	//Receive result from server


}

int MessageHandler::clientDeleteNewsgroup(const Connection& conn, int ng_id) {
	//Send request to server
	writeCommand(conn, Protocol::COM_DELETE_NG);
	writeNumber(conn, ng_id);
	writeCommand(conn, Protocol::COM_END);

	//Receive result from server

}

vector<pair<int, string>> MessageHandler::clientListArticles(const Connection& conn, int ng_id){
	//Send request to server
	writeCommand(conn, Protocol::ANS_LIST_ART);
	writeNumber(conn, ng_id);
	writeCommand(conn, Protocol::COM_END);

	//Receive result from server
}

int MessageHandler::clientCreateArticle(const Connection& conn, int ng_id, string title, string author, string text) {
	//Send request to server
	writeCommand(conn, Protocol::COM_CREATE_ART);
	// writeNumber(conn, ng_id)

	//Receive result from server
}

int MessageHandler::clientDeleteArticle(const Connection& conn, int ng_id, int art_id) {
	//Send request to server
	//Receive result from server
}

Article MessageHandler::clientGetArticle(const Connection& conn, int ng_id, int art_id){
	//Send request to server
	//Receive result from server
}
