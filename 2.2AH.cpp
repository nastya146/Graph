#include <iostream>
#include <vector>
#include <queue>
#include <stack>

class Graph {
 public:
  explicit Graph(int n) : vertex_list_(n + 1), visited_vertex_(n + 1, false) {
  }

  void AddEdge(int u, int v) {
    vertex_list_[u].push_back(v);
    vertex_list_[v].push_back(u);
  }

  void BFS(int begin) {
    std::queue<int> queue;
    queue.push(begin);
    visited_vertex_[begin] = true;
    while (!queue.empty()) {
      int v = queue.front();
      queue.pop();
      for (auto& u : vertex_list_[v]) {
        if (!visited_vertex_[u]) {
          visited_vertex_[u] = true;
          queue.push(u);
        }
      }
    }
  }

  int MinNumOfPigs() {
    int min = 0;
    int size = visited_vertex_.size();
    for (int i = 1; i < size; ++i) {
      if (!visited_vertex_[i]) {
        BFS(i);
        ++min;
      }
    }
    return min;
  }

 private:
  std::vector<std::vector<int>> vertex_list_;
  std::vector<bool> visited_vertex_;
};

int main() {
  int n;
  std::cin >> n;
  Graph graph(n);
  int key;
  for (int i = 1; i <= n; ++i) {
    std::cin >> key;
    graph.AddEdge(i, key);
  }
  std::cout << graph.MinNumOfPigs();
}