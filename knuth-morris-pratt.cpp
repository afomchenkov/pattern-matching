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
 * The main idea of the KMP algorithm is to precompute self-overlaps between
 * portions of the pattern so that when a mismatch occurs at one location, we
 * immediately know the maximum amount to shift the pattern before continuing
 * the search.
 *
 * - worst case time complexity O(n + m)
 */

/**
 * Indicates the proper shift of the pattern upon a failed comparison
 *
 * Consider the pattern "amalgamation", the KMP failure function for the string
 * P is:
 *
 * k    | 0 1 2 3 4 5 6 7 8 9 10 11
 * =================================
 * P[k] | a m a l g a m a t i o  n
 * ---------------------------------
 * f(k) | 0 0 1 0 0 1 2 3 0 0 0  0
 */
vector<int> compute_fail_kmp(string pattern) {
  int m = pattern.length();
  vector<int> fail(m, 0); // by default, all overlaps are zero

  int j = 1;
  int k = 0;

  while (j < m) {
    if (pattern.at(j) == pattern.at(k)) {
      fail[j] = k + 1;
      j++;
      k++;
    } else if (k > 0) {
      k = fail[k - 1];
    } else {
      j++;
    }
  }

  return fail;
}

int kmp(string text, string pattern) {
  int n = text.length();
  int m = pattern.length();
  if (m == 0) {
    return 0;
  }

  vector<int> fail = compute_fail_kmp(pattern);
  int j = 0;
  int k = 0;

  while (j < n) {
    if (text.at(j) == pattern.at(k)) {
      if (k == m - 1) {
        return j - m + 1;
      }
      j++;
      k++;
    } else if (k > 0) {
      k = fail[k - 1];
    } else {
      j++;
    }
  }

  return -1;
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main() {
  string text = "abacaabaccabacabaabb";
  string pattern = "abacab";

  auto idx = kmp(text, pattern);
  printf("The pattern is met at index: %d", idx);

  return 0;
}
