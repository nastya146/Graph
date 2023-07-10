#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

class Graph {
 public:
  explicit Graph(int64_t n) : size_(n + 1), vertex_list_(size_), colours_(size_, 0), components_() {
  }

  void AddEdge(int64_t begin, int64_t end) {
    vertex_list_[begin].push_back(end);
    vertex_list_[end].push_back(begin);
  }

  void DFS(int64_t vertex, std::vector<int64_t>& component) {
    colours_[vertex] = 1;
    component.push_back(vertex);
    for (auto& u : vertex_list_[vertex]) {
      if (colours_[u] == 0) {
        DFS(u, component);
      }
    }
    colours_[vertex] = 2;
  }

  std::vector<std::vector<int64_t>>& Components() {
    int64_t size = vertex_list_.size();
    for (int64_t i = 1; i < size; ++i) {
      if (colours_[i] == 0) {
        std::vector<int64_t> component;
        DFS(i, component);
        components_.push_back(component);
      }
    }
    return components_;
  }

 private:
  int64_t size_;
  std::vector<std::vector<int64_t>> vertex_list_;
  std::vector<int> colours_;
  std::vector<std::vector<int64_t>> components_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n, m;
  std::cin >> n >> m;
  Graph graph(n);
  int64_t guy1, guy2;
  for (int64_t i = 0; i < m; ++i) {
    std::cin >> guy1 >> guy2;
    graph.AddEdge(guy1, guy2);
  }
  std::vector<std::vector<int64_t>> telegram = graph.Components();
  std::cout << telegram.size() << "\n";
  for (auto& chat : telegram) {
    std::cout << chat.size() << "\n";
    for (auto& member : chat) {
      std::cout << member << " ";
    }
    std::cout << "\n";
  }
}