/**
 *  Integer codec
 *  =============
 *
 *  Some good integer coders/decoders.  Coding of 32-bit integers is similar to
 *  64-bit ones below, hence ignored.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>

template <typename T, typename U>
constexpr T
narrow_cast(U&& u)
{
	return static_cast<T>(std::forward<U>(u));
}

namespace {

constexpr uint64_t
_i64_to_zigzag(const int64_t n)
{
	return (static_cast<uint64_t>(n) << 1) ^ static_cast<uint64_t>(n >> 63);
}

inline int64_t
_zigzag_to_i64(uint64_t n)
{
	return (n >> 1) ^ -static_cast<int64_t>(n & 1);
}

inline char*
_encode_varu64(char* b, uint64_t v)
{
	static const unsigned int B = 128;
	unsigned char* p = reinterpret_cast<unsigned char*>(b);
	while (v >= B) {
	*(p++) = (v & (B - 1)) | B;
	v >>= 7;
	}
	*(p++) = static_cast<unsigned char>(v);
	return reinterpret_cast<char*>(p);
}

inline const char*
_getptr_varu64(const char* p, const char* limit, uint64_t* v)
{
	uint64_t ret = 0;
	for (uint32_t shift = 0; shift <= 63 && p < limit; shift += 7) {
	uint64_t b = *(reinterpret_cast<const unsigned char*>(p));
	++p;
	if (b & 128) {
	    ret |= ((b & 127) << shift);
	} else {
	    ret |= (b << shift);
	    *v = ret;
	    return reinterpret_cast<const char*>(p);
	}
	}
	return nullptr;
}

inline const char*
_getptr_vari64(const char* p, const char* limit, int64_t* v)
{
	uint64_t n = 0;
	const char* ret = _getptr_varu64(p, limit, &n);
	*v = _zigzag_to_i64(n);
	return ret;
}

} /* namespace */

inline void
put_varu64(std::string& s, uint64_t v)
{
	char buf[10];
	char* p = _encode_varu64(buf, v);
	s.append(buf, narrow_cast<size_t>(p - buf));
}

inline bool
get_varu64(std::string& s, uint64_t* v)
{
	const char* p = s.data();
	const char* limit = p + s.size();
	const char* q = _getptr_varu64(p, limit, v);
	if (q) {
	s = std::string(q, narrow_cast<size_t>(limit - q));
	return true;
	}
	return false;
}

inline void
put_vari64(std::string& s, int64_t v)
{
	char buf[10];
	char* p = _encode_varu64(buf, _i64_to_zigzag(v));
	s.append(buf, narrow_cast<size_t>(p - buf));
}

inline bool
get_vari64(std::string& s, int64_t* v)
{
	const char* p = s.data();
	const char* limit = p + s.size();
	const char* q = _getptr_vari64(p, limit, v);
	if (q) {
	s = std::string(q, narrow_cast<size_t>(limit - q));
	return true;
	}
	return false;
}

int
main()
{
	uint64_t a;
	int64_t b;
	std::string b0, b1;

	put_varu64(b0, 42ul);
	std::cout << b0.size() << std::endl;
	get_varu64(b0, &a);
	std::cout << a << std::endl;
	std::cout << b0.size() << std::endl;

	put_vari64(b1, -69l);
	std::cout << b1.size() << std::endl;
	get_vari64(b1, &b);
	std::cout << b << std::endl;
	std::cout << b1.size() << std::endl;

	return 0;
}
