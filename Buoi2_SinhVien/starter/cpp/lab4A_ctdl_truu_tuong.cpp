// =====================================================================
//  LAB 4A (TREN LOP) - CHUONG 4: CAU TRUC DU LIEU TRUU TUONG
//  4.1 Danh sach lien ket don | 4.2 Ngan xep | 4.3 Cay BST | 4.4 Do thi BFS/DFS
//  Bien dich:  g++ -O2 -std=c++17 -Wall -o lab4A lab4A_ctdl_truu_tuong.cpp
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

int passed = 0, total = 0;
void check(const string& name, const string& got, const string& expect) {
    total++; bool ok = got == expect; passed += ok;
    cout << "  " << left << setw(34) << name << right << " -> " << got << (ok ? "   [OK]" : "   [SAI] can: " + expect) << "\n";
}

// =====================================================================
// BAI 4.1 - Danh sach lien ket don (Singly linked list)
// =====================================================================
struct Node { int data; Node* next; Node(int d, Node* n = nullptr) : data(d), next(n) {} };

class SinglyLinkedList {
    Node* head = nullptr;
    int count = 0;
public:
    ~SinglyLinkedList() { while (head) { Node* t = head; head = head->next; delete t; } }
    int size() const { return count; }
    string toString() const {                       // dang "[1 -> 2 -> 3]" (da cho san)
        string s = "[";
        for (Node* p = head; p; p = p->next) s += to_string(p->data) + (p->next ? " -> " : "");
        return s + "]";
    }
    void pushFront(int x) {                          // O(1)
        // TODO: viet code cua ban o day
    }
    void pushBack(int x) {                           // O(n) - duyet den cuoi
        // TODO: viet code cua ban o day
    }
    bool insertAt(int pos, int x) {                  // chen de x nam o vi tri pos (0..count)
        // TODO: viet code cua ban o day
        return false;
    }
    int find(int x) const {                          // vi tri dau tien, khong co -> -1
        // TODO: viet code cua ban o day
        return -1;
    }
    bool removeValue(int x) {                        // xoa nut DAU TIEN co data == x
        // TODO: viet code cua ban o day
        return false;
    }
    void reverse() {                                 // dao nguoc tai cho, O(n), O(1) bo nho
        // TODO: viet code cua ban o day
    }
};

// =====================================================================
// BAI 4.2 - Ngan xep cai dat bang MANG + hai ung dung
// =====================================================================
class ArrayStack {
    vector<int> a; int topIdx = -1;
public:
    explicit ArrayStack(int capacity) : a(capacity) {}
    bool empty() const {
        // TODO: viet code cua ban o day
        return true;
    }
    bool full() const {
        // TODO: viet code cua ban o day
        return false;
    }
    bool push(int x) {                               // false neu day (overflow)
        // TODO: viet code cua ban o day
        return false;
    }
    int pop() {                                      // goi khi khong rong
        // TODO: viet code cua ban o day
        return 0;
    }
    int top() const {
        // TODO: viet code cua ban o day
        return 0;
    }
};
// (a) Kiem tra ngoac can bang: ( ) [ ] { }; cac ky tu khac bo qua
bool isBalanced(const string& s) {
    // TODO: viet code cua ban o day
    return false;
}
// (b) Tinh bieu thuc hau to, cac token cach nhau mot dau cach; toan tu + - * / (chia nguyen)
int evalPostfix(const string& expr) {
    // TODO: viet code cua ban o day
    return 0;
}

// =====================================================================
// BAI 4.3 - Cay nhi phan tim kiem (BST). Khoa trung lap: bo qua.
//   height: so NUT tren duong di dai nhat tu goc (cay rong = 0, mot nut = 1)
//   remove: nut co 2 con -> thay bang nut NHO NHAT cua cay con PHAI (successor)
// =====================================================================
struct TNode { int key; TNode *left = nullptr, *right = nullptr; explicit TNode(int k) : key(k) {} };

class BST {
    TNode* root = nullptr;
    static void destroy(TNode* t) { if (t) { destroy(t->left); destroy(t->right); delete t; } }
    static TNode* insertRec(TNode* t, int k) {
        // TODO: viet code cua ban o day
        return t;
    }
    static void inorderRec(TNode* t, string& s) {
        // TODO: viet code cua ban o day
    }
    static void preorderRec(TNode* t, string& s) {
        // TODO: viet code cua ban o day
    }
    static int heightRec(TNode* t) {
        // TODO: viet code cua ban o day
        return 0;
    }
    static TNode* removeRec(TNode* t, int k) {
        // TODO: viet code cua ban o day
        return t;
    }
public:
    ~BST() { destroy(root); }
    void insert(int k) { root = insertRec(root, k); }
    void remove(int k) { root = removeRec(root, k); }
    bool contains(int k) const {                     // lap, khong de quy
        // TODO: viet code cua ban o day
        return false;
    }
    int minKey() const {                             // goi khi cay khong rong
        // TODO: viet code cua ban o day
        return 0;
    }
    int maxKey() const {
        // TODO: viet code cua ban o day
        return 0;
    }
    int height() const { return heightRec(root); }
    string inorder() const { string s; inorderRec(root, s); if (!s.empty()) s.pop_back(); return s; }
    string preorder() const { string s; preorderRec(root, s); if (!s.empty()) s.pop_back(); return s; }
};

// =====================================================================
// BAI 4.4 - Do thi vo huong: danh sach ke, BFS, DFS, thanh phan lien thong
//   Danh sach ke cua moi dinh SAP TANG -> thu tu duyet xac dinh duy nhat.
// =====================================================================
struct Graph {
    int n; vector<vector<int>> adj;
    Graph(int n_, const vector<pair<int, int>>& edges) : n(n_), adj(n_) {
        // TODO: viet code cua ban o day
    }
    // BFS tu s: tra ve thu tu tham; dist[v] = so canh it nhat tu s (-1 neu khong toi), parent[v]
    vector<int> bfs(int s, vector<int>& dist, vector<int>& parent) const {
        vector<int> order; dist.assign(n, -1); parent.assign(n, -1);
        // TODO: viet code cua ban o day
        return order;
    }
    void dfsRec(int u, vector<bool>& vis, vector<int>& order) const {
        // TODO: viet code cua ban o day
    }
    vector<int> dfs(int s) const { vector<bool> vis(n, false); vector<int> order; dfsRec(s, vis, order); return order; }
    int components() const {
        // TODO: viet code cua ban o day
        return 0;
    }
};
string join(const vector<int>& v) { string s; for (size_t i = 0; i < v.size(); i++) s += (i ? " " : "") + to_string(v[i]); return s; }
string pathTo(int t, const vector<int>& parent) {
    vector<int> p; for (int v = t; v != -1; v = parent[v]) p.push_back(v);
    reverse(p.begin(), p.end()); return join(p);
}

// =====================================================================
int main() {
    cout << "===== BAI 4.1: Danh sach lien ket don =====\n";
    {
        SinglyLinkedList L;
        L.pushBack(10); L.pushBack(20); L.pushFront(5); L.pushBack(30);
        check("pushBack 10,20; pushFront 5; pushBack 30", L.toString(), "[5 -> 10 -> 20 -> 30]");
        L.insertAt(2, 15); L.insertAt(0, 1); L.insertAt(L.size(), 99);
        check("insertAt(2,15), (0,1), (size,99)", L.toString(), "[1 -> 5 -> 10 -> 15 -> 20 -> 30 -> 99]");
        check("find(20), find(7)", to_string(L.find(20)) + " " + to_string(L.find(7)), "4 -1");
        L.removeValue(1); L.removeValue(15); L.removeValue(99); bool r = L.removeValue(42);
        check("remove 1,15,99,42", L.toString() + " " + (r ? "true" : "false"), "[5 -> 10 -> 20 -> 30] false");
        L.reverse();
        check("reverse", L.toString() + " size=" + to_string(L.size()), "[30 -> 20 -> 10 -> 5] size=4");
    }

    cout << "\n===== BAI 4.2: Ngan xep =====\n";
    {
        ArrayStack st(3); string s;
        s += st.empty() ? "E " : "N ";
        st.push(1); st.push(2); st.push(3); bool over = st.push(4);
        s += string(st.full() ? "F " : "- ") + (over ? "push4=ok " : "push4=overflow ");
        int p1 = st.pop(); int p2 = st.pop();          // tach rieng: thu tu tinh toan hang khong xac dinh
        s += to_string(p1) + to_string(p2) + " top=" + to_string(st.top());
        check("stack cap 3: push 1,2,3,4; pop x2", s, "E F push4=overflow 32 top=1");
        string b;
        for (string e : {"{[()()]}", "([)]", "((a+b)*c", "a[i] = f(x) + {y}", ")("}) b += isBalanced(e) ? "T" : "F";
        check("ngoac: {[()()]} ([)] ((a+b)*c ...", b, "TFFTF");
        check("hau to: 2 3 4 * + 5 -", to_string(evalPostfix("2 3 4 * + 5 -")), "9");
        check("hau to: 5 1 2 + 4 * + 3 -", to_string(evalPostfix("5 1 2 + 4 * + 3 -")), "14");
        check("hau to: 100 7 / 3 -", to_string(evalPostfix("100 7 / 3 -")), "11");
    }

    cout << "\n===== BAI 4.3: Cay nhi phan tim kiem =====\n";
    {
        BST T;
        for (int k : {50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 40}) T.insert(k);
        check("inorder", T.inorder(), "20 30 35 40 45 50 60 65 70 80");
        check("preorder", T.preorder(), "50 30 20 40 35 45 70 60 65 80");
        check("height / min / max", to_string(T.height()) + " " + to_string(T.minKey()) + " " + to_string(T.maxKey()), "4 20 80");
        check("contains 45, 55", string(T.contains(45) ? "T" : "F") + (T.contains(55) ? "T" : "F"), "TF");
        T.remove(20);
        check("remove 20 (la)", T.preorder(), "50 30 40 35 45 70 60 65 80");
        T.remove(60);
        check("remove 60 (1 con)", T.preorder(), "50 30 40 35 45 70 65 80");
        T.remove(40);
        check("remove 40 (2 con)", T.preorder(), "50 30 45 35 70 65 80");
        T.remove(50);
        check("remove 50 (goc, 2 con)", T.preorder() + " | h=" + to_string(T.height()), "65 30 45 35 70 80 | h=4");
    }

    cout << "\n===== BAI 4.4: Do thi BFS / DFS =====\n";
    {
        vector<pair<int, int>> E = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}, {4, 5}, {2, 6}, {6, 5}, {7, 8}};
        Graph G(9, E);
        string a; for (int v : G.adj[3]) a += to_string(v) + " ";
        check("adj[3]", a, "1 2 4 ");
        vector<int> dist, par;
        auto ob = G.bfs(0, dist, par);
        check("BFS(0) thu tu", join(ob), "0 1 2 3 6 4 5");
        check("dist tu 0 (0..8)", join(dist), "0 1 1 2 3 3 2 -1 -1");
        check("duong di ngan nhat 0 -> 5", pathTo(5, par), "0 2 6 5");
        check("DFS(0) thu tu", join(G.dfs(0)), "0 1 3 2 6 5 4");
        check("so thanh phan lien thong", to_string(G.components()), "2");
    }
    cout << "\nTONG: " << passed << "/" << total << " test dung\n";
    return 0;
}
