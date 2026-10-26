# =====================================================================
#  LAB 1B (VE NHA) - CHUONG 1: DO PHUC TAP THUAT TOAN
#  Muc do:  1B.1-1B.2 Co ban | 1B.3 Trung binh | 1B.4 Nang cao
#  Chay:  python lab1B_ve_nha.py
# =====================================================================
import math
import sys
import time
from bisect import bisect_left

sys.setrecursionlimit(10000)


class LCG:
    def __init__(self, seed):
        self.x = seed

    def next(self):
        self.x = (self.x * 1103515245 + 12345) & 0x7FFFFFFF
        return self.x

    def range(self, lo, hi):
        return lo + self.next() % (hi - lo + 1)


def time_ms(f):
    t0 = time.perf_counter()
    r = f()
    return r, (time.perf_counter() - t0) * 1000


# =====================================================================
# 1B.1 (CO BAN) - Tim kiem tuyen tinh. Moi lan so sanh a[i] == x tang comps.
# =====================================================================
comps = 0


def linear_search(a, x):
    global comps
    # TODO: viet code cua ban o day
    for i in range(len(a)):
        comps += 1
        if a[i] == x:
            return i
    return -1


# =====================================================================
# 1B.2 (CO BAN) - Luy thua b^e mod m. Dem so phep nhan vao mults.
#   pow_fast PHAI theo dung khuon trong tai lieu (xem ban C++).
# =====================================================================
mults = 0


def pow_naive(b, e, m):
    global mults
    # TODO: viet code cua ban o day
    res = 1 % m
    b %= m
    for _ in range(e):
        res = (res * b) % m
        mults += 1
    return res


def pow_fast(b, e, m):
    global mults
    # TODO: viet code cua ban o day
    res = 1 % m
    b %= m
    while e > 0:
        if e % 2 == 1:
            res = (res * b) % m
            mults += 1
        b = (b * b) % m
        mults += 1
        e //= 2
    return res


# =====================================================================
# 1B.3 (TRUNG BINH) - Fibonacci ba cach. Moi lan GOI ham tang calls.
# =====================================================================
calls = 0


def fib_rec(n):
    global calls
    # TODO: viet code cua ban o day
    calls += 1
    if n <= 0:
        return 0
    if n == 1:
        return 1
    return fib_rec(n - 1) + fib_rec(n - 2)


def fib_memo_helper(n, memo):
    global calls
    # TODO: viet code cua ban o day
    calls += 1
    if n <= 0:
        return 0
    if n == 1:
        return 1
    if memo[n] != -1:
        return memo[n]
    memo[n] = fib_memo_helper(n - 1, memo) + fib_memo_helper(n - 2, memo)
    return memo[n]


def fib_memo(n):
    return fib_memo_helper(n, [-1] * (n + 1))


def fib_iter(n):
    # TODO: viet code cua ban o day
    if n <= 0:
        return 0
    if n == 1:
        return 1
    prev2, prev1 = 0, 1
    for _ in range(2, n + 1):
        prev2, prev1 = prev1, prev2 + prev1
    return prev1


# =====================================================================
# 1B.4 (NANG CAO) - 3-SUM: dem bo ba i<j<k co tong bang 0 (phan tu khac nhau)
# =====================================================================
def three_sum_cubic(a):
    # TODO: viet code cua ban o day
    n = len(a)
    count = 0
    for i in range(n):
        for j in range(i + 1, n):
            for k in range(j + 1, n):
                if a[i] + a[j] + a[k] == 0:
                    count += 1
    return count


def three_sum_binary(a):
    # TODO: viet code cua ban o day
    a = sorted(a)
    n = len(a)
    count = 0
    for i in range(n):
        for j in range(i + 1, n):
            target = -(a[i] + a[j])
            idx = bisect_left(a, target, j + 1, n)
            if idx < n and a[idx] == target:
                count += 1
    return count


def three_sum_two_ptr(a):
    # TODO: viet code cua ban o day
    a = sorted(a)
    n = len(a)
    count = 0
    for i in range(n):
        target = -a[i]
        left = i + 1
        right = n - 1
        while left < right:
            s = a[left] + a[right]
            if s == target:
                count += 1
                left += 1
                right -= 1
            elif s < target:
                left += 1
            else:
                right -= 1
    return count


def distinct_data(n, seed):
    """n so nguyen doi mot khac nhau trong [-10n, 10n] (da cho san)."""
    g, used, a = LCG(seed), set(), []
    while len(a) < n:
        v = g.range(-10 * n, 10 * n)
        if v not in used:
            used.add(v)
            a.append(v)
    return a


def main():
    global comps, mults, calls
    print("===== 1B.1: Tim kiem tuyen tinh =====")
    n, g = 1000, LCG(11)
    a = list(range(1, n + 1))
    for i in range(n - 1, 0, -1):
        k = g.next() % (i + 1)
        a[i], a[k] = a[k], a[i]
    comps = 0
    pos = linear_search(a, a[0])
    print(f"Tot nhat  (x = a[0])        : comps = {comps}  pos = {pos}")
    comps = 0
    linear_search(a, 0)
    print(f"Xau nhat  (x khong co)      : comps = {comps}")
    comps = 0
    ok = all(linear_search(a, a[i]) == i for i in range(n))
    print(f"Trung binh (tim lan luot moi phan tu): tong = {comps}  TB = {comps / n:.3f}"
          f"  ly thuyet (n+1)/2 = {(n + 1) / 2:.3f}" + ("  [OK]" if ok else "  [SAI]") + "\n")

    print("===== 1B.2: Luy thua mod 1e9+7 =====")
    MOD = 1000000007
    for e in (10, 1000, 1000000):
        mults = 0
        r1 = pow_naive(3, e, MOD)
        m1 = mults
        mults = 0
        r2 = pow_fast(3, e, MOD)
        m2 = mults
        print(f"3^{e} mod p = {r2}   naive: {m1} phep nhan,  fast: {m2} phep nhan"
              + ("  [OK]" if r1 == r2 == pow(3, e, MOD) else "  [SAI]"))

    print("\n===== 1B.3: Fibonacci =====")
    print(f"{'n':>4}{'F(n)':>14}{'calls(rec)':>14}{'calls(memo)':>12}{'rec (ms)':>12}")
    for n in (10, 20, 25, 30, 32):
        calls = 0
        f1, t = time_ms(lambda: fib_rec(n))
        c1 = calls
        calls = 0
        f2 = fib_memo(n)
        c2 = calls
        f3 = fib_iter(n)
        print(f"{n:>4}{f3:>14}{c1:>14}{c2:>12}{t:>12.3f}" + ("  [OK]" if f1 == f2 == f3 > 0 else "  [SAI]"))
    print(f"F(90) = {fib_iter(90)}  (fib_rec(90) se chay hang tram nam!)")

    print("\n===== 1B.4: 3-SUM =====")
    print(f"{'n':>6}{'so bo ba':>10}{'n^3 (ms)':>12}{'n^2logn (ms)':>14}{'n^2 (ms)':>12}{'khop?':>10}")
    prev = [0, 0, 0]
    for n in (200, 400, 800, 1600, 3200):
        a = distinct_data(n, 7)
        c1, t1 = (-1, -1.0)
        if n <= 400:                             # Python: O(n^3) chi chay n nho
            c1, t1 = time_ms(lambda: three_sum_cubic(a))
        c2, t2 = time_ms(lambda: three_sum_binary(a))
        c3, t3 = time_ms(lambda: three_sum_two_ptr(a))
        ok = c2 == c3 and (c1 == -1 or c1 == c2) and c2 > 0
        line = f"{n:>6}{c3:>10}{t1:>12.3f}{t2:>14.3f}{t3:>12.3f}{('[OK]' if ok else '[SAI]'):>10}"
        if prev[2] > 0:
            line += "   b ~ "
            if t1 > 0 and prev[0] > 0:
                line += f"n^{math.log2(t1 / prev[0]):.3f} | "
            line += f"n^{math.log2(t2 / prev[1]):.3f} | n^{math.log2(t3 / prev[2]):.3f}"
        print(line)
        prev = [t1, t2, t3]
    print("(b = log2( T(2n) / T(n) ) la so mu uoc luong cua T(n) ~ n^b)")


if __name__ == "__main__":
    main()
