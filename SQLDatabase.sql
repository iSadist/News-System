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
  FOREIGN KEY (group_id) REFERENCES newsgroups(id),
  UNIQUE (article_id, group_id)
);

INSERT INTO newsgroups (title, created) VALUES ("Sports", "2017-04-11");
INSERT INTO newsgroups (title, created) VALUES ("Politics", "2017-03-20");
INSERT INTO newsgroups (title, created) VALUES ("Culture", "2017-01-26");
INSERT INTO newsgroups (title, created) VALUES ("School", "2017-01-26");

INSERT INTO articles (title, author, content, created) VALUES (1 , 'Life at LTH', 'Jan Svensson', 'Test test test', CURRENT_DATE);
INSERT INTO articles (title, author, content, created) VALUES (2 , 'Test', 'Jan Svensson', 'Test test test test', CURRENT_DATE);
INSERT INTO articles (title, author, content, created) VALUES (3 , 'Life after LTH', 'Jan Svensson', 'Sweeeeet', CURRENT_DATE);
INSERT INTO articles (title, author, content, created) VALUES (4 , '...', 'Jan Svensson', 'esgrbedrshrerhTest test test', CURRENT_DATE);

INSERT INTO contains VALUES (4,1);
INSERT INTO contains VALUES (2,3);
