#include "client.h"
#include "../connection.h"
#include "../messagehandler.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

Client::Client(const char* host, int port) {
  conn = new Connection(host, port);
  message_handler = new MessageHandler(conn);
}

Client::Client() {}

Client::~Client() {
  delete conn;
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

std::string Client::scanInputString() {
  std::string text;
  std::cin >> text;
  return text;
}

void Client::changeToNewsgroup() {
  std::cout << "Newsgroup ID: ";
  int newsgroupId = scanInputInteger();
  newsgroup_options(newsgroupId);
}

void Client::newsgroup_options(int newsgroup_id) {
  print_newsgroup_menu(newsgroup_id);
  while(1) {
    std::cout << "Enter: ";
    int choice = scanInputInteger();

    switch (choice) {
      case 1:
        listArticles(newsgroup_id);
        break;
      case 2:
        writeArticle(newsgroup_id);
        break;
      case 3:
        readArticle(newsgroup_id);
        break;
      case 4:
        deleteArticle(newsgroup_id);
        break;
      case 5:
        std::cout << "Returning..." << '\n';
        return;
      case 6:
        print_newsgroup_menu(newsgroup_id);
        break;
      default:
        std::cout << "Not a valid choice... Returning..." << '\n';
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
  std::string title = scanInputString();


}

void Client::deleteNewsgroup() {
  std::cout << "Title: ";
  std::string title = scanInputString();


}

void Client::listArticles(int newsgroup_id) {
  std::cout << "Listing articles in Newsgroup Nr." << newsgroup_id << '\n';




  std::cout << "End of list..." << '\n';
}

void Client::readArticle(int newsgroup_id) {
  std::cout << "Article ID: ";
  int article_id = scanInputInteger();


}

void Client::writeArticle(int newsgroup_id) {
  std::cout << "Title: ";
  std::string title = scanInputString();
  std::cout << '\n';
  std::cout << "Article text: ";
  std::string text = scanInputString();

  std::cout << '\n';
  std::cout << "Article:" << title << '\n';
  std::cout << text << '\n';
}

void Client::deleteArticle(int newsgroup_id) {
  std::cout << "Article ID: ";
  int article_id = scanInputInteger();


}

void Client::print_newsgroup_menu(int newsgroup_id) {
  std::cout << "You are inside Newsgroup Nr." << newsgroup_id << '\n'
            << "----------------------------" << '\n'
            << "1. List all Articles" << '\n'
            << "2. Write an Article" << '\n'
            << "3. Read an Article" << '\n'
            << "4. Delete an Article" << '\n'
            << "5. Back" << '\n'
            << "6. Print the menu" << '\n';
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

  Client client(argv[1], port);

  std::cout << "Welcome to Usenet News!" << '\n';
  int main_choice;

  while (1) {
    print_main_menu();

    main_choice = client->scanInputInteger();

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
  exit(1);
}
