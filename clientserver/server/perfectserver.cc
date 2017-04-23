#include "perfectserver.h"
#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "messagehandler.h"
#include "sqldatabase.h"
#include "memdatabase.h"

#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

PerfectServer::PerfectServer(int port) : server(port){
	msg_hand = MessageHandler();
	db_sql = Sqldatabase();
	db_mem = Memdatabase();
	if (!server.isReady()) {
		cerr << "Server initialization error." << endl;
		exit(1);
	}
}

PerfectServer::~PerfectServer(){}

Message PerfectServer::handle_message(Message& message){
	Message resp;
	switch (message.type) {
		case Protocol::COM_LIST_NG:
			// db_sql.list_NG();
			break;
		case Protocol::COM_CREATE_NG:

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
	}
	return resp;
}


void PerfectServer::connection_control(){
	auto conn = server.waitForActivity();
	if (conn != nullptr) {
		try {
			Message msg = msg_hand.getMessage(*conn);
			Message resp_msg = handle_message(msg);
			// msg_hand.sendMessage(*conn,resp_msg);
		} catch (ConnectionClosedException&) {
			server.deregisterConnection(conn);
			cout << "Client closed connection" << endl;
		}
	} else {
		conn = make_shared<Connection>();
		server.registerConnection(conn);
		cout << "New client connects" << endl;
	}
}

int main(int argc, char const *argv[]) {
  	if (argc != 2) {
		cerr << "Usage: myserver port-number" << endl;
		exit(1);
	}

	int port = -1;
	try {
		port = stoi(argv[1]);
	} catch (exception& e) {
		cerr << "Invalid port number. " << e.what() << endl;
		exit(1);
	}

	PerfectServer myServerClient(port);

	while (true){
		myServerClient.connection_control();
	}
}
