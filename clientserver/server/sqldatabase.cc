#include "sqldatabase.h"
#include "article.h"
#include "newsgroup.h"

#include <sstream>
#include <iostream>
#include <string>
#include <sqlite3.h>

using namespace std;

Sqldatabase::Sqldatabase() {
  open_connection("Database.db");

  sqlite3_stmt *statement;
  std::string sql = "SELECT id FROM articles ORDER BY id DESC LIMIT 1";
  char *query = &sql[0];
  if(sqlite3_prepare_v2(db, query, -1, &statement, 0) == SQLITE_OK && sqlite3_step(statement) == SQLITE_ROW) {
    article_counter = sqlite3_column_int(statement, 0) + 1;
  } else {
    article_counter = 1;
  }
}

Sqldatabase::~Sqldatabase(){
  close_connection();
  std::cout << "SQL Database closed..." << '\n';
}

bool Sqldatabase::prepareStatement(std::string sql) {
  char *query = &sql[0];
  sqlite3_stmt *statement;
  int result;

  if (sqlite3_prepare_v2(db, query, sql.size(), &statement, 0) == SQLITE_OK) {
    result = sqlite3_step(statement);
    sqlite3_finalize(statement);
    if(result == SQLITE_DONE) {
       return true;
     }
  }
  std::cout << "SQL failed: " << sql << '\n';
  return false;
}

bool Sqldatabase::insertElement(std::string sql) {
  char *query = &sql[0];
  sqlite3_stmt *statement;
  int result;
  char *err_msg = 0;

  result = sqlite3_exec(db, query, 0, 0, &err_msg);

  if (result != SQLITE_OK) {
    std::cout << "SQL failed: " << sql << '\n';
    return false;
  }
  return true;
}

bool Sqldatabase::open_connection(std::string filepath) {
  if(sqlite3_open(filepath.c_str(), &db) == SQLITE_OK){
    fprintf(stderr, "Opened database successfully\n");
    return true;
  }else{
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return false;
  }
}

void Sqldatabase::close_connection() {
  sqlite3_close(db);
}

std::vector<Newsgroup> Sqldatabase::list_NG() {
  std::vector<Newsgroup> groups;

  sqlite3_stmt *statement;
  std::string sql = "SELECT * FROM newsgroups";
  char *query = &sql[0];

  if(sqlite3_prepare_v2(db, query, -1, &statement, 0) == SQLITE_OK) {

    while (sqlite3_step(statement) == SQLITE_ROW) {
       int id = sqlite3_column_int(statement, 0);
       std::string title(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));
       std::string created(reinterpret_cast<const char*>(sqlite3_column_text(statement, 2)));

       std::string year = created.substr(0,4);
       std::string month = created.substr(5,2);
       std::string day = created.substr(8,2);

       struct tm *date_info;
       std::time_t t;
       std::time(&t);
       date_info = std::localtime(&t);

       date_info->tm_year = stoi(year);
       date_info->tm_mon = stoi(month);
       date_info->tm_mday = stoi(day);

       t = std::mktime(date_info);

       std::tm *date = std::localtime(&t);

       Newsgroup group(id, title, date);
       groups.push_back(group);
    }
  }

  return groups;
}

bool Sqldatabase::create_NG(std::string title) {
  std::ostringstream s;
  s << "INSERT INTO newsgroups (title, created) " <<
        "VALUES ('" << title << "', CURRENT_DATE)";

  std::string sql(s.str());
  return prepareStatement(sql);
}

bool Sqldatabase::delete_NG(int ng_id) {
  //Delete relations
  std::ostringstream s;
  s << "DELETE FROM contains " <<
       "WHERE       group_id = " << ng_id;
  std::string sql(s.str());
  prepareStatement(sql);

  //Delete newsgroup
  std::ostringstream t;
  t << "DELETE FROM newsgroups " <<
       "WHERE id = " << ng_id;
  std::string sql2(t.str());
  return prepareStatement(sql2);
}

std::vector<Article> Sqldatabase::list_ART(int ng_id) {
  std::vector<Article> articles;
  sqlite3_stmt *statement;
  std::ostringstream s;
  s << "SELECT id,title,author,content FROM articles " <<
       "INNER JOIN contains " <<
       "ON         id = article_id " <<
       "WHERE      group_id = " << ng_id;

  std::string sql(s.str());
  char *query = &sql[0];

  if(sqlite3_prepare_v2(db, query, -1, &statement, 0) == SQLITE_OK) {

    while (sqlite3_step(statement) == SQLITE_ROW) {
       int id = sqlite3_column_int(statement, 0);
       std::string title(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));
       std::string author(reinterpret_cast<const char*>(sqlite3_column_text(statement, 2)));
       std::string content(reinterpret_cast<const char*>(sqlite3_column_text(statement, 3)));
       Article art(id, title, author,content);
       articles.push_back(art);
    }
  }

  return articles;
}

bool Sqldatabase::create_ART(int ng_id, std::string title, std::string author, std::string text) {
  //Creating article
  std::ostringstream s;
  s << "INSERT INTO articles (id, title, author, content, created) " <<
       "VALUES (" << article_counter << ", '" << title << "', '" << author << "', '" << text << "' , CURRENT_DATE)";
  std::string sql(s.str());
  prepareStatement(sql);

  //Adding article to newsgroup
  std::ostringstream t;
  t << "INSERT INTO contains VALUES ( " << article_counter << " ,  " << ng_id << ")";
  std::string sql2(t.str());
  article_counter++;
  return prepareStatement(sql2);
}

bool Sqldatabase::delete_ART(int ng_id, int art_id) {
  std::ostringstream s;
  s << "DELETE FROM contains " <<
       "WHERE       article_id = " << art_id <<
       " AND        group_id = " << ng_id;
  std::string sql(s.str());
  return prepareStatement(sql);
}

Article Sqldatabase::get_ART(int ng_id, int art_id) {
  sqlite3_stmt *statement;

  std::ostringstream s;

  s << "SELECT id,title,author,content FROM articles " <<
       "INNER JOIN contains " <<
       "ON         id = article_id " <<
       "WHERE      group_id = " << ng_id <<
       " AND       article_id = " << art_id;

  std::string sql(s.str());
  char *query = &sql[0];
  if(sqlite3_prepare_v2(db, query, -1, &statement, 0) == SQLITE_OK) {

    if (sqlite3_step(statement) == SQLITE_ROW) {
      int id = sqlite3_column_int(statement, 0);
      std::string title(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));
      std::string author(reinterpret_cast<const char*>(sqlite3_column_text(statement, 2)));
      std::string content(reinterpret_cast<const char*>(sqlite3_column_text(statement, 3)));
      Article art(id, title, author,content);
      return art;
    }
  }

  return Article(-1,"null","null","null");
}
