all:
	cd ./src && make
	cd ./src/client && make
	cd ./src/server && make && mv perfectserver memoryserver
	cd ./src/server && make db=-DSQL && mv perfectserver sqlserver

install:
	cd ./src/client && mv client ../../bin/client
	cd ./src/server && mv memoryserver ../../bin/
	cd ./src/server && mv sqlserver ../../bin/
	cd ./src/server && sqlite3 Database.db < SQLDatabase.sql && mv Database.db ../../bin

test: clean all install

# Phony targets
.PHONY: all clean

clean:
	cd ./src/client && make clean
	cd ./src/server && make clean
	cd ./src/ && make clean
	rm -rf bin/*