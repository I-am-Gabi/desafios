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
0 1 2 3
5 4 6 7

 */
using namespace std;
#define WORD 24
#define BLOCK 3
#define NEIGHBORS 8

int min_weight = 0;
vector<bitset<10>> final_containers;
vector<bitset<10>> initial_containers;

int index_map[8];

struct container {
    bitset<WORD> slots;
    int weight;
};
bool operator < (const container &l, const container &r) { return l.weight < r.weight; }

bitset<WORD> set(int position, bitset<WORD> value, bitset<WORD> word) {
  bitset<WORD> default_value(7);

  value <<= position * BLOCK;
  default_value <<= position * BLOCK;

  word = ((~default_value)&word);
  return (value|word);
}

bitset<WORD> getBit(bitset<WORD> byte, int pos) {
  return (((byte >> (pos * BLOCK)) << (7 * BLOCK)) >> (7 * BLOCK));
}

container switch_containers(container s, int origin, int destination){
  container new_ship = s;
  int o = getBit(new_ship.slots, origin).to_ulong();
  int d = getBit(new_ship.slots, destination).to_ulong();

  new_ship.slots = set(origin, d, new_ship.slots);
  new_ship.slots = set(destination, o, new_ship.slots);
  int w = index_map[getBit(new_ship.slots, destination).to_ulong()] + index_map[getBit(new_ship.slots, origin).to_ulong()];
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


void print(vector<bitset<10>> ship) {
  unsigned long n_containers = 0;
  while(n_containers < NEIGHBORS) {
    printf("%d ", ship[n_containers++]);
    if (n_containers == 4) printf("\n");
  }
  printf("\n\n");
}

void print(bitset<WORD> ship) {
  int n_containers = 0;
  while(n_containers < NEIGHBORS) {
    cout << getBit(ship, n_containers++).to_ulong() << ' ';
    if (n_containers == 4) printf("\n");
  }
  printf("\n\n");
}

bool compare(bitset<WORD> slot) {
  int n_containers = 0;

  while(n_containers < NEIGHBORS) {
    if (getBit(slot, n_containers).to_ulong() != final_containers[n_containers++].to_ulong()) return false;
  }
  return true;
}

void process(container c){
  map<container, vector<container> > path_map;
  queue<container> queue;

  queue.push(c);
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
      continue;
    }

    for (int i = 0; i < (int) adjacent_list.size(); i++) {
      container v = adjacent_list[i];
      queue.push(v);
    }
  }
}

void create_map() {
  for (int i = 0; i < NEIGHBORS; i++) {
    index_map[i] = (int) initial_containers[i].to_ulong();
  }
}


int main() {
  container s;
  s.slots = bitset<WORD>();

  for (int i = 0; i < NEIGHBORS; i++) {
    bitset<WORD> value(i);
    s.slots = set(i, value, s.slots);
  }

  unsigned long n_containers = 0;

  while(n_containers++ < NEIGHBORS) {
    int container;
    scanf("%d", &container);
    bitset<10> b(container);
    initial_containers.push_back(b);
  }
  create_map();

  n_containers = 0;
  while(n_containers++ < NEIGHBORS) {
    int container;
    scanf("%d", &container);
    bitset<10> b(container);
    final_containers.push_back(b);
  }

  process(s);

  printf("-- %d", min_weight);

  return 0;
}


