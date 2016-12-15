/**
 * A map from unsigend int to double.
 * This is simply a wrapper, or a typedef of the map STL
 * Support iterators, assingment, and more methods.
 */
#ifndef _MAP_H_
#define _MAP_H_

#include <map>
#include <utility>

typedef std::pair<unsigned int, unsigned int> Pair;
typedef std::map<Pair, double> Map;

#endif // _MAP_H_
