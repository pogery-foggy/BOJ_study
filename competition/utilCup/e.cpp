#include <iostream>

using namespace std;

int d[100001];
int vault[5]; // 1 2 3 4
int N;

void init() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> d[i];
    }
}

int take_gold(int a) {
    if (35 <= a && a < 65)
        return 1;
    else if (65 <= a && a < 95)
        return 2;
    else if (95 <= a && a < 125)
        return 3;
    else if (125 <= a)
        return 4;
    else
        return 0;
}

void solve() {
    bool new_game = false;
    int time = 0, point = 0, flow_time = 4, throw_point = 1;

    for (int i = 0; i < N; i++) {
        if (time > 240)
            new_game = true;
        if (new_game) {
            vault[take_gold(point)]++;
            time = 0;
            point = 0;
            flow_time = 4;
            throw_point = 1;
            new_game = false;
        }
        // init
        int cur = d[i];
        switch (cur) {
        case 1:
            new_game = true;
            continue;
        case 2:
            if (throw_point > 1)
                throw_point /= 2;
            else
                flow_time += 2;
            break;
        case 3:
            break;
        case 4:
            time += 56;
            break;
        case 5:
            if (flow_time > 1)
                flow_time -= 1;
            break;
        case 6:
            if (throw_point < 32)
                throw_point *= 2;
            break;
        default:
            break;
        }
        time += flow_time;
        point += throw_point;
    }

    if (new_game)
        vault[take_gold(point)]++;
    for (int i = 1; i < 5; i++) {
        cout << vault[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}