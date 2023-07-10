#include <iostream>
#include <vector>
#include <queue>
#include <stack>

class Graph {
 public:
  Graph() = default;

  explicit Graph(int n) : vertex_list_(n + 1) {
  }

  void AddWeightedEdge(int u, int v, int weight) {
    vertex_list_[u].emplace_back(std::pair{v, weight});
  }

  int BFS(int begin, int end) const {
    std::deque<int> queue;
    queue.push_back(begin);
    int size = vertex_list_.size();
    std::vector<bool> flag(size, false);
    std::vector<int> dist(size, 10000);
    dist[begin] = 0;
    while (!queue.empty()) {
      int v = queue.front();
      queue.pop_front();
      for (auto& u : vertex_list_[v]) {
        if (dist[v] + u.second < dist[u.first]) {
          if (u.second == 0) {
            queue.push_front(u.first);
            dist[u.first] = dist[v];
          } else {
            queue.push_back(u.first);
            dist[u.first] = dist[v] + 1;
          }
        }
      }
    }
    return dist[end];
  }

 private:
  std::vector<std::vector<std::pair<int, int>>> vertex_list_;
};

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int vertex1, vertex2;
    std::cin >> vertex1 >> vertex2;
    graph.AddWeightedEdge(vertex1, vertex2, 0);
    graph.AddWeightedEdge(vertex2, vertex1, 1);
  }
  int k;
  std::cin >> k;
  int begin, end;
  for (int i = 0; i < k; ++i) {
    std::cin >> begin >> end;
    int distance = graph.BFS(begin, end);
    std::cout << (distance == 10000 ? -1 : distance) << "\n";
  }
}