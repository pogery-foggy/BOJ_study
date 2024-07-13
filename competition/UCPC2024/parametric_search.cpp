/*int answer = 0; // 정답 (조건 만족하는 max값)

while (low <= high) { // break문 없이 모든 배열을 탐색한다
    int mid = (low + high) / 2;

    if (isPossible(mid)) { // 조건을 만족한다면 길이 늘리기
        if (mid > answer)  // 정답 업데이트
            answer = mid;
        low = mid + 1;
    } else { // 조건 만족하지 않으면 길이 줄이기
        high = mid - 1;
    }
} */