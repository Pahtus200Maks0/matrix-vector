#include <iostream>
#include <windows.h>

class matrix
{

private:
    double** matrix_0;
    int n_rows; //���������� ����� � �������
    int n_columns; //���������� �������� � �������

public:
    matrix();
    matrix(int rows, int columns);
    int prompt_input(); //������ �����
    void print_matrix(); //������ �������
    void remove_matrix(); //������ ������

    matrix* operator=(const matrix& a); // �������� ������������
    matrix* operator+(const matrix& a); // �������� ������
    matrix* operator-(const matrix& a); // ��������� ������
    matrix* operator*(const matrix& a); //��������� ������� �� �������
    matrix* operator*(double a); //��������� ������� �� �����
    matrix* operator^(int a); //���������� ������� � �������

    void matrix_transposition(); //���������������� ������
    int inverse_matrix(matrix& M, matrix& result); //���������� �������� �������
    //matrix matrix_copy(matrix M1, matrix M2); //����������� ������ (��������������� ��������)

    matrix minor_matrix(matrix& M, int state_1, int state_2); //���������� ������ �������
    int matrix_determinant(matrix& M, double& result); //���������� ������������ ��� ������������ �������
    int algebraic_matrix_complement(matrix& M, matrix& result); //���������� ��������������� ���������� � �������
    
};

