#include <stdio.h>
#include <vector>
#include <bitset>
#include <iostream>
#include <map>
#include <queue>

/*
 * Gabriela Cavalcante
 * 21/09/2016
 *
1 2 3 4
5 6 7 8
1 2 3 4
6 5 7 8
 */
using namespace std;
#define NUMBER_SIZE 10
#define NEIGHBORS 8

int min_weight = 0;
vector<bitset<NUMBER_SIZE>> final_containers;

struct container {
    vector<bitset<NUMBER_SIZE>> slots;
    int weight;
};
bool operator < (const container &l, const container &r) { return l.weight < r.weight; }

void print(vector<bitset<NUMBER_SIZE>> ship) {
  unsigned long n_containers = 0;
  while(n_containers < NEIGHBORS) {
    printf("%d ", ship[n_containers++]);
    if (n_containers == 4) printf("\n");
  }
  printf("\n\n");
}

container switch_containers(container s, int origin, int destination){
  container new_ship = s;
  bitset<NUMBER_SIZE> tmp = new_ship.slots[destination];
  new_ship.slots[destination] = new_ship.slots[origin];
  new_ship.slots[origin] = tmp;
  int w = (int) (new_ship.slots[destination].to_ulong() + new_ship.slots[origin].to_ulong());
  new_ship.weight += w;
  return new_ship;
}

map<container, vector<container>> permute(map<container, vector<container> > path_map, container s) {
  for(int index = 0; index <= 2; index++) {
    path_map[s].push_back(switch_containers(s, index, index+1));
    path_map[s].push_back(switch_containers(s, index+4, index+5));
  }

  for(int index = 0; index <= 3; index++) {
    path_map[s].push_back(switch_containers(s, index, index+4));
  }

  return path_map;
}

bool compare(vector<bitset<NUMBER_SIZE>> slot) {
  int n_containers = 0;

  while(n_containers < NEIGHBORS)
    if (slot[n_containers] != final_containers[n_containers++]) return false;

  return true;
}

void process(container current_ship) {
  map<container, vector<container> > path_map;
  queue<container> queue;

  queue.push(current_ship);
  int cont = 0;

  while(!queue.empty()) {
    container c = queue.front();
    queue.pop();

    int w = c.weight;

    if (min_weight > 0) {
      if (w >= min_weight)
        continue;
    }

    //printf("weight: %d \n", c.weight);
    //print(c.slots);

    path_map[c] = vector<container>();
    path_map = permute(path_map, c);
    vector<container> adjacent_list = path_map[c];



    int comp = compare(c.slots);
    if (comp && (w < min_weight || min_weight == 0)) {
      min_weight = w;
      printf("weight: %d \n", c.weight);
      print(c.slots);
      continue;
    }

    for (int i = 0; i < (int) adjacent_list.size(); i++) {
      container v = adjacent_list[i];
      queue.push(v);
    }
  }

  return;
}

int main() {
  container s;
  s.slots = vector<bitset<NUMBER_SIZE>>();
  final_containers = vector<bitset<NUMBER_SIZE>>();


  unsigned long n_containers = 0;

  while(n_containers++ < NEIGHBORS) {
    int container;
    scanf("%d", &container);
    bitset<NUMBER_SIZE> b(container);
    s.slots.push_back(b);
  }

  n_containers = 0;
  while(n_containers++ < NEIGHBORS) {
    int container;
    scanf("%d", &container);
    bitset<NUMBER_SIZE> b(container);
    final_containers.push_back(b);
  }

  process(s);

  printf("%d", min_weight);

  return 0;
}
