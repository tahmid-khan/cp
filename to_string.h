/* -*- C++ -*- */

#ifndef TO_STRING_H_GUARD
#define TO_STRING_H_GUARD


#include <bitset>
#include <deque>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>


namespace std {


// Overload for std::string

inline string to_string(const string& s)
{
	return '"' + s + '"';
}


// Template specializations for bool, char, and char*

inline string to_string(bool b)
{
	return b ? "true" : "false";
}

inline string to_string(char c)
{
	return {'\'', c, '\''};
}

inline string to_string(const char* s)
{
	return to_string(string{s});
}


// Overload for std::bitset
//
// Printing style:
// 	b = 42; to_string(b)  =>  101010

template<size_t N>
inline string to_string(const bitset<N>& b)
{
	string res;
	for (size_t i {0}; i < N; ++i)
		res += static_cast<char>('0' + b[i]);
	return res;
}


// Overloads for std::pair and std::tuple
//
// Printing style:
// 	t = make_tuple(1,'2',"3"); to_string(t)  =>  (1, '2', "3")#3

template<typename T1, typename T2>
inline string to_string(const pair<T1, T2>& p)
{
	return '(' + to_string(p.first) + ", " + to_string(p.second) + ')';
}

// Tuple pretty-printer based on ideas from
// https://en.cppreference.com/w/cpp/utility/tuple/tuple_cat#Example

template<typename Tuple, size_t N,
         typename enable_if<N == 1, nullptr_t>::type = nullptr>
inline string pretty_elem_list(const Tuple& t)
{
	return to_string(get<0>(t));
}

template<typename Tuple, size_t N,
         typename enable_if<N != 1, nullptr_t>::type = nullptr>
inline string pretty_elem_list(const Tuple& t)
{
	return pretty_elem_list<Tuple, N-1>(t) + ", " + to_string(get<N-1>(t));
}

template<typename... Types,
         typename enable_if<sizeof...(Types) == 0, nullptr_t>::type = nullptr>
inline string to_string(const tuple<Types...>&)
{
	return "()";
}

template<typename... Types,
         typename enable_if<sizeof...(Types) != 0, nullptr_t>::type = nullptr>
inline string to_string(const tuple<Types...>& t)
{
	return '(' + pretty_elem_list<decltype(t), sizeof...(Types)>(t) + ')';
}


// Template specialization for C-style arrays and overloads for std::array,
// std::vector, and std::deque
//
// Printing style:
// 	a = {1,2,4,8}; to_string(a)  =>  [1, 2, 4, 8]#4

template<typename T, size_t N>
inline string to_string(const T (&arr)[N])
{
	if (N == 0) return "[]#0";
	auto ptr = begin(arr);
	string res {'[' + to_string(*ptr)};
	while (++ptr != end(arr))
		res += ", " + to_string(*ptr);
	res += "]#" + to_string(N);
	return res;
}

template<typename T, size_t N>
inline string to_string(const array<T, N>& arr)
{
	if (arr.empty()) return "[]#0";
	auto it = begin(arr);
	string res {'[' + to_string(*it)};
	while (++it != end(arr))
		res += ", " + to_string(*it);
	res += "]#" + to_string(arr.size());
	return res;
}

template<typename T>
inline string to_string(const vector<T>& vec)
{
	if (vec.empty()) return "[]#0";
	auto it = begin(vec);
	string res {'[' + to_string(*it)};
	while (++it != end(vec))
		res += ", " + to_string(*it);
	res += "]#" + to_string(vec.size());
	return res;
}

template<typename T>
inline string to_string(const deque<T>& deq)
{
	if (deq.empty()) return "[]#0";
	auto it = begin(deq);
	string res {'[' + to_string(*it)};
	while (++it != end(deq))
		res += ", " + to_string(*it);
	res += "]#" + to_string(deq.size());
	return res;
}


// Overloads for std::set, std::unordered_set, and std::multiset
//
// Printing style:
// 	set = {1,2,4,8}; to_string(set)  =>  {1, 2, 4, 8}#4

template<typename T>
inline string to_string(const set<T>& set)
{
	if (set.empty()) return "{}#0";
	auto it = begin(set);
	string res {'{' + to_string(*it)};
	while (++it != end(set))
		res += ", " + to_string(*it);
	res += "}#" + to_string(set.size());
	return res;
}

template<typename T>
inline string to_string(const unordered_set<T>& set)
{
	if (set.empty()) return "{}#0";
	auto it = begin(set);
	string res {'{' + to_string(*it)};
	while (++it != end(set))
		res += ", " + to_string(*it);
	res += "}#" + to_string(set.size());
	return res;
}

template<typename T>
inline string to_string(const multiset<T>& set)
{
	if (set.empty()) return "{}#0";
	auto it = begin(set);
	string res {'{' + to_string(*it)};
	while (++it != end(set))
		res += ", " + to_string(*it);
	res += "}#" + to_string(set.size());
	return res;
}


// Overloads for std::map, std::unordered_map, and std::multimap
//
// Printing style:
// 	map = {{1,2},{4,8}}; to_string(map)  =>  {1: 2, 4: 8}#2

template<typename Key, typename T>
inline string pretty_key_val(const pair<Key, T>& kv)
{
	return to_string(kv.first) + ": " + to_string(kv.second);
}

template<typename Key, typename T>
inline string to_string(const map<Key, T>& map)
{
	if (map.empty()) return "{}#0";
	auto it = begin(map);
	string res {'{' + pretty_key_val(*it)};
	while (++it != end(map))
		res += ", " + pretty_key_val(*it);
	res += "}#" + to_string(map.size());
	return res;
}

template<typename Key, typename T>
inline string to_string(const unordered_map<Key, T>& map)
{
	if (map.empty()) return "{}#0";
	auto it = begin(map);
	string res {'{' + pretty_key_val(*it)};
	while (++it != end(map))
		res += ", " + pretty_key_val(*it);
	res += "}#" + to_string(map.size());
	return res;
}

template<typename Key, typename T>
inline string to_string(const multimap<Key, T>& map)
{
	if (map.empty()) return "{}#0";
	auto it = begin(map);
	string res {'{' + pretty_key_val(*it)};
	while (++it != end(map))
		res += ", " + pretty_key_val(*it);
	res += "}#" + to_string(map.size());
	return res;
}

} // namespace std


#endif // TO_STRING_H_GUARD
