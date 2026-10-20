// =====================================================================
//  LAB 2A (TREN LOP) - CHUONG 2: SAP XEP VA TIM KIEM
//  Bien dich:  g++ -O2 -std=c++17 -Wall -o lab2A lab2A_sap_xep_tim_kiem.cpp
//  Chay:       ./lab2A
//  Viet code vao cac cho "TODO". Code phai dem dung phep so sanh (*) nhu slide.
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

// Bo dem: comps = so phep so sanh khoa (*), moves = so lan doi cho (swap) / dich phan tu
struct Stats { long long comps = 0, moves = 0; };
bool TRACE = false;   // true -> in mang sau moi luot (pass) cua vong ngoai

// =====================================================================
// BAI 2.1 - Ba thuat toan sap xep co ban (sap tang dan)
// =====================================================================
// Selection: comps++ moi lan so sanh a[j] < a[minPos]; moves++ khi swap (chi khi minPos != i)
void selectionSort(vector<int>& a, Stats& st) {
    // TODO: viet code cua ban o day
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < n; j++) {
            st.comps++;
            if (a[j] < a[minPos]) {
                minPos = j;
            }
        }
        if (minPos != i) {
            swap(a[i], a[minPos]);
            st.moves++;
        }
        if (TRACE) { cout << "  "; printArr(a); }
    }
}
// Insertion: key = a[i]; dich cac phan tu > key sang phai.
//   comps++ moi lan so sanh a[j] > key (chi khi j >= 0); moves++ moi lan dich a[j+1] = a[j]
void insertionSort(vector<int>& a, Stats& st) {
    // TODO: viet code cua ban o day
    int n = a.size();
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0) {
            st.comps++;
            if (a[j] > key) {
                a[j + 1] = a[j];
                st.moves++;
                j--;
            } else {
                break;
            }
        }
        a[j + 1] = key;
        if (TRACE) { cout << "  "; printArr(a); }
    }
}
// Bubble (co co 'swapped' de dung som): comps++ moi lan so sanh a[j] > a[j+1]; moves++ moi lan swap
void bubbleSort(vector<int>& a, Stats& st) {
    // TODO: viet code cua ban o day
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            st.comps++;
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                st.moves++;
                swapped = true;
            }
        }
        if (TRACE) { cout << "  "; printArr(a); }
        if (!swapped) break;
    }
}

// =====================================================================
// BAI 2.2 - Quick sort (Lomuto, pivot = phan tu cuoi) va Merge sort
//   Dem comps tai dong (*) giong slide: a[j] <= pivot  va  a[i] <= a[j] trong merge
// =====================================================================
int partitionLomuto(vector<int>& a, int lo, int hi, Stats& st) {
    // TODO: viet code cua ban o day
    int pivot = a[hi];
    int i = lo - 1;
    for (int j = lo; j < hi; j++) {
        st.comps++;
        if (a[j] <= pivot) {
            i++;
            swap(a[i], a[j]);
            st.moves++;
        }
    }
    swap(a[i + 1], a[hi]);
    st.moves++;
    return i + 1;
}
void quickSort(vector<int>& a, int lo, int hi, Stats& st) {
    // TODO: viet code cua ban o day
    if (lo < hi) {
        int p = partitionLomuto(a, lo, hi, st);
        quickSort(a, lo, p - 1, st);
        quickSort(a, p + 1, hi, st);
    }
}
void mergeRuns(vector<int>& a, int lo, int mid, int hi, Stats& st) {
    // TODO: viet code cua ban o day
    vector<int> temp;
    temp.reserve(hi - lo + 1);
    int i = lo, j = mid + 1;
    while (i <= mid && j <= hi) {
        st.comps++;
        if (a[i] <= a[j]) {
            temp.push_back(a[i++]);
        } else {
            temp.push_back(a[j++]);
        }
    }
    while (i <= mid) temp.push_back(a[i++]);
    while (j <= hi) temp.push_back(a[j++]);
    for (int k = 0; k < (int)temp.size(); k++) {
        a[lo + k] = temp[k];
    }
}
void mergeSort(vector<int>& a, int lo, int hi, Stats& st) {
    // TODO: viet code cua ban o day
    if (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        mergeSort(a, lo, mid, st);
        mergeSort(a, mid + 1, hi, st);
        mergeRuns(a, lo, mid, hi, st);
    }
}

// =====================================================================
// BAI 2.3a - Tim kiem nhi phan co in vet (trace) tung buoc
//   In moi buoc theo mau:  step k: lo=.. hi=.. mid=.. a[mid]=..
// =====================================================================
int binarySearchTrace(const vector<int>& a, int x, bool trace) {
    // TODO: viet code cua ban o day
    int lo = 0, hi = (int)a.size() - 1;
    int step = 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (trace) {
            cout << "  step " << step++ << ": lo=" << lo << " hi=" << hi << " mid=" << mid << " a[mid]=" << a[mid] << "\n";
        }
        if (a[mid] == x) {
            return mid;
        } else if (a[mid] < x) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return -1;
}

// =====================================================================
// BAI 2.3b - Bang bam h(k) = k mod m
//   (1) ChainingTable: moi o la mot danh sach, chen vao DAU danh sach (O(1))
//   (2) LinearProbingTable: dung do tuyen tinh (i+1) mod m, o trong = -1
//   search(...) tra ve so lan tham do (probe) de tim thay / ket luan khong co.
// =====================================================================
struct ChainingTable {
    int m; vector<list<int>> slot;
    explicit ChainingTable(int m_) : m(m_), slot(m_) {}
    void insert(int k) {
        // TODO: viet code cua ban o day
        int idx = (k % m + m) % m;
        slot[idx].push_front(k);
    }
    int searchProbes(int k) const {          // so phan tu da xet trong chuoi
        // TODO: viet code cua ban o day
        int idx = (k % m + m) % m;
        int probes = 0;
        for (int v : slot[idx]) {
            probes++;
            if (v == k) return probes;
        }
        return probes;
    }
    void print() const {
        for (int i = 0; i < m; i++) {
            cout << "  [" << setw(2) << i << "]";
            for (int v : slot[i]) cout << " -> " << v;
            cout << "\n";
        }
    }
};
struct LinearProbingTable {
    int m; vector<int> t;
    explicit LinearProbingTable(int m_) : m(m_), t(m_, -1) {}
    bool insert(int k) {                     // false neu bang day
        // TODO: viet code cua ban o day
        for (int step = 0; step < m; step++) {
            int cur = ((k % m + m) % m + step) % m;
            if (t[cur] == -1) {
                t[cur] = k;
                return true;
            }
        }
        return false;
    }
    int searchProbes(int k) const {
        // TODO: viet code cua ban o day
        int probes = 0;
        for (int step = 0; step < m; step++) {
            int cur = ((k % m + m) % m + step) % m;
            probes++;
            if (t[cur] == k || t[cur] == -1) {
                return probes;
            }
        }
        return probes;
    }
    void print() const {
        cout << "  ";
        for (int i = 0; i < m; i++) cout << "[" << i << "]" << (t[i] == -1 ? string("_") : to_string(t[i])) << ' ';
        cout << "\n";
    }
};

// =====================================================================
int main() {
    cout << fixed << setprecision(2);
    cout << "===== BAI 2.1: Selection / Insertion / Bubble =====\n";
    vector<int> sample = {5, 2, 9, 1, 5, 6};
    using SortFn = void (*)(vector<int>&, Stats&);
    vector<pair<string, SortFn>> basic = {{"Selection", selectionSort}, {"Insertion", insertionSort},
                                          {"Bubble", bubbleSort}};
    TRACE = true;
    for (auto& [name, fn] : basic) {
        vector<int> a = sample; Stats st;
        cout << name << " tren 5 2 9 1 5 6:\n";
        fn(a, st);
        cout << "  => comps = " << st.comps << ", moves = " << st.moves
             << (is_sorted(a.begin(), a.end()) ? "  [OK]" : "  [SAI]") << "\n";
    }
    TRACE = false;
    int n = 1000;
    LCG g(2026);
    vector<int> rnd(n); for (int& x : rnd) x = g.range(0, 99999);
    vector<int> asc = rnd; sort(asc.begin(), asc.end());
    vector<int> desc(asc.rbegin(), asc.rend());
    cout << "\nn = 1000      " << setw(22) << "ngau nhien" << setw(22) << "da sap tang" << setw(22)
         << "sap giam" << "\n";
    cout << "(comps / moves)\n";
    for (auto& [name, fn] : basic) {
        cout << setw(10) << name << "   ";
        for (auto* src : {&rnd, &asc, &desc}) {
            vector<int> a = *src; Stats st; fn(a, st);
            string cell = to_string(st.comps) + " / " + to_string(st.moves) +
                          (is_sorted(a.begin(), a.end()) ? "" : " SAI");
            cout << setw(22) << cell;
        }
        cout << "\n";
    }

    cout << "\n===== BAI 2.2: Quick sort vs Merge sort =====\n";
    {
        vector<int> a = sample, b = sample; Stats s1, s2;
        quickSort(a, 0, a.size() - 1, s1); mergeSort(b, 0, b.size() - 1, s2);
        cout << "Mau 5 2 9 1 5 6 -> quick: "; printArr(a);
        cout << "                  merge: "; printArr(b);
    }
    for (auto [label, src] : vector<pair<string, vector<int>*>>{{"ngau nhien n=1000", &rnd}, {"da sap n=1000", &asc}}) {
        vector<int> a = *src, b = *src; Stats s1, s2;
        quickSort(a, 0, n - 1, s1); mergeSort(b, 0, n - 1, s2);
        cout << setw(20) << label << ": quick comps = " << setw(7) << s1.comps << "   merge comps = " << setw(6)
             << s2.comps << ((is_sorted(a.begin(), a.end()) && is_sorted(b.begin(), b.end())) ? "  [OK]" : "  [SAI]")
             << "\n";
    }
    {
        int N = 1000000; LCG h(99);
        vector<int> big(N); for (int& x : big) x = h.range(0, 1000000000);
        vector<int> a = big, b = big, c = big; Stats s1, s2;
        double tq = timeMs([&] { quickSort(a, 0, N - 1, s1); });
        double tm = timeMs([&] { mergeSort(b, 0, N - 1, s2); });
        double ts = timeMs([&] { sort(c.begin(), c.end()); });
        cout << "N = 1 000 000 ngau nhien: quick " << tq << " ms | merge " << tm << " ms | std::sort " << ts
             << " ms" << ((a == c && b == c) ? "  [OK]" : "  [SAI]") << "\n";
    }

    cout << "\n===== BAI 2.3a: Tim kiem nhi phan =====\n";
    vector<int> sorted10 = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    for (int x : {23, 91, 4}) {
        cout << "Tim x = " << x << ":\n";
        int pos = binarySearchTrace(sorted10, x, true);
        cout << "  => pos = " << pos << "\n";
    }
    {
        bool ok = true;
        for (int i = 0; i < 10; i++) ok &= binarySearchTrace(sorted10, sorted10[i], false) == i;
        ok &= binarySearchTrace(sorted10, 100, false) == -1 && binarySearchTrace(sorted10, 1, false) == -1;
        cout << "Kiem tra 12 truy van: " << (ok ? "[OK]" : "[SAI]") << "\n";
    }

    cout << "\n===== BAI 2.3b: Bang bam, m = 11 =====\n";
    for (auto keys : vector<vector<int>>{{12, 25, 35, 26, 5}, {22, 33, 44, 1, 12}}) {
        cout << "Khoa:"; for (int k : keys) cout << ' ' << k; cout << "\n";
        ChainingTable ch(11); LinearProbingTable lp(11);
        for (int k : keys) { ch.insert(k); lp.insert(k); }
        cout << " Chaining:\n"; ch.print();
        cout << " Linear probing:\n"; lp.print();
        cout << " So probe khi tim (chaining / linear):";
        for (int k : keys) cout << "  " << k << ":" << ch.searchProbes(k) << "/" << lp.searchProbes(k);
        cout << "  | khoa 23 (khong co): " << ch.searchProbes(23) << "/" << lp.searchProbes(23) << "\n";
    }
    return 0;
}
