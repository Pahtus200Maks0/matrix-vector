#include <iostream>
#include <windows.h>

class matrix
{

private:
    double** matrix_0;
    int n_rows; //Количество строк в матрице
    int n_columns; //Количество столбцов в матрице

public:
    matrix();
    matrix(int rows, int columns);
    int prompt_input(); //Запрос ввода
    void print_matrix(); //Печать матрицы
    void remove_matrix(); //Чистка памяти

    matrix* operator=(const matrix& a); // Оператор присваивания
    matrix* operator+(const matrix& a); // Сложение матриц
    matrix* operator-(const matrix& a); // Вычитание матриц
    matrix* operator*(const matrix& a); //Умножение матрицы на матрицу
    matrix* operator*(double a); //Умножение матрицы на число
    matrix* operator^(int a); //Возведение матрицы в степень

    void matrix_transposition(); //Транспонирование матриц
    int inverse_matrix(matrix& M, matrix& result); //Вычисление обратной матрицы
    //matrix matrix_copy(matrix M1, matrix M2); //Копирование матриц (вспомогательная операция)

    matrix minor_matrix(matrix& M, int state_1, int state_2); //Вычисление минора матрицы
    int matrix_determinant(matrix& M, double& result); //Вычисление детерминанта или определителя матрицы
    int algebraic_matrix_complement(matrix& M, matrix& result); //Вычисление алгеброического дополнения к матрице
    
};

