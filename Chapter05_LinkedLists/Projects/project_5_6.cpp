// project_5_6

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// ---------------------------------------------------------
// Узел разреженной матрицы.
// Хранит только значение и два указателя:
//   right — на следующий элемент в строке (вправо),
//   down  — на следующий элемент в столбце (вниз).
// Позиция узла определяется местом в решётке,
// а не полями самого узла.
// ---------------------------------------------------------
class MatrixNode {
    public:
        long        value;   // значение ячейки
        MatrixNode* right;   // следующий в строке
        MatrixNode* down;    // следующий в столбце

        MatrixNode(long v) : value(v), right(nullptr), down(nullptr) {}
        void display() const {
            cout << value << " ";
        }
};

// ---------------------------------------------------------
// Разреженная матрица на односвязных списках.
// ---------------------------------------------------------
class SparseMatrix {
    private:
        int rows;            // число строк
        int cols;            // число столбцов
        MatrixNode* head;    // левый верхний угол (0,0)
    private:
        MatrixNode* nodeAt(int r, int c) const {
            if (!inBounds(r, c))
                return nullptr;

            MatrixNode* current = head;
            for (int i = 0; i < c; i++) 
                current = current->right;
            for (int j = 0; j < r; j++)
                current = current->down;
            
            return current;
        }
    public:
        SparseMatrix(int r, int c) : rows(r), cols(c) {

            head = new MatrixNode(0);
            MatrixNode** leftColumn = new MatrixNode*[rows - 1];
            MatrixNode** upperRow   = new MatrixNode*[cols - 1];
            for (int r = 0; r < rows - 1; r++) {
                leftColumn[r] = new MatrixNode(0);
                if (r == 0)
                    head->down = leftColumn[r];
                else
                    leftColumn[r - 1]->down = leftColumn[r];
            }
            for (int c = 0; c < cols - 1; c++) {
                upperRow[c] = new MatrixNode(0);
                if (c == 0)
                    head->right = upperRow[c];
                else
                    upperRow[c - 1]->right = upperRow[c];
            }

            MatrixNode* leftNode  = nullptr;
            MatrixNode* newNode   = nullptr;
            for (int i = 0; i < rows - 1; i++) {

                leftNode = new MatrixNode(0);
                leftColumn[i]->right = leftNode;

                upperRow[0]->down = leftNode;
                upperRow[0] = leftNode;

                for (int j = 1; j < cols - 1; j++) {
                    newNode = new MatrixNode(0);
                    leftNode->right = newNode;
                    upperRow[j]->down = newNode;
                    upperRow[j] = newNode;
                    leftNode = newNode;
                }
            }

            delete[] leftColumn;
            delete[] upperRow;
        }
        ~SparseMatrix() {
            if (head == nullptr)
                return;

            MatrixNode* row = head;

            while (row != nullptr) {
                MatrixNode* col = row->right;
                while (col != nullptr) {
                    MatrixNode* next = col->right;
                    delete col;
                    col = next;
                }
                MatrixNode* nextRow = row->down;
                delete row;
                row = nextRow;
            }

            head = nullptr;

        }

        // Вставка или обновление значения в позиции (r, c).
        // Если узел уже существует — значение обновляется.
        // Возвращает true при успехе, false если (r, c) вне границ.
        bool insert(int r, int c, long value) {
            if (!inBounds(r, c))
                return false;
            MatrixNode* current = nodeAt(r, c);

            current->value = value;
            return true;
        }


        // Получить значение в позиции (r, c).
        // Если узел отсутствует — возвращает 0.
        long get(int r, int c) const {
            if (!inBounds(r, c))
                return 0;

            MatrixNode* current = nodeAt(r, c);

            if (current != nullptr)
                return current->value;
            else
                return 0;
        }

        // Удалить узел в позиции (r, c), если он есть.
        bool remove(int r, int c) {
            if (!inBounds(r, c) || head == nullptr)
                return false;

            MatrixNode* current = nodeAt(r, c);
            
            if (current->value == 0)
                return false;

            current->value = 0;
            return true;
        }

        // Вывести матрицу в виде таблицы rows x cols.
        void display() const {
            MatrixNode* current  = nullptr;
            MatrixNode* tempLeft = nullptr;
            for (int i = 0; i < rows; i++) {
                if (i == 0)
                    tempLeft = head;
                else
                    tempLeft = tempLeft->down;
                current = tempLeft;
                for (int j = 0; j < cols; j++) {
                    cout << setw(4);
                    current->display();
                    current = current->right;
                }
                cout << endl;
            }
        }

        // Геттеры размеров
        int getRows() const {
            return rows;
        }
        int getCols() const {
            return cols;
        }

        // true, если (r, c) внутри границ
        bool inBounds(int r, int c) const {
            return 0 <= r && r < rows && 0 <= c && c < cols;
        }
};

// ---------------------------------------------------------
// Вспомогательное: собрать значения матрицы в вектор
// (для удобного сравнения в тестах).
// ---------------------------------------------------------
static vector<long> snapshot(const SparseMatrix& m) {
    vector<long> v;
    for (int r = 0; r < m.getRows(); ++r)
        for (int c = 0; c < m.getCols(); ++c)
            v.push_back(m.get(r, c));
    return v;
}

static string vecToStr(const vector<long>& v) {
    string s;
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) s += " ";
        s += to_string(v[i]);
    }
    return s;
}

static int g_total = 0;
static int g_passed = 0;

static void check(const string& name,
                  const vector<long>& expected,
                  const vector<long>& actual)
{
    ++g_total;
    bool ok = (expected == actual);
    if (ok) ++g_passed;
    cout << (ok ? "[PASS] " : "[FAIL] ") << name << endl;
    if (!ok) {
        cout << "        expected: " << vecToStr(expected) << endl;
        cout << "        actual  : " << vecToStr(actual)   << endl;
    }
}

static void checkBool(const string& name, bool expected, bool actual) {
    ++g_total;
    bool ok = (expected == actual);
    if (ok) ++g_passed;
    cout << (ok ? "[PASS] " : "[FAIL] ") << name << endl;
    if (!ok) {
        cout << "        expected: " << (expected ? "true" : "false")
             << ", actual: " << (actual ? "true" : "false") << endl;
    }
}

// =========================================================
// MAIN — тесты
// =========================================================
int main() {
    // -----------------------------------------------------
    // T1: Пустая матрица 3x4 — все нули
    // -----------------------------------------------------
    cout << "=== T1: пустая матрица 3x4 ===" << endl;
    {
        SparseMatrix m(3, 4);
        vector<long> expected(12, 0);
        check("T1: все нули", expected, snapshot(m));
    }

    // -----------------------------------------------------
    // T2: Вставка одного элемента
    // -----------------------------------------------------
    cout << "=== T2: вставка одного элемента ===" << endl;
    {
        SparseMatrix m(3, 4);
        bool ok = m.insert(1, 2, 42);
        checkBool("T2a: insert вернул true", true, ok);

        vector<long> expected(12, 0);
        expected[1 * 4 + 2] = 42;
        check("T2b: элемент (1,2)=42", expected, snapshot(m));

        checkBool("T2c: get(1,2)==42", true, m.get(1, 2) == 42);
        checkBool("T2d: get(0,0)==0",  true, m.get(0, 0) == 0);
    }

    // -----------------------------------------------------
    // T3: Обновление существующего элемента
    // -----------------------------------------------------
    cout << "=== T3: обновление элемента ===" << endl;
    {
        SparseMatrix m(3, 4);
        m.insert(1, 2, 42);
        m.insert(1, 2, 99);       // то же место — обновление

        vector<long> expected(12, 0);
        expected[1 * 4 + 2] = 99;
        check("T3: значение обновилось до 99", expected, snapshot(m));
    }

    // -----------------------------------------------------
    // T4: Несколько элементов в одной строке
    // -----------------------------------------------------
    cout << "=== T4: несколько элементов в строке ===" << endl;
    {
        SparseMatrix m(3, 4);
        m.insert(0, 0, 1);
        m.insert(0, 2, 3);
        m.insert(0, 3, 4);

        vector<long> expected(12, 0);
        expected[0]  = 1;
        expected[2]  = 3;
        expected[3]  = 4;
        check("T4: строка 0 = 1 0 3 4", expected, snapshot(m));
    }

    // -----------------------------------------------------
    // T5: Несколько элементов в одном столбце
    // -----------------------------------------------------
    cout << "=== T5: несколько элементов в столбце ===" << endl;
    {
        SparseMatrix m(4, 3);
        m.insert(0, 1, 10);
        m.insert(2, 1, 20);
        m.insert(3, 1, 30);

        vector<long> expected(12, 0);
        expected[0 * 3 + 1] = 10;
        expected[2 * 3 + 1] = 20;
        expected[3 * 3 + 1] = 30;
        check("T5: столбец 1 = 10 0 20 30", expected, snapshot(m));
    }

    // -----------------------------------------------------
    // T6: Вставка вне границ — должна вернуть false и не изменить матрицу
    // -----------------------------------------------------
    cout << "=== T6: вставка вне границ ===" << endl;
    {
        SparseMatrix m(3, 3);
        checkBool("T6a: insert(-1,0) = false", false, m.insert(-1, 0, 5));
        checkBool("T6b: insert(0,-1) = false", false, m.insert(0, -1, 5));
        checkBool("T6c: insert(3,0)  = false", false, m.insert(3, 0, 5));
        checkBool("T6d: insert(0,3)  = false", false, m.insert(0, 3, 5));

        vector<long> expected(9, 0);
        check("T6e: матрица не изменилась", expected, snapshot(m));
    }

    // -----------------------------------------------------
    // T7: get вне границ
    // -----------------------------------------------------
    cout << "=== T7: get вне границ ===" << endl;
    {
        SparseMatrix m(3, 3);
        m.insert(1, 1, 7);
        checkBool("T7a: get(-1,0)==0", true, m.get(-1, 0) == 0);
        checkBool("T7b: get(3,0)==0",  true, m.get(3, 0)  == 0);
        checkBool("T7c: get(0,3)==0",  true, m.get(0, 3)  == 0);
        checkBool("T7d: get(1,1)==7",  true, m.get(1, 1)  == 7);
    }

    // -----------------------------------------------------
    // T8: Диагональ
    // -----------------------------------------------------
    cout << "=== T8: диагональная матрица ===" << endl;
    {
        SparseMatrix m(4, 4);
        for (int i = 0; i < 4; ++i)
            m.insert(i, i, i + 1);

        vector<long> expected(16, 0);
        for (int i = 0; i < 4; ++i)
            expected[i * 4 + i] = i + 1;
        check("T8: диагональ 1 2 3 4", expected, snapshot(m));
    }

    // -----------------------------------------------------
    // T9: Удаление элемента
    // -----------------------------------------------------
    cout << "=== T9: удаление ===" << endl;
    {
        SparseMatrix m(3, 3);
        m.insert(0, 0, 1);
        m.insert(1, 1, 2);
        m.insert(2, 2, 3);

        checkBool("T9a: remove(1,1) = true", true, m.remove(1, 1));
        checkBool("T9b: remove(1,1) снова = false", false, m.remove(1, 1));

        vector<long> expected(9, 0);
        expected[0] = 1;
        expected[8] = 3;
        check("T9c: после удаления", expected, snapshot(m));
    }

    // -----------------------------------------------------
    // T10: Удаление несуществующего элемента
    // -----------------------------------------------------
    cout << "=== T10: удаление несуществующего ===" << endl;
    {
        SparseMatrix m(3, 3);
        m.insert(0, 0, 5);
        checkBool("T10a: remove(1,1) = false", false, m.remove(1, 1));
        checkBool("T10b: remove(-1,0) = false", false, m.remove(-1, 0));

        vector<long> expected(9, 0);
        expected[0] = 5;
        check("T10c: матрица не изменилась", expected, snapshot(m));
    }

    // -----------------------------------------------------
    // T11: Матрица 1x1
    // -----------------------------------------------------
    cout << "=== T11: матрица 1x1 ===" << endl;
    {
        SparseMatrix m(1, 1);
        checkBool("T11a: изначально 0", true, m.get(0, 0) == 0);
        m.insert(0, 0, 7);
        checkBool("T11b: после insert == 7", true, m.get(0, 0) == 7);
        checkBool("T11c: remove = true", true, m.remove(0, 0));
        checkBool("T11d: после remove == 0", true, m.get(0, 0) == 0);
    }

    // -----------------------------------------------------
    // T12: Полная (не разреженная) матрица 3x3
    // -----------------------------------------------------
    cout << "=== T12: полная матрица 3x3 ===" << endl;
    {
        SparseMatrix m(3, 3);
        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < 3; ++c)
                m.insert(r, c, r * 3 + c + 1);

        vector<long> expected = {1,2,3, 4,5,6, 7,8,9};
        check("T12: значения 1..9", expected, snapshot(m));
    }

    // -----------------------------------------------------
    // T13: Матрица 7x10 (пример из условия)
    // -----------------------------------------------------
    cout << "=== T13: матрица 7x10 ===" << endl;
    {
        SparseMatrix m(7, 10);
        m.insert(0, 0, 1);
        m.insert(2, 4, 5);
        m.insert(6, 9, 70);

        vector<long> expected(70, 0);
        expected[0 * 10 + 0] = 1;
        expected[2 * 10 + 4] = 5;
        expected[6 * 10 + 9] = 70;
        check("T13: 1, 5, 70 в нужных позициях", expected, snapshot(m));
    }

    // -----------------------------------------------------
    // T14: Вставка в обратном порядке (снизу вверх, справа налево)
    // Проверяем, что структура строится корректно независимо
    // от порядка вставок.
    // -----------------------------------------------------
    cout << "=== T14: обратный порядок вставок ===" << endl;
    {
        SparseMatrix m(3, 3);
        m.insert(2, 2, 9);
        m.insert(1, 1, 5);
        m.insert(0, 0, 1);

        vector<long> expected(9, 0);
        expected[0] = 1;
        expected[4] = 5;
        expected[8] = 9;
        check("T14: диагональ через обратные вставки", expected, snapshot(m));
    }

    // -----------------------------------------------------
    // T15: Много элементов в одной строке
    // -----------------------------------------------------
    cout << "=== T15: строка целиком ===" << endl;
    {
        SparseMatrix m(2, 6);
        for (int c = 0; c < 6; ++c)
            m.insert(0, c, c + 1);

        vector<long> expected(12, 0);
        for (int c = 0; c < 6; ++c)
            expected[c] = c + 1;
        check("T15: строка 0 = 1..6", expected, snapshot(m));
    }

    // -----------------------------------------------------
    // T16: Много элементов в одном столбце
    // -----------------------------------------------------
    cout << "=== T16: столбец целиком ===" << endl;
    {
        SparseMatrix m(6, 2);
        for (int r = 0; r < 6; ++r)
            m.insert(r, 1, (r + 1) * 10);

        vector<long> expected(12, 0);
        for (int r = 0; r < 6; ++r)
            expected[r * 2 + 1] = (r + 1) * 10;
        check("T16: столбец 1 = 10..60", expected, snapshot(m));
    }

    // -----------------------------------------------------
    // T17: insert + remove + insert в одну позицию
    // -----------------------------------------------------
    cout << "=== T17: insert/remove/insert ===" << endl;
    {
        SparseMatrix m(3, 3);
        m.insert(1, 1, 100);
        m.remove(1, 1);
        m.insert(1, 1, 200);

        vector<long> expected(9, 0);
        expected[1 * 3 + 1] = 200;
        check("T17: значение 200 после цикла", expected, snapshot(m));
    }

    // -----------------------------------------------------
    // T18: Крупная матрица — проверка границ
    // -----------------------------------------------------
    cout << "=== T18: границы большой матрицы ===" << endl;
    {
        SparseMatrix m(100, 100);
        m.insert(0,   0,   1);
        m.insert(0,   99,  2);
        m.insert(99,  0,   3);
        m.insert(99,  99,  4);
        m.insert(50,  50,  5);

        checkBool("T18a: (0,0)==1",    true, m.get(0, 0)   == 1);
        checkBool("T18b: (0,99)==2",   true, m.get(0, 99)  == 2);
        checkBool("T18c: (99,0)==3",   true, m.get(99, 0)  == 3);
        checkBool("T18d: (99,99)==4",  true, m.get(99, 99) == 4);
        checkBool("T18e: (50,50)==5",  true, m.get(50, 50) == 5);
        checkBool("T18f: (1,1)==0",    true, m.get(1, 1)   == 0);
    }

    // -----------------------------------------------------
    // ИТОГ
    // -----------------------------------------------------
    cout << "----------------------------------------" << endl;
    cout << "Пройдено: " << g_passed << " / " << g_total << endl;

    return (g_passed == g_total) ? 0 : 1;
}