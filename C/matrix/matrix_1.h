#pragma once
#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h> //�������� � ���� char *strerror(int errcode) - ������� 42 ����������� ������
#include <windows.h>
#include <memory.h>
#include <errno.h> // ��� ���������� errno
#pragma warning(disable : 4996)

typedef struct matrix_0
{
    double** matrix;
    int n_rows; //���������� ����� � �������
    int n_columns; //���������� �������� � �������

} matrix_1;

//size_t sizeofmatrix_0(); //����������� ������� ������� � ������

matrix_1* malloc_matrix(const int rows, const int columns); //�������� ������� � ��������� ������
void remove_matrix(matrix_1* M); //������ ������
void print_matrix(matrix_1* M); //������ �������
int prompt_input(matrix_1* M); //������ �����


matrix_1* minor_matrix(matrix_1* M, int state_1, int state_2); //���������� ������ �������
int inverse_matrix(matrix_1* M, matrix_1** result); //���������� �������� �������
int algebraic_matrix_complement(matrix_1* M, matrix_1** result); //���������� ��������������� ���������� � �������
matrix_1* matrix_power(matrix_1* M1, int n); //���������� ������� � �������
matrix_1* matrix_copy(matrix_1* M1, matrix_1* M2); //����������� ������ (��������������� ��������)
matrix_1* matrix_multiply_matrix(matrix_1* M1, matrix_1* M2); //��������� ������� �� �������
matrix_1* multiplying_number(matrix_1* M, double n); //��������� ������� �� �����
matrix_1* matrix_transposition(matrix_1* M); //���������������� ������
matrix_1* summ_matrix(matrix_1* M1, matrix_1* M2); //������������ ������
matrix_1* subtraction_matrix(matrix_1* M1, matrix_1* M2); //��������� ������
int matrix_determinant(matrix_1* M, double* result); //���������� ������������ ��� ������������ �������

#endif // MATRIX_H_INCLUDED

