// 병사관리

struct Node {
    int mTeam;
    int mScore;
    int mID;
    Node *prev;
    Node *next;
};

Node soldier[1000001], head[6][6], tail[6][6]; // mteam,mscore

void init() {
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            head[i][j].next = &tail[i][j];
            tail[i][j].prev = &head[i][j];
        }
    }
}

void hire(int mID, int mTeam, int mScore) {
    soldier[mID].mTeam = mTeam;
    soldier[mID].mScore = mScore;
    soldier[mID].mID = mID;

    soldier[mID].next = head[mTeam][mScore].next;
    soldier[mID].prev = soldier[mID].next->prev;
    head[mTeam][mScore].next = &soldier[mID];
    soldier[mID].next->prev = &soldier[mID];
}

void updateSoldier(int mID, int mScore) {
    soldier[mID].mScore = mScore;

    soldier[mID].next->prev = soldier[mID].prev;
    soldier[mID].prev->next = soldier[mID].next;

    int team = soldier[mID].mTeam;
    soldier[mID].next = head[team][mScore].next;
    soldier[mID].prev = soldier[mID].next->prev;
    head[team][mScore].next = &soldier[mID];
    soldier[mID].next->prev = &soldier[mID];
}
void fire(int mID) {
    soldier[mID].next->prev = soldier[mID].prev;
    soldier[mID].prev->next = soldier[mID].next;
}

void updateTeam(int mTeam, int mChangeScore) {
    if (mChangeScore == 0)
        return;

    if (mChangeScore > 0) {
        // a + mChangeScore >= 5
        // a >= 5 - mChangeScore
        // 연결
        // 꼬리'.p.n -> 머리.n
        // 꼬리'.p -> 꼬리.p
        for (int i = 4; i >= 5 - mChangeScore; i--) {
            tail[mTeam][5].prev->next = head[mTeam][i].next;
            head[mTeam][i].next->prev = tail[mTeam][5].prev;

            tail[mTeam][5].prev = tail[mTeam][i].prev;
            tail[mTeam][i].prev->next = &tail[mTeam][5];
        }
        // shift
        for (int i = 4 - mChangeScore; i > 0; i--) {
            int nextScore = i + mChangeScore;
            head[mTeam][nextScore].next = head[mTeam][i].next;
            head[mTeam][i].next->prev = &head[mTeam][nextScore];
            tail[mTeam][nextScore].prev = tail[mTeam][i].prev;
            tail[mTeam][i].prev->next = &tail[mTeam][nextScore];
        }
        for (int i = 1; i < mChangeScore + 1; i++) {
            head[mTeam][i].next = &tail[mTeam][i];
            tail[mTeam][i].prev = &head[mTeam][i];
        }
    } else {
        // a-mChangeScore <= 1
        // a <= 1 + m
        mChangeScore = -mChangeScore;
        for (int i = 2; i <= 1 + mChangeScore; i++) {
            tail[mTeam][1].prev->next = head[mTeam][i].next;
            head[mTeam][i].next->prev = tail[mTeam][1].prev;

            tail[mTeam][1].prev = tail[mTeam][i].prev;
            tail[mTeam][i].prev->next = &tail[mTeam][1];
        }
        // shift
        for (int i = 2 + mChangeScore; i < 6; i++) {
            int nextScore = i - mChangeScore;
            head[mTeam][nextScore].next = head[mTeam][i].next;
            head[mTeam][i].next->prev = &head[mTeam][nextScore];
            tail[mTeam][nextScore].prev = tail[mTeam][i].prev;
            tail[mTeam][i].prev->next = &tail[mTeam][nextScore];
        }
        for (int i = 5; i > 5 - mChangeScore; i--) {
            head[mTeam][i].next = &tail[mTeam][i];
            tail[mTeam][i].prev = &head[mTeam][i];
        }
    }
}

int bestSoldier(int mTeam) {
    for (int i = 5; i >= 1; i--) {
        if (head[mTeam][i].next == &tail[mTeam][i])
            continue;
        int answer = 0;
        Node *cur = &head[mTeam][i];
        while (cur->next != &tail[mTeam][i]) {
            cur = cur->next;
            answer = (answer > cur->mID) ? answer : cur->mID;
        }
        return answer;
    }
    return -1;
}