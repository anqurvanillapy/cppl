/**
 *  std::getline
 *  ============
 *
 *  How about getting lines by CRLFs in Linux using std::getline?
 *
 *  Note: Compile with -std=c++17.
 */

#include <sstream>
#include <vector>
#include <cassert>

int
main()
{
	std::istringstream iss{"GET / HTTP/1.1\r\nHost: www.example.com\r\n\r\n"};
	std::vector<std::string> lines;
	for (std::string item; std::getline(iss, item, '\r'); ) {
		lines.emplace_back(item);
		iss.ignore(1, '\n');
	}
	assert(lines.size() == 3);
	assert(lines[0].back() == '1');
	return 0;
}
