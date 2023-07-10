#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <set>
#include <map>

class Graph {
 public:
  explicit Graph(int16_t n)
      : size_(n + 1), time_(0), vertex_list_(size_), colours_(size_, 0), time_in_(size_, 0), time_up_(size_, 0) {
  }

  void AddEdge(int16_t vertex1, int16_t vertex2) {
    vertex_list_[vertex1].push_back(vertex2);
    vertex_list_[vertex2].push_back(vertex1);
  }

  void Dfs(int16_t vertex, std::queue<std::pair<int16_t, int16_t>>& bridges, int16_t parent = 0) {
    colours_[vertex] = 1;
    time_in_[vertex] = ++time_;
    time_up_[vertex] = time_in_[vertex];
    for (auto& u : vertex_list_[vertex]) {
      if (parent != u) {
        if (colours_[u] == 1) {
          time_up_[vertex] = std::min(time_up_[vertex], time_in_[u]);
        }
        if (colours_[u] == 0) {
          Dfs(u, bridges, vertex);
          time_up_[vertex] = std::min(time_up_[vertex], time_up_[u]);
          if (time_in_[vertex] < time_up_[u]) {
            if (std::count(vertex_list_[vertex].begin(), vertex_list_[vertex].end(), u) == 1) {
              bridges.push(std::pair<int16_t, int16_t>{std::min(vertex, u), std::max(vertex, u)});
            }
          }
        }
      }
    }
    colours_[vertex] = 2;
  }

  std::queue<std::pair<int16_t, int16_t>> Bridges() {
    std::queue<std::pair<int16_t, int16_t>> bridges;
    for (int16_t i = 1; i < size_; ++i) {
      if (colours_[i] == 0) {
        Dfs(i, bridges);
      }
    }
    return bridges;
  }

 private:
  int16_t size_;
  int16_t time_;
  std::vector<std::vector<int16_t>> vertex_list_;
  std::vector<int> colours_;
  std::vector<int16_t> time_in_;
  std::vector<int16_t> time_up_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int16_t n;
  int32_t m;
  std::cin >> n >> m;
  Graph graph(n);
  std::map<std::pair<int16_t, int16_t>, int32_t> edges;
  int16_t vert1, vert2;
  for (int32_t i = 0; i < m; ++i) {
    std::cin >> vert1 >> vert2;
    graph.AddEdge(vert1, vert2);
    edges[std::pair<int16_t, int16_t>{std::min(vert1, vert2), std::max(vert1, vert2)}] = i + 1;
  }
  std::queue<std::pair<int16_t, int16_t>> bridges = graph.Bridges();
  std::set<int32_t> list;
  while (!bridges.empty()) {
    list.insert(edges[bridges.front()]);
    bridges.pop();
  }
  int32_t size = list.size();
  std::cout << size << "\n";
  for (auto& number : list) {
    std::cout << number << "\n";
  }
}