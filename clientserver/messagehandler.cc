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

void MessageHandler::writeString(const shared_ptr<Connection>& conn, const string& s) {
	for (char c : s) {
		conn->write(c);
	}
	conn->write('$');
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
