#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


vector<int> computeTotients(int limit) {
    vector<int> phi(limit + 1);
    for (int i = 0; i <= limit; i++)
        phi[i] = i;
    
    for (int i = 2; i <= limit; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= limit; j += i)
                phi[j] -= phi[j] / i;
        }
    }
    return phi;
}


vector<int> getPrimeFactors(int num) {
    vector<int> primes;
    if (num % 2 == 0) {
        primes.push_back(2);
        while (num % 2 == 0) num /= 2;
    }
    for (int f = 3; f * f <= num; f += 2) {
        if (num % f == 0) {
            primes.push_back(f);
            while (num % f == 0) num /= f;
        }
    }
    if (num > 1) primes.push_back(num);
    return primes;
}

long long countMultiples(long long x, const vector<int>& primes) {
    int n = primes.size();
    long long count = 0;
    
    for (int mask = 1; mask < (1 << n); mask++) {
        long long product = 1;
        int bits = 0;
        for (int j = 0; j < n; j++) {
            if (mask & (1 << j)) {
                product *= primes[j];
                bits++;
            }
        }
        if (bits % 2 == 1)
            count += x / product;
        else
            count -= x / product;
    }
    return count;
}


long long countCoprimes(long long x, int s, const vector<int>& primes) {
    return x - countMultiples(x, primes);
}

int main() {
	cout << "---------------------------------------------------------------------------------"<< endl;
    cout << "Welcome to Big Brother Ben Problem!" << endl; 
    cout << "Enter number of test cases followed by each test case value (house number): " << endl;
    cout << "---------------------------------------------------------------------------------"<< endl;

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    vector<long long> testCases(T);
    long long maxHouse = 0;

    for (int i = 0; i < T; i++) {
        cin >> testCases[i];
        maxHouse = max(maxHouse, testCases[i]);
    }

    const int LIMIT = 70000;
    vector<int> phi = computeTotients(LIMIT);

    vector<long long> cumulative(LIMIT + 1, 0);
    for (int s = 2; s <= LIMIT; s++) {
        cumulative[s] = cumulative[s - 1] + phi[s];
    }

    cout << "\n?? Your coordinates are:\n";
    for (size_t i = 0 ; i < testCases.size(); ++i) {
        long long houseNum = testCases[i];
        int s = 2;
        int low = 2, high = LIMIT;
        while (low < high) {
            int mid = (low + high) / 2;
            if (cumulative[mid] < houseNum)
                low = mid + 1;
            else
                high = mid;
        }
        s = low;

        long long housesBefore = cumulative[s - 1];
        long long indexInShell = houseNum - housesBefore;

        vector<int> primeFactors = getPrimeFactors(s);
        int xLow = 1, xHigh = s - 1, x;

        while (xLow <= xHigh) {
            int mid = (xLow + xHigh) / 2;
            if (countCoprimes(mid, s, primeFactors) < indexInShell)
                xLow = mid + 1;
            else {
                x = mid;
                xHigh = mid - 1;
            }
        }

        int y = s - x;
    
        cout << " House #" << houseNum << " is at coordinates: (" << x << ", " << y << ")\n";
    }

    return 0;
}

