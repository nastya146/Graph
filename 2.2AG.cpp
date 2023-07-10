#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

class Graph {
 public:
  explicit Graph(int32_t n)
      : size_(n + 1), vertex_list_(size_), colours_(size_, 0), parent_(size_, 0), contains_cycle_(false), begin_(0) {
  }

  void AddForwardEdge(int32_t begin, int32_t end) {
    vertex_list_[begin].push_back(end);
  }

  // 0-white, 1-gray, 2-black
  bool HasCycleDFS(int32_t vertex) {
    colours_[vertex] = 1;
    for (auto& u : vertex_list_[vertex]) {
      if (colours_[u] == 1) {
        begin_ = u;
        parent_[u] = vertex;
        return true;
      }
      if (colours_[u] == 0) {
        parent_[u] = vertex;
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

  std::stack<int32_t> Cycle() {
    std::stack<int32_t> cycle;
    int32_t cur = begin_;
    while (parent_[cur] != begin_) {
      cycle.push(cur);
      cur = parent_[cur];
    }
    cycle.push(cur);
    return cycle;
  }

 private:
  int32_t size_;
  std::vector<std::vector<int32_t>> vertex_list_;
  std::vector<int> colours_;
  std::vector<int32_t> parent_;
  bool contains_cycle_;
  int32_t begin_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int32_t n, m;
  std::cin >> n >> m;
  Graph graph(n);
  for (int32_t i = 0; i < m; ++i) {
    int32_t vertex1, vertex2;
    std::cin >> vertex1 >> vertex2;
    graph.AddForwardEdge(vertex1, vertex2);
  }
  if (graph.ContainCycle()) {
    std::cout << "YES\n";
    std::stack<int32_t> cycle = graph.Cycle();
    while (!cycle.empty()) {
      std::cout << cycle.top() << " ";
      cycle.pop();
    }
  } else {
    std::cout << "NO";
  }
}