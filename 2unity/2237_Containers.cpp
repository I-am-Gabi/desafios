#include <stdio.h>
#include <vector>
#include <bitset>
#include <iostream>
#include <map>

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

int min_weight = -1;
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

void process(map<container, vector<container> > path_map, container current_ship) {
  path_map[current_ship] = vector<container>();
  path_map = permute(path_map, current_ship);
  vector<container> adjacent_list = path_map[current_ship];

  for (int i = 0; i < adjacent_list.size(); i++) {
    int w = adjacent_list[i].weight;
    if (min_weight > 0) {
      if (w > min_weight)
        continue;
    }

    printf("weight: %d \n", w);
    int comp = compare(adjacent_list[i].slots);
    if (comp) min_weight = w;

    printf("end: %d \n", comp);
    print(adjacent_list[i].slots);
  }
}

int main() {
  map<container, vector<container> > path_map;

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

  print(s.slots);

  process(path_map, s);

  return 0;
}
