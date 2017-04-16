#include "sqldatabase.h"

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

}

Sqldatabase::~Sqldatabase(){

}

void Sqldatabase::open_connection() {
  rc = sqlite3_open("Database.db", &db);

  if( rc ){
     fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
  }else{
     fprintf(stderr, "Opened database successfully\n");
  }
}

void Sqldatabase::close_connection() {
  if (db) {
    sqlite3_close(db);
  }
}

bool Sqldatabase::create_NG(std::string title) {

}

bool Sqldatabase::delete_NG(int ng_id) {

}

std::vector<Article> list_ART(int ng_id) {

}

bool create_ART(int ng_id, std::string title, std::string author, std::string text) {

}

bool delete_ART(int ng_id, int art_id) {

}

Article get_ART(int ng_id, int art_id) {
  
}
