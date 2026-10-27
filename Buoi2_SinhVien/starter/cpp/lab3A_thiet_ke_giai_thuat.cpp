// =====================================================================
//  LAB 3A (TREN LOP) - CHUONG 3: KY THUAT THIET KE GIAI THUAT
//  3.1 Sinh ke tiep | 3.2 Quay lui | 3.3 Quy hoach dong
//  Bien dich:  g++ -O2 -std=c++17 -Wall -o lab3A lab3A_thiet_ke_giai_thuat.cpp
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

// =====================================================================
// BAI 3.1 - Sinh ke tiep: to hop chap k cua {1..n} theo thu tu tu dien
//   Cau hinh dau: 1 2 ... k        Cau hinh cuoi: n-k+1 ... n
//   nextCombination: bien c thanh cau hinh ke tiep, tra ve false neu c la cau hinh cuoi.
//   Y tuong: tim i lon nhat co c[i] < n - k + i + 1 (chi so tu 0),
//            tang c[i] len 1, roi dat c[j] = c[j-1] + 1 voi j > i.
// =====================================================================
bool nextCombination(vector<int>& c, int n) {
    // TODO: viet code cua ban o day
    int k = c.size();
    int i = 0;
    for(int i = k-1; i>=0; i--){
        if(c[i] == n-k+1+i) continue;
        c[i]++;
        for(int j = i+1; j < k; j++){
            c[j] = c[j-1]+1;
        }
        return true;
    }
    return false;
}
long long binom(int n, int k) {            // C(n,k) theo cong thuc (da cho san)
    long long r = 1;
    for (int i = 1; i <= k; i++) r = r * (n - k + i) / i;
    return r;
}

// =====================================================================
// BAI 3.2 - Quay lui: liet ke cac tap con cua a (DA SAP TANG) co tong = S
//   Try(start, sum): voi j = start..n-1 -> chon a[j], neu sum + a[j] == S thi ghi nhan,
//                    neu < S thi goi Try(j+1, sum + a[j]).
//   'nodes' tang 1 moi lan GOI Try.
//   prune = true  : gap sum + a[j] > S thi BREAK (vi mang da sap, cac j sau con lon hon)
//   prune = false : khong cat nhanh, van de quy ca khi tong da vuot S
// =====================================================================
long long nodes = 0;
vector<vector<int>> found;
void trySubset(const vector<int>& a, int S, int start, int sum, vector<int>& cur, bool prune) {
    // TODO: viet code cua ban o day
}

// =====================================================================
// BAI 3.3 - Quy hoach dong: xau con chung dai nhat (LCS)
//   L[i][j] = do dai LCS cua X[0..i-1] va Y[0..j-1]
//   L[i][j] = L[i-1][j-1] + 1               neu X[i-1] == Y[j-1]
//           = max(L[i-1][j], L[i][j-1])     nguoc lai
//   Truy vet tu (m, n): neu X[i-1]==Y[j-1] -> lay ky tu, di cheo;
//                       neu L[i-1][j] >= L[i][j-1] -> di LEN (i-1); nguoc lai di TRAI (j-1).
// =====================================================================
vector<vector<int>> lcsTable(const string& X, const string& Y) {
    int m = X.size(), n = Y.size();
    vector<vector<int>> L(m + 1, vector<int>(n + 1, 0));
    // TODO: viet code cua ban o day
    return L;
}
string lcsTrace(const string& X, const string& Y, const vector<vector<int>>& L) {
    string res;
    // TODO: viet code cua ban o day
    return res;
}
// Kiem tra Z co la day con cua X khong (da cho san)
bool isSubseq(const string& Z, const string& X) {
    size_t k = 0; for (char c : X) if (k < Z.size() && Z[k] == c) k++;
    return k == Z.size();
}

// =====================================================================
int main() {
    cout << "===== BAI 3.1: Sinh to hop chap k cua n =====\n";
    {
        int n = 5, k = 3; vector<int> c(k); iota(c.begin(), c.end(), 1);
        int cnt = 0;
        do { cnt++; cout << setw(3) << cnt << ":"; for (int x : c) cout << ' ' << x; cout << "\n"; }
        while (nextCombination(c, n));
        cout << "So to hop C(5,3) = " << cnt << (cnt == binom(5, 3) ? "  [OK]" : "  [SAI]") << "\n";
        bool ok = true;
        for (auto [nn, kk] : vector<pair<int, int>>{{10, 4}, {12, 6}, {20, 3}}) {
            vector<int> d(kk); iota(d.begin(), d.end(), 1); long long t = 0;
            do t++; while (nextCombination(d, nn));
            cout << "C(" << nn << "," << kk << "): sinh duoc " << t << ", cong thuc " << binom(nn, kk) << "\n";
            ok &= t == binom(nn, kk);
        }
        cout << (ok ? "[OK]" : "[SAI]") << "\n";
    }

    cout << "\n===== BAI 3.2: Quay lui - tap con co tong S =====\n";
    {
        vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int S = 15; vector<int> cur;
        found.clear(); nodes = 0;
        trySubset(a, S, 0, 0, cur, false);
        long long nodesNo = nodes; size_t cntNo = found.size();
        found.clear(); nodes = 0;
        trySubset(a, S, 0, 0, cur, true);
        cout << "a = 1..10, S = 15: so tap con = " << found.size() << "\n";
        for (size_t i = 0; i < found.size(); i++) {
            cout << "  {"; for (size_t t = 0; t < found[i].size(); t++) cout << (t ? "," : "") << found[i][t];
            cout << "}" << ((i % 5 == 4) ? "\n" : "");
        }
        cout << "So nut KHONG cat nhanh = " << nodesNo << " | CO cat nhanh = " << nodes
             << ((cntNo == found.size() && found.size() == 20) ? "  [OK]" : "  [SAI]") << "\n";
    }

    cout << "\n===== BAI 3.3: QHD - Xau con chung dai nhat =====\n";
    vector<pair<string, string>> tests = {{"ABCBDAB", "BDCABA"}, {"QUYHOACHDONG", "QUAYLUINHANHCAN"},
                                          {"AGGTAB", "GXTXAYB"}};
    for (auto& [X, Y] : tests) {
        auto L = lcsTable(X, Y);
        string z = lcsTrace(X, Y, L);
        bool ok = (int)z.size() == L[X.size()][Y.size()] && isSubseq(z, X) && isSubseq(z, Y) && !z.empty();
        cout << X << " / " << Y << " -> do dai " << L[X.size()][Y.size()] << ", LCS = " << z
             << (ok ? "  [OK]" : "  [SAI]") << "\n";
        if (X == "ABCBDAB") {
            cout << "     ";
            for (char c : Y) cout << setw(3) << c;
            cout << "\n";
            for (size_t i = 1; i <= X.size(); i++) {
                cout << "  " << X[i - 1] << "  ";
                for (size_t j = 1; j <= Y.size(); j++) cout << setw(3) << L[i][j];
                cout << "\n";
            }
        }
    }
    return 0;
}
