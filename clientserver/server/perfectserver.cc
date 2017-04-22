#include "perfectserver.h"
#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "messagehandler.h"

#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

int main(int argc, char const *argv[]) {
  if (argc != 2) {
		cerr << "Usage: myserver port-number" << endl;
		exit(1);
	}

	int port = -1;
	try {
		port = stoi(argv[1]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}

	Server server(port);
	MessageHandler msg_hand = MessageHandler();

	if (!server.isReady()) {
		cerr << "Server initialization error." << endl;
		exit(1);
	}

	while (true) {
		Message msg;
		auto conn = server.waitForActivity();
		if (conn != nullptr) {
			try {
				Message msg = msg_hand.getMessage(conn);

				msg_hand.sendMessage(conn);
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
}
