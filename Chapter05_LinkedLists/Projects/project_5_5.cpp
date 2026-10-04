// project_5_5.cpp

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Link {
    public:
        long dData;
        Link* next;
        Link* previous;
    public:
        Link(long dd) : dData(dd), next(nullptr), previous(nullptr) {}
        void displayLink() {
            cout << dData << " ";
        }
};

class CircularList {
    private:
        Link* current;
    public:
        CircularList() : current(nullptr) {}
        ~CircularList() {
            if (current == nullptr)
                return;
            Link* start = current;
            Link* temp = current;
            do {
                Link* next = temp->next;
                delete temp;
                temp = next;
            } while (temp != start);
            current = nullptr;
        }
        bool isEmpty() {
            return current == nullptr;
        }
        void step() {
            if (isEmpty())
                return;
            current = current->next;
        }
        bool find(long key) {
            if (isEmpty())
                return false;
            Link* start = current;
            Link* temp = current;
            do {
                if (temp->dData == key) {
                    current = temp;
                    return true;
                }
                temp = temp->next;
            } while (temp != start);
            return false;
        }
        void insert(long key) {
            Link* newLink = new Link(key);
            if (isEmpty()) {
                current = newLink;
                newLink->next = newLink;
                newLink->previous = newLink;
                return;
            }
            newLink->next = current->next;
            newLink->next->previous = newLink;
            newLink->previous = current;
            current->next = newLink;
            current = newLink;
        }
        long remove() {
            if (isEmpty())
                return 0;
            if (current->next == current) {
                long dData = current->dData;
                delete current;
                current = nullptr;
                return dData;
            }
            Link* temp = current;
            long dData = current->dData;
            current = temp->next;
            temp->previous->next = temp->next;
            temp->next->previous = temp->previous;
            delete temp;
            return dData;
        }
        void display() {
            if (isEmpty())
                return;
            if (current->next == current) {
                current->displayLink();
                return;
            }
            Link* start = current;
            Link* temp = current;
            do {
                temp->displayLink();
                temp = temp->next;
            } while (temp != start);
        }
};

class JosephusSolver {
    private:
        int N;          // количество человек в круге
        int M;          // число для отсчёта (каждый M-й выбывает)
        int startPos;   // номер человека, с которого начинается отсчёт
        CircularList* list;
    public:
        JosephusSolver(int n, int m, int start) {
            list = new CircularList();
            N = n;
            M = m;
            startPos = start;
        }
        ~JosephusSolver() {
            delete list;
        }
        void buildCircle() {
            for (int i = 1; i <= N; i++)
                list->insert(i);
        }           
        void solve() {
            vector<long> order = simulate();
            for (long x : order) cout << x << " ";
            cout << endl;
        }
        vector<long> simulate() {
            vector<long> solution;
            for (int i = 0; i < startPos; i++)
                list->step();
            
            for (int i = 0; i < N; i++) {
                // cout << "list in simulate " << i << ": "; list->display(); cout << endl;
                for (int j = 0; j < M; j++)
                    list->step();
                solution.push_back(list->remove());
            }

            solution.pop_back();

            return solution;
        }
};

// ---------------------------------------------------------
// Вспомогательная функция: превратить вектор в строку "a b c"
// ---------------------------------------------------------
static string vecToStr(const vector<long>& v) {
    string s;
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) s += " ";
        s += to_string(v[i]);
    }
    return s;
}

// ---------------------------------------------------------
// Проверка одного теста
// ---------------------------------------------------------
static int g_total = 0;
static int g_passed = 0;

static void check(const string& testName,
                  const vector<long>& expected,
                  const vector<long>& actual)
{
    ++g_total;
    bool ok = (expected == actual);
    if (ok) ++g_passed;

    cout << (ok ? "[PASS] " : "[FAIL] ") << testName << endl;
    if (!ok) {
        cout << "        expected: " << vecToStr(expected) << endl;
        cout << "        actual  : " << vecToStr(actual)   << endl;
    }
}

// ---------------------------------------------------------
// Универсальный прогон: N, M, start -> порядок выбывания
// ---------------------------------------------------------
static vector<long> run(int N, int M, int start) {
    JosephusSolver solver(N, M, start);
    solver.buildCircle();
    return solver.simulate();   // метод, возвращающий порядок выбывания
}

// =========================================================
// MAIN — тесты под 0-based семантику
// =========================================================
int main() {
    // -----------------------------------------------------
    // ТЕСТ 1: N=7, M=3, start=1
    // Порядок выбывания: 4 1 6 5 7 3 2 (выживший 2)
    // simulate() возвращает: 4 1 6 5 7 3
    // -----------------------------------------------------
    check("T1: N=7, M=3, start=1",
          {4, 1, 6, 5, 7, 3},
          run(7, 3, 1));

    // -----------------------------------------------------
    // ТЕСТ 2: N=5, M=2, start=1
    // Порядок выбывания: 3 1 5 2 4 (выживший 4)
    // simulate(): 3 1 5 2
    // -----------------------------------------------------
    check("T2: N=5, M=2, start=1",
          {3, 1, 5, 2},
          run(5, 2, 1));

    // -----------------------------------------------------
    // ТЕСТ 3: N=1, M=1, start=1
    // Единственный элемент выбывает, simulate() = {}
    // -----------------------------------------------------
    check("T3: N=1, M=1, start=1",
          {},
          run(1, 1, 1));

    // -----------------------------------------------------
    // ТЕСТ 4: N=2, M=1, start=1
    // Порядок выбывания: 2 1 (выживший 1)
    // simulate(): 2
    // -----------------------------------------------------
    check("T4: N=2, M=1, start=1",
          {2},
          run(2, 1, 1));

    // -----------------------------------------------------
    // ТЕСТ 5: N=2, M=2, start=1
    // Порядок выбывания: 1 2 (выживший 2)
    // simulate(): 1
    // -----------------------------------------------------
    check("T5: N=2, M=2, start=1",
          {1},
          run(2, 2, 1));

    // -----------------------------------------------------
    // ТЕСТ 6: N=3, M=2, start=1
    // Порядок выбывания: 3 1 2 (выживший 2)
    // simulate(): 3 1
    // -----------------------------------------------------
    check("T6: N=3, M=2, start=1",
          {3, 1},
          run(3, 2, 1));

    // -----------------------------------------------------
    // ТЕСТ 7: N=4, M=2, start=1
    // Порядок выбывания: 3 2 4 1 (выживший 1)
    // simulate(): 3 2 4
    // -----------------------------------------------------
    check("T7: N=4, M=2, start=1",
          {3, 2, 4},
          run(4, 2, 1));

    // -----------------------------------------------------
    // ТЕСТ 8: N=6, M=3, start=1
    // Порядок выбывания: 4 2 1 3 6 5 (выживший 5)
    // simulate(): 4 2 1 3 6
    // -----------------------------------------------------
    check("T8: N=6, M=3, start=1",
          {4, 2, 1, 3, 6},
          run(6, 3, 1));

    // -----------------------------------------------------
    // ТЕСТ 9: N=6, M=3, start=2
    // Порядок выбывания: 5 3 2 4 1 6 (выживший 6)
    // simulate(): 5 3 2 4 1
    // -----------------------------------------------------
    check("T9: N=6, M=3, start=2",
          {5, 3, 2, 4, 1},
          run(6, 3, 2));

    // -----------------------------------------------------
    // ТЕСТ 10: N=7, M=3, start=4
    // Порядок выбывания: 7 4 2 1 3 6 5 (выживший 5)
    // simulate(): 7 4 2 1 3 6
    // -----------------------------------------------------
    check("T10: N=7, M=3, start=4",
          {7, 4, 2, 1, 3, 6},
          run(7, 3, 4));

    // -----------------------------------------------------
    // ТЕСТ 11: N=5, M=12, start=1
    // M > N: эквивалентность M mod N НЕ работает,
    // т.к. модуль меняется с уменьшением круга.
    // Порядок выбывания: 3 4 5 1 2 (выживший 2)
    // simulate(): 3 4 5 1
    // -----------------------------------------------------
    check("T11: N=5, M=12, start=1",
          {3, 4, 5, 1},
          run(5, 12, 1));

    // -----------------------------------------------------
    // ТЕСТ 12: N=5, M=5, start=1
    // Порядок выбывания: 1 3 2 5 4 (выживший 4)
    // simulate(): 1 3 2 5
    // -----------------------------------------------------
    check("T12: N=5, M=5, start=1",
          {1, 3, 2, 5},
          run(5, 5, 1));

    // -----------------------------------------------------
    // ТЕСТ 13: N=10, M=4, start=1
    // Порядок выбывания: 5 10 6 2 9 8 1 4 7 3 (выживший 3)
    // simulate(): 5 10 6 2 9 8 1 4 7
    // -----------------------------------------------------
    check("T13: N=10, M=4, start=1",
          {5, 10, 6, 2, 9, 8, 1, 4, 7},
          run(10, 4, 1));

    // -----------------------------------------------------
    // ТЕСТ 14: N=15, M=3, start=1
    // Порядок выбывания: 4 8 12 1 6 11 2 9 15 10 5 3 13 14 7 (выживший 7)
    // simulate(): 14 элементов, последний = 14
    // -----------------------------------------------------
    {
        vector<long> res = run(15, 3, 1);

        ++g_total;
        bool ok = (res.size() == 14);
        if (ok) ++g_passed;
        cout << (ok ? "[PASS] " : "[FAIL] ")
             << "T14: N=15, M=3, start=1 — размер 14" << endl;
        if (!ok) cout << "        actual size: " << res.size() << endl;

        ++g_total;
        ok = (!res.empty() && res.back() == 14);
        if (ok) ++g_passed;
        cout << (ok ? "[PASS] " : "[FAIL] ")
             << "T14b: последний выбывший = 14" << endl;
        if (!ok) cout << "        actual last: "
                      << (res.empty() ? -1 : res.back()) << endl;

        ++g_total;
        ok = (res.size() == 14 && res[0] == 4 && res[1] == 8 && res[2] == 12);
        if (ok) ++g_passed;
        cout << (ok ? "[PASS] " : "[FAIL] ")
             << "T14c: первые три = 4 8 12" << endl;
        if (!ok) cout << "        actual first 3: ";
        if (!ok) {
            for (int i = 0; i < 3 && i < (int)res.size(); ++i)
                cout << res[i] << " ";
            cout << endl;
        }
    }

    // -----------------------------------------------------
    // ТЕСТ 15: N=20, M=7, start=3
    // Инвариант: сумма всех выбывших + выживший = N*(N+1)/2 = 210
    // simulate() возвращает 19 выбывших; выживший = 210 - sum
    // -----------------------------------------------------
    {
        vector<long> res = run(20, 7, 3);

        ++g_total;
        bool ok = (res.size() == 19);
        if (ok) ++g_passed;
        cout << (ok ? "[PASS] " : "[FAIL] ")
             << "T15: N=20, M=7, start=3 — размер 19" << endl;
        if (!ok) cout << "        actual size: " << res.size() << endl;

        ++g_total;
        long sum = 0;
        for (long x : res) sum += x;
        long total = 20L * 21 / 2;   // 210
        long survivor = total - sum;
        ok = (survivor >= 1 && survivor <= 20);
        if (ok) ++g_passed;
        cout << (ok ? "[PASS] " : "[FAIL] ")
             << "T15b: выживший в [1,20], survivor=" << survivor << endl;
        if (!ok) cout << "        actual sum: " << sum << endl;

        // Проверка: все выбывшие — различные числа из 1..20
        ++g_total;
        vector<bool> seen(21, false);
        bool allDistinct = true;
        for (long x : res) {
            if (x < 1 || x > 20 || seen[x]) { allDistinct = false; break; }
            seen[x] = true;
        }
        ok = allDistinct;
        if (ok) ++g_passed;
        cout << (ok ? "[PASS] " : "[FAIL] ")
             << "T15c: все выбывшие — различные из 1..20" << endl;
    }

    // -----------------------------------------------------
    // ИТОГ
    // -----------------------------------------------------
    cout << "----------------------------------------" << endl;
    cout << "Пройдено: " << g_passed << " / " << g_total << endl;

    return (g_passed == g_total) ? 0 : 1;
}