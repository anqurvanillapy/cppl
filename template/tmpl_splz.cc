/**
 *  Template specialization
 *  =======================
 *
 *  And it just looks so... weird.
 */

template <typename T>
class foo
{
	/* nop */
};

// Forward declaration.
template <typename> class bar;

template <>
class bar<int> : public foo<int>
{
	/* nop */
};
