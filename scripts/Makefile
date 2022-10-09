CC=g++
INCLUDE_PATH=../include/
SRC_PATH=../libsrc/
FLAGS=-std=c++2a -Wall -Wextra -Werror -Wno-unused-variable -Wno-unused-parameter -pedantic -I$(INCLUDE_PATH)
BOOST_LIBS=-lboost_serialization -lboost_system

.PHONY: clean


all: vocab search

vocab: $(SRC_PATH)vocab/vocab.cpp $(INCLUDE_PATH)*
	$(CC) $(FLAGS) -o vocab $(SRC_PATH)vocab/vocab.cpp $(BOOST_LIBS)

search: $(SRC_PATH)search/search.cpp $(INCLUDE_PATH)*
	$(CC) $(FLAGS) -o search $(SRC_PATH)search/search.cpp $(BOOST_LIBS)