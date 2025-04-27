#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N;
        cin >> N;
        double x, y;
        double minx = 1e9, maxx = -1e9;
        double miny = 1e9, maxy = -1e9;

        // Read all points and update extrema
        for (int i = 0; i < N; ++i) {
            cin >> x >> y;
            minx = min(minx, x);
            maxx = max(maxx, x);
            miny = min(miny, y);
            maxy = max(maxy, y);
        }

        double width  = maxx - minx;
        double height = maxy - miny;
        double area   = width * height;

        cout << fixed << setprecision(10); << area;
        if (T) cout << endl;
    }
    return 0;
}

