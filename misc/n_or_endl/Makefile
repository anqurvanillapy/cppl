#	'\n' or std::endl
#	=================
#
#	std::endl is implemented with a '\n' followed by a flush. Indeed '\n'
#	is faster. It's worth to note the sync_with_stdout(false).

CXX=g++
CXXFLAGS=-std=c++11 -O2 -Wall -Wextra -pedantic
REDIR=1>/dev/null

.PHONY: clean

build: n.cc endl.cc endl1.cc
	$(CXX) n.cc -o n.out $(CXXFLAGS)
	$(CXX) endl.cc -o endl.out $(CXXFLAGS)
	$(CXX) endl1.cc -o endl1.out $(CXXFLAGS)

run: build
	@echo "[time] n"
	time ./n.out $(REDIR)
	@echo "[time] endl"
	time ./endl.out $(REDIR)
	@echo "[time] endl (sync_with_stdout(false))"
	time ./endl1.out $(REDIR)

clean:
	rm -rf ./n.out ./endl.out ./endl1.out
