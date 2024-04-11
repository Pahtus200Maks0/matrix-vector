#pragma once
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h> //Включает в себя strerror
#include <windows.h>
#include <memory.h>
#include <errno.h>
#pragma warning(disable : 4996)

typedef struct vector_0
{
    double v_1; //Координата 1
    double v_2; //Координата 2
    double v_3; //Координата 3

} vector_1;

typedef struct vector_m
{
    double** minor_vector;
    int n_rows; //Количество строк в матрице
    int n_columns; //Количество столбцов в матрице

} vector_minor;

vector_minor* malloc_matrix_vector(const int rows, const int columns); //Создание матрицы и выделение памяти
vector_1* malloc_vector(double state1, double state2, double state3); //Создание вектора и выделение памяти
void print_vector(vector_1* M); //Печать вектора

vector_1* summ_vector(vector_1* M1,vector_1* M2); //Суммирование векторов
vector_1* subtraction_vector(vector_1* M1, vector_1* M2); //Вычитание векторов
vector_1* multiplying_vector_1(vector_1* M, double state); //Умножение векторов на число
double modulus_vector(vector_1* M); //Длина (модуль) вектора
double vector_multip_scal_vector(vector_1* M1, vector_1* M2); //Умножение вектора на вектор (скалярное произведение)
vector_1* vector_multip_vect_vector(vector_1* M1, vector_1* M2); //Умножение вектора на вектор (векторное произведение)
void mixed_of_vectors(vector_1* M1, vector_1* M2, vector_1* M3, double* state1); //Смешанное произведение векторов
double angle_vectors(vector_1* M1, vector_1* M2); //Угол между векторами
double dvector_projection(vector_1* M1, vector_1* M2); //Проекция вектор на вектор
vector_minor* minor_matrix(vector_minor* M, int state_1, int state_2); //Вычисление минора матрицы
int matrix_determinant(vector_minor* M, double* result); //Вычисление детерминанта или определителя матрицы

void area_of_​​a_triangle(vector_1* M1, vector_1* M2, double* state1); //Площадь треугольника построенного на векторах
void area_of_a_parallelogram(vector_1* M1, vector_1* M2, double* state1); //Площадь параллелограмма построенного на векторах
void volume_of_a_pyramid(vector_1* M1, vector_1* M2, vector_1* M3, double* state1); //Объем пирамиды построенного на векторах




