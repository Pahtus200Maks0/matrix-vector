
/*���� ��� ������������ �� ���� ����������� ��������� �� ��++ ��� ������ 
� ��������� ���, ��� ��� �������� � ����������. ��� �������� �����������������
�������� ������� �������� ��������������� ���������.*/

#include "matematicc++.h"
#include <windows.h>

int m1, m2 = 0;
matrix M_4;
matrix M_5;
matrix M_6;

int main(void)
{
    system("chcp 1251 > 0");

    printf("������� ����������� ����� � �������� ��� ������� ������������� ��� ����������:\n");
    std::cin >> m1 >> m2;
    matrix M_2(m1, m2);
    std::cout << "\n������� ������� ������������� ��� ����������:\n";
    M_2.prompt_input();
    std::cout << "������� ����������� ����� � �������� ��� ������� ������� ��������� ������:\n";
    std::cin >> m1 >> m2;
    matrix M_3(m1, m2);
    std::cout << "\n������� ������� ��������� ������:\n";
    M_3.prompt_input();
    M_2.inverse_matrix(M_2, M_4); //���������� �������� �������
    M_4 * M_3; M_5 = M_4;
    std::cout << "\n\n";
    M_5.print_matrix();
    std::cout << "\n������� ��������: (����������� ������� ������ �������� � �������� ��������� ������)\n\n";
    M_2 * M_5; M_6 = M_5;
    M_6.print_matrix();
}
   












