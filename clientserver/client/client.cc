#include "client.h"
#include <iostream>

Client::Client() {

}

Client::~Client() {

}

void Client::changeToNewsgroup(int newsgroupId) {

}

void Client::listNewsgroups() {

}

void Client::createNewsgroup(std::string title) {

}

void Client::deleteNewsgroup(std::string title) {

}

void Client::listArticles() {

}

void Client::readArticle() {

}

void Client::writeArticle() {

}

void Client::deleteArticle() {

}

void Client::switchServer() {

}

void print_main_menu() {
  std::cout << "Main Menu" << '\n'
            << "----------------------------" << '\n'
            << "1. List all Newsgroups" << '\n'
            << "2. Create a Newsgroup" << '\n'
            << "3. Delete a Newsgroup" << '\n'
            << "4. Go to a Newsgroup" << '\n';
}

void print_newsgroup_menu() {
  std::cout << "/* message */" << '\n';
}

int main(int argc, char const *argv[]) {
  Client client();

  std::cout << "Welcome to Usenet News!" << '\n';

  print_main_menu();

  int main_choice;

  std::cin >> main_choice;
  std::cout << main_choice << '\n';



  return 0;
}
