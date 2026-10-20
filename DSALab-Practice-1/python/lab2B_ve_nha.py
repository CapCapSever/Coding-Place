# =====================================================================
#  LAB 2B (VE NHA) - CHUONG 2: SAP XEP VA TIM KIEM
#  Muc do:  2B.1-2B.2 Co ban | 2B.3-2B.4 Trung binh | 2B.5-2B.6 Nang cao
#  Chay:  python lab2B_ve_nha.py
# =====================================================================
import sys
import time

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


def show(a):
    return " ".join(map(str, a))


# =====================================================================
# 2B.1 (CO BAN) - Radix sort LSD co so 10. trace -> in "  exp=<exp>: <mang>"
# =====================================================================
def counting_by_digit(a, exp):
    """Sap xep ON DINH mang a theo chu so (a[i] // exp) % 10; tra ve mang moi."""
    # TODO: viet code cua ban o day
    return a


def radix_sort(a, trace):
    """Sap xep TAI CHO mang a (gan lai a[:] = ...)."""
    # TODO: viet code cua ban o day
    pass


# =====================================================================
# 2B.2 (CO BAN) - Noi suy vs nhi phan: moi lan doc a[mid]/a[pos] = 1 probe
# =====================================================================
probes = 0


def binary_search(a, x):
    global probes
    # TODO: viet code cua ban o day
    return -1


def interpolation_search(a, x):
    global probes
    # TODO: viet code cua ban o day
    return -1


# =====================================================================
# 2B.3 (TRUNG BINH) - Quick sort voi pivot trung vi cua ba (xem mo ta ban C++)
# =====================================================================
qcomps = 0


def lomuto(a, lo, hi):
    global qcomps
    pivot, i = a[hi], lo - 1
    for j in range(lo, hi):
        qcomps += 1
        if a[j] <= pivot:
            i += 1
            a[i], a[j] = a[j], a[i]
    a[i + 1], a[hi] = a[hi], a[i + 1]
    return i + 1


def quick_sort_last(a, lo, hi):          # ban goc (da cho san)
    if lo >= hi:
        return
    p = lomuto(a, lo, hi)
    quick_sort_last(a, lo, p - 1)
    quick_sort_last(a, p + 1, hi)


def median_of_three(a, lo, hi):
    # TODO: viet code cua ban o day
    pass


def quick_sort_med3(a, lo, hi):
    # TODO: viet code cua ban o day
    pass


# =====================================================================
# 2B.4 (TRUNG BINH) - Bang bam chaining tu cai dat (KHONG dung dict) dem tan suat tu
#   h(s) = (...((s0*31 + s1)*31 + s2)...) mod m (mod sau moi buoc, s_i = ord(ky tu))
#   size/m > 0.75 sau khi them -> rehash sang m' = 2m + 1
# =====================================================================
class WordCounter:
    def __init__(self, m0):
        self.m, self.sz, self.rehashes = m0, 0, 0
        self.slot = [[] for _ in range(m0)]     # moi phan tu chuoi la [tu, dem]

    @staticmethod
    def hash_str(s, m):
        # TODO: viet code cua ban o day
        return 0

    def rehash(self):
        # TODO: viet code cua ban o day
        pass

    def add(self, w):
        # TODO: viet code cua ban o day
        pass

    def get(self, w):
        # TODO: viet code cua ban o day
        return 0

    def longest_chain(self):
        return max(len(c) for c in self.slot)


# =====================================================================
# 2B.5 (NANG CAO) - Dem nghich the
# =====================================================================
def inversions_brute(a):
    # TODO: viet code cua ban o day
    return 0


def sort_count(a):
    """Tra ve (mang da sap, so nghich the) bang merge sort."""
    # TODO: viet code cua ban o day
    return (sorted(a), 0)


def inversions_merge(a):
    return sort_count(list(a))[1]


# =====================================================================
# 2B.6 (NANG CAO) - Quickselect: phan tu nho thu k (k tu 1). Dung median_of_three + lomuto.
# =====================================================================
def quick_select(a, k):
    # TODO: viet code cua ban o day
    return 0


def main():
    global probes, qcomps
    print("===== 2B.1: Radix sort =====")
    r = [329, 457, 657, 839, 436, 720, 355]
    radix_sort(r, True)
    g = LCG(5)
    a = [g.range(0, 999999) for _ in range(100000)]
    b = sorted(a)
    _, t = time_ms(lambda: radix_sort(a, False))
    print(f"n = 100000: {t:.3f} ms" + ("  [OK]" if a == b else "  [SAI]"))

    print("\n===== 2B.2: Noi suy vs Nhi phan (probe trung binh / 1000 truy van) =====")
    uni = [10 * (i + 1) for i in range(1000000)]
    skew = [(i + 1) ** 3 for i in range(1000)]
    for name, arr in (("deu   a[i]=10(i+1),  n=1e6", uni), ("lech  a[i]=(i+1)^3,  n=1000", skew)):
        g = LCG(77)
        pb = pi = 0
        ok = True
        for _ in range(1000):
            idx = g.range(0, len(arr) - 1)
            x = arr[idx]
            probes = 0
            ok &= binary_search(arr, x) == idx
            pb += probes
            probes = 0
            ok &= interpolation_search(arr, x) == idx
            pi += probes
        ok &= binary_search(arr, 5) == -1 and interpolation_search(arr, 5) == -1
        print(f"{name}:  binary {pb / 1000:.3f}   interpolation {pi / 1000:.3f}" + ("  [OK]" if ok else "  [SAI]"))

    print("\n===== 2B.3: Quick sort - pivot cuoi vs trung vi cua ba =====")
    n, g = 1000, LCG(2026)
    rnd = [g.range(0, 99999) for _ in range(n)]
    asc = sorted(rnd)
    desc = asc[::-1]
    print(f"{'':>14}{'pivot cuoi':>14}{'trung vi 3':>14}")
    for label, src in (("ngau nhien", rnd), ("da sap", asc), ("sap giam", desc)):
        a, b = src[:], src[:]
        qcomps = 0
        quick_sort_last(a, 0, n - 1)
        c1 = qcomps
        qcomps = 0
        quick_sort_med3(b, 0, n - 1)
        c2 = qcomps
        print(f"{label:>14}{c1:>14}{c2:>14}" + ("  [OK]" if a == asc and b == asc else "  [SAI]"))

    print("\n===== 2B.4: Bang bam dem tu =====")
    text = ("the quick brown fox jumps over the lazy dog the dog sleeps and the fox runs "
            "a hash table maps a key to a slot and the slot holds a chain of keys "
            "when the load factor grows the table doubles and every key is hashed again "
            "searching a hash table costs one plus alpha on average and n in the worst case "
            "the fox and the dog are friends and the table is fast")
    wc = WordCounter(7)
    words = text.split()
    for w in words:
        wc.add(w)
    allw = [tuple(kv) for chain in wc.slot for kv in chain]
    allw.sort(key=lambda kv: (-kv[1], kv[0]))
    print(f"Tong so tu = {len(words)}, so tu khac nhau = {wc.sz}, m = {wc.m}, so lan rehash = {wc.rehashes}, "
          f"alpha = {wc.sz / wc.m:.3f}, chuoi dai nhat = {wc.longest_chain()}")
    print("Top 5:" + "".join(f"  {w}={c}" for w, c in allw[:5]))
    print(f'get("fox") = {wc.get("fox")}, get("cat") = {wc.get("cat")}, h("fox", 7) = {WordCounter.hash_str("fox", 7)}')

    print("\n===== 2B.5: Dem nghich the =====")
    print(f"2 4 1 3 5 -> {inversions_merge([2, 4, 1, 3, 5])} nghich the")
    g = LCG(31)
    a = [g.range(0, 9999) for _ in range(3000)]
    b1, b2 = inversions_brute(a), inversions_merge(a)
    print(f"n = 3000: brute = {b1}, merge = {b2}" + ("  [OK]" if b1 == b2 > 0 else "  [SAI]"))
    big = [g.range(0, 1000000000) for _ in range(200000)]     # Python: 200 000 thay cho 1 000 000
    c, t = time_ms(lambda: inversions_merge(big))
    print(f"n = 200 000: {c} nghich the, {t:.3f} ms (brute se mat ~ vai phut)")

    print("\n===== 2B.6: Quickselect =====")
    g = LCG(8)
    a = [g.range(0, 1000000) for _ in range(100001)]
    b = sorted(a)
    ok = True
    for k in (1, 10, 50001, 99999, 100001):
        v = quick_select(a, k)
        ok &= v == b[k - 1]
        print(f"  k = {k:>6} -> {v}")
    print(f"Trung vi cua 100001 so = {quick_select(a, 50001)}" + ("  [OK]" if ok else "  [SAI]"))


if __name__ == "__main__":
    main()
