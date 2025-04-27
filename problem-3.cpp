#include <iostream>
#include <string>
using namespace std;

void solve() {
    int P;
    cin >> P;
    int primogems = P;
    
    for (int i = 0; i < 180; ++i) { // maximum 180 tries
        if (primogems >= 160) {
            cout << "wish" << endl;
            string res;
            cin >> res;
            if (res == "baizhu") {
                break;
            }
            primogems -= 160;
        } else {
            cout << "buy" << endl;
            string res;
            cin >> res;
            primogems += 60;
            // no decrement of i here, we continue in the next loop
        }
    }
}

int main() {
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        solve();
    }
    return 0;
}

