/**
 * @file Proje2
 * @description Karmaşık sayılar uzayında tanımlı olan vektör ve matris üzerinde bir takım lineer cebir işlemleri gerçekleştiren sınıf ve metotları gerçekledim ve oluşturduğum metotları main metodu içerisinde test ettim.
 * @assignment 2. Proje
 * @date 23/12/2023
 * @author Hacer Ebra ÖZDEMİR hacerebra.ozdemir@stu.fsm.edu.tr
 */

#include <iostream>
#include <vector>

// “LinearAlgebraObject” adında soyut (abstract) sınıf
class LinearAlgebraObject
{
public:
    virtual void print() = 0;
    virtual void operator+() const = 0;
    virtual void operator-() const = 0;
    virtual void operator*() const = 0;
};

// Karmaşık sayıların sanal (Imaginary) kısmını ifade eden Imaginary sınıfı.
class Imaginary
{
private:
    double imaginaryPart;

public:
    Imaginary(double imag = 0.0) : imaginaryPart(imag) {}

    // Getter
    double getImaginaryPart() const
    {
        return imaginaryPart;
    }

    void setImaginaryPart(double im)
    {
        imaginaryPart = im;
    }

    // Toplama atama
    Imaginary &operator+=(const Imaginary &other)
    {
        imaginaryPart += other.getImaginaryPart();
        return *this;
    }

    // Çıkarma atama
    Imaginary &operator-=(const Imaginary &other)
    {
        imaginaryPart -= other.getImaginaryPart();
        return *this;
    }

    // Eşitlik kontrolü
    bool operator==(const Imaginary &other) const
    {
        return imaginaryPart == other.imaginaryPart;
    }

    void print() const
    {
        std::cout << imaginaryPart << "i\t";
    }
};

// “Imaginary” sınıfından türettilen (inheritance) Complex sınıfı.
class Complex : public Imaginary
{
private:
    double realPart;

public:
    Complex(double real = 0.0, double imag = 0.0) : Imaginary(imag), realPart(real) {}

    // Getter
    double getRealPart() const
    {
        return realPart;
    }

    // Aritmetik işlemler
    Complex operator+(const Complex &other) const
    {
        return Complex(realPart + other.realPart, getImaginaryPart() + other.getImaginaryPart());
    }

    Complex operator-(const Complex &other) const
    {
        return Complex(realPart - other.realPart, getImaginaryPart() - other.getImaginaryPart());
    }

    Complex operator*(const Complex &other) const
    {
        return Complex(realPart * other.realPart - getImaginaryPart() * other.getImaginaryPart(),
                       realPart * other.getImaginaryPart() + getImaginaryPart() * other.realPart);
    }

    Complex operator/(const Complex &other) const
    {
        double denominator = other.realPart * other.realPart + other.getImaginaryPart() * other.getImaginaryPart();
        if (denominator != 0)
        {
            return Complex((realPart * other.realPart + getImaginaryPart() * other.getImaginaryPart()) / denominator,
                           (realPart * other.getImaginaryPart() - getImaginaryPart() * other.realPart) / denominator);
        }
        else
        {

            std::cerr << "Division by zero." << std::endl;
            return Complex(0.0, 0.0);
        }
    }

    // Atama operatörü
    Complex &operator=(const Complex &other)
    {
        if (this != &other)
        {
            realPart = other.realPart;
            Imaginary::operator=(other);
        }
        return *this;
    }

    // Eşlenik operatörü
    Complex conjugate() const
    {
        return Complex(realPart, -getImaginaryPart());
    }

    // Toplama atama
    Complex &operator+=(const Complex &other)
    {
        realPart += other.getRealPart();
        setImaginaryPart(getImaginaryPart() + other.getImaginaryPart());
        return *this;
    }

    // Çıkarma atama
    Complex &operator-=(const Complex &other)
    {
        realPart -= other.getRealPart();
        setImaginaryPart(getImaginaryPart() - other.getImaginaryPart());
        return *this;
    }

    // Çarpma atama
    Complex &operator*=(const Complex &other)
    {
        double temp_re = realPart * other.getRealPart() - getImaginaryPart() * other.getImaginaryPart();
        double temp_im = realPart * other.getImaginaryPart() + getImaginaryPart() * other.getRealPart();
        realPart = temp_re;
        setImaginaryPart(temp_im);
        return *this;
    }

    // Bölme atama
    Complex &operator/=(const Complex &other)
    {
        double denominator = other.getRealPart() * other.getRealPart() + other.getImaginaryPart() * other.getImaginaryPart();
        double temp_re = (realPart * other.getRealPart() + getImaginaryPart() * other.getImaginaryPart()) / denominator;
        double temp_im = (realPart * other.getImaginaryPart() - getImaginaryPart() * other.getRealPart()) / denominator;
        realPart = temp_re;
        setImaginaryPart(temp_im);
        return *this;
    }

    // Print metodu
    void print() const
    {
        std::cout << realPart << " + ";
        Imaginary::print();
    }
};

// Complex sayılar üzerinde tanımlı Vector sınıfı.
class Vector
{
private:
    size_t _size;
    std::vector<Complex> element;

public:
    Vector(size_t size) : element(size) {}

    // Elemanlara erişim
    Complex &operator[](size_t index)
    {
        return element[index];
    }

    const Complex &operator[](size_t index) const
    {
        return element[index];
    }

    Vector &operator=(const Vector &other)
    {
        if (this != &other)
        {
            element = other.element;
        }
        return *this;
    }

    // Aritmetik işlemler
    Vector operator+(const Vector &other) const
    {
        Vector result(size());
        for (size_t i = 0; i < size(); ++i)
        {
            result[i] = element[i] + other[i];
        }
        return result;
    }

    Vector operator-(const Vector &other) const
    {
        Vector result(size());
        for (size_t i = 0; i < size(); ++i)
        {
            result[i] = element[i] - other[i];
        }
        return result;
    }

    Vector operator*(const Vector &other) const
    {
        Vector result(size());
        for (size_t i = 0; i < size(); ++i)
        {
            result[i] = element[i] * other[i];
        }
        return result;
    }

    // Boyutu alma
    size_t size() const
    {
        return element.size();
    }

    // Toplama atama
    Vector &operator+=(const Vector &other)
    {
        for (size_t i = 0; i < size(); ++i)
        {
            element[i] += other[i];
        }
        return *this;
    }

    // Çıkarma atama
    Vector &operator-=(const Vector &other)
    {
        for (size_t i = 0; i < size(); ++i)
        {
            element[i] -= other[i];
        }
        return *this;
    }
    // Çarpma atama
    Vector &operator*=(const Vector &other)
    {
        for (size_t i = 0; i < size(); ++i)
        {
            element[i] *= other[i];
        }
        return *this;
    }

    // Eşitlik kontrolü
    bool operator==(const Vector &other) const
    {
        if (size() != other.size())
        {
            return false;
        }

        for (size_t i = 0; i < size(); ++i)
        {
            if (!(element[i] == other[i]))
            {
                return false;
            }
        }

        return true;
    }

    // Print metodu
    void print() const
    {
        for (const Complex &element : element)
        {
            element.print();
        }
    }
};

// Complex sayılar üzerinde tanımlı Matrix sınıfı.
class Matrix
{
private:
    size_t row_;
    size_t col_;
    std::vector<std::vector<Complex> > element;

public:
    // Constructor
    Matrix(size_t row, size_t col) : row_(row), col_(col), element(row, std::vector<Complex>(col)) {}

    size_t getrow() const
    {
        return row_;
    }
    size_t getcol() const
    {
        return col_;
    }

    // Elemanlara erişim
    Complex &operator()(size_t rowIndex, size_t colIndex)
    {
        return element[rowIndex][colIndex];
    }

    const Complex &operator()(size_t rowIndex, size_t colIndex) const
    {
        return element[rowIndex][colIndex];
    }

    Matrix &operator=(const Matrix &other)
    {
        if (this != &other)
        {
            row_ = other.row_;
            col_ = other.col_;
            element = other.element;
        }
        return *this;
    }

    // Aritmetik işlemler
    Matrix operator+(const Matrix &other) const
    {
        if (row_ != other.row_ || col_ != other.col_)
        {
            return Matrix(0, 0);
        }

        Matrix result(row_, col_);
        for (size_t i = 0; i < row_; ++i)
        {
            for (size_t j = 0; j < col_; ++j)
            {
                result(i, j) = element[i][j] + other(i, j);
            }
        }
        return result;
    }

    Matrix operator-(const Matrix &other) const
    {
        if (row_ != other.row_ || col_ != other.col_)
        {
            return Matrix(0, 0);
        }

        Matrix result(row_, col_);
        for (size_t i = 0; i < row_; ++i)
        {
            for (size_t j = 0; j < col_; ++j)
            {
                result(i, j) = element[i][j] - other(i, j);
            }
        }
        return result;
    }

    Matrix operator*(const Matrix &other) const
    {
        if (col_ != other.row_)
        {
            return Matrix(0, 0);
        }

        Matrix result(row_, other.col_);
        for (size_t i = 0; i < row_; ++i)
        {
            for (size_t j = 0; j < other.col_; ++j)
            {
                for (size_t k = 0; k < col_; ++k)
                {
                    result(i, j) = result(i, j) + element[i][k] * other(k, j);
                }
            }
        }
        return result;
    }

    // Toplama atama
    Matrix &operator+=(const Matrix &other)
    {
        if (row_ != other.getrow() || col_ != other.getcol())
        {
            throw std::invalid_argument("Matrix dimensions are not compatible for addition.");
        }

        for (size_t i = 0; i < row_; ++i)
        {
            for (size_t j = 0; j < col_; ++j)
            {
                element[i][j] += other(i, j);
            }
        }

        return *this;
    }

    // Çıkarma atama
    Matrix &operator-=(const Matrix &other)
    {
        if (row_ != other.getrow() || col_ != other.getcol())
        {
            throw std::invalid_argument("Matrix dimensions are not compatible for subtraction.");
        }

        for (size_t i = 0; i < row_; ++i)
        {
            for (size_t j = 0; j < col_; ++j)
            {
                element[i][j] -= other(i, j);
            }
        }

        return *this;
    }

    // Çarpma atama
    Matrix &operator*=(const Matrix &other)
    {
        if (col_ != other.getrow())
        {
            throw std::invalid_argument("Matrix dimensions are not compatible for multiplication.");
        }

        Matrix result(row_, other.getcol());

        for (size_t i = 0; i < row_; ++i)
        {
            for (size_t j = 0; j < other.getcol(); ++j)
            {
                for (size_t k = 0; k < col_; ++k)
                {
                    result(i, j) += element[i][k] * other(k, j);
                }
            }
        }

        *this = result;

        return *this;
    }

    // Eşitlik kontrolü
    bool operator==(const Matrix &other) const
    {
        if (row_ != other.getrow() || col_ != other.getcol())
        {
            return false;
        }

        for (size_t i = 0; i < row_; ++i)
        {
            for (size_t j = 0; j < col_; ++j)
            {
                if (!(element[i][j] == other(i, j)))
                {
                    return false;
                }
            }
        }

        return true;
    }

    // Transpose metodu
    Matrix transpose() const
    {
        Matrix result(col_, row_);
        for (size_t i = 0; i < row_; ++i)
        {
            for (size_t j = 0; j < col_; ++j)
            {
                result(j, i) = element[i][j];
            }
        }
        return result;
    }

    // Deteminant bulma metodu
    Complex determinant() const
    {
        if (row_ != col_)
        {
            throw std::logic_error("Determinant is only defined for square matrices.");
        }

        if (row_ == 1)
        {
            return element[0][0];
        }
        else if (row_ == 2)
        {
            return element[0][0] * element[1][1] - element[0][1] * element[1][0];
        }
        else
        {
            Complex det = Complex(0, 0);
            for (size_t i = 0; i < col_; ++i)
            {
                Matrix submatrix(row_ - 1, col_ - 1);
                for (size_t j = 1; j < row_; ++j)
                {
                    size_t l = 0;
                    for (size_t k = 0; k < col_; ++k)
                    {
                        if (k == i)
                        {
                            continue;
                        }
                        submatrix(j - 1, l) = element[j][k];
                        ++l;
                    }
                }

                // Çarpanın işareti doğru bir şekilde belirlenmeli
                Complex sign = ((i % 2) == 0) ? Complex(1, 0) : Complex(-1, 0);

                // Rekürsif olarak alt matris determinantı hesaplanır ve ana determinanta eklenir.
                det += sign * element[0][i] * submatrix.determinant();
            }
            return det;
        }
    }

    // Print metodu
    void print() const
    {
        for (size_t i = 0; i < row_; ++i)
        {
            for (size_t j = 0; j < col_; ++j)
            {
                element[i][j].print();
            }
            std::cout << std::endl;
        }
    }
};

// Matrix sınıfından türetilen SquareMatrix sınıfı.
class SquareMatrix : public Matrix
{
public:
    SquareMatrix(size_t size) : Matrix(size, size) {}

    // Kare matris oluşturma
    static SquareMatrix createSquareMatrix(const std::vector<std::vector<Complex> > &values)
    {
        size_t size = values.size();
        SquareMatrix squareMatrix(size);
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < size; ++j)
            {
                squareMatrix(i, j) = values[i][j];
            }
        }
        return squareMatrix;
    }
};

// Matrix sınıfından türetilen IdentityMatrix sınıfı.
class IdentityMatrix : public Matrix
{
public:
    IdentityMatrix(size_t size) : Matrix(size, size) {}

    // Birim matris oluşturma
    static IdentityMatrix createIdentityMatrix(size_t size)
    {
        IdentityMatrix identityMatrix(size);
        for (size_t i = 0; i < size; ++i)
        {
            identityMatrix(i, i) = Complex(1, 0); // Ana köşegen elemanlar 1, diğerleri 0
        }
        return identityMatrix;
    }
};

// Matrix sınıfından türetilen TriangleMatrix sınıfı.
class TriangleMatrix : public Matrix
{
public:
    TriangleMatrix(size_t size) : Matrix(size, size) {}

    // Üçgen matris oluşturma
    static TriangleMatrix createTriangleMatrix(const std::vector<std::vector<Complex> > &values)
    {
        size_t size = values.size();
        TriangleMatrix triangleMatrix(size);
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < size; ++j)
            {
                if (j <= i)
                {
                    triangleMatrix(i, j) = values[i][j];
                }
                else
                {
                    triangleMatrix(i, j) = Complex(0, 0); // Üst üçgen elemanları sıfır
                }
            }
        }
        return triangleMatrix;
    }
};

int main()
{
    // Örnek kullanım
    Complex c1(3.0, 2.0);
    Complex c2(5.0, 4.0);
    std::cout << "1.Complex: ";
    c1.print();
    std::cout << std::endl;
    std::cout << "2.Complex: ";
    c2.print();
    std::cout << std::endl;

    // Aritmetik islemler
    Complex sum = c1 + c2;
    Complex difference = c1 - c2;
    Complex product = c1 * c2;
    Complex quotient = c1 / c2;
    Complex conjugateC1 = c1.conjugate();
    bool isEqual = (c1 == c2);
    std::cout << "\nSum (+): ";
    sum.print();
    std::cout << std::endl;
    std::cout << "Difference (-): ";
    difference.print();
    std::cout << std::endl;
    std::cout << "Product (*): ";
    product.print();
    std::cout << std::endl;
    std::cout << "Quotient (/): ";
    quotient.print();
    std::cout << std::endl;
    std::cout << "Conjugate of c1: ";
    conjugateC1.print();
    std::cout << std::endl;

    if (c1 == c2)
    {
        std::cout << "Equality(==): c1 is equal to c2" << std::endl;
    }
    else
    {
        std::cout << "Equality(==): c1 is not equal to c2\n"
                  << std::endl;
    }

    // Toplama atama
    Complex toplamAtama = c1;
    toplamAtama += c2;
    std::cout << "Sum (+=): ";
    toplamAtama.print();
    std::cout << std::endl;

    // Çıkarma atama
    Complex cıkarmaAtama = c1;
    cıkarmaAtama -= c2;
    std::cout << "Difference (-=): ";
    cıkarmaAtama.print();
    std::cout << std::endl;

    // Çarpma atama
    Complex carpmaAtama = c1;
    carpmaAtama *= c2;
    std::cout << "Product (*=): ";
    carpmaAtama.print();
    std::cout << std::endl;

    // Bölme atama
    Complex bolmeAtama = c1;
    bolmeAtama /= c2;
    std::cout << "Quotient (/=): ";
    bolmeAtama.print();
    std::cout << std::endl;

    // Örnek vector kullanımı
    Vector vector1(3);
    vector1[0] = Complex(1.0, 2.0);
    vector1[1] = Complex(3.0, 4.0);
    vector1[2] = Complex(5.0, 6.0);
    std::cout << "\n1.Vector: " << std::endl;
    vector1.print();
    std::cout << std::endl;

    Vector vector2(3);
    vector2[0] = Complex(7.0, 8.0);
    vector2[1] = Complex(9.0, 10.0);
    vector2[2] = Complex(11.0, 12.0);
    std::cout << "\n2.Vector: " << std::endl;
    vector2.print();
    std::cout << std::endl;

    // Aritmetik işlemleri uygulama
    Vector sumv = vector1 + vector2;
    Vector diffv = vector1 - vector2;
    Vector productv = vector1 * vector2;

    std::cout << "\nSum of vectors: " << std::endl;
    sumv.print();
    std::cout << std::endl;

    std::cout << "\nDifference of vectors: " << std::endl;
    diffv.print();
    std::cout << std::endl;

    std::cout << "\nMultiplication of vectors: " << std::endl;
    product.print();
    std::cout << std::endl;

    // Toplama atama
    Vector toplam = vector1;
    toplam += vector2;
    std::cout << "\nSum Vector(+=): " << std::endl;
    toplam.print();
    std::cout << std::endl;

    // Çıkarma atama
    Vector fark = vector1;
    fark -= vector2;
    std::cout << "\nDifference Vector(-=): " << std::endl;
    fark.print();
    std::cout << std::endl;

    // Çarpma atama
    Vector carpma = vector1;
    carpma *= vector2;
    std::cout << "\nProduct Vector(*=): " << std::endl;
    carpma.print();
    std::cout << std::endl;

    // Vector için eşitlik kontrolü
    if (vector1 == vector2)
    {
        std::cout << "\nVectors are equal." << std::endl;
    }
    else
    {
        std::cout << "\nVectors are not equal." << std::endl;
    }

    // Örnek matrix kullanımı
    Matrix matrix1(2, 2);
    matrix1(0, 0) = Complex(4.0, 1.0);
    matrix1(0, 1) = Complex(6.0, 3.0);
    matrix1(1, 0) = Complex(10.0, 7.0);
    matrix1(1, 1) = Complex(9.0, 10.0);

    Matrix matrix2(2, 2);
    matrix2(0, 0) = Complex(1.0, 2.0);
    matrix2(0, 1) = Complex(3.0, 4.0);
    matrix2(1, 0) = Complex(5.0, 6.0);
    matrix2(1, 1) = Complex(7.0, 8.0);

    std::cout << "\n1.Matrix:" << std::endl;
    matrix1.print();
    std::cout << "\n2.Matrix:" << std::endl;
    matrix2.print();

    // Determinant hesaplama
    Complex det = matrix1.determinant();
    std::cout << "\nDeterminantof first matrix: " << std::endl;
    det.print();
    std::cout << std::endl;

    // Transpoz hesaplama
    Matrix transposeM1 = matrix1.transpose();
    std::cout << "\nTranspose of first matrix:" << std::endl;
    transposeM1.print();

    // Aritmetik işlemler
    Matrix summ = matrix1 + matrix2;
    Matrix diffm = matrix1 - matrix2;
    Matrix productm = matrix1 * matrix2;

    // Sonuçları yazdırma
    std::cout << "\nSum of matrices: " << std::endl;
    summ.print();

    std::cout << "\nDifference of matrices: " << std::endl;
    diffm.print();

    std::cout << "\nMultiplication of matrices: " << std::endl;
    productm.print();

    // Toplama atama
    Matrix toplamMatrix = matrix1;
    toplamMatrix += matrix2;
    std::cout << "\nSum Matrix(+=): " << std::endl;
    toplamMatrix.print();

    // Çıkarma atama
    Matrix farkMatrix = matrix1;
    farkMatrix -= matrix2;
    std::cout << "\nDifference Matrix(-=): " << std::endl;
    farkMatrix.print();

    // Çarpma atama
    Matrix carpımMatrix = matrix1;
    carpımMatrix *= matrix2;
    std::cout << "\nProduct Matrix(*=): " << std::endl;
    carpımMatrix.print();
    std::cout << std::endl;

    // Eşitlik kontrolü
    if (matrix1 == matrix2)
    {
        std::cout << "Matrices are equal." << std::endl;
    }
    else
    {
        std::cout << "Matrices are not equal." << std::endl;
    }
    std::cout << std::endl;

    // Square matrix oluşturma öreneği
    std::vector<std::vector<Complex> > squareValues(2, std::vector<Complex>(2));
    squareValues[0][0] = Complex(4, 1);
    squareValues[0][1] = Complex(6, 3);
    squareValues[1][0] = Complex(10, 7);
    squareValues[1][1] = Complex(9, 10);
    SquareMatrix squareMatrix = SquareMatrix::createSquareMatrix(squareValues);

    // Identity matrix oluşturma öreneği
    IdentityMatrix identityMatrix = IdentityMatrix::createIdentityMatrix(4);

    // Triangle matrix oluşturma örenği
    std::vector<std::vector<Complex> > triangleValues(3, std::vector<Complex>(3));
    triangleValues[0][0] = Complex(4, 1);
    triangleValues[1][0] = Complex(6, 3);
    triangleValues[1][1] = Complex(10, 7);
    triangleValues[2][0] = Complex(2, 5);
    triangleValues[2][1] = Complex(8, 9);
    triangleValues[2][2] = Complex(1, 3);
    TriangleMatrix triangleMatrix = TriangleMatrix::createTriangleMatrix(triangleValues);

    // Özel matrisleri yazdırma
    std::cout << "Square Matrix:" << std::endl;
    squareMatrix.print();
    std::cout << std::endl;

    std::cout << "Identity Matrix:" << std::endl;
    identityMatrix.print();
    std::cout << std::endl;

    std::cout << "Triangle Matrix:" << std::endl;
    triangleMatrix.print();
    std::cout << std::endl;

    return 0;
}
