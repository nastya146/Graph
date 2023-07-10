#include <iostream>
#include <vector>
#include <queue>
#include <stack>

class Graph {
 public:
  Graph(int64_t n, int64_t m) : map_(n * m, -1), n_(n), m_(m) {
  }

  // соседние вершины
  std::vector<int> Neighbours(int64_t i) {
    std::vector<int> neighbours;
    if (i % m_ != 0) {
      neighbours.push_back(i - 1);
    }
    if (i % m_ != m_ - 1) {
      neighbours.push_back(i + 1);
    }
    if (i / m_ != 0) {
      neighbours.push_back(i - m_);
    }
    if (i / m_ != n_ - 1) {
      neighbours.push_back(i + m_);
    }
    return neighbours;
  }

  // расставили сабы
  std::queue<int64_t> MapSab() {
    std::queue<int64_t> queue_of_sabs;
    bool rest;
    int64_t size = n_ * m_;
    for (int64_t i = 0; i < size; ++i) {
      std::cin >> rest;
      if (rest) {
        queue_of_sabs.push(i);
        map_[i] = 0;
      }
    }
    return queue_of_sabs;
  }

  // посчиатли расстояния
  void BFS() {
    std::queue<int64_t> queue = MapSab();
    while (!queue.empty()) {
      int64_t v = queue.front();
      queue.pop();
      std::vector<int> neighbours = Neighbours(v);
      for (auto& u : neighbours) {
        if (map_[u] == -1) {
          map_[u] = map_[v] + 1;
          queue.push(u);
        }
      }
    }
  }

  void Print() {
    for (int64_t i = 0; i < n_; ++i) {
      for (int64_t j = 0; j < m_; ++j) {
        std::cout << map_[i * m_ + j] << " ";
      }
      std::cout << "\n";
    }
  }

 private:
  std::vector<int64_t> map_;
  int n_;
  int m_;
};

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph(n, m);
  graph.BFS();
  graph.Print();
}