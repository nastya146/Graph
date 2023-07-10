#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

class Graph {
 public:
  explicit Graph(int64_t n) : size_(n + 1), vertex_list_(size_), colours_(size_, 0), components_(size_, 0) {
  }

  void AddForwardEdge(int64_t begin, int64_t end) {
    vertex_list_[begin].push_back(end);
  }

  void Dfs(int64_t vertex, int64_t component) {
    colours_[vertex] = 1;
    for (auto& u : vertex_list_[vertex]) {
      if (colours_[u] == 0) {
        Dfs(u, component);
      }
    }
    components_[vertex] = component;
    colours_[vertex] = 2;
  }

  // 0-white, 1-gray, 2-black
  void TopSortDfs(int64_t vertex) {
    colours_[vertex] = 1;
    for (auto& u : vertex_list_[vertex]) {
      if (colours_[u] == 0) {
        TopSortDfs(u);
      }
    }
    top_sort_.push_back(vertex);
    colours_[vertex] = 2;
  }

  std::deque<int64_t> TopSort() {
    int64_t size = vertex_list_.size();
    for (int64_t i = 1; i < size; ++i) {
      if (colours_[i] == 0) {
        TopSortDfs(i);
      }
    }
    return top_sort_;
  }

  int64_t Components() {
    TopSort();
    Graph graph_t(size_ - 1);
    for (int64_t i = 1; i < size_; ++i) {
      for (auto& dest : vertex_list_[i]) {
        graph_t.AddForwardEdge(dest, i);
      }
    }
    int64_t component = 0;
    for (int64_t i = size_ - 2; i >= 0; --i) {
      if (graph_t.colours_[top_sort_[i]] == 0) {
        ++component;
        graph_t.Dfs(top_sort_[i], component);
      }
    }
    components_ = graph_t.components_;
    return component;
  }

  void PrintComponents() {
    for (int64_t i = 1; i < size_; ++i) {
      std::cout << components_[i] << " ";
    }
  }

 private:
  int64_t size_;
  std::vector<std::vector<int64_t>> vertex_list_;
  std::vector<int> colours_;
  std::vector<int> components_;
  std::deque<int64_t> top_sort_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n, m;
  std::cin >> n >> m;
  Graph graph(n);
  int64_t vert1, vert2;
  for (int64_t i = 0; i < m; ++i) {
    std::cin >> vert1 >> vert2;
    graph.AddForwardEdge(vert1, vert2);
  }
  std::cout << graph.Components() << "\n";
  graph.PrintComponents();
}