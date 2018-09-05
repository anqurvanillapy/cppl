/**
 *  Red-black tree
 *  ==============
 */

#include <iostream>
#include <memory>
#include <cassert>

#define UNLIKELY(c) __builtin_expect(static_cast<bool>(c), false)

enum class color_t : bool {
	BLACK = false,
	RED = true,
};

template <typename T>
class tree_set {
private:
	struct _node_t {
		T value;
		color_t color;
		_node_t *left, *right, *parent;

		_node_t()
			: value{}
			, color{color_t::RED}
			, left{nullptr}
			, right{nullptr}
			, parent{nullptr}
		{
			/* nop */
		}

		inline _node_t*
		grandparent() const
		{
			if (parent) {
			return parent->parent;
			}

			return nullptr;
		}

		inline _node_t*
		uncle() const
		{
			if (UNLIKELY(!grandparent())) {
				return nullptr;
			}

			if (parent == grandparent()->right) {
			return grandparent()->left;
			}

			return grandparent()->right;
		}

		inline _node_t*
		sibling()
		{
			if (UNLIKELY(!parent)) {
			return nullptr;
			}

			if (parent->left == this) {
			return parent->right;
			}

			return parent->left;
		}
	};

	void
	rotr_(_node_t* n)
	{
		_node_t* g = n->grandparent();
		_node_t* p = n->parent;
		_node_t* r = n->right;

		p->left = r;
		if (r != NIL_) {
			r->parent = p;
		}
		n->right = p;
		p->parent = n;
		if (p == root_) {
			root_ = n;
		}
		n->parent = g;

		if (UNLIKELY(!g)) {
			return;
		}
		if (g->left == p) {
			g->left = n;
			return;
		}
		g->right = n;
	}

	void
	rotl_(_node_t* n)
	{
		if (UNLIKELY(!n->parent)) {
			root_ = n;
			return;
		}

		_node_t* g = n->grandparent();
		_node_t* p = n->parent;
		_node_t* l = n->left;

		p->right = l;
		if (l != NIL_) {
			l->parent = p;
		}
		n->left = p;
		p->parent = n;
		if (p == root_) {
			root_ = n;
		}
		n->parent = g;

		if (UNLIKELY(!g)) {
			return;
		}
		if (g->left == p) {
			g->left = n;
			return;
		}
		g->right = n;
	}

	void
	walk_(_node_t* n) const
	{
		if (UNLIKELY(n == NIL_)) {
			return;
		}

		if (n->left) {
			walk_(n->left);
		}

		std::cout << n->value << ',';

		if (n->right) {
			walt_(n->right);
		}
	}

	inline _node_t*
	smallest_child_(_node_t* n) const
	{
		if (UNLIKELY(n->left == NIL_)) {
			return n;
		}
		return smallest_child_(n->left);
	}

	bool
	delete_child_(_node_t* n, T& value)
	{
		if (n->value == value) {
			if (n->right == NIL_) {
				delete_one_child_(n);
				return true;
			}

			_node_t* smallest = smallest_child_(n->right);
			std::swap(n->value, smallest->value);
			delete_one_child_(smallest);

			return true;
		}

		if (n->value > value) {
			if (n->left == NIL_) {
				return false;
			}
			return delete_child_(n->left, value);
		}

		if (n->value < value) {
			if (n->right == NIL_) {
				return false;
			}
			return delete_child_(n->right, value);
		}
	}

	void
	delete_one_child_(_node_t* n)
	{
		if (UNLIKEYLY(!n)) {
			return;
		}

		std::unique_ptr<_node_t> p{n};

		_node_t* child = n->left == NIL_ ? n->right : n->left;

		if (UNLIKELY(!n->parent && n->left == NIL_ && n->right == NIL_)) {
			root_ = n = nullptr;
			return;
		}

		if (!n->parent) {
			child->parent = nullptr;
			root_ = child;
			root_->color = color_t::BLACK;
			return;
		}

		if (n->parent->left == n) {
			n->parent->left = child;
		} else {
			n->parent->right = child;
		}
		child->parent = n->parent;

		if (n->color == color_t::BLACK) {
			if (child->color == color_t::RED) {
			child->color = color_t::BLACK;
			} else {
			delete_case_(child);
			}
		}
	}

	void
	delete_case_(_node_t* n)
	{
		if (UNLIKELY(!n)) {
			return;
		}

		if (UNLIKELY(!n->parent)) {
			n->color = color_t::BLACK;
			return;
		}

		if (n->sibling()->color == color_t::RED) {
			n->parent->color = color_t::RED;
			n->sibling()->color = color_t::BLACK;
			if (n == n->parent->left) {
			rotl_(n->sibling());
			} else {
			rotr_(n->sibling());
			}
		}

		if (n->parent->color == color_t::BLACK
			&& n->sibling()->color == color_t::BLACK
			&& n->sibling()->left->color == color_t::BLACK
			&& n->sibling()->right->color == color_t::BLACK)
		{
			n->sibling()->color = color_t::RED;
			delete_case_(n->parent);
		} // TODO
	}

	_node_t* root_{};
	_node_t* NIL_{};
};

int
main()
{
	return 0;
}
