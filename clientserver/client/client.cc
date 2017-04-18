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

void Client::listArticles(Newsgroup group) {

}

void Client::readArticle(Newsgroup group, Article article) {

}

void Client::writeArticle(Newsgroup group, std::string text) {

}

void Client::deleteArticle(Newsgroup group, Article article) {

}

void Client::switchServer() {

}

int main(int argc, char const *argv[]) {
  std::cout << "Hello World" << '\n';
  return 0;
}
