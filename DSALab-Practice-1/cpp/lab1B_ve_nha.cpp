// =====================================================================
//  LAB 1B (VE NHA) - CHUONG 1: DO PHUC TAP THUAT TOAN
//  Muc do:  1B.1-1B.2 Co ban | 1B.3 Trung binh | 1B.4 Nang cao
//  Bien dich:  g++ -O2 -std=c++17 -Wall -o lab1B lab1B_ve_nha.cpp
// =====================================================================
#include <algorithm>
#include <chrono>
#include <climits>
#include <cmath>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

struct LCG {
    unsigned long long x;
    explicit LCG(unsigned long long seed) : x(seed) {}
    int next() { x = (x * 1103515245ULL + 12345ULL) & 0x7fffffffULL; return (int)x; }
    int range(int lo, int hi) { return lo + next() % (hi - lo + 1); }
};
template <class F> double timeMs(F f) {
    auto t0 = chrono::high_resolution_clock::now(); f();
    return chrono::duration<double, milli>(chrono::high_resolution_clock::now() - t0).count();
}

// =====================================================================
// 1B.1 (CO BAN) - Tim kiem tuyen tinh: truong hop tot / trung binh / xau
//   linearSearch tra ve chi so dau tien co a[i] == x, khong co -> -1.
//   Moi lan so sanh a[i] == x phai tang bien 'comps'.
// =====================================================================
long long comps = 0;
int linearSearch(const vector<int>& a, int x) {
    // TODO: viet code cua ban o day
    for (int i = 0; i < (int)a.size(); i++) {
        comps++;
        if (a[i] == x) return i;
    }
    return -1;
}

// =====================================================================
// 1B.2 (CO BAN) - Luy thua b^e mod m: O(e) va O(log e)
//   Dem so phep NHAN (moi lan thuc hien phep * ... % m) vao 'mults'.
//   powFast PHAI theo dung khuon:
//       res = 1
//       while e > 0:
//           if e la so le:  res = res * b % m      (dem 1)
//           b = b * b % m                          (dem 1)
//           e = e / 2
// =====================================================================
long long mults = 0;
long long powNaive(long long b, long long e, long long m) {
    // TODO: viet code cua ban o day
    long long res = 1 % m;
    b %= m;
    for (long long i = 0; i < e; i++) {
        res = (res * b) % m;
        mults++;
    }
    return res;
}
long long powFast(long long b, long long e, long long m) {
    // TODO: viet code cua ban o day
    long long res = 1 % m;
    b %= m;
    while (e > 0) {
        if (e % 2 == 1) {
            res = (res * b) % m;
            mults++;
        }
        b = (b * b) % m;
        mults++;
        e /= 2;
    }
    return res;
}

// =====================================================================
// 1B.3 (TRUNG BINH) - Fibonacci ba cach. F(0)=0, F(1)=1.
//   fibRec : de quy thuan, moi lan GOI ham tang 'calls'
//   fibMemo: de quy co nho (memo), moi lan GOI ham tang 'calls'
//   fibIter: vong lap, O(n) thoi gian, O(1) bo nho
// =====================================================================
long long calls = 0;
long long fibRec(int n) {
    // TODO: viet code cua ban o day
    calls++;
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibRec(n - 1) + fibRec(n - 2);
}
long long fibMemoHelper(int n, vector<long long>& memo) {
    // TODO: viet code cua ban o day
    calls++;
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (memo[n] != -1) return memo[n];
    return memo[n] = fibMemoHelper(n - 1, memo) + fibMemoHelper(n - 2, memo);
}
long long fibMemo(int n) { vector<long long> memo(n + 1, -1); return fibMemoHelper(n, memo); }
long long fibIter(int n) {
    // TODO: viet code cua ban o day
    if (n <= 0) return 0;
    if (n == 1) return 1;
    long long prev2 = 0, prev1 = 1;
    for (int i = 2; i <= n; i++) {
        long long cur = prev1 + prev2;
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

// =====================================================================
// 1B.4 (NANG CAO) - Bai toan 3-SUM: dem bo ba i<j<k co a[i]+a[j]+a[k] == 0
//   Cac phan tu cua a doi mot KHAC NHAU.
//   threeSumCubic : 3 vong lap                  O(n^3)
//   threeSumBinary: sap xep + tim kiem nhi phan O(n^2 log n)
//   threeSumTwoPtr: sap xep + hai con tro       O(n^2)
// =====================================================================
long long threeSumCubic(const vector<int>& a) {
    // TODO: viet code cua ban o day
    long long count = 0;
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (a[i] + a[j] + a[k] == 0) {
                    count++;
                }
            }
        }
    }
    return count;
}
long long threeSumBinary(vector<int> a) {
    // TODO: viet code cua ban o day
    sort(a.begin(), a.end());
    long long count = 0;
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int target = -(a[i] + a[j]);
            if (binary_search(a.begin() + j + 1, a.end(), target)) {
                count++;
            }
        }
    }
    return count;
}
long long threeSumTwoPtr(vector<int> a) {
    // TODO: viet code cua ban o day
    sort(a.begin(), a.end());
    long long count = 0;
    int n = a.size();
    for (int i = 0; i < n; i++) {
        int target = -a[i];
        int left = i + 1, right = n - 1;
        while (left < right) {
            int sum = a[left] + a[right];
            if (sum == target) {
                count++;
                left++;
                right--;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }
    return count;
}
// Sinh n so nguyen doi mot khac nhau trong [-10n, 10n] (da cho san)
vector<int> distinctData(int n, unsigned long long seed) {
    LCG g(seed); set<int> used; vector<int> a;
    while ((int)a.size() < n) {
        int v = g.range(-10 * n, 10 * n);
        if (used.insert(v).second) a.push_back(v);
    }
    return a;
}

// =====================================================================
int main() {
    cout << fixed << setprecision(3);
    cout << "===== 1B.1: Tim kiem tuyen tinh =====\n";
    {
        int n = 1000; LCG g(11);
        vector<int> a(n); iota(a.begin(), a.end(), 1);
        for (int i = n - 1; i > 0; i--) swap(a[i], a[g.next() % (i + 1)]);
        comps = 0; int pos = linearSearch(a, a[0]);
        cout << "Tot nhat  (x = a[0])        : comps = " << comps << "  pos = " << pos << "\n";
        comps = 0; linearSearch(a, 0);
        cout << "Xau nhat  (x khong co)      : comps = " << comps << "\n";
        comps = 0; bool ok = true;
        for (int i = 0; i < n; i++) ok &= linearSearch(a, a[i]) == i;
        cout << "Trung binh (tim lan luot moi phan tu): tong = " << comps
             << "  TB = " << (double)comps / n << "  ly thuyet (n+1)/2 = " << (n + 1) / 2.0
             << (ok ? "  [OK]" : "  [SAI]") << "\n\n";
    }

    cout << "===== 1B.2: Luy thua mod 1e9+7 =====\n";
    const long long MOD = 1000000007LL;
    for (long long e : {10LL, 1000LL, 1000000LL}) {
        mults = 0; long long r1 = powNaive(3, e, MOD); long long m1 = mults;
        mults = 0; long long r2 = powFast(3, e, MOD);  long long m2 = mults;
        cout << "3^" << e << " mod p = " << r2 << "   naive: " << m1 << " phep nhan,  fast: " << m2
             << " phep nhan" << (r1 == r2 && r1 != 0 ? "  [OK]" : "  [SAI]") << "\n";
    }

    cout << "\n===== 1B.3: Fibonacci =====\n";
    cout << setw(4) << "n" << setw(14) << "F(n)" << setw(14) << "calls(rec)" << setw(12) << "calls(memo)"
         << setw(12) << "rec (ms)" << "\n";
    for (int n : {10, 20, 25, 30, 32}) {
        calls = 0; long long f1 = 0; double t = timeMs([&] { f1 = fibRec(n); }); long long c1 = calls;
        calls = 0; long long f2 = fibMemo(n); long long c2 = calls;
        long long f3 = fibIter(n);
        cout << setw(4) << n << setw(14) << f3 << setw(14) << c1 << setw(12) << c2 << setw(12) << t
             << ((f1 == f2 && f2 == f3 && f3 > 0) ? "  [OK]" : "  [SAI]") << "\n";
    }
    cout << "F(90) = " << fibIter(90) << "  (fibRec(90) se chay hang tram nam!)\n";

    cout << "\n===== 1B.4: 3-SUM =====\n";
    cout << setw(6) << "n" << setw(10) << "so bo ba" << setw(12) << "n^3 (ms)" << setw(14) << "n^2logn (ms)"
         << setw(12) << "n^2 (ms)" << setw(10) << "khop?" << "\n";
    double prev[3] = {0, 0, 0};
    for (int n : {200, 400, 800, 1600, 3200}) {
        vector<int> a = distinctData(n, 7);
        long long c1 = -1, c2 = 0, c3 = 0;
        double t1 = -1, t2, t3;
        if (n <= 1600) t1 = timeMs([&] { c1 = threeSumCubic(a); });
        t2 = timeMs([&] { c2 = threeSumBinary(a); });
        t3 = timeMs([&] { c3 = threeSumTwoPtr(a); });
        bool ok = c2 == c3 && (c1 == -1 || c1 == c2) && c2 > 0;
        cout << setw(6) << n << setw(10) << c3 << setw(12) << t1 << setw(14) << t2 << setw(12) << t3
             << setw(10) << (ok ? "[OK]" : "[SAI]");
        if (prev[2] > 0) {
            cout << "   b ~ ";
            if (t1 > 0 && prev[0] > 0) cout << "n^" << log2(t1 / prev[0]) << " | ";
            cout << "n^" << log2(t2 / prev[1]) << " | n^" << log2(t3 / prev[2]);
        }
        cout << "\n";
        prev[0] = t1; prev[1] = t2; prev[2] = t3;
    }
    cout << "(b = log2( T(2n) / T(n) ) la so mu uoc luong cua T(n) ~ n^b)\n";
    return 0;
}
