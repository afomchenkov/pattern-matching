#include <cstdio>
#include <stdexcept>

#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <deque>
#include <forward_list>
#include <functional>
#include <future>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <queue>
#include <regex>
#include <set>
#include <stack>
#include <string>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

/**
 * The Boyer-Moor pattern-matching algorithm can sometimes avoid examining a
 * significant fraction of the character in the text. The main idea of the
 * algorithm is to improve the running time of the brute-force algorithm by
 * adding two potentially time-saving heuristics:
 *
 * - Looking-Glass Heuristic - when testing a possible placement of the pattern
 * against the text, perform the comparisons against the pattern from
 * right-to-left.
 * - Character-Jump Heuristic - during testing of a possible placement, a
 * mismatch of character (text[i] = c) with pattern[k] is handled as follows:
 *              - if c is not contained in the pattern, then shift the pattern
 * completely past text[i] = c
 *              - otherwise shift the pattern until an occurrence of character c
 * is aligned with text[i]
 *
 *  Basic case:
 *  [. . . . e . . . . s . . . . . . . . . . . . .]
 *  [s u s h i] <- no match, shift the whole pattern
 *            [s u s h i] <- no match, but s occurs in the pattern
 *                [s u s h i] <- last occurrence of s is aligned with s in the
 * text
 *                    ..... and so on
 */
int find_pattern(string text, string pattern) {
  int n = text.length();
  int m = pattern.length();
  if (m == 0) {
    return 0;
  }

  map<char, int> last;
  for (int i = 0; i < n; ++i) {
    last[text.at(i)] = -1;
  }
  // rightmost occurrence in pattern is last
  for (int k = 0; k < m; ++k) {
    last[pattern.at(k)] = k;
  }

  int i = m - 1; // index in text
  int k = m - 1; // index in pattern
  while (i < n) {
    if (text.at(i) == pattern.at(k)) {
      if (k == 0) {
        return i;
      }
      i--;
      k--;
    } else {
      i += m - min(k, 1 + last[text.at(i)]);
      k = m - 1;
    }
  }

  return -1;
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main() {
  string text = "abacaabaccabacabaabb";
  string pattern = "abacab";

  auto idx = find_pattern(text, pattern);
  printf("The pattern is met at index: %d", idx);

  return 0;
}
