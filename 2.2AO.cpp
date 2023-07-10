#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <set>

class Graph {
 public:
  explicit Graph(int64_t n, int64_t m)
      : size_(n + 1)
      , time_(0)
      , vertex_list_(size_)
      , colours_(size_, 0)
      , time_in_(size_, 0)
      , time_up_(size_, 0)
      , max_(m) {
  }

  void AddEdge(int64_t vertex1, int64_t vertex2) {
    vertex_list_[vertex1].push_back(vertex2);
    vertex_list_[vertex2].push_back(vertex1);
  }

  void Dfs(int64_t vertex, std::set<int64_t>& points, int64_t root) {
    colours_[vertex] = 1;
    time_in_[vertex] = ++time_;
    time_up_[vertex] = time_in_[vertex];
    int64_t children_counter = 0;
    for (auto& u : vertex_list_[vertex]) {
      if (colours_[u] == 1) {
        time_up_[vertex] = std::min(time_up_[vertex], time_in_[u]);
      }
      if (colours_[u] == 0) {
        ++children_counter;
        Dfs(u, points, root);
        time_up_[vertex] = std::min(time_up_[vertex], time_up_[u]);
        if (vertex <= max_ && vertex != root && time_in_[vertex] <= time_up_[u]) {
          points.insert(vertex);
        }
      }
    }
    if (vertex <= max_ && vertex == root && children_counter >= 2) {
      points.insert(vertex);
    }
    colours_[vertex] = 2;
  }

  std::set<int64_t> ArticulationPoints() {
    std::set<int64_t> points;
    for (int64_t i = 1; i < size_; ++i) {
      if (colours_[i] == 0) {
        Dfs(i, points, i);
      }
    }
    return points;
  }

 private:
  int64_t size_;
  int64_t time_;
  std::vector<std::vector<int64_t>> vertex_list_;
  std::vector<int> colours_;
  std::vector<int64_t> time_in_;
  std::vector<int64_t> time_up_;
  int64_t max_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n, m;
  std::cin >> n >> m;
  Graph graph(n + m, m);
  int64_t vert1, vert2, vert3;
  for (int64_t i = 1; i <= m; ++i) {
    std::cin >> vert1 >> vert2 >> vert3;
    graph.AddEdge(i, m + vert2);
    graph.AddEdge(i, m + vert1);
    graph.AddEdge(i, m + vert3);
  }
  std::set<int64_t> points = graph.ArticulationPoints();
  int64_t size = points.size();
  std::cout << size << "\n";
  for (auto& vertex : points) {
    std::cout << vertex << "\n";
  }
}