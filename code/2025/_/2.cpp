#include <iostream>
#include <vector>

#define MAX_N 1000
#define MAX_M 20

using namespace std;

int n, m;
int arr[MAX_N][MAX_N];
vector<pair<int, int>> v, q(20);
pair<int, int> standard_treasure, base;

struct Result {
    int y, x;
} res;

void init(int N, int M, int Map[MAX_N][MAX_N]) {
    v.clear();
    n = N;
    m = M;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = Map[i][j];
            if (Map[i][j])
                v.emplace_back(i, j);
        }
    }
}

bool check() {
    for (auto &[y, x] : v) {
        if (y < base.first || y + m - base.first > n)
            continue;
        if (x < base.second || x + m - base.second > n)
            continue;
        bool flag = true;
        for (auto &[dy, dx] : q) {
            if (!arr[y + dy][x + dx]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            res = {y + standard_treasure.first, x + standard_treasure.second};
            return true;
        }
    }
    return false;
}

Result findTreasureChest(int Pieces[MAX_M][MAX_M]) {
    q.clear();
    base.first = -1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (!Pieces[i][j])
                continue;
            if (base.first == -1)
                base = {i, j};
            else
                q.emplace_back(i - base.first, j - base.second);
            if (Pieces[i][j] == 9)
                standard_treasure = {i - base.first, j - base.second};
        }
    }
    if (check())
        return res;

    // 90
    q.clear();
    base.first = -1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (!Pieces[m - j - 1][i])
                continue;
            if (base.first == -1)
                base = {i, j};
            else
                q.emplace_back(i - base.first, j - base.second);
            if (Pieces[m - j - 1][i] == 9)
                standard_treasure = {i - base.first, j - base.second};
        }
    }
    if (check())
        return res;

    // 180
    q.clear();
    base.first = -1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (!Pieces[m - i - 1][m - j - 1])
                continue;
            if (base.first == -1)
                base = {i, j};
            else
                q.emplace_back(i - base.first, j - base.second);
            if (Pieces[m - i - 1][m - j - 1] == 9)
                standard_treasure = {i - base.first, j - base.second};
        }
    }
    if (check())
        return res;

    // 270
    q.clear();
    base.first = -1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (!Pieces[j][m - i - 1])
                continue;
            if (base.first == -1)
                base = {i, j};
            else
                q.emplace_back(i - base.first, j - base.second);
            if (Pieces[j][m - i - 1] == 9)
                standard_treasure = {i - base.first, j - base.second};
        }
    }
    if (check())
        return res;

    return res;
}