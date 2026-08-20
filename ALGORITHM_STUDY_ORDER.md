# 알고리즘 기억 복원 순서

이 문서의 목적은 코드를 통째로 외우는 것이 아니라, 문제를 보았을 때 **어떤 상태를 저장하고 어떤 불변식을 유지해야 하는지** 다시 떠올리게 하는 것이다.

> 수서역에 도착했다는 사실보다, 지하철과 버스 중 어떤 방법을 선택했고 왜 그 방법이 맞았는지를 복원한다.

## 한 알고리즘을 다시 익히는 반복 루프

1. 해당 폴더의 `CORE.md`를 읽고, 코드를 보지 않은 채 핵심 상태와 불변식을 한 문장으로 말한다.
2. 종이나 빈 파일에 **함수 이름과 작성 순서만** 적는다.
3. `CORE.md`의 최소 골격을 보고 한 번 작성한다.
4. 폴더의 대표 본인 코드와 비교하며 상태, 경계, 복잡도 차이만 표시한다.
5. 코드를 닫고 다시 작성한다. 두 번 연속으로 되면 다음 항목으로 간다.
6. [코드가 없는 기존 해결 문제](MISSING_SOLVED_NON_BRONZE.md)에서 관련 문제 하나를 골라, 예전 코드를 찾지 않고 다시 풀어 본다.

## 통과 기준

다음 다섯 가지를 코드 없이 설명할 수 있으면 해당 알고리즘을 일단 복원한 것으로 본다.

- 언제 사용하는가?
- 무엇을 상태로 저장하는가?
- 반복문 한 바퀴 후에 무엇이 참인가?
- 정답이 되는 이유는 무엇인가?
- 시간·메모리 복잡도는 어떻게 되는가?

---

## 1단계 — 문법과 상태 흐름 다시 잡기

복잡한 정답 증명보다 입력, 상태 갱신, 경계 처리 감각을 먼저 복원한다.

- [ ] [implementation](TAG/10_IMPLEMENTATION/implementation/CORE.md)
- [ ] [simulation](TAG/10_IMPLEMENTATION/simulation/CORE.md)
- [ ] [math](TAG/07_MATH/math/CORE.md)
- [ ] [string](TAG/06_STRING/string/CORE.md)
- [ ] [sorting](TAG/08_TECHNIQUE/sorting/CORE.md)

**체크포인트:** 인덱스 범위와 자료형을 스스로 결정하고, 작은 시뮬레이션을 디버거 없이 작성한다.

## 2단계 — 선형 자료를 흐르게 하기

배열을 한 방향으로 읽으며 상태를 쌓고, 빼고, 줄이는 방법을 익힌다.

- [ ] [prefix_sum](TAG/08_TECHNIQUE/prefix_sum/CORE.md)
- [ ] [two_pointer](TAG/05_SEARCH/two_pointer/CORE.md)
- [ ] [stack](TAG/03_DATA_STRUCTURE/stack/CORE.md)
- [ ] [monotone_stack](TAG/03_DATA_STRUCTURE/monotone_stack/CORE.md)
- [ ] [queue](TAG/03_DATA_STRUCTURE/queue/CORE.md)
- [ ] [deque](TAG/03_DATA_STRUCTURE/deque/CORE.md)
- [ ] [priority_queue](TAG/03_DATA_STRUCTURE/priority_queue/CORE.md)
- [ ] [set_map](TAG/03_DATA_STRUCTURE/set_map/CORE.md)
- [ ] [linked_list](TAG/03_DATA_STRUCTURE/linked_list/CORE.md)

**체크포인트:** 각 자료구조에서 어떤 원소가 먼저 나오는지와, 원소 하나가 몇 번 들어가고 나오는지를 설명한다.

## 3단계 — 탐색 공간 줄이기

정답 후보를 어떻게 만들고 제거하는지에 집중한다.

- [ ] [bruteforce](TAG/05_SEARCH/bruteforce/CORE.md)
- [ ] [recursion](TAG/09_PARADIGM/recursion/CORE.md)
- [ ] [backtracking](TAG/05_SEARCH/backtracking/CORE.md)
- [ ] [bitmask](TAG/08_TECHNIQUE/bitmask/CORE.md)
- [ ] [binary_search](TAG/05_SEARCH/binary_search/CORE.md)
- [ ] [coordinate_compression](TAG/08_TECHNIQUE/coordinate_compression/CORE.md)
- [ ] [greedy](TAG/09_PARADIGM/greedy/CORE.md)
- [ ] [divide_and_conquer](TAG/09_PARADIGM/divide_and_conquer/CORE.md)

**체크포인트:** 완전 탐색, 가지치기, 이분 탐색, 탐욕 선택이 각각 정답인 이유를 한 문장으로 설명한다.

## 4단계 — DP의 상태와 전이 복원하기

DP 테이블 모양을 먼저 외우지 말고, `dp[상태]` 문장을 먼저 정의한다.

- [ ] [dp](TAG/01_DP/dp/CORE.md)
- [ ] [knapsack](TAG/01_DP/knapsack/CORE.md)
- [ ] [lis](TAG/01_DP/lis/CORE.md)
- [ ] [lcs](TAG/01_DP/lcs/CORE.md)
- [ ] [tsp](TAG/01_DP/tsp/CORE.md)
- [ ] [hirschberg](TAG/01_DP/hirschberg/CORE.md)

**체크포인트:** 상태, 전이, 기뱃값, 계산 순서를 코드 전에 적고 그대로 구현한다. `hirschberg`는 LCS와 분할 정복이 편안해진 뒤에 본다.

## 5단계 — 그래프의 순서와 연결성 복원하기

먼저 순회를 복원하고, 그 위에 트리·최단 경로·연결 요소 알고리즘을 쌓는다.

- [ ] [graph_traversal](TAG/02_GRAPH/graph_traversal/CORE.md)
- [ ] [dfs](TAG/02_GRAPH/dfs/CORE.md)
- [ ] [bfs](TAG/02_GRAPH/bfs/CORE.md)
- [ ] [tree](TAG/02_GRAPH/tree/CORE.md)
- [ ] [union_find](TAG/02_GRAPH/union_find/CORE.md)
- [ ] [mst](TAG/02_GRAPH/mst/CORE.md)
- [ ] [dijkstra](TAG/02_GRAPH/dijkstra/CORE.md)
- [ ] [zero_one_bfs](TAG/02_GRAPH/zero_one_bfs/CORE.md)
- [ ] [floyd_warshall](TAG/02_GRAPH/floyd_warshall/CORE.md)
- [ ] [topological_sort](TAG/02_GRAPH/topological_sort/CORE.md)
- [ ] [lca](TAG/02_GRAPH/lca/CORE.md)
- [ ] [articulation_point](TAG/02_GRAPH/articulation_point/CORE.md)
- [ ] [scc](TAG/02_GRAPH/scc/CORE.md)
- [ ] [two_sat](TAG/02_GRAPH/two_sat/CORE.md)
- [ ] [bipartite_matching](TAG/02_GRAPH/bipartite_matching/CORE.md)

**체크포인트:** 간선을 보는 순서, 방문 완료의 시점, 갱신되는 값이 무엇인지를 각 알고리즘별로 비교한다.

## 6단계 — 구간 질의와 고급 자료구조

단순한 배열을 어떤 정보로 요약하면 질의가 빨라지는지를 이해한 후 구현한다.

- [ ] [trie](TAG/03_DATA_STRUCTURE/trie/CORE.md)
- [ ] [bitset](TAG/03_DATA_STRUCTURE/bitset/CORE.md)
- [ ] [segment_tree](TAG/03_DATA_STRUCTURE/segment_tree/CORE.md)
- [ ] [inversion_counting](TAG/08_TECHNIQUE/inversion_counting/CORE.md)
- [ ] [merge_sort_tree](TAG/03_DATA_STRUCTURE/merge_sort_tree/CORE.md)
- [ ] [persistent_segment_tree](TAG/03_DATA_STRUCTURE/persistent_segment_tree/CORE.md)
- [ ] [mo](TAG/03_DATA_STRUCTURE/mo/CORE.md)
- [ ] [segment_tree_beats](TAG/03_DATA_STRUCTURE/segment_tree_beats/CORE.md)
- [ ] [splay_tree](TAG/03_DATA_STRUCTURE/splay_tree/CORE.md)

**체크포인트:** 각 노드가 표현하는 구간과 정보, `merge/apply/push`의 의미, 질의당 복잡도를 설명한다.

## 7단계 — 수학 도구 복원하기

공식을 외우기 전에 그 공식이 어떤 반복 계산을 줄이는지 확인한다.

- [ ] [number_theory](TAG/07_MATH/number_theory/CORE.md)
- [ ] [combinatorics](TAG/07_MATH/combinatorics/CORE.md)
- [ ] [fast_exponentiation](TAG/07_MATH/fast_exponentiation/CORE.md)
- [ ] [big_integer](TAG/07_MATH/big_integer/CORE.md)

**체크포인트:** 나머지 연산을 언제 하는지, 오버플로가 어디서 나는지, 전처리가 어떤 반복을 없애는지를 확인한다.

## 8단계 — 기하와 스위핑

좌표 공식을 외우기보다 부호와 정렬 기준을 그림으로 검증한다.

- [ ] [geometry](TAG/04_GEOMETRY/geometry/CORE.md)
- [ ] [line_intersection](TAG/04_GEOMETRY/line_intersection/CORE.md)
- [ ] [convex_hull](TAG/04_GEOMETRY/convex_hull/CORE.md)
- [ ] [sweeping](TAG/08_TECHNIQUE/sweeping/CORE.md)

**체크포인트:** CCW의 부호, 공선 처리, 정렬 기준, 이벤트 순서를 작은 좌표로 손으로 검증한다.

## 9단계 — 특수 표현과 문제 독해

정형화된 틀보다 문제의 문장을 조건과 상태로 바꾸는 연습을 한다.

- [ ] [regex](TAG/06_STRING/regex/CORE.md)
- [ ] [ad_hoc](TAG/09_PARADIGM/ad_hoc/CORE.md)

**체크포인트:** 문제의 각 문장을 조건문, 상태, 반례 중 하나로 바꾸어 적는다.

---

## 추천 주기

- 하루에 새 알고리즘은 1~2개만 본다.
- 다음 날: 어제 골격을 코드 없이 다시 적는다.
- 3일 뒤: 대표 문제 하나를 다시 풀어 본다.
- 7일 뒤: `CORE.md`의 자주 틀리는 지점만 보고 다시 구현한다.
- 14일 뒤: 코드가 없는 기존 해결 문제로 복원 여부를 확인한다.

중간에 막히면 순서를 앞으로 돌린다. 막힌 상태에서 뒷단계 템플릿을 외우는 것보다, 바로 앞의 선수 개념을 다시 연결하는 편이 빠르다.
