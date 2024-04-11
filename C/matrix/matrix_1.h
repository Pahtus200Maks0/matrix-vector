#pragma once
#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h> //Включает в себя char *strerror(int errcode) - выводит 42 стандартные ошибки
#include <windows.h>
#include <memory.h>
#include <errno.h> // для переменной errno
#pragma warning(disable : 4996)

typedef struct matrix_0
{
    double** matrix;
    int n_rows; //Количество строк в матрице
    int n_columns; //Количество столбцов в матрице

} matrix_1;

//size_t sizeofmatrix_0(); //Определения размера матрицы в байтах

matrix_1* malloc_matrix(const int rows, const int columns); //Создание матрицы и выделение памяти
void remove_matrix(matrix_1* M); //Чистка памяти
void print_matrix(matrix_1* M); //Печать матрицы
int prompt_input(matrix_1* M); //Запрос ввода


matrix_1* minor_matrix(matrix_1* M, int state_1, int state_2); //Вычисление минора матрицы
int inverse_matrix(matrix_1* M, matrix_1** result); //Вычисление обратной матрицы
int algebraic_matrix_complement(matrix_1* M, matrix_1** result); //Вычисление алгеброического дополнения к матрице
matrix_1* matrix_power(matrix_1* M1, int n); //Возведение матрицы в степень
matrix_1* matrix_copy(matrix_1* M1, matrix_1* M2); //Копирование матриц (вспомогательная операция)
matrix_1* matrix_multiply_matrix(matrix_1* M1, matrix_1* M2); //Умножение матрицы на матрицу
matrix_1* multiplying_number(matrix_1* M, double n); //Умножение матрицы на число
matrix_1* matrix_transposition(matrix_1* M); //Транспонирование матриц
matrix_1* summ_matrix(matrix_1* M1, matrix_1* M2); //Суммирование матриц
matrix_1* subtraction_matrix(matrix_1* M1, matrix_1* M2); //Вычитание матриц
int matrix_determinant(matrix_1* M, double* result); //Вычисление детерминанта или определителя матрицы

#endif // MATRIX_H_INCLUDED

