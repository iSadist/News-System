#include "sqldatabase.h"
#include "article.h"
#include "newsgroup.h"

#include <sstream>
#include <iostream>
#include <string>
#include <sqlite3.h>

Sqldatabase::Sqldatabase(){
  article_counter = 0;
}

Sqldatabase::~Sqldatabase(){

}

bool Sqldatabase::prepareStatement(std::string sql) {
  char *query = &sql[0];
  sqlite3_stmt *statement;
  int result;

  if (sqlite3_prepare(db, query, -1, &statement, 0) == SQLITE_OK) {
    result = sqlite3_step(statement);
    sqlite3_finalize(statement);
    if(result != 0) return true;
  }
  return false;
}

bool Sqldatabase::open_connection(const std::string& filepath) {
  if(sqlite3_open("Database.db", &db) == SQLITE_OK){ // std::string.c_string
    fprintf(stderr, "Opened database successfully\n");
    return true;
  }else{
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return false;
  }
}

void Sqldatabase::close_connection() {
  if (db) {
    sqlite3_close(db);
  }
}

std::vector<Newsgroup> Sqldatabase::list_NG() {
  std::vector<Newsgroup> groups;

  sqlite3_stmt *statement;
  std::string sql = "SELECT * FROM newsgroups";
  char *query = &sql[0];

  if(sqlite3_prepare(db, query, -1, &statement, 0) == SQLITE_OK) {
    int columns = sqlite3_column_count(statement);

    while (sqlite3_step(statement) == SQLITE_ROW) {
       int id = sqlite3_column_int(statement, 1);
       std::string title = (char*)sqlite3_column_text(statement, 2);
       std::string created = (char*)sqlite3_column_text(statement, 3);

       std::string year = created.substr(0,4);
       std::string month = created.substr(4,2);
       std::string day = created.substr(7,2);

       std::tm *date;
       date->tm_year = atoi(year.c_str());
       date->tm_mon = atoi(month.c_str());
       date->tm_mday = atoi(day.c_str());

       Newsgroup group(id, title, date);
       groups.push_back(group);
    }
  }

  return groups;
}

bool Sqldatabase::create_NG(std::string title) {
  std::ostringstream s;
  s << "INSERT INTO newsgroups (title, created)" <<
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

  if(sqlite3_prepare(db, query, -1, &statement, 0) == SQLITE_OK) {
    int columns = sqlite3_column_count(statement);

    while (sqlite3_step(statement) == SQLITE_ROW) {
       int id = sqlite3_column_int(statement, 1);
       std::string title = (char*)sqlite3_column_text(statement, 2);
       std::string author = (char*)sqlite3_column_text(statement, 3);
       std::string content = (char*)sqlite3_column_text(statement, 4);
       Article art(id, title, author,content);
       articles.push_back(art);
    }
  }

  return articles;
}

bool Sqldatabase::create_ART(int ng_id, std::string title, std::string author, std::string text) {
  //Creating article
  std::ostringstream s;
  s << "INSERT INTO articles (id, title, author, content, created)" <<
       "VALUES (" << article_counter << ", '" << title << "', '" << author << "', '" << text << "' , CURRENT_DATE)";
  std::string sql(s.str());
  article_counter++;
  prepareStatement(sql);

  //Adding article to newsgroup
  std::ostringstream t;
  t << "INSERT INTO contains VALUES ( " << ng_id << " ,  " << article_counter << ")";
  std::string sql2(t.str());
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
  if(sqlite3_prepare(db, query, -1, &statement, 0) == SQLITE_OK) {
    int columns = sqlite3_column_count(statement);

    if (sqlite3_step(statement) == SQLITE_ROW) {
      int id = sqlite3_column_int(statement, 1);
      std::string title = (char*)sqlite3_column_text(statement, 2);
      std::string author = (char*)sqlite3_column_text(statement, 3);
      std::string content = (char*)sqlite3_column_text(statement, 4);
      Article art(id, title, author,content);
      return art;
    }
  }

  return Article(-1,"null","null","null");
}
