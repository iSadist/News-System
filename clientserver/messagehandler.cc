#include "messagehandler.h"

using namespace std;


MessageHandler::MessageHandler() {
}

MessageHandler::~MessageHandler() {
}

//Server -> Client

int MessageHandler::readNumber(const shared_ptr<Connection>& conn) {
	unsigned char byte1 = conn->read();
	unsigned char byte2 = conn->read();
	unsigned char byte3 = conn->read();
	unsigned char byte4 = conn->read();
	return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

int MessageHandler::readCommand(const shared_ptr<Connection>& conn) {
	unsigned char byte1 = conn->read();
	return byte1;
}

void MessageHandler::writeString(const shared_ptr<Connection>& conn, const string& s) {
	for (char c : s) {
		conn->write(c);
	}
	conn->write('$');
}

string MessageHandler::readString(const shared_ptr<Connection>& conn, int char_count) {
	string s;
	char ch;
	while (char_count > 0) {
		ch = conn->read();
		s += ch;
		char_count--;
	}
	return s;
}

Message MessageHandler::getMessage(const shared_ptr<Connection>& conn){
	Message msg;
	switch (readCommand(conn)) {
		case Protocol::COM_LIST_NG:
			if (readCommand(conn) == Protocol::COM_END){
				msg.type = Protocol::COM_LIST_NG;
				return msg;
			}
			break;
		case Protocol::COM_CREATE_NG:
			msg.type = Protocol::COM_CREATE_NG;
			if (readCommand(conn) == Protocol::PAR_STRING){
				int char_count = readNumber(conn);
				string ng_name = readString(conn, char_count);
				if (readCommand(conn) == Protocol::COM_END){
					msg.contents.push_back(ng_name);
					return msg;
				}
			}
			break;
		case Protocol::COM_DELETE_NG:
			break;
		case Protocol::COM_LIST_ART:
			break;
		case Protocol::COM_CREATE_ART:
			break;
		case Protocol::COM_DELETE_ART:
			break;
		case Protocol::COM_GET_ART:
			break;
		case Protocol::COM_END:
			break;
	}
	return msg;
}

void MessageHandler::sendMessage(const shared_ptr<Connection>& conn){

}

//Client -> Server

void MessageHandler::writeNumber(const Connection& conn, int value) {
	conn.write((value >> 24) & 0xFF);
	conn.write((value >> 16) & 0xFF);
	conn.write((value >> 8)	 & 0xFF);
	conn.write(value & 0xFF);
}

string MessageHandler::readString(const Connection& conn) {
	string s;
	char ch;
	while ((ch = conn.read()) != '$') {
		s += ch;
	}
	return s;
}

vector<pair<int, string>> MessageHandler::clientListNewsgroups(const Connection& conn) const {
	//Send request to server
	string request = ""; //TODO
	writeString(request);

	//Receive result from server
	vector<pair<int,string>> newsgroups;


	string result =	readString(conn); //



	for() {
		pair<int,string> group = make_pair(id,title);
		newsgroups.push_back(group);
	}

	return newsgroups;
}

int MessageHandler::clientCreateNewsgroup(const Connection& conn, string title) {
	string request = ""; //TODO
	writeString(request);

}

int MessageHandler::clientDeleteNewsgroup(const Connection& conn, int ng_id) {
	string request = ""; //TODO
	writeString(request);
}

vector<pair<int, string>> MessageHandler::clientListArticles(const Connection& conn, int ng_id) const {
	string request = ""; //TODO
	writeString(request);
}

int MessageHandler::clientCreateArticle(const Connection& conn, ng_id, string title, string author, string text) {
	string request = ""; //TODO
	writeString(request);
}

int MessageHandler::clientDeleteArticle(const Connection& conn, ng_id, art_id) {
	string request = ""; //TODO
	writeString(request);
}

Article MessageHandler::clientGetArticle(const Connection& conn, ng_id, art_id) const {
	string request = ""; //TODO
	writeString(request);
}
