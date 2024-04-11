
/*Этот код представляет из себя законченную библиотку на Си для работы с матрицами  
3х мерными векторами так, как это делается в математике. Для демонстрации работы приведён код
проверки данных
*/

#include "matrix_1.h"
#include "vector_1.h"


matrix_1* matrix_2 = NULL;
matrix_1* matrix_3 = NULL;
matrix_1* matrix_4 = NULL;
matrix_1* matrix_5 = NULL;
matrix_1* matrix_6 = NULL;
matrix_1* result = NULL;

vector_1* vector_2 = NULL;
vector_1* vector_3 = NULL;
vector_1* vector_4 = NULL;
vector_1* vector_5 = NULL;

int m1, m2 = 0;


int showMenu(void); //Показать меню

int main(void)
{
    system("chcp 1251 > 0");

    int input = 0;
    system("chcp 1251 > 0");
    puts("Input rules x x x SPACE... Enter matrix:"); //Правила ввода x x x ПРОБЕЛ... Введите матрицу :
    double det = 0.0;

    matrix_2 = malloc_matrix(3, 3); 
    matrix_3 = malloc_matrix(3, 3); 

    vector_2 = malloc_vector(13, 23, 33);
    vector_3 = malloc_vector(31, 32, 33);
    vector_5 = malloc_vector(11, 12, 13);

    while (input != 1)
    {
        input = showMenu();
        switch (input)
        {
            case 2:
                prompt_input(matrix_2);
                puts("Определитель матрицы:");
                matrix_determinant(matrix_2, &det);
                printf("det = %3.lf", det);
                break;
            case 3:
                prompt_input(matrix_2);
                puts("Вычисление алгеброического дополнения к матрице:");
                algebraic_matrix_complement(matrix_2, &result);
                print_matrix(result);
                break;
            case 4:
                prompt_input(matrix_2);
                puts("Вычисление обратной матрицы:");
                inverse_matrix(matrix_2, &result);
                print_matrix(result);
                break;
            case 5:
                prompt_input(matrix_2);
                puts("Возведение матрицы в степень:");
                matrix_2 = matrix_power(matrix_2, 2);
                print_matrix(matrix_2);
                break;
            case 6:
                prompt_input(matrix_2);
                prompt_input(matrix_3);
                puts("Умножение матрицы на матрицу:");
                matrix_2 = matrix_multiply_matrix(matrix_2, matrix_3);
                print_matrix(matrix_2);
                break;
            case 7:
                prompt_input(matrix_2);
                puts("Транспонирование матриц:");
                matrix_2 = matrix_transposition(matrix_2);
                print_matrix(matrix_2);
                break;
            case 8:
                prompt_input(matrix_2);
                prompt_input(matrix_3);
                puts("Суммирование матриц:");
                matrix_4 = summ_matrix(matrix_2, matrix_3);
                print_matrix(matrix_4);
                break;
            case 9:
                prompt_input(matrix_2);
                prompt_input(matrix_3);
                puts("Вычитание матриц:");
                prompt_input(matrix_3);
                matrix_4 = subtraction_matrix(matrix_2, matrix_3);
                print_matrix(matrix_4);
                break;
            case 10:
                prompt_input(matrix_2);
                puts("Умножение матрицы на число:");
                matrix_4 = multiplying_number(matrix_2, 28);
                print_matrix(matrix_4);
                break;
            case 11:
                puts("Суммирование векторов:");
                vector_4 = summ_vector(vector_2, vector_3);
                print_vector(vector_4);
                break;
            case 12:
                puts("Вычитание векторов:");
                vector_4 = subtraction_vector(vector_2, vector_3);
                print_vector(vector_4);
                break;
            case 13:
                puts("Умножение векторов на число:");
                vector_4 = multiplying_vector_1(vector_2, 11);
                print_vector(vector_4);
                break;
            case 14:
                puts("Длина (модуль) вектора:");
                det = modulus_vector(vector_2);
                printf("%f", det);
                break;
            case 15:
                puts("Умножение вектора на вектор (скалярное произведение):");
                det = vector_multip_scal_vector(vector_2, vector_3);
                printf("%f", det);
                break;
            case 16:
                puts("Умножение вектора на вектор (векторное произведение):");
                vector_4 = vector_multip_vect_vector(vector_2, vector_3);
                print_vector(vector_4);
                break;
            case 17:
                puts("Смешанное произведение векторов:");
                mixed_of_vectors(vector_2, vector_3, vector_5, &det);
                printf("%f", det);
                break;
            case 18:
                puts("Угол между векторами:");
                det = angle_vectors(vector_2, vector_3);
                printf("%f", det);
                break;
            case 19:
                puts("Проекция вектор на вектор:");
                det = dvector_projection(vector_2, vector_3);
                printf("%f", det);
                break;
            case 20:
                puts("Площадь треугольника построенного на векторах:");
                area_of_​​a_triangle(vector_2, vector_3, &det);
                printf("%f", det);
                break;
            case 21:
                puts("Площадь параллелограмма построенного на векторах:");
                area_of_a_parallelogram(vector_2, vector_3, &det);
                printf("%f", det);
                break;
            case 22:
                puts("Объем пирамиды построенного на векторах:");
                volume_of_a_pyramid(vector_2, vector_3, vector_5, &det);
                printf("%f", det);
                break;
            //default:
            //break;
        }

        return 0;
    }
}

int showMenu(void) //Показать меню
{
    int input = 0;
    puts("2 - Вычисление детерминанта или определителя матрицы\n" 
         "3 - Вычисление алгеброического дополнения к матрице\n" 
         "4 - Вычисление обратной матрицы\n"
         "5 - Возведение матрицы в степень\n"
         "6 - Умножение матрицы на матрицу\n"
         "7 - Транспонирование матриц\n"
         "8 - Суммирование матриц\n"
         "9 - Вычитание матриц\n"
         "10 - Умножение матрицы на число\n"
         "11 - Суммирование векторов:\n"
         "12 - Вычитание векторов:\n"
         "13 - Умножение векторов на число:\n"
         "14 - Длина (модуль) вектора:\n"
         "15 - Умножение вектора на вектор (скалярное произведение):\n"
         "16 - Умножение вектора на вектор (векторное произведение):\n"
         "17 - Смешанное произведение векторов:\n"
         "18 - Угол между векторами:\n"
         "19 - Проекция вектор на вектор:\n"
         "20 - Площадь треугольника построенного на векторах:\n"
         "21 - Площадь параллелограмма построенного на векторах:\n"
         "22 - Объем пирамиды построенного на векторах:\n"
         "1 - Exit");
    scanf("%d", &input);
    return(input);
}


















