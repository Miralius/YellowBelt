#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
public:
    Matrix() = default;

    [[maybe_unused]] Matrix(int num_rows, int num_cols) {
        if (num_rows < 0 or num_cols < 0) {
            throw out_of_range("The row/column number is/are negative");
        }
        resizeMatrix(num_rows, num_cols);
    }

    [[maybe_unused]] void Reset(int num_rows, int num_cols) {
        if (num_rows < 0 or num_cols < 0) {
            throw out_of_range("The row/column number is/are negative");
        }
        _matrix.clear();
        resizeMatrix(num_rows, num_cols);
    }

    [[nodiscard]] int At(int rowNumber, int num_cols) const {
        return _matrix.at(rowNumber).at(num_cols);
    }

    int &At(int rowNumber, int num_cols) {
        return _matrix.at(rowNumber).at(num_cols);
    }

    [[nodiscard]] size_t GetNumRows() const {
        return _matrix.size();
    }

    [[nodiscard]] size_t GetNumColumns() const {
        return !_matrix.empty() ? _matrix.at(0).size() : 0;
    }

    static bool DoMatrixesHaveTheSameSize(const Matrix &lhs, const Matrix &rhs) {
        return lhs.GetNumRows() == rhs.GetNumRows() and lhs.GetNumColumns() == rhs.GetNumColumns();
    }

private:
    void resizeMatrix(int num_rows, int num_cols) {
        if (num_cols != 0) {
            _matrix.assign(num_rows, vector<int>(num_cols));
        }
    }

    vector<vector<int>> _matrix;
};

istream &operator>>(istream &in, Matrix &obj) {
    int rowCount;
    in >> rowCount;
    int columnCount;
    in >> columnCount;
    auto temp = Matrix(rowCount, columnCount);
    for (auto i = 0; i < rowCount; ++i) {
        for (auto j = 0; j < columnCount; ++j) {
            int number;
            in >> number;
            temp.At(i, j) = number;
        }
    }
    if (in) {
        obj = temp;
    }
    return in;
}

ostream &operator<<(ostream &out, const Matrix &obj) {
    out << obj.GetNumRows() << ' ' << obj.GetNumColumns() << '\n';
    for (size_t i = 0; i < obj.GetNumRows(); ++i) {
        for (size_t j = 0; j < obj.GetNumColumns(); ++j) {
            out << obj.At(static_cast<int>(i), static_cast<int>(j)) << ' ';
        }
        out << '\n';
    }
    return out;
}

// * оператор проверки на равенство двух объектов класса Matrix
bool operator==(const Matrix &lhs, const Matrix &rhs) {
    if (!Matrix::DoMatrixesHaveTheSameSize(lhs, rhs)) {
        return false;
    }
    for (size_t i = 0; i < lhs.GetNumRows(); ++i) {
        for (size_t j = 0; j < lhs.GetNumColumns(); ++j) {
            if (lhs.At(static_cast<int>(i), static_cast<int>(j)) != rhs.At(static_cast<int>(i), static_cast<int>(j))) {
                return false;
            }
        }
    }
    return true;
}

Matrix operator+(const Matrix &lhs, const Matrix &rhs) {
    if (!Matrix::DoMatrixesHaveTheSameSize(lhs, rhs)) {
        throw invalid_argument("");
    }
    auto result = Matrix(static_cast<int>(lhs.GetNumRows()), static_cast<int>(lhs.GetNumColumns()));
    for (size_t i = 0; i < lhs.GetNumRows(); ++i) {
        for (size_t j = 0; j < lhs.GetNumColumns(); ++j) {
            result.At(static_cast<int>(i), static_cast<int>(j)) =
                    lhs.At(static_cast<int>(i), static_cast<int>(j)) + rhs.At(static_cast<int>(i), static_cast<int>(j));
        }
    }
    return result;
}

int main() {
    Matrix one;
    Matrix two;

    cin >> one >> two;
    cout << one + two << endl;
    return 0;
}
