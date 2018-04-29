/**
 *  Split
 *  =====
 *
 *  Split strings by delimiter.
 *
 *  Note: Compile with -std=c++17.
 */

#include <sstream>
#include <optional>
#include <vector>
#include <cassert>

std::optional<std::vector<std::string>>
splitc(const std::string& str, char delim = '\n')
{
	std::istringstream iss{str};
	std::vector<std::string> ret;
	for (std::string item;
		 std::getline(iss, item, delim);
		 ret.emplace_back(item));
	return std::make_optional(ret);
}

std::optional<std::vector<std::string>>
splits(const std::string& str, const std::string& delim)
{
	size_t s, p;
	auto delim_siz = delim.size();
	std::vector<std::string> ret;

	for (s = 0, p = str.find(delim);
		 p != std::string::npos;
		 s = p + delim_siz, p = str.find(delim, ++p)) {
		ret.emplace_back(str.substr(s, p - s));
	}

	ret.emplace_back(str.substr(s));
	return std::make_optional(ret);
}

std::optional<std::vector<std::string>>
splitws(const std::string& str)
{
	std::istringstream iss{str};
	std::vector<std::string> ret;
	std::string item;
	while (iss >> item) {
		ret.emplace_back(item);
	}
	return std::make_optional(ret);
}

int
main()
{
	auto ret0 = splitc("1,2,3", ',');
	assert((*ret0)[0] == "1");
	assert((*ret0)[1] == "2");
	assert((*ret0)[2] == "3");

	auto ret1 = splitc("123", ',');
	assert((*ret1)[0] == "123");


	auto ret2 = splits("1002003", "00");
	assert((*ret2)[0] == "1");
	assert((*ret2)[1] == "2");
	assert((*ret2)[2] == "3");

	auto ret3 = splits("123", "00");
	assert((*ret3)[0] == "123");


	auto ret4 = splitws("1 2 3");
	assert((*ret4)[0] == "1");

	auto ret5 = splitws("123");
	assert((*ret5)[0] == "123");

	return 0;
}
