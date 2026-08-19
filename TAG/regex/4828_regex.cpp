#include <iostream>
#include <regex>
#include <stack>
#include <string>
using namespace std;

string line;
void init() {}

void solve() {

    while (getline(cin, line)) {
        // 태그만 미리 빼놓자
        // &lt;,&gt;,&amp;
        regex gt("&(amp|gt|lt);");
        //&xHEX
        regex hex_reg("&x[0-9a-fA-F]+;");
        // <tag/>
        regex tag_slash("<[a-z0-9]+/>");
        // <tag></tag>
        regex tag("</?.[^>]*>");
        bool invalidHex = false;
        stack<string> s;
        smatch tag_str;
        string copy_line = line; // 무한루프때문에 계속 넘겨줘야함

        while (regex_search(copy_line, tag_str, tag)) {
            //cout << tag_str.str();
            if (tag_str.str()[1] != '/') {
                for (int i = 1; i < tag_str.str().size() - 2; i++) {
                    char a = tag_str.str()[i];
                    if (!((a >= 'a' && a <= 'z') || (a >= '0' && a <= '9'))) {

                        cout << "invalid\n";
                        goto Invalid;
                    }
                }
                char a = tag_str.str()[tag_str.str().size() - 2];
                if (a == '/') {
                    copy_line = tag_str.suffix();
                    continue;
                }
                if (!((a >= 'a' && a <= 'z') || (a >= '0' && a <= '9'))) {

                    cout << "invalid\n";
                    goto Invalid;
                }
                s.push(regex_replace(tag_str.str(), regex("[<>/]"), ""));
            } else {
                for (int i = 2; i < tag_str.str().size() - 1; i++) {
                    char a = tag_str.str()[i];
                    if (!((a >= 'a' && a <= 'z') || (a >= '0' && a <= '9'))) {
                        cout << "invalid\n";
                        goto Invalid;
                    }
                }
                string closed = regex_replace(tag_str.str(), regex("[<>/]"), "");
                if (s.empty()) {
                    cout << "invalid\n";
                    goto Invalid;
                }
                if (s.top() != closed) {
                    cout << "invalid\n";
                    goto Invalid;
                }
                s.pop();
            }
            copy_line = tag_str.suffix(); // 이게 다음검색하게 해주는거
        }

        // 아니면 <안에 특수있는애들 다 빼버려

        line = regex_replace(line, gt, "");

        for (sregex_iterator it(line.begin(), line.end(), hex_reg), end_it; it != end_it; ++it) {
            string hexStr = it->str();
            if (hexStr.size() % 2 == 0) { // 길이가 짝수면 잘못된 경우
                cout << "invalid\n";
                invalidHex = true;
                break;
            }
        }
        if (invalidHex) {
            continue;
        }
        line = regex_replace(line, hex_reg, "");

        line = regex_replace(line, tag_slash, "");

        if (!s.empty()) {
            cout << "invalid\n";
            continue;
        }

        line = regex_replace(line, tag, "");

        // total check
        for (auto a : line) {
            if (a == '<' || a == '>' || a == '&') {
                cout << "invalid\n";
                goto Invalid;
            }
        }
        cout << "valid\n";
    Invalid:;
        // 반복문안의 반복문을 빠져나오기 위함
        line.clear();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}