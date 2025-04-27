#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string generate_string(ll N) {
    string result = "";
    
    for (ll i = 0; i < N; i++) {
        result += "uw";
    }

    for (ll i = 0; i < N; i++) {
        result += "u";
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    while(T--) {
        ll N;
        cin >> N;

        cout << generate_string(N) << "\n";
    }

    return 0;
}

