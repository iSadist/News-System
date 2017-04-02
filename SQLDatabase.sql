PRAGMA FOREIGN_KEY = OFF;

DROP TABLE IF EXISTS newsgroups;
DROP TABLE IF EXISTS articles;
DROP TABLE IF EXISTS contains;

PRAGMA FOREIGN_KEY = ON;

CREATE TABLE newsgroups (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  title TEXT UNIQUE NOT NULL,
  created DATE NOT NULL
);

CREATE TABLE articles (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  title TEXT NOT NULL,
  author TEXT NOT NULL,
  content TEXT NOT NULL,
  created DATE NOT NULL
);

CREATE TABLE contains (
  article_id INTEGER,
  group_id INTEGER,
  FOREIGN KEY (article_id) REFERENCES articles(id),
  FOREIGN KEY (group_id) REFERENCES newsgroups(id)
);

INSERT INTO articles (title, author, content, created) VALUES ('Life at LTH', 'Jan Svensson', 'Test test test', CURRENT_DATE);
INSERT INTO articles (title, author, content, created) VALUES ('Test', 'Jan Svensson', 'Test test test test', CURRENT_DATE);
INSERT INTO articles (title, author, content, created) VALUES ('Life after LTH', 'Jan Svensson', 'Sweeeeet', CURRENT_DATE);
INSERT INTO articles (title, author, content, created) VALUES ('...', 'Jan Svensson', 'esgrbedrshrerhTest test test', CURRENT_DATE);
