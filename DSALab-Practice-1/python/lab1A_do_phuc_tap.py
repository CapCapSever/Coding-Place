# =====================================================================
#  LAB 1A (TREN LOP) - CHUONG 1: GIOI THIEU CTDL & GT, DO PHUC TAP
#  Mon: Cau truc du lieu va Giai thuat (INT1306_CLC) - PTIT
#  Chay:  python lab1A_do_phuc_tap.py        (Python 3.8+)
#  Sinh vien chi viet code vao cac cho co "TODO". Khong sua ham main().
# =====================================================================
import math
import time


class LCG:
    """Bo sinh so gia ngau nhien DUNG CHUNG voi ban C++ (cung du lieu)."""

    def __init__(self, seed):
        self.x = seed

    def next(self):
        self.x = (self.x * 1103515245 + 12345) & 0x7FFFFFFF
        return self.x

    def range(self, lo, hi):
        return lo + self.next() % (hi - lo + 1)


# =====================================================================
# BAI 1.1 - Giai ax^2 + bx + c = 0
#   Tra ve (count, x1, x2): count = -1 vo so nghiem, 0 vo nghiem,
#   1 mot nghiem (x1 = x2), 2 hai nghiem (x1 < x2). Dung EPS so sanh delta.
# =====================================================================
EPS = 1e-9


def solve_quadratic(a, b, c):
    # TODO: viet code cua ban o day
    if abs(a) <= EPS:
        if abs(b) <= EPS:
            if abs(c) <= EPS:
                return (-1, 0.0, 0.0)
            return (0, 0.0, 0.0)
        temp = -c / b
        return (1, temp, temp)
    delta = b * b - 4 * a * c
    if abs(delta) <= EPS:
        delta = 0.0
    if delta < -EPS:
        return (0, 0.0, 0.0)
    if abs(delta) <= EPS:
        temp = -b / (2 * a)
        return (1, temp, temp)
    elif delta > EPS:
        x1 = (-b - math.sqrt(delta)) / (2 * a)
        x2 = (-b + math.sqrt(delta)) / (2 * a)
        return (2, min(x1, x2), max(x1, x2))
    return (0, 0.0, 0.0)


# =====================================================================
# BAI 1.2 - Dem so phep toan co ban
# =====================================================================
def ceil_log2(n):
    """ceil(log2 n) voi n >= 1 (da cho san)."""
    k, p = 0, 1
    while p < n:
        p <<= 1
        k += 1
    return k


def count_f1(n):
    """F1: for i in 0..n-1: cnt += 1"""
    cnt = 0
    # TODO: viet code cua ban o day
    for i in range(n):
        cnt += 1
    return cnt


def count_f2(n):
    """F2: for i in 0..n-1: for j in 0..n-1: cnt += 1"""
    cnt = 0
    # TODO: viet code cua ban o day
    for i in range(n):
        for j in range(n):
            cnt += 1
    return cnt


def count_f3(n):
    """F3: for i in 0..n-1: for j in i+1..n-1: cnt += 1"""
    cnt = 0
    # TODO: viet code cua ban o day
    for i in range(n):
        for j in range(i + 1, n):
            cnt += 1
    return cnt


def count_f4(n):
    """F4: i = 1; while i < n: cnt += 1; i *= 2"""
    cnt = 0
    # TODO: viet code cua ban o day
    i = 1
    while i < n:
        cnt += 1
        i *= 2
    return cnt


def count_f5(n):
    """F5: for i in 0..n-1: j = 1; while j < n: cnt += 1; j *= 2"""
    cnt = 0
    # TODO: viet code cua ban o day
    for i in range(n):
        j = 1
        while j < n:
            cnt += 1
            j *= 2
    return cnt


def formula_f1(n):
    # TODO: viet code cua ban o day
    return n


def formula_f2(n):
    # TODO: viet code cua ban o day
    return n * n


def formula_f3(n):
    # TODO: viet code cua ban o day
    return n * (n - 1) // 2


def formula_f4(n):
    # TODO: viet code cua ban o day
    return ceil_log2(n)


def formula_f5(n):
    # TODO: viet code cua ban o day
    return n * ceil_log2(n)


# =====================================================================
# BAI 1.3 - Thuc nghiem nhan doi n: mang co phan tu trung khong?
# =====================================================================
pair_comparisons = 0   # has_dup_brute phai tang bien nay moi lan so sanh a[i] == a[j]


def has_dup_brute(a):
    global pair_comparisons
    # TODO: viet code cua ban o day
    n = len(a)
    for i in range(n):
        for j in range(i + 1, n):
            pair_comparisons += 1
            if a[i] == a[j]:
                return True
    return False


def has_dup_sort(a):
    # TODO: viet code cua ban o day
    b = sorted(a)
    for i in range(1, len(b)):
        if b[i] == b[i - 1]:
            return True
    return False


def has_dup_hash(a):
    # TODO: viet code cua ban o day
    seen = set()
    for x in a:
        if x in seen:
            return True
        seen.add(x)
    return False


# ---------------- Ham ho tro (da cho san) ----------------
def random_permutation(n, g):
    a = list(range(n))
    for i in range(n - 1, 0, -1):
        k = g.next() % (i + 1)
        a[i], a[k] = a[k], a[i]
    return a


def time_ms(f, repeat=1):
    t0 = time.perf_counter()
    for _ in range(repeat):
        f()
    return (time.perf_counter() - t0) * 1000 / repeat


def main():
    global pair_comparisons
    print("===== BAI 1.1: Giai phuong trinh bac hai =====")
    tests = [(1, -3, 2, 2, 1, 2), (1, 2, 1, 1, -1, -1), (1, 0, 1, 0, 0, 0),
             (2, -7, 3, 2, 0.5, 3), (1, 0.2, 0.01, 1, -0.1, -0.1),
             (0, 2, -4, 1, 2, 2), (0, 0, 0, -1, 0, 0), (0, 0, 5, 0, 0, 0)]
    passed = 0
    for a, b, c, cnt, e1, e2 in tests:
        r = solve_quadratic(a, b, c)
        ok = r[0] == cnt and (r[0] <= 0 or (abs(r[1] - e1) < 1e-6 and abs(r[2] - e2) < 1e-6))
        passed += ok
        line = f"a={a:.4f} b={b:.4f} c={c:.4f}  -> count={r[0]}"
        if r[0] > 0:
            line += f"  x1={r[1]:.4f}  x2={r[2]:.4f}"
        print(line + ("   [OK]" if ok else "   [SAI]"))
    print(f"Dung {passed}/{len(tests)} test\n")

    print("===== BAI 1.2: Dem phep toan =====")
    print(f"{'n':>6}{'F1':>12}{'F2':>12}{'F3':>12}{'F4':>6}{'F5':>10}   khop cong thuc?")
    for n in (8, 100, 1000):
        c = [count_f1(n), count_f2(n), count_f3(n), count_f4(n), count_f5(n)]
        f = [formula_f1(n), formula_f2(n), formula_f3(n), formula_f4(n), formula_f5(n)]
        print(f"{n:>6}{c[0]:>12}{c[1]:>12}{c[2]:>12}{c[3]:>6}{c[4]:>10}   "
              + ("[OK]" if c == f and min(c) > 0 else "[SAI]"))

    print("\n===== BAI 1.3: Thuc nghiem nhan doi n =====")
    d1, d2 = [5, 1, 4, 2, 3], [5, 1, 4, 1, 3]
    ok = (not has_dup_brute(d1) and has_dup_brute(d2) and not has_dup_sort(d1)
          and has_dup_sort(d2) and not has_dup_hash(d1) and has_dup_hash(d2))
    print("Kiem tra tinh dung:", "[OK]" if ok else "[SAI]")
    print(f"{'n':>7}{'so cap (A)':>14}{'A (ms)':>11}{'tiA':>8}{'B (ms)':>10}{'tiB':>8}{'C (ms)':>10}{'tiC':>8}")
    pa = pb = pc = 0
    # Python cham hon C++ ~50 lan -> dung n nho hon ban C++
    for n in (1000, 2000, 4000, 8000):
        a = random_permutation(n, LCG(2026))
        pair_comparisons = 0
        ta = time_ms(lambda: has_dup_brute(a))
        tb = time_ms(lambda: has_dup_sort(a), 20)
        tc = time_ms(lambda: has_dup_hash(a), 20)
        print(f"{n:>7}{pair_comparisons:>14}{ta:>11.4f}{(ta / pa if pa else 0):>8.4f}"
              f"{tb:>10.4f}{(tb / pb if pb else 0):>8.4f}{tc:>10.4f}{(tc / pc if pc else 0):>8.4f}")
        pa, pb, pc = ta, tb, tc
    print("(ti = T(n) / T(n/2). O(n^2) -> ~4, O(n log n) -> ~2.1, O(n) -> ~2)")


if __name__ == "__main__":
    main()
