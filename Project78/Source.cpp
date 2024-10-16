#include <iostream>

class A 
{
private:
    int value;

public:
    A(int v = 0) : value(v) {}

    A operator+(const A& other) const { return A(value + other.value); }
    A operator-(const A& other) const { return A(value - other.value); }
    A operator*(const A& other) const { return A(value * other.value); }
    A operator/(const A& other) const {
        return A(value / other.value);
    }

    friend std::ostream& operator<<(std::ostream& os, const A& obj) 
    {
        os << obj.value;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, A& obj) 
    {
        is >> obj.value;
        return is;
    }

    int getValue() const { return value; }
};

template <typename T>
class Matrix 
{
private:
    T** data;
    int rows, cols;

    void allocateMemory() 
    {
        data = new T * [rows];
        for (int i = 0; i < rows; ++i)
            data[i] = new T[cols];
    }

    void deallocateMemory() 
    {
        for (int i = 0; i < rows; ++i)
            delete[] data[i];
        delete[] data;
    }

public:
    Matrix(int r, int c) : rows(r), cols(c) 
    {
        allocateMemory();
    }

    ~Matrix() 
    {
        deallocateMemory();
    }

    
    void fillFromInput() 
    {
        std::cout << "Введите элементы матрицы (" << rows << "x" << cols << "):" << std::endl;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                std::cin >> data[i][j];
    }

    void display() const 
    {
        std::cout << "Матрица:" << std::endl;
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < cols; ++j)
                std::cout << data[i][j] << " ";
            std::cout << std::endl;
        }
    }

    Matrix operator+(const Matrix& other) const 
    {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    T maxElement() const 
    {
        T maxVal = data[0][0];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                if (data[i][j].getValue() > maxVal.getValue())
                    maxVal = data[i][j];
        return maxVal;
    }

    T minElement() const 
    {
        T minVal = data[0][0];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                if (data[i][j].getValue() < minVal.getValue())
                    minVal = data[i][j];
        return minVal;
    }
};

int main() 
{
    Matrix<A> mat1(2, 2);
    Matrix<A> mat2(2, 2);

   
    mat1.fillFromInput();

    
    mat2.fillFromInput();

    
    Matrix<A> matSum = mat1 + mat2;

    
    matSum.display();

    std::cout << "Максимальный элемент в сумме матриц: " << matSum.maxElement() << std::endl;
    std::cout << "Минимальный элемент в сумме матриц: " << matSum.minElement() << std::endl;

    return 0;
}