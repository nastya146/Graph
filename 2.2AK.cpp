#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

class Graph {
 public:
  explicit Graph(int32_t n) : size_(n + 1), vertex_list_(size_), colours_(size_, 0), parent_(size_, 0) {
  }

  void AddForwardEdge(int32_t begin, int32_t end) {
    vertex_list_[begin].push_back(end);
  }

  // 0-white, 1-gray, 2-black
  bool HasCycleDFS(int32_t vertex) {
    colours_[vertex] = 1;
    for (auto& u : vertex_list_[vertex]) {
      if (colours_[u] == 1) {
        return true;
      }
      if (colours_[u] == 0) {
        if (HasCycleDFS(u)) {
          return true;
        }
      }
    }
    colours_[vertex] = 2;
    return false;
  }

  bool ContainCycle() {
    for (int32_t i = 1; i < size_; ++i) {
      if (colours_[i] == 0) {
        if (HasCycleDFS(i)) {
          return true;
        }
      }
    }
    return false;
  }

 private:
  int32_t size_;
  std::vector<std::vector<int32_t>> vertex_list_;
  std::vector<int> colours_;
  std::vector<int32_t> parent_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int32_t n;
  std::cin >> n;
  Graph graph(n);
  char direction;
  for (int32_t i = 1; i < n; ++i) {
    for (int32_t j = i + 1; j <= n; ++j) {
      std::cin >> direction;
      if (direction == 'R') {
        graph.AddForwardEdge(i, j);
      } else {
        graph.AddForwardEdge(j, i);
      }
    }
  }
  std::cout << (graph.ContainCycle() ? "NO" : "YES");
}