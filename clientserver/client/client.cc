#include "client.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

Client::Client(const char* host, int port) {
  // conn = new Connection(host, port);
}

Client::Client() {
}

Client::~Client() {
  // delete conn;
}

int Client::scanInputInteger() {
  int value;
  bool ok = false;

  while(!ok) {
    try {
      std::cin >> value;
    } catch (exception& e) {
      cerr << "Wrong input. " << e.what() << endl;
    }
    ok = true;
  }
  return value;
}

void Client::changeToNewsgroup() {
  std::cout << "Newsgroup ID: ";
  int newsgroupId = scanInputInteger();
  newsgroup_options(newsgroupId);
}

void Client::newsgroup_options(int newsgroup_id) {
  print_newsgroup_menu(newsgroup_id);
  while(1) {
    int choice = scanInputInteger();

    switch (choice) {
      case 1:
        listArticles(newsgroup_id);
        break;
      case 2:

        break;
      case 3:

        break;
      case 4:

        break;
      case 5:
      default:
        std::cout << "Returning..." << '\n';
        return;
    }
  }
}

void Client::listNewsgroups() {
  std::cout << "Available Newsgroups" << '\n';
  std::cout << "--------------------" << '\n';
}

void Client::createNewsgroup() {
  std::cout << "Title: ";
  std::string title;
  std::cin >> title;
}

void Client::deleteNewsgroup() {
  std::cout << "Title: ";
  std::string title;
  std::cin >> title;
}

void Client::listArticles(int newsgroup_id) {
  std::cout << "Listing articles in newsgroup " << newsgroup_id << '\n';
}

void Client::readArticle() {

}

void Client::writeArticle() {

}

void Client::deleteArticle() {

}

void Client::switchServer() {

}

void Client::print_newsgroup_menu(int newsgroup_id) {
  std::cout << "You are inside Newsgroup Nr." << newsgroup_id << '\n'
            << "----------------------------" << '\n'
            << "1. List all Articles" << '\n'
            << "2. Write an Article" << '\n'
            << "3. Read an Article" << '\n'
            << "4. Delete an Article" << '\n'
            << "5. Back" << '\n'
            << "Enter: ";
}

void print_main_menu() {
  std::cout << "Main Menu" << '\n'
            << "----------------------------" << '\n'
            << "1. List all Newsgroups" << '\n'
            << "2. Create a Newsgroup" << '\n'
            << "3. Delete a Newsgroup" << '\n'
            << "4. Go to a Newsgroup" << '\n'
            << "5. Quit" << '\n'
            << "Enter: ";
}


int main(int argc, char const *argv[]) {
  std::cout << argc << '\n';
  if (argc != 3) {
    cerr << "Usage: myclient host-name port-number" << endl;
    exit(1);
  }

  int port = -1;
	try {
		port = stoi(argv[2]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}

  Client *client = new Client(argv[1], port);

  std::cout << "Welcome to Usenet News!" << '\n';
  int main_choice;

  while (1) {
    print_main_menu();

    std::cin >> main_choice;
    std::cout << main_choice << '\n';

    switch (main_choice) {
      case 1:
        client->listNewsgroups();
        break;
      case 2:
        client->createNewsgroup();
        break;
      case 3:
        client->deleteNewsgroup();
        break;
      case 4:
        client->changeToNewsgroup();
        break;
      case 5:
        std::cout << "Goodbye!" << '\n';
        delete client;
        exit(0);
      default:
        std::cout << "Not a valid choice" << '\n';
    }
  }

  delete client;
  exit(1);
}
