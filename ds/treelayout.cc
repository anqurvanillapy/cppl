#include <vector>
#include <algorithm>
#include <iostream>

struct treeelem_t {
	double value;
	int lchild;
	int rchild;
};

struct treenode_t {
	double value;
	treenode_t* lchild;
	treenode_t* rchild;
	int height;
};

double
find_root(std::vector<double>& vals)
{
	std::sort(vals.begin(), vals.end());
	return vals[vals.size() / 2];
}

treenode_t*
create_tree(std::vector<double>&)
{
}

int main()
{
	return 0;
}
