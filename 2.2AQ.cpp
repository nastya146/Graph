#include <iostream>
#include <vector>
#include <queue>
#include <stack>

struct Edge {
  int64_t begin;
  int64_t end;
};

class Graph {
 public:
  explicit Graph(int64_t n) : size_(n + 1), vertex_list_(size_), colours_(size_, 0), deg_(size_), euler_cycle_() {
  }

  void ForwardAddEdge(int64_t from, int64_t to) {
    vertex_list_[from].push_back(to);
    ++deg_[from].deg_out_;
    ++deg_[to].deg_in_;
  }

  void DfsEulerCycle(int64_t vertex) {
    while (!vertex_list_[vertex].empty()) {
      int64_t other = vertex_list_[vertex].back();
      vertex_list_[vertex].pop_back();
      DfsEulerCycle(other);
    }
    euler_cycle_.push_front(vertex);
  }

  std::deque<int64_t>& Tour() {
    for (int64_t i = 1; i < size_; ++i) {
      if (!vertex_list_[i].empty()) {
        DfsEulerCycle(i);
        break;
      }
    }
    for (int64_t i = 1; i < size_; ++i) {
      if (!vertex_list_[i].empty()) {
        euler_cycle_.clear();
      }
    }
    return euler_cycle_;
  }

 private:
  struct Vertex {
    int64_t deg_in_ = 0;
    int64_t deg_out_ = 0;
  };
  int64_t size_;
  std::vector<std::vector<int64_t>> vertex_list_;
  std::vector<int> colours_;
  std::vector<Vertex> deg_;
  std::deque<int64_t> euler_cycle_;
};

int main() {
  int64_t cycles, squares;
  std::cin >> cycles >> squares;
  Graph graph(squares);
  for (int64_t i = 0; i < cycles; ++i) {
    int64_t k;
    std::cin >> k;
    int64_t from;
    std::cin >> from;
    for (int64_t i = 0; i < k; ++i) {
      int64_t to;
      std::cin >> to;
      graph.ForwardAddEdge(from, to);
      from = to;
    }
  }
  std::deque<int64_t> tour = graph.Tour();
  if (tour.empty()) {
    std::cout << 0;
  } else {
    std::cout << tour.size() << " ";
    for (auto& station : tour) {
      std::cout << station << " ";
    }
  }
}