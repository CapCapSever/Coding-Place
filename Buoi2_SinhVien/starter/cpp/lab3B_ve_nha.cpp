// =====================================================================
//  LAB 3B (VE NHA) - CHUONG 3: KY THUAT THIET KE GIAI THUAT
//  Muc do: 3B.1 De quy, 3B.2 Quay lui (Co ban) | 3B.3 Tham lam, 3B.4 QHD (Trung binh)
//          3B.5 Nhanh can, 3B.6 Chia de tri (Nang cao)
//  Bien dich:  g++ -O2 -std=c++17 -Wall -o lab3B lab3B_ve_nha.cpp
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
// 3B.1 (CO BAN) - De quy: C(n,k) = C(n-1,k-1) + C(n-1,k), C(n,0) = C(n,n) = 1
//   binomRec : de quy thuan, moi lan goi tang 'calls'
//   binomMemo: de quy co nho (bang memo[n+1][k+1], -1 = chua tinh), moi lan goi tang 'calls'
// =====================================================================
long long calls = 0;
long long binomRec(int n, int k) {
    // TODO: viet code cua ban o day
    return 0;
}
long long binomMemoHelper(int n, int k, vector<vector<long long>>& memo) {
    // TODO: viet code cua ban o day
    return 0;
}
long long binomMemo(int n, int k) {
    vector<vector<long long>> memo(n + 1, vector<long long>(k + 1, -1));
    return binomMemoHelper(n, k, memo);
}

// =====================================================================
// 3B.2 (CO BAN) - Quay lui: liet ke xau nhi phan do dai n KHONG co hai bit 1 lien ke
//   Thu bit 0 truoc, roi bit 1 (chi khi bit truoc khong phai 1) -> ket qua theo thu tu tu dien.
// =====================================================================
void genNoAdj(int n, string& cur, vector<string>& out) {
    // TODO: viet code cua ban o day
}

// =====================================================================
// 3B.3 (TRUNG BINH) - Tham lam: so phong hop toi thieu (interval partitioning)
//   Sap cac cuoc hop theo (start, end) tang dan. Duy tri min-heap cac cap (gio_ket_thuc, so_phong).
//   Voi moi cuoc hop: neu phong ket thuc som nhat co end <= start -> dung lai phong do,
//   nguoc lai mo phong moi (so phong = so phong hien co + 1, danh so tu 1).
//   Tra ve so phong; room[i] = phong gan cho cuoc hop thu i (theo thu tu da sap).
// =====================================================================
struct Meeting { string name; int s, e; };
int minRooms(vector<Meeting>& ms, vector<int>& room) {
    // TODO: viet code cua ban o day
    return 0;
}

// =====================================================================
// 3B.4 (TRUNG BINH) - QHD: day con tang chat dai nhat (LIS)
//   lisN2: dp[i] = 1 + max{dp[j] : j < i, a[j] < a[i]}; prev[i] = j NHO NHAT dat max (-1 neu khong co)
//          Diem ket thuc = chi so i NHO NHAT co dp[i] lon nhat. Tra ve day LIS (truy vet bang prev).
//   lisNlogN: chi tra ve DO DAI, dung mang tails + tim kiem nhi phan (lower_bound).
// =====================================================================
vector<int> lisN2(const vector<int>& a) {
    vector<int> res;
    // TODO: viet code cua ban o day
    return res;
}
int lisNlogN(const vector<int>& a) {
    // TODO: viet code cua ban o day
    return 0;
}

// =====================================================================
// 3B.5 (NANG CAO) - Nhanh va can: bai toan nguoi du lich (TSP), xuat phat va ve thanh pho 0
//   tspBrute: duyet moi hoan vi cua 1..n-1 (dung next_permutation) -> chi phi nho nhat.
//   tspBnB  : quay lui chon thanh pho tiep theo theo chi so TANG DAN.
//             'bnbNodes' tang 1 moi lan GOI ham de quy.
//             Can duoi tai nut co k thanh pho da di (ke ca 0), chi phi hien tai cost:
//                 bound = cost + (n - k + 1) * cmin     (cmin = canh nho nhat cua ma tran, i != j)
//             Neu bound >= best -> cat nhanh (khong di tiep).
// =====================================================================
long long bnbNodes = 0;
int tspBrute(const vector<vector<int>>& c) {
    // TODO: viet code cua ban o day
    return 0;
}
void bnb(const vector<vector<int>>& c, int cmin, int last, int k, int cost, vector<bool>& used,
         vector<int>& path, int& best, vector<int>& bestPath) {
    // TODO: viet code cua ban o day
}
int tspBnB(const vector<vector<int>>& c, vector<int>& bestPath) {
    int n = c.size(), cmin = INT_MAX;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (i != j) cmin = min(cmin, c[i][j]);
    vector<bool> used(n, false); used[0] = true;
    vector<int> path = {0};
    int best = INT_MAX;
    bnb(c, cmin, 0, 1, 0, used, path, best, bestPath);
    return best;
}

// =====================================================================
// 3B.6 (NANG CAO) - Chia de tri: cap diem gan nhat. Tra ve BINH PHUONG khoang cach (so nguyen).
//   closestBrute: O(n^2)
//   closestDC   : sap theo x; chia doi; d = min(trai, phai); xet dai |x - xmid| < d
//                 sap dai theo y, moi diem chi so voi cac diem sau no co (dy)^2 < d. O(n log^2 n)
// =====================================================================
typedef pair<long long, long long> Pt;
long long dist2(const Pt& a, const Pt& b) {
    long long dx = a.first - b.first, dy = a.second - b.second; return dx * dx + dy * dy;
}
long long closestBrute(const vector<Pt>& p) {
    // TODO: viet code cua ban o day
    return 0;
}
long long closestRec(vector<Pt>& p, int lo, int hi) {       // p[lo..hi) da sap theo x
    // TODO: viet code cua ban o day
    return 0;
}
long long closestDC(vector<Pt> p) { sort(p.begin(), p.end()); return closestRec(p, 0, p.size()); }
vector<Pt> randomPoints(int n, unsigned long long seed) {
    LCG g(seed); vector<Pt> p(n);
    for (auto& q : p) { q.first = g.range(0, 1000000); q.second = g.range(0, 1000000); }
    return p;
}

// =====================================================================
int main() {
    cout << fixed << setprecision(3);
    cout << "===== 3B.1: To hop C(n,k) de quy =====\n";
    for (auto [n, k] : vector<pair<int, int>>{{5, 2}, {10, 5}, {20, 10}, {26, 13}}) {
        calls = 0; long long r1 = binomRec(n, k); long long c1 = calls;
        calls = 0; long long r2 = binomMemo(n, k); long long c2 = calls;
        cout << "C(" << n << "," << k << ") = " << r1 << "   calls rec = " << c1 << ", calls memo = " << c2
             << (r1 == r2 && r1 > 0 ? "  [OK]" : "  [SAI]") << "\n";
    }

    cout << "\n===== 3B.2: Xau nhi phan khong co hai bit 1 lien ke =====\n";
    {
        vector<string> out; string cur; genNoAdj(4, cur, out);
        cout << "n = 4:"; for (auto& s : out) cout << ' ' << s; cout << "  (" << out.size() << " xau)\n";
        cout << "So xau theo n:";
        long long f1 = 1, f2 = 2; bool ok = out.size() == 8;   // F(n+2): n=0 ->1, n=1 ->2
        for (int n = 1; n <= 20; n++) {
            vector<string> o; string c; genNoAdj(n, c, o);
            if (n <= 10 || n == 20) cout << ' ' << o.size();
            ok &= (long long)o.size() == f2;
            long long f3 = f1 + f2; f1 = f2; f2 = f3;
        }
        cout << (ok ? "  [OK]" : "  [SAI]") << "\n";
    }

    cout << "\n===== 3B.3: So phong hop toi thieu =====\n";
    {
        vector<Meeting> ms = {{"M1", 9, 11}, {"M2", 9, 10}, {"M3", 10, 12}, {"M4", 11, 13}, {"M5", 9, 12},
                              {"M6", 13, 14}, {"M7", 12, 15}, {"M8", 14, 16}, {"M9", 10, 11}, {"M10", 15, 17}};
        vector<int> room; int r = minRooms(ms, room);
        room.resize(ms.size());
        for (size_t i = 0; i < ms.size(); i++)
            cout << "  " << setw(4) << ms[i].name << " [" << setw(2) << ms[i].s << "," << setw(2) << ms[i].e
                 << ") -> phong " << room[i] << "\n";
        int depth = 0;                                  // kiem tra: so cuoc hop chong nhau lon nhat
        for (int t = 0; t < 24; t++) { int c = 0; for (auto& m : ms) c += (m.s <= t && t < m.e); depth = max(depth, c); }
        cout << "So phong = " << r << ", do chong lan lon nhat = " << depth << (r == depth && r > 0 ? "  [OK]" : "  [SAI]") << "\n";
    }

    cout << "\n===== 3B.4: Day con tang dai nhat =====\n";
    {
        vector<vector<int>> tests = {{10, 9, 2, 5, 3, 7, 101, 18}, {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15}};
        for (auto& a : tests) {
            auto s = lisN2(a);
            bool inc = !s.empty(); for (size_t i = 1; i < s.size(); i++) inc &= s[i - 1] < s[i];
            cout << "  do dai " << s.size() << ", LIS ="; for (int x : s) cout << ' ' << x;
            cout << ((inc && (int)s.size() == lisNlogN(a)) ? "  [OK]" : "  [SAI]") << "\n";
        }
        LCG g(4); vector<int> a(3000); for (int& x : a) x = g.range(0, 100000);
        int l1 = 0, l2 = 0;
        double t1 = timeMs([&] { l1 = lisN2(a).size(); }), t2 = timeMs([&] { l2 = lisNlogN(a); });
        cout << "  n = 3000: O(n^2) -> " << l1 << " (" << t1 << " ms), O(n log n) -> " << l2 << " (" << t2 << " ms)"
             << (l1 == l2 && l1 > 0 ? "  [OK]" : "  [SAI]") << "\n";
    }

    cout << "\n===== 3B.5: TSP - Nhanh va can =====\n";
    {
        vector<vector<int>> c5 = {{0, 3, 14, 18, 15}, {3, 0, 4, 22, 20}, {17, 9, 0, 16, 4}, {6, 3, 7, 0, 12}, {9, 15, 11, 5, 0}};
        vector<int> path; bnbNodes = 0;
        int b = tspBnB(c5, path);
        cout << "n = 5: brute = " << tspBrute(c5) << ", B&B = " << b << ", hanh trinh:";
        for (int v : path) cout << ' ' << v;
        cout << " 0, so nut = " << bnbNodes
             << (b == tspBrute(c5) ? "  [OK]" : "  [SAI]") << "\n";
        int n = 10; LCG g(10); vector<vector<int>> c(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (i != j) c[i][j] = g.range(10, 99);
        int br = 0; double tb = timeMs([&] { br = tspBrute(c); });
        bnbNodes = 0; int bb = 0; double tn = timeMs([&] { bb = tspBnB(c, path); });
        cout << "n = 10: brute = " << br << " (9! = 362880 hanh trinh, " << tb << " ms), B&B = " << bb << " ("
             << bnbNodes << " nut, " << tn << " ms)" << (br == bb ? "  [OK]" : "  [SAI]") << "\n";
        cout << "        hanh trinh:"; for (int v : path) cout << ' ' << v; cout << " 0\n";
    }

    cout << "\n===== 3B.6: Cap diem gan nhat =====\n";
    {
        auto p = randomPoints(2000, 3);
        long long d1 = closestBrute(p), d2 = closestDC(p);
        cout << "n = 2000: brute d^2 = " << d1 << ", chia de tri d^2 = " << d2 << (d1 == d2 ? "  [OK]" : "  [SAI]") << "\n";
        auto q = randomPoints(200000, 9);
        long long d = 0; double t = timeMs([&] { d = closestDC(q); });
        cout << "n = 200000: d^2 = " << d << ", " << t << " ms\n";
    }
    return 0;
}
