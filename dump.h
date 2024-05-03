/* -*- C++ -*- */

#ifndef DUMP_H_GUARD
#define DUMP_H_GUARD


#include <cstddef>
#include <iostream>
#include <string>

#include "to_string.h"


inline std::ostream& dump_values()
{
	return std::cerr << std::endl;
}

template<typename First, typename... Rest>
inline std::ostream& dump_values(First first, Rest... rest)
{
	std::cerr << std::to_string(first);
	if (sizeof...(rest) != 0)
		std::cerr << ", ";
	return dump_values(rest...);
}

template<typename T, std::size_t N, typename... Rest>
inline std::ostream& dump_values(T (&first)[N], Rest... rest)
{
	std::cerr << std::to_string(first);
	if (sizeof...(rest) != 0)
		std::cerr << ", ";
	return dump_values(rest...);
}

#define DUMP(...)	\
	std::cerr << '[' << __LINE__ << "] "  \
	          << #__VA_ARGS__ << ":\t",   \
	dump_values(__VA_ARGS__)


#endif // DUMP_H_GUARD
