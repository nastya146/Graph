#include <iostream>
#include <vector>

struct Edge {
  int64_t to;
  int64_t weight;
};

class Graph {
 public:
  Graph() = default;

  explicit Graph(int n) : size_(n + 1), vertex_list_(n + 1) {
  }

  void AddWeightedEdge(int64_t from, int64_t to, int64_t weight) {
    vertex_list_[from].push_back(Edge{to, weight});
  }

  int64_t ArgMin(const std::vector<int64_t>& dist, const std::vector<bool>& visit) {
    int64_t ptr = 0;
    for (int64_t i = 1; i < size_; ++i) {
      if (!visit[i] && (dist[ptr] > dist[i] || ptr == 0)) {
        ptr = i;
      }
    }
    return ptr;
  }

  int64_t Dijkstra(int64_t begin, int64_t end) {
    if (begin == end) {
      return 0;
    }
    std::vector<int64_t> distance(size_, inf_);
    std::vector<bool> visit(size_, false);
    distance[begin] = 0;
    int64_t count = 0;
    while (count != size_ - 1) {
      int64_t vertex = ArgMin(distance, visit);
      ++count;
      visit[vertex] = true;
      // if (distance[vertex] == inf_) {
      //   break;
      // }
      for (auto& edge : vertex_list_[vertex]) {
        if (distance[edge.to] > distance[vertex] + edge.weight) {
          distance[edge.to] = distance[vertex] + edge.weight;
        }
      }
    }
    if (distance[end] == inf_) {
      return -1;
    }
    return distance[end];
  }

 private:
  int64_t size_;
  std::vector<std::vector<Edge>> vertex_list_;
  int64_t inf_ = 1'000'000'000'000'000'000;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t m;
  int64_t n;
  std::cin >> n >> m;
  int64_t begin, end;
  std::cin >> begin >> end;
  Graph graph(n);
  for (int64_t i = 0; i < m; ++i) {
    int64_t vertex1, vertex2;
    int64_t weight;
    std::cin >> vertex1 >> vertex2 >> weight;
    graph.AddWeightedEdge(vertex1, vertex2, weight);
  }
  std::cout << graph.Dijkstra(begin, end);
}