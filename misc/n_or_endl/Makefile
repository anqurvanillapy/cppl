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
	$(CXX) n.cc -o n $(CXXFLAGS)
	$(CXX) endl.cc -o endl $(CXXFLAGS)
	$(CXX) endl1.cc -o endl1 $(CXXFLAGS)

run: build
	@echo "[time] n"
	time ./n $(REDIR)
	@echo "[time] endl"
	time ./endl $(REDIR)
	@echo "[time] endl (sync_with_stdout(false))"
	time ./endl1 $(REDIR)

clean:
	rm -rf ./n ./endl ./endl1
