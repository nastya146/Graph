#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

class Graph {
 public:
  explicit Graph(int64_t n) : size_(n + 1), vertex_list_(size_), colours_(size_, 0), top_sort_() {
  }

  void AddForwardEdge(int64_t begin, int64_t end) {
    vertex_list_[begin].push_back(end);
  }

  // 0-white, 1-gray, 2-black
  bool DFS(int64_t vertex) {
    colours_[vertex] = 1;
    for (auto& u : vertex_list_[vertex]) {
      if (colours_[u] == 1) {
        return true;
      }
      if (colours_[u] == 0) {
        if (DFS(u)) {
          return true;
        }
      }
    }
    top_sort_.push_back(vertex);
    colours_[vertex] = 2;
    return false;
  }

  std::deque<int64_t> TopSort() {
    int64_t size = vertex_list_.size();
    for (int64_t i = 1; i < size; ++i) {
      if (colours_[i] == 0) {
        if (DFS(i)) {
          return std::deque<int64_t>{0};
        }
      }
    }
    return top_sort_;
  }

 private:
  int64_t size_;
  std::vector<std::vector<int64_t>> vertex_list_;
  std::vector<int> colours_;
  std::deque<int64_t> top_sort_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n, m;
  std::cin >> n >> m;
  Graph graph(n);
  int64_t vertex1, vertex2;
  for (int64_t i = 0; i < m; ++i) {
    std::cin >> vertex1 >> vertex2;
    graph.AddForwardEdge(vertex1, vertex2);
  }
  std::deque<int64_t> top_sort = graph.TopSort();
  if (top_sort.size() == 1) {
    std::cout << -1;
  } else {
    while (!top_sort.empty()) {
      std::cout << top_sort.back() << " ";
      top_sort.pop_back();
    }
  }
}