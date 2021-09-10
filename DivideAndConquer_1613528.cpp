#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <climits>
using namespace std;
struct pt {
        int id, x, y;
        pt(int _id, int _x, int _y) {
                id = _id;
                x = _x;
                y = _y;
        }
};
double dist(pt a, pt b) {
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
void splitNodes(vector<pt> nodes, vector<pt> &part1, vector<pt> &part2) {
        int min_x = nodes[0].x, max_x = nodes[0].x, min_y = nodes[0].y, max_y = nodes[0].y;
        for (int i = 1; i < (int)nodes.size(); i++) {
                min_x = min(min_x, nodes[i].x);
                max_x = max(max_x, nodes[i].x);
                min_y = min(min_y, nodes[i].y);
                max_y = max(max_y, nodes[i].y);
        }
        if (max_x - min_x > max_y - min_y) {
                vector<int> x_values;
                for (int i = 0; i < (int)nodes.size(); i++) {
                        x_values.push_back(nodes[i].x);
                }
                sort(x_values.begin(), x_values.end());
                int med_x = x_values[(int)x_values.size() / 2];
                for (int i = 0; i < (int)nodes.size(); i++) {
                        if (nodes[i].x < med_x) part1.push_back(nodes[i]);
                        else part2.push_back(nodes[i]);
                }
        }
        else {
                vector<int> y_values;
                for (int i = 0; i < (int)nodes.size(); i++) {
                        y_values.push_back(nodes[i].y);
                }
                sort(y_values.begin(), y_values.end());
                int med_y = y_values[(int)y_values.size() / 2];
                for (int i = 0; i < (int)nodes.size(); i++) {
                        if (nodes[i].y < med_y) part1.push_back(nodes[i]);
                        else part2.push_back(nodes[i]);
                }
        }
}
void mergeSols(vector<pt> sol1, vector<pt> sol2, vector<pt> &sol) {
        double smallest = INT_MAX;
        int best_i, best_j;
        int n = (int)sol1.size(), m = (int)sol2.size();
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                        pt n1 = sol1[i], n2 = (i + 1 == n) ? sol1[0] : sol1[i + 1];
                        pt n3 = sol2[j], n4 = (j + 1 == m) ? sol2[0] : sol2[j + 1];
                        double delta = min(dist(n1, n3) + dist(n2, n4) - dist(n1, n2) - dist(n3, n4), dist(n1, n4) + dist(n2, n3) - dist(n1, n2) - dist(n3, n4));
                        if (delta < smallest) {
                                smallest = delta;
                                best_i = i;
                                best_j = j;
                        }
                }
        }
        pt n1 = sol1[best_i], n2 = (best_i + 1 == n) ? sol1[0] : sol1[best_i + 1];
        pt n3 = sol2[best_j], n4 = (best_j + 1 == m) ? sol2[0] : sol2[best_j + 1];
        int cur = best_i + 1;
        for (int i = 0; i < n; i++) {
                sol.push_back(sol1[(cur + i) % n]);
        }
        if (dist(n1, n3) + dist(n2, n4) < dist(n1, n4) + dist(n2, n3)) {
                cur = best_j;
                for (int i = 0; i < m; i++) {
                        sol.push_back(sol2[(cur - i + m) % m]);
                }
        }
        else {
                cur = best_j + 1;
                for (int i = 0; i < m; i++) {
                        sol.push_back(sol2[(cur + i) % m]);
                }
        }
}
vector<pt> solveTSP(vector<pt> nodes) {
        if ((int)nodes.size() <= 2) {
                vector<pt> sol = nodes;
                return sol;
        }
        vector<pt> part1, part2;
        splitNodes(nodes, part1, part2);
        vector<pt> sol1 = solveTSP(part1);
        vector<pt> sol2 = solveTSP(part2);
        vector<pt> sol;
        mergeSols(sol1, sol2, sol);
        return sol;
}
int main() {
        FILE* file_coords = fopen("att48_xy.txt", "r");
        int N = 0; 
        vector<pt> nodes;
        int x, y;
        while (fscanf_s(file_coords, "%d %d", &x, &y) == 2) {
                nodes.emplace_back(N + 1, x, y);
                N += 1;
        }
        printf("Input finished! Nodes: %d\n", N);
        vector<pt> solution = solveTSP(nodes);
        double sol = 0;
        for (int i = 0; i < N; i++) {
                if (i + 1 == N) {
                        sol += dist(solution[i], solution[0]);
                }
                else {
                        sol += dist(solution[i], solution[i + 1]);
                }
        }
        printf("Solution found, distance = %.2f\n", sol);
        for (int i = 0; i < N; i++) printf("%d ", solution[i].id);
        printf("%d\n", solution[0].id);
        system("pause");
        return 0;
}
