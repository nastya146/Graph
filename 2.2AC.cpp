#include <iostream>
#include <vector>
#include <queue>
#include <stack>

class Graph {
 public:
  Graph() : vertex_list_(10000), flag_(10000, false) {
  }

  void AddForwardEdge(int begin, int end) {
    vertex_list_[begin].push_back(end);
  }

  void AddEdge(int u, int v) {
    vertex_list_[u].push_back(v);
    vertex_list_[v].push_back(u);
  }

  bool BFS(std::vector<int>& colours, int begin) const {
    std::queue<int> queue;
    queue.push(begin);
    int size = vertex_list_.size();
    std::vector<bool> flag(size, false);
    flag[begin] = true;
    colours[begin] = 1;
    while (!queue.empty()) {
      int v = queue.front();
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

  void AddEdges(int u) {
    if (u / 1000 < 9) {
      vertex_list_[u].push_back((u / 1000 + 1) * 1000 + u % 1000);
    }
    if (u % 10 > 1) {
      vertex_list_[u].push_back(u - 1);
    }

    vertex_list_[u].push_back((u * 10) % 10000 + u / 1000);
    vertex_list_[u].push_back(u / 10 + (u % 10) * 1000);
  }

  void BuildGraph(int n) {
    std::queue<int> queue;
    queue.push(n);
    flag_[n] = true;
    while (!queue.empty()) {
      int v = queue.front();
      queue.pop();
      AddEdges(v);
      for (auto& u : vertex_list_[v]) {
        if (!flag_[u]) {
          flag_[u] = true;
          queue.push(u);
        }
      }
    }
  }

  void Print() {
    for (int i = 1111; i < 10000; ++i) {
      if (flag_[i]) {
        std::cout << i << ": ";
        for (auto& vertex : vertex_list_[i]) {
          std::cout << vertex << " ";
        }
        std::cout << "\n";
      }
    }
  }

  std::vector<int> BFS(int begin) {
    std::queue<int> queue;
    queue.push(begin);
    int size = vertex_list_.size();
    std::vector<bool> flag(size, false);
    std::vector<int> dist(size);
    std::vector<int> prev(size);
    flag[begin] = true;
    prev[begin] = 0;
    while (!queue.empty()) {
      int v = queue.front();
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

  std::deque<int> Path(int begin, int end) {
    std::vector<int> prev = BFS(begin);
    std::deque<int> path;
    int prev_v = prev[end];
    path.push_front(end);
    while (prev_v != 0) {
      path.push_front(prev_v);
      prev_v = prev[prev_v];
    }
    return path;
  }

 private:
  std::vector<std::vector<int>> vertex_list_;
  std::vector<bool> flag_;
};

int main() {
  int begin, end;
  std::cin >> begin >> end;
  Graph graph;
  graph.BuildGraph(begin);
  std::deque<int> path = graph.Path(begin, end);
  std::cout << path.size() << "\n";
  for (auto& vertex : path) {
    std::cout << vertex << "\n";
  }
}