#ifndef PERFECT_SERVER_H
#define PERFECT_SERVER_H

#include "server.h"
#include "messagehandler.h"
#include "sqldatabase.h"
#include "memdatabase.h"

class PerfectServer{
private:
	Server server;
	MessageHandler msg_hand;
	Sqldatabase db_sql;
	Memdatabase db_mem;
	Message handle_message(Message& message);

public:
	PerfectServer(int port);
	virtual ~PerfectServer ();
	void connection_control();

};

#endif