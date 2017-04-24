#include "sqldatabase.h"
#include "article.h"
#include "newsgroup.h"

#include <sstream>
#include <iostream>
#include <string>
#include <sqlite3.h>

using namespace std;

Sqldatabase::Sqldatabase() {
  std::cout << "SQL Database opened" << '\n';
}

Sqldatabase::~Sqldatabase(){
  std::cout << "SQL Database closed..." << '\n';
}

bool Sqldatabase::open_connection(std::string filepath) {
  if(sqlite3_open(filepath.c_str(), &db) == SQLITE_OK){
    fprintf(stderr, "Opened database successfully\n");
    return true;
  }else{
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return false;
  }

  sqlite3_stmt *statement;
  std::string sql = "SELECT id FROM articles ORDER BY id DESC LIMIT 1";
  char *query = &sql[0];
  if(sqlite3_prepare_v2(db, query, -1, &statement, 0) == SQLITE_OK && sqlite3_step(statement) == SQLITE_ROW) {
    article_counter = sqlite3_column_int(statement, 0) + 1;
  } else {
    article_counter = 1;
  }
}

void Sqldatabase::close_connection() {
  sqlite3_close(db);
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
     else {
       std::cout << "Could not complete the request: " << sql << '\n';
       return false;
     }
  }
  std::cout << "SQL failed: " << sql << '\n';
  return false;
}

bool Sqldatabase::executeSQL(std::string sql) {
  char *query = &sql[0];
  int result;
  char *err_msg = 0;

  result = sqlite3_exec(db, query, 0, 0, &err_msg);

  std::cout << "Result: " << result << '\n';

  if (result != SQLITE_OK) {
    std::cout << "SQL failed: " << sql << '\n';
    std::cout << *err_msg << '\n';
    return false;
  }
  return true;
}

std::vector<Newsgroup> Sqldatabase::list_NG() {
  std::vector<Newsgroup> groups;

  sqlite3_stmt *statement;
  std::string sql = "SELECT * FROM newsgroups";
  char *query = &sql[0];

  if(sqlite3_prepare_v2(db, query, -1, &statement, 0) == SQLITE_OK) {
    std::cout << "SQL: Listing newsgroups" << '\n';

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
  return executeSQL(sql);
}

bool Sqldatabase::delete_NG(int ng_id) {
  sqlite3_stmt *statement;
  std::ostringstream s;
  s << "SELECT * FROM newsgroups " <<
       "WHERE      id = " << ng_id;

  std::string sql(s.str());
  char *query = &sql[0];

  if(sqlite3_prepare_v2(db, query, -1, &statement, 0) == SQLITE_OK) {
    if (sqlite3_step(statement) != SQLITE_ROW) {
      return false;
    }
  } else {
    return false;
  }
  sqlite3_finalize(statement);

  std::ostringstream t;
  t << "DELETE FROM newsgroups " <<
       "WHERE id = " << ng_id;
  std::string sql2(t.str());
  return executeSQL(sql2);
}

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
THIS METHOD NEEDS TO RETURN A List with only one element:
Article(0,"null","null","null") if the newsgroup (ng_id) is not found
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
std::vector<Article> Sqldatabase::list_ART(int ng_id) {
  sqlite3_stmt *statement2;
  std::ostringstream s2;
  s2 << "SELECT * FROM newsgroups " <<
       "WHERE      id = " << ng_id;

  std::string sql2(s2.str());
  char *query2 = &sql2[0];

  if(sqlite3_prepare_v2(db, query2, -1, &statement2, 0) == SQLITE_OK) {
    if (sqlite3_step(statement2) != SQLITE_ROW) {
      std::vector<Article> null_list;
    	null_list.push_back(Article(0,"null","null","null"));
    	return null_list;
    }
  } else {
    std::vector<Article> null_list;
  	null_list.push_back(Article(0,"null","null","null"));
  	return null_list;
  }
  sqlite3_finalize(statement2);

  std::vector<Article> articles;
  sqlite3_stmt *statement;
  std::ostringstream s;
  s << "SELECT id,title,author,content FROM articles " <<
       "WHERE      newsgroup = " << ng_id;

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
  sqlite3_finalize(statement);

  return articles;
}

bool Sqldatabase::create_ART(int ng_id, std::string title, std::string author, std::string text) {
  if (!groupExists(ng_id)) {
    return false;
  }

  //Creating article
  std::ostringstream s;
  s << "INSERT INTO articles (id, title, author, content, created, newsgroup) " <<
       "VALUES (" << article_counter << ", '" << title << "', '" << author << "', '" << text << "' , CURRENT_DATE, " << ng_id << ")";
  std::string sql(s.str());
  article_counter++;
  return executeSQL(sql);
}


/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\
MUST BE FIXED TO RETURN 1 ON SUCCESS 0 ON NO SUCH NG_ID and -1 on NO SUCH ART_ID
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
int Sqldatabase::delete_ART(int ng_id, int art_id) {
  if(!groupExists(ng_id)) {
    return 0;
  }

  if(!articleExists(ng_id, art_id)) {
    return -1;
  }

  std::ostringstream s;
  s << "DELETE FROM articles " <<
       "WHERE       id = " << art_id <<
       " AND        newsgroup = " << ng_id;
  std::string sql(s.str());

  return executeSQL(sql) ? 1 : -1;
}

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
MUST BE FIXED SO RETURN ARTICLE ID IS 0 ON NO SUCH NG_ID and -1 on NO SUCH ART_ID
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
Article Sqldatabase::get_ART(int ng_id, int art_id) {
  sqlite3_stmt *statement2;
  std::ostringstream s2;

  s2 << "SELECT * FROM newsgroups "
     << "WHERE id = " << ng_id;

  std::string sql2(s2.str());
  char *query2 = &sql2[0];

  if(sqlite3_prepare_v2(db, query2, -1, &statement2, 0) != SQLITE_OK) {
    return Article(0,"null","null","null");
  }

  sqlite3_stmt *statement;
  std::ostringstream s;

  s << "SELECT id,title,author,content FROM articles " <<
       "WHERE      newsgroup = " << ng_id <<
       " AND       id = " << art_id;

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

bool Sqldatabase::groupExists(int ng_id) {
  sqlite3_stmt *statement;
  std::ostringstream s;
  s << "SELECT * FROM newsgroups " <<
       "WHERE      id = " << ng_id;

  std::string sql(s.str());
  char *query = &sql[0];

  if(sqlite3_prepare_v2(db, query, -1, &statement, 0) == SQLITE_OK) {
    if (sqlite3_step(statement) != SQLITE_ROW) {
      return false;
    }
  } else {
    return false;
  }
  sqlite3_finalize(statement);
  return true;
}

bool Sqldatabase::articleExists(int ng_id, int art_id) {
  sqlite3_stmt *statement;
  std::ostringstream s;
  s << "SELECT * FROM articles " <<
       "WHERE      id = " << art_id <<
       " AND        newsgroup = " << ng_id;

  std::string sql(s.str());
  char *query = &sql[0];

  if(sqlite3_prepare_v2(db, query, -1, &statement, 0) == SQLITE_OK) {
    if (sqlite3_step(statement) != SQLITE_ROW) {
      return false;
    }
  } else {
    return false;
  }
  sqlite3_finalize(statement);
  return true;
}
