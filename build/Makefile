include_path    = /home/RSQuant/include
unit_test_path  = /home/RSQuant/unit_test
CXXFLAGS 	= -std=c++17 -I$(include_path) -g

.PHONY : all
all	: format indexer

.PHONY : format
format  : $(include_path)/RSQuant/format/GFF3.hpp $(unit_test_path)/RSQuant/format/GFF3_test.cpp
	g++ $(CXXFLAGS) -o GFF3_test $(unit_test_path)/RSQuant/format/GFF3_test.cpp

.PHONY : indexer
indexer : $(include_path)/RSQuant/indexer.hpp $(unit_test_path)/RSQuant/indexer_test.cpp
	g++ $(CXXFLAGS) -o indexer_test $(unit_test_path)/RSQuant/indexer_test.cpp

.PHONY : clean
clean : 
	rm GFF3_test
	rm indexer_test

.PHONY : clean_core
clean_core :
	rm core.*
