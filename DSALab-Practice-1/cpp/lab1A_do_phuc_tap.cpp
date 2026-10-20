// =====================================================================
//  LAB 1A (TREN LOP) - CHUONG 1: GIOI THIEU CTDL & GT, DO PHUC TAP
//  Mon: Cau truc du lieu va Giai thuat (INT1306_CLC) - PTIT
//  Bien dich:  g++ -O2 -std=c++17 -Wall -o lab1A lab1A_do_phuc_tap.cpp
//  Chay:       ./lab1A
//  Sinh vien chi viet code vao cac cho co "TODO". Khong sua ham main().
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

// ---------------------------------------------------------------------
// Bo sinh so gia ngau nhien DUNG CHUNG cho C++ va Python
// -> hai ngon ngu sinh ra cung mot du lieu, ket qua dem phai trung nhau.
// ---------------------------------------------------------------------
struct LCG {
    unsigned long long x;
    explicit LCG(unsigned long long seed) : x(seed) {}
    int next() { x = (x * 1103515245ULL + 12345ULL) & 0x7fffffffULL; return (int)x; }
    int range(int lo, int hi) { return lo + next() % (hi - lo + 1); }
};

// =====================================================================
// BAI 1.1 - Dac ta va cai dat thuat toan giai ax^2 + bx + c = 0
//   Tra ve: count = -1 (vo so nghiem), 0 (vo nghiem), 1 (mot nghiem), 2 (hai nghiem)
//   Neu count = 2 thi x1 < x2.  Dung EPS de so sanh delta voi 0.
// =====================================================================
struct Roots { int count; double x1, x2; };
const double EPS = 1e-9;

Roots solveQuadratic(double a, double b, double c) {
    // TODO: viet code cua ban o day
    if(std::abs(a) <= EPS){
        if(std::abs(b) <= EPS){
            if(std::abs(c) <= EPS) return {-1, 0, 0};
            return {0, 0, 0};
        }
        double temp = -c/b;
        return {1, temp, temp};
    }
    double delta = b*b - 4*a*c;
    //cout << "delta " << setprecision(20) << delta << endl;
    //Avoid delta = -0.0 for better squareroot.
    if(std::abs(delta) <= EPS) delta = 0.0;
    if(delta < -EPS) return {0,0,0};
    if(std::abs(delta) <= EPS){
        double temp = -b/(2*a);
        return{1, temp, temp};
    }
    else if(delta > EPS){
        double x1 = (-b - sqrt(delta)) / (2*a);
        double x2 = (-b + sqrt(delta)) / (2*a);
        //if(a < -EPS) return {2, x2, x1};
        return {2, min(x1,x2), max(x1,x2)};
    }

    return {0, 0, 0};
}

// =====================================================================
// BAI 1.2 - Dem so phep toan co ban (phuong phap dem - accounting method)
//   Moi ham countFk(n) chay dung doan vong lap mo ta, tang bien dem o
//   than vong lap trong cung, roi tra ve bien dem.
//   Moi ham formulaFk(n) tra ve cong thuc dong (khong dung vong lap).
// =====================================================================
// Ham ho tro: ceil(log2 n) voi n >= 1 (da cho san)
long long ceilLog2(long long n) { long long k = 0, p = 1; while (p < n) { p <<= 1; k++; } return k; }

// F1: for i = 0..n-1:                         cnt++
long long countF1(long long n) {
    long long cnt = 0;
    // TODO: viet code cua ban o day
    for (long long i = 0; i < n; i++) {
        cnt++;
    }
    return cnt;
}
// F2: for i = 0..n-1: for j = 0..n-1:          cnt++
long long countF2(long long n) {
    long long cnt = 0;
    // TODO: viet code cua ban o day
    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < n; j++) {
            cnt++;
        }
    }
    return cnt;
}
// F3: for i = 0..n-1: for j = i+1..n-1:        cnt++
long long countF3(long long n) {
    long long cnt = 0;
    // TODO: viet code cua ban o day
    for (long long i = 0; i < n; i++) {
        for (long long j = i + 1; j < n; j++) {
            cnt++;
        }
    }
    return cnt;
}
// F4: i = 1; while (i < n) { cnt++; i = i * 2; }
long long countF4(long long n) {
    long long cnt = 0;
    // TODO: viet code cua ban o day
    long long i = 1;
    while (i < n) {
        cnt++;
        i = i * 2;
    }
    return cnt;
}
// F5: for i = 0..n-1: { j = 1; while (j < n) { cnt++; j = j * 2; } }
long long countF5(long long n) {
    long long cnt = 0;
    // TODO: viet code cua ban o day
    for (long long i = 0; i < n; i++) {
        long long j = 1;
        while (j < n) {
            cnt++;
            j = j * 2;
        }
    }
    return cnt;
}
long long formulaF1(long long n) {
    // TODO: viet code cua ban o day
    return n;
}
long long formulaF2(long long n) {
    // TODO: viet code cua ban o day
    return n * n;
}
long long formulaF3(long long n) {
    // TODO: viet code cua ban o day
    return n * (n - 1) / 2;
}
long long formulaF4(long long n) {
    // TODO: viet code cua ban o day
    return ceilLog2(n);
}
long long formulaF5(long long n) {
    // TODO: viet code cua ban o day
    return n * ceilLog2(n);
}

// =====================================================================
// BAI 1.3 - Thuc nghiem "nhan doi n" (doubling experiment)
//   Bai toan: mang a co phan tu nao trung nhau khong?
//   A: so sanh moi cap         -> du kien O(n^2)
//   B: sap xep roi xet ke nhau -> du kien O(n log n)
//   C: dung bang bam (set)     -> du kien O(n) trung binh
//   Moi ham tra ve true neu CO phan tu trung.
// =====================================================================
long long pairComparisons = 0;   // A phai tang bien nay moi lan so sanh a[i]==a[j]

bool hasDupBrute(const vector<int>& a) {
    // TODO: viet code cua ban o day
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            pairComparisons++;
            if (a[i] == a[j]) return true;
        }
    }
    return false;
}
bool hasDupSort(vector<int> a) {          // nhan ban sao -> duoc phep sap xep
    // TODO: viet code cua ban o day
    sort(a.begin(), a.end());
    for (size_t i = 1; i < a.size(); i++) {
        if (a[i] == a[i - 1]) return true;
    }
    return false;
}
bool hasDupHash(const vector<int>& a) {
    // TODO: viet code cua ban o day
    //unordered is a hash table, while set is a red-black tree
    unordered_set<int> seen;
    for (int x : a) {
        if (seen.find(x) != seen.end()) return true;
        seen.insert(x);
    }
    return false;
}

// ---------------- Ham ho tro (da cho san) ----------------
// Hoan vi ngau nhien cua 0..n-1 (Fisher-Yates) -> khong co phan tu trung (truong hop xau nhat)
vector<int> randomPermutation(int n, LCG& g) {
    vector<int> a(n);
    iota(a.begin(), a.end(), 0);
    for (int i = n - 1; i > 0; i--) swap(a[i], a[g.next() % (i + 1)]);
    return a;
}
template <class F> double timeMs(F f) {
    auto t0 = chrono::high_resolution_clock::now();
    f();
    auto t1 = chrono::high_resolution_clock::now();
    return chrono::duration<double, milli>(t1 - t0).count();
}

// =====================================================================
int main() {
    cout << fixed << setprecision(4);
    cout << "===== BAI 1.1: Giai phuong trinh bac hai =====\n";
    struct T { double a, b, c; int cnt; double x1, x2; };
    vector<T> tests = {
        {1, -3, 2, 2, 1, 2}, {1, 2, 1, 1, -1, -1}, {1, 0, 1, 0, 0, 0},
        {2, -7, 3, 2, 0.5, 3}, {1, 0.2, 0.01, 1, -0.1, -0.1},
        {0, 2, -4, 1, 2, 2}, {0, 0, 0, -1, 0, 0}, {0, 0, 5, 0, 0, 0}};
    int pass = 0;
    for (auto& t : tests) {
        Roots r = solveQuadratic(t.a, t.b, t.c);
        bool ok = r.count == t.cnt &&
                  (r.count <= 0 || (fabs(r.x1 - t.x1) < 1e-6 && fabs(r.x2 - t.x2) < 1e-6));
        pass += ok;
        cout << "a=" << t.a << " b=" << t.b << " c=" << t.c << "  -> count=" << r.count;
        if (r.count > 0) cout << "  x1=" << r.x1 << "  x2=" << r.x2;
        cout << (ok ? "   [OK]" : "   [SAI]") << "\n";
    }
    cout << "Dung " << pass << "/" << tests.size() << " test\n\n";

    cout << "===== BAI 1.2: Dem phep toan =====\n";
    cout << setw(6) << "n" << setw(12) << "F1" << setw(12) << "F2" << setw(12) << "F3"
         << setw(6) << "F4" << setw(10) << "F5" << "   khop cong thuc?\n";
    for (long long n : {8LL, 100LL, 1000LL}) {
        long long c1 = countF1(n), c2 = countF2(n), c3 = countF3(n), c4 = countF4(n), c5 = countF5(n);
        bool ok = c1 == formulaF1(n) && c2 == formulaF2(n) && c3 == formulaF3(n) &&
                  c4 == formulaF4(n) && c5 == formulaF5(n) && min({c1, c2, c3, c4, c5}) > 0;
        cout << setw(6) << n << setw(12) << c1 << setw(12) << c2 << setw(12) << c3
             << setw(6) << c4 << setw(10) << c5 << "   " << (ok ? "[OK]" : "[SAI]") << "\n";
    }

    cout << "\n===== BAI 1.3: Thuc nghiem nhan doi n =====\n";
    {   // kiem tra tinh dung
        vector<int> d1 = {5, 1, 4, 2, 3}, d2 = {5, 1, 4, 1, 3};
        bool ok = !hasDupBrute(d1) && hasDupBrute(d2) && !hasDupSort(d1) && hasDupSort(d2) &&
                  !hasDupHash(d1) && hasDupHash(d2);
        cout << "Kiem tra tinh dung: " << (ok ? "[OK]" : "[SAI]") << "\n";
    }
    cout << setw(7) << "n" << setw(14) << "so cap (A)" << setw(11) << "A (ms)" << setw(8) << "tiA"
         << setw(10) << "B (ms)" << setw(8) << "tiB" << setw(10) << "C (ms)" << setw(8) << "tiC" << "\n";
    double pa = 0, pb = 0, pc = 0;
    for (int n : {2000, 4000, 8000, 16000}) {
        LCG g(2026);
        vector<int> a = randomPermutation(n, g);
        pairComparisons = 0;
        double ta = timeMs([&] { hasDupBrute(a); });
        double tb = timeMs([&] { for (int r = 0; r < 20; r++) hasDupSort(a); }) / 20;
        double tc = timeMs([&] { for (int r = 0; r < 20; r++) hasDupHash(a); }) / 20;
        cout << setw(7) << n << setw(14) << pairComparisons << setw(11) << ta << setw(8)
             << (pa > 0 ? ta / pa : 0) << setw(10) << tb << setw(8) << (pb > 0 ? tb / pb : 0)
             << setw(10) << tc << setw(8) << (pc > 0 ? tc / pc : 0) << "\n";
        pa = ta; pb = tb; pc = tc;
    }
    cout << "(ti = T(n) / T(n/2). O(n^2) -> ~4, O(n log n) -> ~2.1, O(n) -> ~2)\n";
    return 0;
}
