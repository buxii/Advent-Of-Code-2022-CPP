#include "split.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <set>
#include <vector>

struct coord {
    int x = 0;
    int y = 0;

    // Fem operator < perquè en el set compara < per ordenarlos
    bool operator<(const coord& other) const {
        if (x == other.x) {
            return y < other.y;
        }
        return x < other.x;
    }
};

bool needs_to_move(const coord h, const coord t) {
    return abs(h.x - t.x) > 1 || abs(h.y - t.y) > 1;
}

coord where_to_move(const coord h, const coord t) {
    coord pos = t;
    if (h.y == t.y) {
        if (h.x > t.x)
            pos.x++;
        else
            pos.x--;
    }
    else if (h.y > t.y) {
        if (h.x > t.x) {
            pos.x++;
            pos.y++;
        }
        else if (h.x < t.x) {
            pos.x--;
            pos.y++;
        }
        else {
            pos.y++;
        }
    }
    else {
        if (h.x < t.x) {
            pos.x--;
            pos.y--;
        }
        else if (h.x > t.x) {
            pos.x++;
            pos.y--;
        }
        else {
            pos.y--;
        }
    }

    return pos;
}

void movement(char dir, int dist, coord& head, coord& tail,
    std::set<coord>& used) {
    switch (dir) {
    case 'U':
        for (int i = 0; i < dist; ++i) {
            head.y++;
            if (needs_to_move(head, tail)) {
                tail = where_to_move(head, tail);
            }
            used.insert(tail);
        }
        break;
    case 'D':
        for (int i = 0; i < dist; ++i) {
            head.y--;
            if (needs_to_move(head, tail)) {
                tail = where_to_move(head, tail);
            }
            used.insert(tail);
        }
        break;
    case 'L':
        for (int i = 0; i < dist; ++i) {
            head.x--;
            if (needs_to_move(head, tail)) {
                tail = where_to_move(head, tail);
            }
            used.insert(tail);
        }
        break;
    case 'R':
        for (int i = 0; i < dist; ++i) {
            head.x++;
            if (needs_to_move(head, tail)) {
                tail = where_to_move(head, tail);
            }
            used.insert(tail);
        }
        break;
    }
}

void process_data(std::vector<std::string> vec) {
    coord head, tail, start;
    std::set<coord> used_positions;
    used_positions.insert(start);
    for (auto it : vec) {
        auto s = split<std::string>(it, " ");
        char dir = s[0][0];
        int dist = std::stoi(s[1]);
        movement(dir, dist, head, tail, used_positions);
    }
    std::cout << "A: " << used_positions.size() << std::endl;
}

void llegir_fitxer(std::ifstream& f) {
    if (f.is_open()) {
        std::vector<std::string> vec;
        while (!f.eof()) {
            std::string temp;
            std::getline(f, temp);
            vec.push_back(temp);
        }
        process_data(vec);
    }
    else
        std::cerr << "ERROR AL OBRIR EL FITXER" << std::endl;
    f.close();
}

int main() {
    std::ifstream f("input.txt");
    llegir_fitxer(f);
    return 0;
}