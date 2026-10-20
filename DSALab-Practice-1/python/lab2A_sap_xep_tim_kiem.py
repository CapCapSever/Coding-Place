# =====================================================================
#  LAB 2A (TREN LOP) - CHUONG 2: SAP XEP VA TIM KIEM
#  Chay:  python lab2A_sap_xep_tim_kiem.py
#  Viet code vao cac cho "TODO". Code phai dem dung phep so sanh (*) nhu slide.
# =====================================================================
import sys
import time

sys.setrecursionlimit(10000)   # quick sort tren mang da sap co do sau de quy ~ n


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
    f()
    return (time.perf_counter() - t0) * 1000


def is_sorted(a):
    return all(a[i] <= a[i + 1] for i in range(len(a) - 1))


class Stats:
    """comps = so phep so sanh khoa (*), moves = so lan swap / dich phan tu"""

    def __init__(self):
        self.comps = 0
        self.moves = 0


TRACE = False   # True -> in mang sau moi luot cua vong ngoai


def show(a):
    return " ".join(map(str, a))


# =====================================================================
# BAI 2.1 - Ba thuat toan sap xep co ban
# =====================================================================
def selection_sort(a, st):
    """comps++ moi lan so sanh a[j] < a[min_pos]; moves++ khi swap (chi khi min_pos != i)"""
    # TODO: viet code cua ban o day
    pass


def insertion_sort(a, st):
    """comps++ moi lan so sanh a[j] > key (khi j >= 0); moves++ moi lan dich a[j+1] = a[j]"""
    # TODO: viet code cua ban o day
    pass


def bubble_sort(a, st):
    """Co co swapped. comps++ moi lan so sanh a[j] > a[j+1]; moves++ moi lan swap"""
    # TODO: viet code cua ban o day
    pass


# =====================================================================
# BAI 2.2 - Quick sort (Lomuto, pivot cuoi) va Merge sort
# =====================================================================
def partition_lomuto(a, lo, hi, st):
    # TODO: viet code cua ban o day
    return lo


def quick_sort(a, lo, hi, st):
    # TODO: viet code cua ban o day
    pass


def merge_runs(a, lo, mid, hi, st):
    # TODO: viet code cua ban o day
    pass


def merge_sort(a, lo, hi, st):
    # TODO: viet code cua ban o day
    pass


# =====================================================================
# BAI 2.3a - Tim kiem nhi phan co in vet
#   Mau:  step k: lo=.. hi=.. mid=.. a[mid]=..
# =====================================================================
def binary_search_trace(a, x, trace):
    # TODO: viet code cua ban o day
    return -1


# =====================================================================
# BAI 2.3b - Bang bam h(k) = k mod m: chaining (chen dau) va linear probing
# =====================================================================
class ChainingTable:
    def __init__(self, m):
        self.m = m
        self.slot = [[] for _ in range(m)]   # phan tu dau list = dau chuoi

    def insert(self, k):
        # TODO: viet code cua ban o day
        pass

    def search_probes(self, k):
        # TODO: viet code cua ban o day
        return 0

    def print(self):
        for i, chain in enumerate(self.slot):
            print(f"  [{i:>2}]" + "".join(f" -> {v}" for v in chain))


class LinearProbingTable:
    def __init__(self, m):
        self.m = m
        self.t = [-1] * m

    def insert(self, k):
        # TODO: viet code cua ban o day
        return False

    def search_probes(self, k):
        # TODO: viet code cua ban o day
        return 0

    def print(self):
        print("  " + " ".join(f"[{i}]{'_' if v == -1 else v}" for i, v in enumerate(self.t)) + " ")


def main():
    global TRACE
    print("===== BAI 2.1: Selection / Insertion / Bubble =====")
    sample = [5, 2, 9, 1, 5, 6]
    basic = [("Selection", selection_sort), ("Insertion", insertion_sort), ("Bubble", bubble_sort)]
    TRACE = True
    for name, fn in basic:
        a, st = sample[:], Stats()
        print(f"{name} tren 5 2 9 1 5 6:")
        fn(a, st)
        print(f"  => comps = {st.comps}, moves = {st.moves}" + ("  [OK]" if a == sorted(sample) else "  [SAI]"))
    TRACE = False
    n, g = 1000, LCG(2026)
    rnd = [g.range(0, 99999) for _ in range(n)]
    asc = sorted(rnd)
    desc = asc[::-1]
    print(f"\nn = 1000      {'ngau nhien':>22}{'da sap tang':>22}{'sap giam':>22}")
    print("(comps / moves)")
    for name, fn in basic:
        row = f"{name:>10}   "
        for src in (rnd, asc, desc):
            a, st = src[:], Stats()
            fn(a, st)
            row += f"{f'{st.comps} / {st.moves}' + ('' if a == asc else ' SAI'):>22}"
        print(row)

    print("\n===== BAI 2.2: Quick sort vs Merge sort =====")
    a, b = sample[:], sample[:]
    quick_sort(a, 0, len(a) - 1, Stats())
    merge_sort(b, 0, len(b) - 1, Stats())
    print("Mau 5 2 9 1 5 6 -> quick:", show(a), "")
    print("                  merge:", show(b), "")
    for label, src in (("ngau nhien n=1000", rnd), ("da sap n=1000", asc)):
        a, b, s1, s2 = src[:], src[:], Stats(), Stats()
        quick_sort(a, 0, n - 1, s1)
        merge_sort(b, 0, n - 1, s2)
        print(f"{label:>20}: quick comps = {s1.comps:>7}   merge comps = {s2.comps:>6}"
              + ("  [OK]" if a == asc and b == asc else "  [SAI]"))
    N, h = 200000, LCG(99)      # Python: dung 200 000 thay cho 1 000 000
    big = [h.range(0, 1000000000) for _ in range(N)]
    a, b = big[:], big[:]
    tq = time_ms(lambda: quick_sort(a, 0, N - 1, Stats()))
    tm = time_ms(lambda: merge_sort(b, 0, N - 1, Stats()))
    c = []
    ts = time_ms(lambda: c.extend(sorted(big)))
    print(f"N = 200 000 ngau nhien: quick {tq:.2f} ms | merge {tm:.2f} ms | sorted() {ts:.2f} ms"
          + ("  [OK]" if a == c and b == c else "  [SAI]"))

    print("\n===== BAI 2.3a: Tim kiem nhi phan =====")
    sorted10 = [2, 5, 8, 12, 16, 23, 38, 56, 72, 91]
    for x in (23, 91, 4):
        print(f"Tim x = {x}:")
        print(f"  => pos = {binary_search_trace(sorted10, x, True)}")
    ok = all(binary_search_trace(sorted10, v, False) == i for i, v in enumerate(sorted10))
    ok = ok and binary_search_trace(sorted10, 100, False) == -1 and binary_search_trace(sorted10, 1, False) == -1
    print("Kiem tra 12 truy van:", "[OK]" if ok else "[SAI]")

    print("\n===== BAI 2.3b: Bang bam, m = 11 =====")
    for keys in ([12, 25, 35, 26, 5], [22, 33, 44, 1, 12]):
        print("Khoa: " + " ".join(map(str, keys)))
        ch, lp = ChainingTable(11), LinearProbingTable(11)
        for k in keys:
            ch.insert(k)
            lp.insert(k)
        print(" Chaining:")
        ch.print()
        print(" Linear probing:")
        lp.print()
        print(" So probe khi tim (chaining / linear):"
              + "".join(f"  {k}:{ch.search_probes(k)}/{lp.search_probes(k)}" for k in keys)
              + f"  | khoa 23 (khong co): {ch.search_probes(23)}/{lp.search_probes(23)}")


if __name__ == "__main__":
    main()
