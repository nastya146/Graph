#include <iostream>
#include <vector>
#include <queue>
#include <stack>

class Graph {
 public:
  Graph() = default;

  explicit Graph(int n) : vertex_list_(n + 1), colours_(n + 1, 0) {
  }

  void AddForwardEdge(int begin, int end) {
    vertex_list_[begin].push_back(end);
  }

  bool BFS(int begin) {
    std::queue<int> queue;
    queue.push(begin);
    int size = vertex_list_.size();
    std::vector<bool> visited(size, false);
    visited[begin] = true;
    colours_[begin] = 1;
    while (!queue.empty()) {
      int vertex = queue.front();
      queue.pop();
      for (auto& neighbour : vertex_list_[vertex]) {
        if (!visited[neighbour]) {
          colours_[neighbour] = (colours_[vertex] == 1 ? 2 : 1);
          visited[neighbour] = true;
          queue.push(neighbour);
        } else {
          if (colours_[vertex] == colours_[neighbour]) {
            return false;
          }
        }
      }
    }
    return true;
  }

  bool IsBipartiteGraph() {
    int size = vertex_list_.size();
    for (int i = 1; i < size; ++i) {
      if (colours_[i] == 0) {
        bool bipartite = BFS(i);
        if (!bipartite) {
          return false;
        }
      }
    }
    return true;
  }

 private:
  std::vector<std::vector<int>> vertex_list_;
  std::vector<int> colours_;
};

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int vertex1, vertex2;
    std::cin >> vertex1 >> vertex2;
    graph.AddForwardEdge(vertex1, vertex2);
  }
  std::cout << (graph.IsBipartiteGraph() ? "YES" : "NO");
}