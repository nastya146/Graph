#include <iostream>
#include <vector>
#include <queue>
#include <stack>

class Graph {
 public:
  explicit Graph(int64_t n) : vertex_list_(n + 1), flag_(n, false) {
  }

  void AddEdge(int64_t vertex1, int64_t vertex2) {
    vertex_list_[vertex1].push_back(vertex2);
    vertex_list_[vertex2].push_back(vertex1);
  }

  bool BFS(std::vector<int64_t>& colours, int64_t begin) const {
    std::queue<int64_t> queue;
    queue.push(begin);
    int64_t size = vertex_list_.size();
    std::vector<bool> flag(size, false);
    flag[begin] = true;
    colours[begin] = 1;
    while (!queue.empty()) {
      int64_t v = queue.front();
      queue.pop();
      for (auto& u : vertex_list_[v]) {
        if (!flag[u]) {
          colours[u] = (colours[v] == 1 ? 2 : 1);
          flag[u] = true;
          queue.push(u);
        } else {
          if (colours[v] == colours[u]) {
            return false;
          }
        }
      }
    }
    return true;
  }

  std::vector<int64_t> BFS(int64_t begin) {
    std::queue<int64_t> queue;
    queue.push(begin);
    int64_t size = vertex_list_.size();
    std::vector<bool> flag(size, false);
    std::vector<int64_t> dist(size);
    std::vector<int64_t> prev(size);
    flag[begin] = true;
    prev[begin] = 0;
    while (!queue.empty()) {
      int64_t v = queue.front();
      queue.pop();
      for (auto& u : vertex_list_[v]) {
        if (!flag[u]) {
          flag[u] = true;
          queue.push(u);
          dist[u] = dist[v] + 1;
          prev[u] = v;
        }
      }
    }
    return prev;
  }

  std::deque<int64_t> Path(int64_t begin, int64_t end) {
    std::vector<int64_t> prev = BFS(begin);
    std::deque<int64_t> path;
    int64_t prev_v = prev[end];
    path.push_front(end);
    while (prev_v != 0) {
      path.push_front(prev_v);
      prev_v = prev[prev_v];
    }
    return path;
  }

 private:
  std::vector<std::vector<int64_t>> vertex_list_;
  std::vector<bool> flag_;
};

int main() {
  int64_t n, m;
  std::cin >> n >> m;
  int64_t begin, end;
  std::cin >> begin >> end;
  Graph graph(n);
  for (int64_t i = 0; i < m; ++i) {
    int64_t vertex1, vertex2;
    std::cin >> vertex1 >> vertex2;
    graph.AddEdge(vertex1, vertex2);
  }
  if (begin == end) {
    std::cout << 0 << '\n' << begin;
    return 0;
  }
  std::deque<int64_t> path = graph.Path(begin, end);
  if (path.size() == 1) {
    std::cout << -1;
  } else {
    std::cout << path.size() - 1 << "\n";
    for (auto& vertex : path) {
      std::cout << vertex << " ";
    }
  }
}