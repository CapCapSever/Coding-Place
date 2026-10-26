// =====================================================================
//  LAB 2B (VE NHA) - CHUONG 2: SAP XEP VA TIM KIEM
//  Muc do:  2B.1-2B.2 Co ban | 2B.3-2B.4 Trung binh | 2B.5-2B.6 Nang cao
//  Bien dich:  g++ -O2 -std=c++17 -Wall -o lab2B lab2B_ve_nha.cpp
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
void printArr(const vector<int>& a) { for (int x : a) cout << x << ' '; cout << '\n'; }

// =====================================================================
// 2B.1 (CO BAN) - Radix sort LSD co so 10 (so nguyen khong am)
//   Neu trace = true: sau moi luot in "  exp=<exp>: <mang>"
// =====================================================================
void countingByDigit(vector<int>& a, int exp) {
    // TODO: viet code cua ban o day
    if (a.empty()) return;
    int n = a.size();
    vector<int> out(n);
    int count[10] = {0};
    for (int i = 0; i < n; i++) {
        int digit = (a[i] / exp) % 10;
        count[digit]++;
    }
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        int digit = (a[i] / exp) % 10;
        out[--count[digit]] = a[i];
    }
    a = move(out);
}
void radixSort(vector<int>& a, bool trace) {
    // TODO: viet code cua ban o day
    if (a.empty()) return;
    int mx = *max_element(a.begin(), a.end());
    for (int exp = 1; mx / exp > 0; exp *= 10) {
        countingByDigit(a, exp);
        if (trace) {
            cout << "  exp=" << exp << ": ";
            printArr(a);
        }
    }
}

// =====================================================================
// 2B.2 (CO BAN) - Tim kiem noi suy vs nhi phan: dem so lan tham do (probe)
//   Moi lan doc a[mid] / a[pos] trong vong lap = 1 probe (cong vao 'probes').
// =====================================================================
long long probes = 0;
int binarySearch(const vector<long long>& a, long long x) {
    // TODO: viet code cua ban o day
    int lo = 0, hi = (int)a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        probes++;
        if (a[mid] == x) return mid;
        if (a[mid] < x) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}
int interpolationSearch(const vector<long long>& a, long long x) {
    // TODO: viet code cua ban o day
    int lo = 0, hi = (int)a.size() - 1;
    while (lo <= hi && x >= a[lo] && x <= a[hi]) {
        if (a[lo] == a[hi]) {
            probes++;
            if (a[lo] == x) return lo;
            return -1;
        }
        int pos = lo + (x - a[lo]) * (hi - lo) / (a[hi] - a[lo]);
        probes++;
        if (a[pos] == x) return pos;
        if (a[pos] < x) lo = pos + 1;
        else hi = pos - 1;
    }
    return -1;
}

// =====================================================================
// 2B.3 (TRUNG BINH) - Quick sort cai tien: chon pivot "trung vi cua ba"
//   Voi doan [lo..hi] co it nhat 3 phan tu:
//     mid = (lo + hi) / 2; sap xep 3 gia tri a[lo], a[mid], a[hi] (khong dem so sanh);
//     swap(a[mid], a[hi]) -> trung vi thanh pivot o cuoi; roi partition Lomuto.
//   Chi dem comps tai dong (*) a[j] <= pivot.
// =====================================================================
long long qcomps = 0;
int lomuto(vector<int>& a, int lo, int hi) {
    int pivot = a[hi], i = lo - 1;
    for (int j = lo; j < hi; j++) { qcomps++; if (a[j] <= pivot) swap(a[++i], a[j]); }
    swap(a[i + 1], a[hi]);
    return i + 1;
}
void quickSortLast(vector<int>& a, int lo, int hi) {         // ban goc (da cho san)
    if (lo >= hi) return;
    int p = lomuto(a, lo, hi);
    quickSortLast(a, lo, p - 1); quickSortLast(a, p + 1, hi);
}
void medianOfThree(vector<int>& a, int lo, int hi) {
    // TODO: viet code cua ban o day
    if (hi - lo < 2) return;
    int mid = lo + (hi - lo) / 2;
    if (a[lo] > a[mid]) swap(a[lo], a[mid]);
    if (a[lo] > a[hi]) swap(a[lo], a[hi]);
    if (a[mid] > a[hi]) swap(a[mid], a[hi]);
    swap(a[mid], a[hi]);
}
void quickSortMed3(vector<int>& a, int lo, int hi) {
    // TODO: viet code cua ban o day
    if (lo >= hi) return;
    if (hi - lo >= 2) {
        medianOfThree(a, lo, hi);
    }
    int p = lomuto(a, lo, hi);
    quickSortMed3(a, lo, p - 1);
    quickSortMed3(a, p + 1, hi);
}

// =====================================================================
// 2B.4 (TRUNG BINH) - Bang bam chaining tu cai dat cho chuoi -> dem tan suat tu
//   h(s) = (... ((s0*31 + s1)*31 + s2) ...) mod m   (tinh mod sau MOI buoc)
//   Khi load factor = size/m > 0.75 sau khi them -> rehash sang m' = 2m + 1.
// =====================================================================
struct WordCounter {
    int m, sz = 0, rehashes = 0;
    vector<vector<pair<string, int>>> slot;
    explicit WordCounter(int m0) : m(m0), slot(m0) {}
    static int hashStr(const string& s, int m) {
        // TODO: viet code cua ban o day
        long long h = 0;
        for (char c : s) {
            h = (h * 31 + (unsigned char)c) % m;
        }
        return (int)h;
    }
    void rehash() {
        // TODO: viet code cua ban o day
        rehashes++;
        int new_m = 2 * m + 1;
        vector<vector<pair<string, int>>> new_slot(new_m);
        for (const auto& chain : slot) {
            for (const auto& kv : chain) {
                int idx = hashStr(kv.first, new_m);
                new_slot[idx].push_back(kv);
            }
        }
        m = new_m;
        slot = move(new_slot);
    }
    void add(const string& w) {                // tang dem cua w them 1
        // TODO: viet code cua ban o day
        int idx = hashStr(w, m);
        for (auto& kv : slot[idx]) {
            if (kv.first == w) {
                kv.second++;
                return;
            }
        }
        slot[idx].push_back({w, 1});
        sz++;
        if ((double)sz / m > 0.75) {
            rehash();
        }
    }
    int get(const string& w) const {
        // TODO: viet code cua ban o day
        int idx = hashStr(w, m);
        for (const auto& kv : slot[idx]) {
            if (kv.first == w) {
                return kv.second;
            }
        }
        return 0;
    }
    int longestChain() const { size_t L = 0; for (auto& c : slot) L = max(L, c.size()); return L; }
};

// =====================================================================
// 2B.5 (NANG CAO) - Dem so nghich the (cap i<j co a[i] > a[j])
// =====================================================================
long long inversionsBrute(const vector<int>& a) {
    // TODO: viet code cua ban o day
    long long count = 0;
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                count++;
            }
        }
    }
    return count;
}
long long sortCount(vector<int>& a, vector<int>& tmp, int lo, int hi) {   // [lo, hi]
    // TODO: viet code cua ban o day
    if (lo >= hi) return 0;
    int mid = lo + (hi - lo) / 2;
    long long count = 0;
    count += sortCount(a, tmp, lo, mid);
    count += sortCount(a, tmp, mid + 1, hi);

    int i = lo, j = mid + 1, k = lo;
    while (i <= mid && j <= hi) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
            count += (mid - i + 1);
        }
    }
    while (i <= mid) {
        tmp[k++] = a[i++];
    }
    while (j <= hi) {
        tmp[k++] = a[j++];
    }
    for (int p = lo; p <= hi; p++) {
        a[p] = tmp[p];
    }
    return count;
}
long long inversionsMerge(vector<int> a) {
    vector<int> tmp(a.size());
    return a.empty() ? 0 : sortCount(a, tmp, 0, a.size() - 1);
}

// =====================================================================
// 2B.6 (NANG CAO) - Quickselect: phan tu nho thu k (k tinh tu 1), O(n) trung binh
//   Dung medianOfThree + lomuto o tren; KHONG sap xep toan bo mang.
// =====================================================================
int quickSelect(vector<int> a, int k) {
    // TODO: viet code cua ban o day
    int lo = 0, hi = (int)a.size() - 1;
    int target = k - 1;
    while (lo <= hi) {
        if (lo == hi) return a[lo];
        if (hi - lo >= 2) {
            medianOfThree(a, lo, hi);
        }
        int p = lomuto(a, lo, hi);
        if (p == target) return a[p];
        if (p < target) lo = p + 1;
        else hi = p - 1;
    }
    return a[target];
}

// =====================================================================
int main() {
    cout << fixed << setprecision(3);
    cout << "===== 2B.1: Radix sort =====\n";
    vector<int> r = {329, 457, 657, 839, 436, 720, 355};
    radixSort(r, true);
    {
        LCG g(5); vector<int> a(100000); for (int& x : a) x = g.range(0, 999999);
        vector<int> b = a; sort(b.begin(), b.end());
        double t = timeMs([&] { radixSort(a, false); });
        cout << "n = 100000: " << t << " ms" << (a == b ? "  [OK]" : "  [SAI]") << "\n";
    }

    cout << "\n===== 2B.2: Noi suy vs Nhi phan (probe trung binh / 1000 truy van) =====\n";
    {
        int n = 1000000;
        vector<long long> uni(n); for (int i = 0; i < n; i++) uni[i] = 10LL * (i + 1);
        int m = 1000;
        vector<long long> skew(m); for (int i = 0; i < m; i++) skew[i] = 1LL * (i + 1) * (i + 1) * (i + 1);
        for (auto [name, arr] : vector<pair<string, vector<long long>*>>{{"deu   a[i]=10(i+1),  n=1e6", &uni},
                                                                         {"lech  a[i]=(i+1)^3,  n=1000", &skew}}) {
            LCG g(77); long long pb = 0, pi = 0; bool ok = true;
            for (int q = 0; q < 1000; q++) {
                int idx = g.range(0, arr->size() - 1); long long x = (*arr)[idx];
                probes = 0; ok &= binarySearch(*arr, x) == idx; pb += probes;
                probes = 0; ok &= interpolationSearch(*arr, x) == idx; pi += probes;
            }
            ok &= binarySearch(*arr, 5) == -1 && interpolationSearch(*arr, 5) == -1;
            cout << name << ":  binary " << pb / 1000.0 << "   interpolation " << pi / 1000.0
                 << (ok ? "  [OK]" : "  [SAI]") << "\n";
        }
    }

    cout << "\n===== 2B.3: Quick sort - pivot cuoi vs trung vi cua ba =====\n";
    {
        int n = 1000; LCG g(2026);
        vector<int> rnd(n); for (int& x : rnd) x = g.range(0, 99999);
        vector<int> asc = rnd; sort(asc.begin(), asc.end());
        vector<int> desc(asc.rbegin(), asc.rend());
        cout << setw(14) << "" << setw(14) << "pivot cuoi" << setw(14) << "trung vi 3" << "\n";
        for (auto [label, src] : vector<pair<string, vector<int>*>>{{"ngau nhien", &rnd}, {"da sap", &asc}, {"sap giam", &desc}}) {
            vector<int> a = *src, b = *src;
            qcomps = 0; quickSortLast(a, 0, n - 1); long long c1 = qcomps;
            qcomps = 0; quickSortMed3(b, 0, n - 1); long long c2 = qcomps;
            cout << setw(14) << label << setw(14) << c1 << setw(14) << c2
                 << ((a == asc && b == asc) ? "  [OK]" : "  [SAI]") << "\n";
        }
    }

    cout << "\n===== 2B.4: Bang bam dem tu =====\n";
    {
        string text =
            "the quick brown fox jumps over the lazy dog the dog sleeps and the fox runs "
            "a hash table maps a key to a slot and the slot holds a chain of keys "
            "when the load factor grows the table doubles and every key is hashed again "
            "searching a hash table costs one plus alpha on average and n in the worst case "
            "the fox and the dog are friends and the table is fast";
        WordCounter wc(7);
        stringstream ss(text); string w; int total = 0;
        while (ss >> w) { wc.add(w); total++; }
        vector<pair<string, int>> all;
        for (auto& c : wc.slot) for (auto& kv : c) all.push_back(kv);
        sort(all.begin(), all.end(), [](auto& x, auto& y) { return x.second != y.second ? x.second > y.second : x.first < y.first; });
        cout << "Tong so tu = " << total << ", so tu khac nhau = " << wc.sz << ", m = " << wc.m
             << ", so lan rehash = " << wc.rehashes << ", alpha = " << (double)wc.sz / wc.m
             << ", chuoi dai nhat = " << wc.longestChain() << "\n";
        cout << "Top 5:"; for (int i = 0; i < 5 && i < (int)all.size(); i++) cout << "  " << all[i].first << "=" << all[i].second;
        cout << "\nget(\"fox\") = " << wc.get("fox") << ", get(\"cat\") = " << wc.get("cat")
             << ", h(\"fox\", 7) = " << WordCounter::hashStr("fox", 7) << "\n";
    }

    cout << "\n===== 2B.5: Dem nghich the =====\n";
    {
        vector<int> s = {2, 4, 1, 3, 5};
        cout << "2 4 1 3 5 -> " << inversionsMerge(s) << " nghich the\n";
        LCG g(31); vector<int> a(3000); for (int& x : a) x = g.range(0, 9999);
        long long b1 = inversionsBrute(a), b2 = inversionsMerge(a);
        cout << "n = 3000: brute = " << b1 << ", merge = " << b2 << (b1 == b2 && b1 > 0 ? "  [OK]" : "  [SAI]") << "\n";
        vector<int> big(1000000); for (int& x : big) x = g.range(0, 1000000000);
        long long c = 0; double t = timeMs([&] { c = inversionsMerge(big); });
        cout << "n = 1 000 000: " << c << " nghich the, " << t << " ms (brute se mat ~ vai phut)\n";
    }

    cout << "\n===== 2B.6: Quickselect =====\n";
    {
        LCG g(8); vector<int> a(100001); for (int& x : a) x = g.range(0, 1000000);
        vector<int> b = a; sort(b.begin(), b.end());
        bool ok = true;
        for (int k : {1, 10, 50001, 99999, 100001}) {
            int v = quickSelect(a, k); ok &= v == b[k - 1];
            cout << "  k = " << setw(6) << k << " -> " << v << "\n";
        }
        cout << "Trung vi cua 100001 so = " << quickSelect(a, 50001) << (ok ? "  [OK]" : "  [SAI]") << "\n";
    }
    return 0;
}
