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

void movement_aux(int dist, std::vector<coord>& c, std::set<coord>& used) {
    for (int j = 1; j < 10; j++) {
        if (needs_to_move(c[j - 1], c[j])) {
            c[j] = where_to_move(c[j - 1], c[j]);
        }
        else break;
        used.insert(c.back());
    }
}

void movement(char dir, int dist, std::vector<coord> &c, std::set<coord>& used) {
    for (int i = 0; i < dist; i++) {
        switch (dir) {
        case 'U':
            c.front().y++;
            movement_aux(dist, c, used);
            break;
        case 'D':
            c.front().y--;
            movement_aux(dist, c, used);
            break;
        case 'L':
            c.front().x--;
            movement_aux(dist, c, used);
            break;
        case 'R':
            c.front().x++;
            movement_aux(dist, c, used);
            break;
        }
    }
}

void process_data(std::vector<std::string> vec) {
    std::vector<coord> coords(10);
    std::set<coord> used_positions;
    used_positions.insert(coords.back());
    for (auto it : vec) {
        auto s = split<std::string>(it, " ");
        char dir = s[0][0];
        int dist = std::stoi(s[1]);
        movement(dir, dist, coords, used_positions);
    }
    std::cout << "B: " << used_positions.size() << std::endl;
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
