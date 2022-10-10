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
 * In general, we enumerate all possible configurations of the inputs and
 * pick the best of all those enumerated configurations.
 *
 * - the wors-case time complexity O(m * n)
 */
int find_pattern(string text, string pattern) {
  int n = text.length();
  int m = pattern.length();

  for (int i = 0; i <= n - m; ++i) {
    int k = 0;

    while (k < m && text[i + k] == pattern[k]) {
      k++;
    }

    if (k == m) {
      return i;
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
