#ifndef PERFECT_SERVER_H
#define PERFECT_SERVER_H

#include "server.h"
#include "messagehandler.h"
#include "sqldatabase.h"
#include "memdatabase.h"
#include <memory>

class PerfectServer{
private:
	Server server;
	MessageHandler msg_hand;
	#ifdef SQL
	Sqldatabase db;
	#else
	Memdatabase db;
	#endif
	void handle_message(shared_ptr<Connection>& conn, Message& message);
	// void handle_LIST_NG(Message& message);

public:
	PerfectServer(int port);
	virtual ~PerfectServer ();
	void connection_control();

};

#endif