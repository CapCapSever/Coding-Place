// =====================================================================
//  LAB 4B (VE NHA) - CHUONG 4: CAU TRUC DU LIEU TRUU TUONG
//  Co ban    : 4B.1 DS lien ket kep co thu tu | 4B.2 DS vong - Josephus | 4B.3 Hang doi vong + Deque
//  Trung binh: 4B.4 Heap + Heap sort          | 4B.5 Trung to -> Hau to
//  Nang cao  : 4B.6 Dijkstra + Floyd-Warshall | 4B.7 Kruskal + Prim    | 4B.8 (thu thach) AVL
//  Bien dich:  g++ -O2 -std=c++17 -Wall -o lab4B lab4B_ve_nha.cpp
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
int passed = 0, total = 0;
void check(const string& name, const string& got, const string& expect) {
    total++; bool ok = got == expect; passed += ok;
    cout << "  " << left << setw(36) << name << right << " -> " << got << (ok ? "   [OK]" : "   [SAI] can: " + expect) << "\n";
}
string join(const vector<int>& v) { string s; for (size_t i = 0; i < v.size(); i++) s += (i ? " " : "") + to_string(v[i]); return s; }

// =====================================================================
// 4B.1 (CO BAN) - Danh sach lien ket KEP luon giu thu tu TANG (sorted doubly linked list)
//   insert(x): chen x SAU cac phan tu <= x (on dinh). remove(x): xoa nut dau tien == x.
// =====================================================================
struct DNode { int data; DNode *prev = nullptr, *next = nullptr; explicit DNode(int d) : data(d) {} };
class SortedDList {
    DNode *head = nullptr, *tail = nullptr;
public:
    ~SortedDList() { while (head) { DNode* t = head; head = head->next; delete t; } }
    void insert(int x) {
        // TODO: viet code cua ban o day
    }
    bool remove(int x) {
        // TODO: viet code cua ban o day
        return false;
    }
    string forward() const { vector<int> v; for (DNode* p = head; p; p = p->next) v.push_back(p->data); return join(v); }
    string backward() const { vector<int> v; for (DNode* p = tail; p; p = p->prev) v.push_back(p->data); return join(v); }
};

// =====================================================================
// 4B.2 (CO BAN) - Danh sach lien ket VONG: bai toan Josephus
//   n nguoi 1..n dung thanh vong, dem tu nguoi 1, nguoi thu k bi loai, tiep tuc dem tu nguoi ke tiep.
//   Tra ve thu tu bi loai (phan tu cuoi cung = nguoi song sot). Phai dung DS vong tu cai dat.
// =====================================================================
struct CNode { int id; CNode* next; };
vector<int> josephus(int n, int k) {
    vector<int> order;
    // TODO: viet code cua ban o day
    return order;
}

// =====================================================================
// 4B.3 (CO BAN) - Hang doi vong bang mang + ung dung Deque (cua so truot)
// =====================================================================
class CircularQueue {
    vector<int> a; int front_ = 0, count_ = 0;
public:
    explicit CircularQueue(int cap) : a(cap) {}
    bool empty() const { return count_ == 0; }
    bool full() const { return count_ == (int)a.size(); }
    int size() const { return count_; }
    bool enqueue(int x) {                                // false neu day
        // TODO: viet code cua ban o day
        return false;
    }
    int dequeue() {                                      // goi khi khong rong
        // TODO: viet code cua ban o day
        return 0;
    }
    int front() const {
        // TODO: viet code cua ban o day
        return 0;
    }
};
// Gia tri lon nhat cua moi cua so do dai k. Dung deque chua CHI SO, gia tri giam dan. O(n).
vector<int> slidingMax(const vector<int>& a, int k) {
    vector<int> res;
    // TODO: viet code cua ban o day
    return res;
}
vector<int> slidingMaxBrute(const vector<int>& a, int k) {
    vector<int> r; for (int i = 0; i + k <= (int)a.size(); i++) r.push_back(*max_element(a.begin() + i, a.begin() + i + k));
    return r;
}

// =====================================================================
// 4B.4 (TRUNG BINH) - Min-heap tren mang (goc o chi so 0, con cua i la 2i+1, 2i+2)
//   + heapSort tai cho (dung MAX-heap, siftDown) + topK lon nhat (dung min-heap kich thuoc k)
// =====================================================================
class MinHeap {
public:
    vector<int> h;
    void push(int x) {                                   // them cuoi + siftUp
        // TODO: viet code cua ban o day
    }
    int pop() {                                          // lay goc; dua phan tu cuoi len goc + siftDown
        // TODO: viet code cua ban o day
        return 0;
    }
    int peek() const { return h[0]; }
    int size() const { return h.size(); }
};
void siftDownMax(vector<int>& a, int i, int n) {
    // TODO: viet code cua ban o day
}
void heapSort(vector<int>& a) {                          // build max-heap O(n) roi lan luot dua max ve cuoi
    // TODO: viet code cua ban o day
}
vector<int> topK(const vector<int>& a, int k) {          // k phan tu lon nhat, tra ve theo thu tu GIAM
    vector<int> res;
    // TODO: viet code cua ban o day
    return res;
}

// =====================================================================
// 4B.5 (TRUNG BINH) - Chuyen trung to -> hau to (thuat toan shunting-yard cua Dijkstra)
//   Toan hang: so nhieu chu so hoac mot chu cai. Toan tu: + - (uu tien 1), * / (2), ^ (3, KET HOP PHAI).
//   Ket qua: cac token cach nhau mot dau cach. evalPostfix: tinh bieu thuc so nguyen (^ la luy thua).
// =====================================================================
int prec(char op) { return op == '^' ? 3 : (op == '*' || op == '/') ? 2 : (op == '+' || op == '-') ? 1 : 0; }
string infixToPostfix(const string& s) {
    vector<string> out;
    // TODO: viet code cua ban o day
    string r; for (size_t i = 0; i < out.size(); i++) r += (i ? " " : "") + out[i];
    return r;
}
long long evalPostfix(const string& expr) {
    // TODO: viet code cua ban o day
    return 0;
}

// =====================================================================
// 4B.6 (NANG CAO) - Duong di ngan nhat tren do thi CO HUONG, trong so khong am
//   dijkstra: dung priority_queue (min-heap) cap (dist, dinh); bo qua phan tu cu (lazy deletion).
//   floydWarshall: ma tran khoang cach moi cap, dung de KIEM CHUNG ket qua Dijkstra.
// =====================================================================
const long long INF = LLONG_MAX / 4;
typedef vector<vector<pair<int, int>>> WAdj;             // adj[u] = {(v, w)}
vector<long long> dijkstra(const WAdj& adj, int s, vector<int>& parent) {
    int n = adj.size(); vector<long long> d(n, INF); parent.assign(n, -1);
    // TODO: viet code cua ban o day
    return d;
}
vector<vector<long long>> floydWarshall(const WAdj& adj) {
    int n = adj.size(); vector<vector<long long>> D(n, vector<long long>(n, INF));
    // TODO: viet code cua ban o day
    return D;
}

// =====================================================================
// 4B.7 (NANG CAO) - Cay khung nho nhat tren do thi VO HUONG
//   kruskal: sap canh theo (w, u, v) tang dan, dung DSU (hop theo hang + nen duong).
//            Tra ve tong trong so; 'chosen' = cac canh duoc chon theo thu tu chon.
//   prim   : bat dau tu dinh 0, dung min-heap; tra ve tong trong so (de doi chieu).
// =====================================================================
struct Edge { int u, v, w; };
struct DSU {
    vector<int> p, r;
    explicit DSU(int n) : p(n), r(n, 0) { iota(p.begin(), p.end(), 0); }
    int find(int x) {
        // TODO: viet code cua ban o day
        return x;
    }
    bool unite(int a, int b) {
        // TODO: viet code cua ban o day
        return false;
    }
};
long long kruskal(int n, vector<Edge> edges, vector<Edge>& chosen) {
    long long total = 0; chosen.clear();
    // TODO: viet code cua ban o day
    return total;
}
long long prim(int n, const vector<Edge>& edges) {
    long long total = 0;
    // TODO: viet code cua ban o day
    return total;
}

// =====================================================================
// 4B.8 (THU THACH) - Cay AVL: chen co tu can bang. height: so nut (rong = 0, la = 1).
//   Dem tong so phep xoay don ('rotations'): LL/RR = 1, LR/RL = 2.
// =====================================================================
struct ANode { int key, h = 1; ANode *l = nullptr, *r = nullptr; explicit ANode(int k) : key(k) {} };
int rotations = 0;
int H(ANode* t) { return t ? t->h : 0; }
void upd(ANode* t) { t->h = 1 + max(H(t->l), H(t->r)); }
ANode* rotRight(ANode* y) {
    // TODO: viet code cua ban o day
    return y;
}
ANode* rotLeft(ANode* x) {
    // TODO: viet code cua ban o day
    return x;
}
ANode* avlInsert(ANode* t, int k) {
    // TODO: viet code cua ban o day
    return t ? t : new ANode(k);
}
void pre(ANode* t, vector<int>& v) { if (t) { v.push_back(t->key); pre(t->l, v); pre(t->r, v); } }
void freeAvl(ANode* t) { if (t) { freeAvl(t->l); freeAvl(t->r); delete t; } }
int heightAny(ANode* t) { return t ? 1 + max(heightAny(t->l), heightAny(t->r)) : 0; }   // tinh lai, khong dung h

// =====================================================================
int main() {
    cout << "===== 4B.1: DS lien ket kep co thu tu =====\n";
    {
        SortedDList L;
        for (int x : {30, 10, 50, 20, 40, 10}) L.insert(x);
        check("insert 30 10 50 20 40 10", L.forward() + " | " + L.backward(), "10 10 20 30 40 50 | 50 40 30 20 10 10");
        bool a = L.remove(10), b = L.remove(50), c = L.remove(99);
        L.insert(5); L.insert(60);
        check("remove 10,50,99; insert 5,60", L.forward() + " | " + L.backward() + " | " + (a ? "T" : "F") + (b ? "T" : "F") + (c ? "T" : "F"),
              "5 10 20 30 40 60 | 60 40 30 20 10 5 | TTF");
    }
    cout << "\n===== 4B.2: Josephus =====\n";
    {
        check("n=7, k=3 (thu tu bi loai)", join(josephus(7, 3)), "3 6 2 7 5 1 4");
        check("n=10, k=2 song sot", to_string(josephus(10, 2).empty() ? 0 : josephus(10, 2).back()), "5");
        check("n=41, k=3 song sot", to_string(josephus(41, 3).empty() ? 0 : josephus(41, 3).back()), "31");
        check("n=1, k=5", join(josephus(1, 5)), "1");
    }
    cout << "\n===== 4B.3: Hang doi vong + cua so truot =====\n";
    {
        CircularQueue q(5); string s;
        for (int i = 1; i <= 5; i++) q.enqueue(i);
        s += q.enqueue(6) ? "ok " : "full ";
        int d1 = q.dequeue(); int d2 = q.dequeue(); s += to_string(d1) + to_string(d2) + " ";
        q.enqueue(6); q.enqueue(7);
        s += "front=" + to_string(q.front()) + " size=" + to_string(q.size()) + " :";
        while (!q.empty()) s += " " + to_string(q.dequeue());
        check("cap 5: 1..5, +6, -2, +6 +7, xa het", s, "full 12 front=3 size=5 : 3 4 5 6 7");
        check("slidingMax [1 3 -1 -3 5 3 6 7], k=3", join(slidingMax({1, 3, -1, -3, 5, 3, 6, 7}, 3)), "3 3 5 5 6 7");
        LCG g(12); vector<int> a(5000); for (int& x : a) x = g.range(-1000, 1000);
        check("n=5000, k=50: khop vet can?", slidingMax(a, 50) == slidingMaxBrute(a, 50) ? "khop" : "lech", "khop");
    }
    cout << "\n===== 4B.4: Heap =====\n";
    {
        MinHeap hp; for (int x : {5, 3, 8, 1, 9, 2}) hp.push(x);
        check("mang heap sau push 5 3 8 1 9 2", join(hp.h), "1 3 2 5 9 8");
        vector<int> out; while (hp.size()) out.push_back(hp.pop());
        check("pop het", join(out), "1 2 3 5 8 9");
        vector<int> b = {4, 10, 3, 5, 1, 7, 7, 2}; heapSort(b);
        check("heapSort 4 10 3 5 1 7 7 2", join(b), "1 2 3 4 5 7 7 10");
        LCG g(21); vector<int> a(100000); for (int& x : a) x = g.range(0, 1000000);
        vector<int> c = a, d = a; heapSort(c); sort(d.begin(), d.end());
        check("heapSort 100000 so ngau nhien", c == d ? "dung" : "sai", "dung");
        vector<int> e(d.rbegin(), d.rbegin() + 5);
        check("top-5 lon nhat", join(topK(a, 5)), join(e));
    }
    cout << "\n===== 4B.5: Trung to -> Hau to =====\n";
    {
        check("a+b*c", infixToPostfix("a+b*c"), "a b c * +");
        check("(a+b)*(c-d)/e", infixToPostfix("(a+b)*(c-d)/e"), "a b + c d - * e /");
        check("a-b-c (ket hop trai)", infixToPostfix("a-b-c"), "a b - c -");
        check("a^b^c (ket hop phai)", infixToPostfix("a^b^c"), "a b c ^ ^");
        check("3+4*2/(1-5)^2^3", infixToPostfix("3+4*2/(1-5)^2^3"), "3 4 2 * 1 5 - 2 3 ^ ^ / +");
        check("gia tri (12+3)*4-100/(2+3)", to_string(evalPostfix(infixToPostfix("(12+3)*4-100/(2+3)"))), "40");
        check("gia tri 2^3^2", to_string(evalPostfix(infixToPostfix("2^3^2"))), "512");
    }
    cout << "\n===== 4B.6: Dijkstra + Floyd-Warshall =====\n";
    {
        int n = 6; WAdj adj(n);
        vector<Edge> E = {{0, 1, 4}, {0, 2, 1}, {2, 1, 2}, {1, 3, 1}, {2, 3, 5}, {3, 4, 3}, {4, 5, 1}, {3, 5, 6}, {2, 4, 8}};
        for (auto& e : E) adj[e.u].push_back({e.v, e.w});
        vector<int> par; auto d = dijkstra(adj, 0, par);
        vector<int> dv(d.begin(), d.end());
        check("dist tu 0", join(dv), "0 3 1 4 7 8");
        vector<int> p; for (int v = 5; v != -1; v = par[v]) p.push_back(v); reverse(p.begin(), p.end());
        check("duong di 0 -> 5", join(p), "0 2 1 3 4 5");
        auto D = floydWarshall(adj);
        bool ok = true; for (int v = 0; v < n; v++) ok &= D[0][v] == d[v];
        check("Floyd dong 0 khop Dijkstra?", ok ? "khop" : "lech", "khop");
        check("Floyd D[3][0] (khong toi duoc)", D[3][0] >= INF ? "INF" : to_string(D[3][0]), "INF");
        // do thi ngau nhien lon hon: 200 dinh, 2000 canh
        LCG g(33); int N = 200; WAdj A(N);
        for (int i = 0; i < 2000; i++) { int u = g.range(0, N - 1), v = g.range(0, N - 1), w = g.range(1, 100); A[u].push_back({v, w}); }
        auto D2 = floydWarshall(A); bool all = true; long long sum = 0;
        for (int s = 0; s < N; s++) { vector<int> pp; auto ds = dijkstra(A, s, pp); for (int v = 0; v < N; v++) { all &= ds[v] == D2[s][v]; if (ds[v] < INF) sum += ds[v]; } }
        check("200 dinh: Dijkstra x200 == Floyd?", all ? "khop" : "lech", "khop");
        cout << "  (tong moi khoang cach toi duoc = " << sum << ")\n";
    }
    cout << "\n===== 4B.7: Kruskal + Prim =====\n";
    {
        vector<Edge> E = {{0, 1, 7}, {0, 3, 5}, {1, 2, 8}, {1, 3, 9}, {1, 4, 7}, {2, 4, 5}, {3, 4, 15},
                          {3, 5, 6}, {4, 5, 8}, {4, 6, 9}, {5, 6, 11}};
        vector<Edge> ch; long long w = kruskal(7, E, ch);
        string s; for (auto& e : ch) s += "(" + to_string(e.u) + "," + to_string(e.v) + "," + to_string(e.w) + ")";
        check("Kruskal: canh chon", s, "(0,3,5)(2,4,5)(3,5,6)(0,1,7)(1,4,7)(4,6,9)");
        check("Kruskal / Prim tong trong so", to_string(w) + " / " + to_string(prim(7, E)), "39 / 39");
        LCG g(44); int N = 300; vector<Edge> R;
        for (int i = 1; i < N; i++) R.push_back({g.range(0, i - 1), i, g.range(1, 1000)});   // dam bao lien thong
        for (int i = 0; i < 3000; i++) { int u = g.range(0, N - 1), v = g.range(0, N - 1); if (u != v) R.push_back({min(u, v), max(u, v), g.range(1, 1000)}); }
        long long k1 = kruskal(N, R, ch), p1 = prim(N, R);
        check("300 dinh: Kruskal == Prim?", (k1 == p1 && (int)ch.size() == N - 1) ? "khop" : "lech", "khop");
        cout << "  (trong so MST = " << k1 << ")\n";
    }
    cout << "\n===== 4B.8: AVL (thu thach) =====\n";
    {
        ANode* t = nullptr; rotations = 0;
        for (int k : {10, 20, 30, 40, 50, 25}) t = avlInsert(t, k);
        vector<int> v; pre(t, v);
        check("chen 10 20 30 40 50 25: preorder", join(v) + " | h=" + to_string(heightAny(t)) + " rot=" + to_string(rotations),
              "30 20 10 25 40 50 | h=3 rot=4");
        freeAvl(t); t = nullptr; rotations = 0;
        for (int k = 1; k <= 1000; k++) t = avlInsert(t, k);
        check("chen 1..1000 tang dan: chieu cao", to_string(heightAny(t)), "10");
        freeAvl(t);
    }
    cout << "\nTONG: " << passed << "/" << total << " test dung\n";
    return 0;
}
