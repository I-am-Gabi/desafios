#include <stdio.h>
#include <vector>
#include <bitset>
#include <queue>
/*
 * Codigo nao validado
 */
using namespace std;
int max_distance = 0;

int bfs(int u, vector<vector<int> > adjacent_list) {
  unsigned long vertices = adjacent_list.size();
  int max_node = 0;

  queue<int> queue;

  vector<int> visited;
  visited.assign(vertices, 0);

  vector<int> distance;
  distance.assign(vertices, -1);

  visited[u] = 1;
  distance[u] = 0;
  queue.push(u);

  while(!queue.empty()) {
    int u = queue.front();
    queue.pop();
    for (int i = 0; i < (int) adjacent_list[u].size(); i++) {
      int v = adjacent_list[u][i];
      if (!visited[v]) {
        visited[v] = 0;
        distance[v] = distance[u] + 1;
        if (distance[v] > max_distance) {
          max_distance = distance[v];
          max_node = v;
        }
        queue.push(v);
      }
    }
  }

  return max_node;
}

int main() {
  int nodes, u, v;

  scanf("%d", &nodes);

  vector<vector<int> > adjacent_list;
  adjacent_list.assign(nodes, vector<int>());

  while (--nodes) {
    scanf("%d %d", &u, &v);
    --u, --v;
    adjacent_list[u].push_back(v);
  }


  int max_node = bfs(0, adjacent_list);
  bfs(max_node, adjacent_list);
  printf("%d\n", max_distance);
  return 0;
}
