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
    n = len(a)
    for i in range(n - 1):
        min_pos = i
        for j in range(i + 1, n):
            st.comps += 1
            if a[j] < a[min_pos]:
                min_pos = j
        if min_pos != i:
            a[i], a[min_pos] = a[min_pos], a[i]
            st.moves += 1
        if TRACE:
            print("  " + show(a))


def insertion_sort(a, st):
    """comps++ moi lan so sanh a[j] > key (khi j >= 0); moves++ moi lan dich a[j+1] = a[j]"""
    # TODO: viet code cua ban o day
    n = len(a)
    for i in range(1, n):
        key = a[i]
        j = i - 1
        while j >= 0:
            st.comps += 1
            if a[j] > key:
                a[j + 1] = a[j]
                st.moves += 1
                j -= 1
            else:
                break
        a[j + 1] = key
        if TRACE:
            print("  " + show(a))


def bubble_sort(a, st):
    """Co co swapped. comps++ moi lan so sanh a[j] > a[j+1]; moves++ moi lan swap"""
    # TODO: viet code cua ban o day
    n = len(a)
    for i in range(n - 1):
        swapped = False
        for j in range(n - 1 - i):
            st.comps += 1
            if a[j] > a[j + 1]:
                a[j], a[j + 1] = a[j + 1], a[j]
                st.moves += 1
                swapped = True
        if TRACE:
            print("  " + show(a))
        if not swapped:
            break


# =====================================================================
# BAI 2.2 - Quick sort (Lomuto, pivot cuoi) va Merge sort
# =====================================================================
def partition_lomuto(a, lo, hi, st):
    # TODO: viet code cua ban o day
    pivot = a[hi]
    i = lo - 1
    for j in range(lo, hi):
        st.comps += 1
        if a[j] <= pivot:
            i += 1
            a[i], a[j] = a[j], a[i]
            st.moves += 1
    a[i + 1], a[hi] = a[hi], a[i + 1]
    st.moves += 1
    return i + 1


def quick_sort(a, lo, hi, st):
    # TODO: viet code cua ban o day
    if lo < hi:
        p = partition_lomuto(a, lo, hi, st)
        quick_sort(a, lo, p - 1, st)
        quick_sort(a, p + 1, hi, st)


def merge_runs(a, lo, mid, hi, st):
    # TODO: viet code cua ban o day
    temp = []
    i, j = lo, mid + 1
    while i <= mid and j <= hi:
        st.comps += 1
        if a[i] <= a[j]:
            temp.append(a[i])
            i += 1
        else:
            temp.append(a[j])
            j += 1
    while i <= mid:
        temp.append(a[i])
        i += 1
    while j <= hi:
        temp.append(a[j])
        j += 1
    for k in range(len(temp)):
        a[lo + k] = temp[k]


def merge_sort(a, lo, hi, st):
    # TODO: viet code cua ban o day
    if lo < hi:
        mid = lo + (hi - lo) // 2
        merge_sort(a, lo, mid, st)
        merge_sort(a, mid + 1, hi, st)
        merge_runs(a, lo, mid, hi, st)


# =====================================================================
# BAI 2.3a - Tim kiem nhi phan co in vet
#   Mau:  step k: lo=.. hi=.. mid=.. a[mid]=..
# =====================================================================
def binary_search_trace(a, x, trace):
    # TODO: viet code cua ban o day
    lo, hi = 0, len(a) - 1
    step = 1
    while lo <= hi:
        mid = lo + (hi - lo) // 2
        if trace:
            print(f"  step {step}: lo={lo} hi={hi} mid={mid} a[mid]={a[mid]}")
            step += 1
        if a[mid] == x:
            return mid
        elif a[mid] < x:
            lo = mid + 1
        else:
            hi = mid - 1
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
        idx = k % self.m
        self.slot[idx].insert(0, k)

    def search_probes(self, k):
        # TODO: viet code cua ban o day
        idx = k % self.m
        probes = 0
        for v in self.slot[idx]:
            probes += 1
            if v == k:
                return probes
        return probes

    def print(self):
        for i, chain in enumerate(self.slot):
            print(f"  [{i:>2}]" + "".join(f" -> {v}" for v in chain))


class LinearProbingTable:
    def __init__(self, m):
        self.m = m
        self.t = [-1] * m

    def insert(self, k):
        # TODO: viet code cua ban o day
        for step in range(self.m):
            cur = (k % self.m + step) % self.m
            if self.t[cur] == -1:
                self.t[cur] = k
                return True
        return False

    def search_probes(self, k):
        # TODO: viet code cua ban o day
        probes = 0
        for step in range(self.m):
            cur = (k % self.m + step) % self.m
            probes += 1
            if self.t[cur] == k or self.t[cur] == -1:
                return probes
        return probes

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
