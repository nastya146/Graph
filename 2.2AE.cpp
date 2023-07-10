#include <iostream>
#include <vector>
#include <queue>
#include <stack>

struct Edge {
  int to;
  int weight;
};

class Graph {
 public:
  Graph() = default;

  explicit Graph(int n) : vertex_list_(n + 1) {
  }

  void AddForwardWeightedEdge(int from, int to, int weight) {
    vertex_list_[from].push_back(Edge{to, weight});
  }

  int BFS(int begin, int end) const {
    if (begin == end) {
      return 0;
    }
    std::queue<int> queue;
    queue.push(begin);
    int size = vertex_list_.size();
    std::vector<int> dist(size, inf_);
    dist[begin] = 0;
    while (!queue.empty()) {
      int vertex = queue.front();
      queue.pop();
      for (auto& edge : vertex_list_[vertex]) {
        if (dist[vertex] + edge.weight < dist[edge.to]) {
          dist[edge.to] = dist[vertex] + edge.weight;
          queue.push(edge.to);
        }
      }
    }
    if (dist[end] == inf_) {
      return -1;
    }
    return dist[end];
  }

 private:
  std::vector<std::vector<Edge>> vertex_list_;
  int inf_ = 1000000000;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  int begin, end;
  std::cin >> begin >> end;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int vertex1, vertex2, weight;
    std::cin >> vertex1 >> vertex2 >> weight;
    graph.AddForwardWeightedEdge(vertex1, vertex2, weight);
  }
  std::cout << graph.BFS(begin, end);
}