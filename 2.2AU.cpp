#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <set>

class Graph {
 public:
  Graph() = default;

  explicit Graph(int n)
      : size_(n + 1), vertex_list_(n + 1), type_(n + 1, 0), colours_(n + 1, 0), visited_(n + 1, false) {
  }

  void AddType(char letter, int i) {
    if (letter == 'C') {
      type_[i] = 4;
    } else {
      type_[i] = 1;
    }
  }

  void AddEdge(int vertex1, int vertex2) {
    vertex_list_[vertex1].push_back(vertex2);
    vertex_list_[vertex2].push_back(vertex1);
  }

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

  bool BFS(int begin) {
    std::queue<int> queue;
    queue.push(begin);
    colours_[begin] = 1;
    while (!queue.empty()) {
      int v = queue.front();
      queue.pop();
      for (auto& u : vertex_list_[v]) {
        if (colours_[u] == 1) {
          return false;
        }
        if (!colours_[u]) {
          colours_[u] = 1;
          queue.push(u);
        }
      }
    }
    return true;
  }

  int Connection(int begin) {
    std::queue<int> queue;
    queue.push(begin);
    visited_[begin] = 1;
    int count = 1;
    while (!queue.empty()) {
      int v = queue.front();
      queue.pop();
      for (auto& u : vertex_list_[v]) {
        if (!visited_[u]) {
          ++count;
          visited_[u] = 1;
          queue.push(u);
        }
      }
    }
    return count;
  }

  bool IsAlkane() {
    if (Connection(1) != size_ - 1) {
      return false;
    }
    if (BFS(1)) {
      return false;
    }
    for (int i = 1; i < size_; ++i) {
      int size = vertex_list_[i].size();
      if (size != type_[i]) {
        return false;
      }
      if (vertex_list_[i].size() == 4) {
        std::set<int> set{vertex_list_[i][0], vertex_list_[i][1], vertex_list_[i][2], vertex_list_[i][3]};
        if (set.size() != 4) {
          return false;
        }
      }
      if (vertex_list_[i][0] == i) {
        return false;
      }
    }
    return true;
  }

 private:
  int size_;
  std::vector<std::vector<int>> vertex_list_;
  std::vector<int> type_;
  std::vector<int> colours_;
  std::vector<int> visited_;
};

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph(n);
  int count = 0;
  for (int i = 0; i < n; ++i) {
    char letter;
    std::cin >> letter;
    graph.AddType(letter, i + 1);
    ++count;
  }
  if (count < 5 || n - 1 != m) {
    std::cout << "NO";
    return 0;
  }
  for (int i = 0; i < m; ++i) {
    int vertex1, vertex2;
    std::cin >> vertex1 >> vertex2;
    graph.AddEdge(vertex1, vertex2);
  }
  std::cout << (graph.IsAlkane() ? "YES" : "NO");
}