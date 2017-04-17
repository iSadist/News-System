#include "sqldatabase.h"
#include "article.h"

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

Sqldatabase::Sqldatabase(){
  article_counter = 0;
}

Sqldatabase::~Sqldatabase(){

}

bool prepareStatement(std::string sql) {
  char *query = &sql[0];
  sqlite3_stmt *statement;
  int result;

  if (sqlite3_prepare(db, query, -1, statement, 0) == SQLITE_OK) {
    result = sqlite3_step(statement);
    if(result != 0) {
      return true;
    }
    sqlite3_finalize(statement);
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

bool Sqldatabase::create_NG(std::string title) {
  std::string sql = "INSERT INTO newsgroups (title, created)" \
                    "VALUES ('" + title + "', CURRENT_DATE)";
  return prepareStatement(sql);
}

bool Sqldatabase::delete_NG(int ng_id) {
  //Delete relations
  std::string sql = "DELETE FROM contains " \
                    "WHERE group_id = " + ng_id;
  prepareStatement(sql);

  //Delete newsgroup
  sql = "DELETE FROM newsgroups " \
        "WHERE id = " + ng_id;
  return prepareStatement(sql);
}

std::vector<Article> list_ART(int ng_id) {
  std::vector<Article> articles;
  

}

bool create_ART(int ng_id, std::string title, std::string author, std::string text) {
  //Creating article
  std::string sql = "INSERT INTO articles (id, title, author, content, created)" \
                    "VALUES (" + article_counter + ", '" + title + "', '" + author + "', '" + text + "' , CURRENT_DATE)";
  article_counter++;
  prepareStatement(sql);

  //Adding article to newsgroup
  sql = "INSERT INTO contains VALUES ( " + ng_id + " ,  " + article_counter + ")";
  return prepareStatement(sql);
}

bool delete_ART(int ng_id, int art_id) {
  std::string sql = "DELETE FROM contains " \
                    "WHERE article_id = " + art_id +
                    " AND  group_id = " + ng_id;
  return prepareStatement(sql);
}

Article get_ART(int ng_id, int art_id) {

}
