#include "matrix_1.h"

void remove_matrix(matrix_1* M) //Чистка памяти
{
    for (int i = 0; i < M->n_rows; i++)
    {
        free(M->matrix[i]); //Высвободить память из под указателей на столбцы
    }

    free(M->matrix); //Высвободить память из под указателей на строки
    M->n_rows = 0;
    M->n_columns = 0;
    free(M);
}

matrix_1* malloc_matrix(const int rows, const int columns) //Создание матрицы и выделение памяти
{
    matrix_1* result = NULL;
    if (rows <= 0 || columns <= 0)
    {
        puts("Rows and columns must be >= 0"); //Строки и столбцы должны быть >= 0
        return NULL;
    }

    result = (matrix_1*)malloc(sizeof(matrix_1)); //Выделяю память под структуру 
    if (!result)
    {
        perror("Error");
        free(result);
        printf("Errno number %d\n", errno); //Числовой код ошибки
        return NULL;
    }

    result->n_rows = rows;
    result->n_columns = columns;
    result->matrix = (double**)malloc(rows * sizeof(double*)); //Выделяю память для указателей на строки, 
    //здесь память выделяется целым куском rows * sizeof(double*)
    if (!result->matrix)
    {
        perror("Error");
        free(result->matrix);
        free(result);
        printf("Errno number %d\n", errno); //errno возвращает числовой код ошибки
        return NULL;
    }

    for (int i = 0; i < rows; i++)
    {
        result->matrix[i] = (double*)malloc(columns * sizeof(double)); //Выделяю память для столбцов; matrix[i] указатель на подмассив элементов типа double
        //В памяти будет выглядеть так: rows[1]->columns[1][2][3]..., rows[2]->columns[1][2][3] .....,
        //так же память выделяю целым куском columns * sizeof(double)
        if (!result->matrix[i])
        {
            for (int j = 0; j < i; ++j)
            {
                free(result->matrix[j]); //Чистка памяти под столбцы
            }
            free(result->matrix); //Чистка памяти под указатели на столбцы
            free(result);  //Чистка памяти под указатель на структуру
            perror("Error");
            printf("Errno number %d\n", errno);
            exit(1);
        }
    }

    return result;
}

void print_matrix(matrix_1* M) //Печать матрицы
{
    if (M == NULL)
    {
        puts("Matrix is empty"); //Матрица пуста
        return;
    }
    for (int i = 0; i < M->n_rows; ++i)
    {
        for (int j = 0; j < M->n_columns; ++j)
        {
            printf("%.3lf ", M->matrix[i][j]);
        }
        printf("\n");
    }
}

int prompt_input(matrix_1* M) //Запрос ввода
{
    //int x = 0;
    //char buff[100];
    if (M == NULL)
    {
        puts("An empty matrix cannot be filled"); //Пустую матрицу заполнить нельзя
        return 1;
    }

    for (int i = 0; i < M->n_rows; ++i)
    {
        for (int j = 0; j < M->n_columns; ++j)
        {
            if (!(scanf("%lf", &M->matrix[i][j])))
            {
                printf("Only numbers!\n"); //Только цифры!
                exit(1);
            }
        }
    }
    puts("matrix entered!");
    return 0;
}

matrix_1* summ_matrix(matrix_1* M1, matrix_1* M2) //Суммирование матриц
{
    /*Складывать и вычитать матрицы можно только одинаковой размерности. При сумме или разности будет получаться матрица
    C такой же размерности как и слагаемые (вычитаемые) матрицы A и B.
    Если матрицы A и B отличаются друг от друга размерами, то сложение (вычитание) таких матриц будет ошибкой!
    */
    if (M1 == NULL || M2 == NULL) //Такая ситуация может быть в случаи если при нахождении обратной матрицы детерминант равен 0 и память под одну из матриц не выдилилась или её не выделил пользователь
    {
        return NULL;
    }
    if (M1->n_rows <= 0 && M2->n_columns <= 0)
    {
        puts("Matrix is empty, error!"); //Матрица пуста, ошибка!
        return NULL;
    }
    if (M1->n_rows != M2->n_rows || M1->n_columns != M2->n_columns)
    {
        puts("Matrices of different sizes, error!"); //Матрицы разных размеров, ошибка!
        return NULL;
    }
    matrix_1* result = NULL;
    result = malloc_matrix(M1->n_rows, M1->n_columns);
    if (result == NULL)
        return NULL;

    for (int i = 0; i < M1->n_rows; ++i)
    {
        for (int j = 0; j < M1->n_columns; ++j)
        {
            result->matrix[i][j] = M1->matrix[i][j] + M2->matrix[i][j];
        }
    }
    return result;
}

matrix_1* subtraction_matrix(matrix_1* M1, matrix_1* M2) //Вычитание матриц
{
    /*Складывать и вычитать матрицы можно только одинаковой размерности. При сумме или разности будет получаться матрица
    C такой же размерности как и слагаемые (вычитаемые) матрицы A и B.
    Если матрицы A и B отличаются друг от друга размерами, то сложение (вычитание) таких матриц будет ошибкой!
    */
    if (M1 == NULL || M2 == NULL) //Такая ситуация может быть в случаи если при нахождении обратной матрицы детерминант равен 0 и память под одну из матриц не выдилилась или её не выделил пользователь
    {
        return NULL;
    }
    if (M1->n_rows <= 0 && M2->n_columns <= 0)
    {
        puts("Matrix is empty, error!"); //Матрица пуста, ошибка!
        return NULL;
    }
    if (M1->n_rows != M2->n_rows || M1->n_columns != M2->n_columns)
    {
        puts("Matrices of different sizes, error!"); //Матрицы разных размеров, ошибка!
        return NULL;
    }
    matrix_1* result = NULL;
    result = malloc_matrix(M1->n_rows, M1->n_columns);
    if (result == NULL)
        return NULL;

    for (int i = 0; i < M1->n_rows; ++i)
    {
        for (int j = 0; j < M1->n_columns; ++j)
        {
            result->matrix[i][j] = M1->matrix[i][j] - M2->matrix[i][j];
        }
    }
    return result;
}

matrix_1* multiplying_number(matrix_1* M, double n) //Умножение матрицы на число
{
    /*Результатом умножения матрицы M на любое число n, не равное нулю, является матрица того же порядка
    (размера), элементы которой равны произведению соответствующих элементов исходной матрицы на
    данное число.*/
    if (M == NULL) //Память не выделена
        return NULL;
    if (M->n_rows <= 0 && M->n_columns <= 0)
    {
        puts("Matrix is empty, error!"); //Матрица пуста, ошибка!
        return NULL;
    }
    matrix_1* result = NULL;
    result = malloc_matrix(M->n_rows, M->n_columns);
    if (result == NULL)
        return NULL;

    for (int i = 0; i < M->n_rows; ++i)
    {
        for (int j = 0; j < M->n_columns; ++j)
        {
            result->matrix[i][j] = M->matrix[i][j] * n;
        }
    }
    return result;
}

matrix_1* matrix_multiply_matrix(matrix_1* M1, matrix_1* M2) //Умножение матрицы на матрицу
{
    /*Матрицу M1 можно умножить на матрицу M2 только в том случае, если число столбцов матрицы M1
    равняется числу строк матрицы M2. Матрицы, для которых данное условие не выполняется,
    умножать нельзя. Матрицы могут быть разных размеров.
    Мы будем умножать столбец первой матрицы на строку второй матрицы и т.д.
    Поменять матрицы местами в вызове функции нельзя, т.к нарушится условие соответствия столбцов и строк
    */
    if (M1 == NULL || M2 == NULL) //Такая ситуация может быть в случаи если при нахождении обратной матрицы детерминант равен 0 и память под одну из матриц не выдилилась или её не выделил пользователь
    {
        return NULL;
    }
    if (M1->n_rows <= 0 && M2->n_columns <= 0)
    {
        puts("Matrix is empty, error!"); //Матрица пуста, ошибка!
        return NULL;
    }
    if (M1->n_columns != M2->n_rows)
    {
        puts("The number of columns does not match the number of rows"); //Число столбцов не соответствует числу строк
        return NULL;
    }

    matrix_1* result = NULL;
    result = malloc_matrix(M1->n_rows, M2->n_columns);
    if (result == NULL)
        return NULL;

    for (int i = 0; i < M1->n_rows; ++i) //Указатель на строку
    {
        for (int j = 0; j < M2->n_columns; ++j) //Указатель на столбец
        {
            result->matrix[i][j] = 0;
            for (int q = 0; q < M1->n_columns; ++q) //Для вертикального прохода по второй матрице
                result->matrix[i][j] += M1->matrix[i][q] * M2->matrix[q][j];
        }
    }
    return result;
}

matrix_1* matrix_power(matrix_1* M, int n) //Возведение матрицы в степень
{
    /*Операция возведения в степень k определена только для квадратных матриц,
    т.е. матриц размера k×k — 2×2, 3×3 и т.д. Кроме того, показатель степени
    (число в которое мы возводим матрицу) должен быть натуральным:… 1,2,3,4,5
    Алгоритм работы - первую строчку * первый столбец, после складываем.
    */

    if (n == 1) //Если матрица в первой степени
        return M;
    if (M->n_columns != M->n_rows)
    {
        puts("Exponentiations for square matrices only"); //Возведения в степень только для квадратных матриц
        return NULL;
    }

    matrix_1* result = NULL;
    matrix_1* result_1 = NULL;
    result = malloc_matrix(M->n_rows, M->n_columns);
    if (result == NULL)
        return NULL;

    result_1 = malloc_matrix(M->n_rows, M->n_columns);
    if (result_1 == NULL)
        return NULL;

    for (int i = 0; i < M->n_rows; ++i)
    {
        for (int j = 0; j < M->n_columns; ++j)
        {
            result->matrix[i][j] = 0;
            for (int q = 0; q < M->n_columns; ++q)
                result->matrix[i][j] += M->matrix[i][q] * M->matrix[q][j];
        }
    }

    if (n == 2) //Если матрица во второй степени
        return result;

    //Если матрица возводится в 3 и большую степень
    --n;
    while ((n = n - 1) != 0)
    {
        for (int i = 0; i < M->n_rows; ++i)
        {
            for (int j = 0; j < M->n_columns; ++j)
            {
                result_1->matrix[i][j] = 0; //Всегда зануляем, т.к нужно вернуть только последнее значение
                for (int q = 0; q < M->n_columns; ++q)
                {
                    result_1->matrix[i][j] += result->matrix[i][q] * M->matrix[q][j]; //При возведении в степень нужно вернуть только последние значения
                }
            }
        }
        result = matrix_copy(result, result_1); // Будем умножать именно result на исходную матрицу
    }
    return result_1;
}

matrix_1* matrix_copy(matrix_1* M1, matrix_1* M2) //Копирование матриц (вспомогательная операция)
{
    /*В М1 копируем М2*/
    M1->n_rows = M2->n_rows;
    M1->n_columns = M2->n_columns;
    for (int i = 0; i < M1->n_rows; ++i)
    {
        for (int j = 0; j < M1->n_columns; ++j)
        {
            M1->matrix[i][j] = M2->matrix[i][j];
        }
    }
    return M1;
}

matrix_1* matrix_transposition(matrix_1* M) //Транспонирование матриц
{
    /*Матрица, полученная из данной заменой каждой ее строки столбцом с этим же номером,
    называется матрицей транспонированной данной.*/
    matrix_1* result = NULL;
    result = malloc_matrix(M->n_columns, M->n_rows); //При транспониролвании меняем местами столбцы со строками.
    if (result == NULL)
        return NULL;

    for (int i = 0; i < M->n_rows; ++i)
    {
        for (int j = 0; j < M->n_columns; ++j)
            result->matrix[j][i] = M->matrix[i][j];
    }
    return result;
}

matrix_1* minor_matrix(matrix_1* M, int state_1, int state_2) //Вычисление минора матрицы
{
    /*Минор матрицы - это определитель n−1 порядка, составленный путём вычеркивания i-ой строки и j-го столбца из
    матрицы M порядка n. Обозначается минор Mij*/

    matrix_1* minor_matrix = NULL;
    minor_matrix = malloc_matrix(M->n_rows - 1, M->n_columns - 1); //Возвращаем матрицу меньше на 1 столбец и на 1 строчку
    if (minor_matrix == NULL)
        return NULL;

    for (int i = 0, x = 0; i < M->n_rows; ++i)
    {
        if (state_1 != i)
        {
            for (int j = 0, y = 0; j < M->n_columns; ++j)
            {
                if (state_2 != j)
                {
                    minor_matrix->matrix[x][y] = M->matrix[i][j];
                    ++y;
                }
            }
            ++x;
        }
    }
    return minor_matrix;
}

int matrix_determinant(matrix_1* M, double* result) //Вычисление детерминанта или определителя матрицы
{
    /*Определитель может быть вычислен только для квадратной матрицы.
    Детерминант или определитель - это некоторое число, которое ставится в соответствие каждой квадратной матрице.
    Определитель матрицы равен сумме произведений элементов строки или столбца на соответствующие алгебраическиое дополнение.*/
    /*Данная функция реализована с помощью рекурсии, которая залорженна в цикл for (),
    когда 1-й минор полностью посчитан, исходный(главный) цикл for запускает подсчёт следующего минора самой первой матрицы, т.е ++i
    В данном случае использовано разложение определителя по элементам строки (столбца)*/

    matrix_1* minor = NULL;
    double determinant = 0.0;
    double fin_result = 0.0;

    if (M->matrix != NULL && M->n_columns > 0 && M->n_rows > 0)
    {
        if (M->n_columns == M->n_rows)
        {
            if (M->n_rows == 1) //В последний шаг рекурсии (при подсчёте соответствующего минора) функция вернёт крайнее правое значение матрицы (одну цифру), а в следующий проход сдвинемся влево на один шаг
            {
                *result = M->matrix[0][0];
            }
            else if (M->n_rows > 1)
            {
                *result = 0;

                for (int i = 0; i < M->n_rows; ++i)
                {
                    minor = minor_matrix(M, 0, i); //Мы будем брать всегда именно первую строчку матрицы и полностью считать минор относительно этой первой строки
                    matrix_determinant(minor, &determinant); //Рекурсивный вызов
                    fin_result = M->matrix[0][i] * determinant; //Шагаем по первой строчке матрицы

                    if ((2 + i) % 2 == 1)
                        fin_result *= -1;

                    *result += fin_result;
                    remove_matrix(minor);
                }
            }
        }
    }
    else
    {
        return 1;
    }
    return 0;
}

int algebraic_matrix_complement(matrix_1* M, matrix_1** result) //Вычисление алгеброического дополнения к матрице
{
    /*Алгебраическое дополнение элемента матрицы — это число, которое получается из определителя матрицы,
    из которой исключили строку и столбец элемента,
    умноженного на (-1) в степени суммы номера строки и столбца элемента.*/
    matrix_1* minor = NULL;
    double determinant = 0.0;

    if (M->matrix != NULL && M->n_columns > 0 && M->n_rows > 0)
    {
        if (M->n_columns == M->n_rows)
        {
            *result = malloc_matrix(M->n_rows, M->n_columns);
            if (result == NULL)
                return 1;
            for (int i = 0; i < (*result)->n_rows; ++i) //Переход на строчку  ниже
            {
                for (int j = 0; j < (*result)->n_columns; ++j) //Гуляем по этой строчке
                {
                    minor = minor_matrix(M, j, i); //Мы берём всегда именно первые строчки матрицы и полностью считаем минор относительно их
                    matrix_determinant(minor, &determinant); //Рекурсивный вызов

                    (*result)->matrix[j][i] = determinant;

                    if ((i + j) % 2 == 1)
                    {
                        (*result)->matrix[j][i] *= -1;
                    }

                    remove_matrix(minor);
                }
            }
        }
    }
    else
    {
        return 1;
    }
    return 0;
}

int inverse_matrix(matrix_1* M, matrix_1** result) //Вычисление обратной матрицы
{
    /*Обратная матрица - это матрица, которая при умножении на исходную матрицу дает единичную матрицу.*/


    // *result = malloc_matrix(M->n_rows, M->n_columns); Память выделять не нужно, т.к работаем с указателем на указатель на структуру matrix_1
    matrix_1* dop_1 = NULL;
    matrix_1* dop_2 = NULL;
    *result = NULL;
    double determinant = 0.0;

    matrix_determinant(M, &determinant);
    if (determinant == 0)
    {
        puts("Determinant == 0, matrix inverse does not exist"); //Детерминант == 0, обратной матрицы несуществует
        return 0;
    }
    algebraic_matrix_complement(M, &dop_1);
    dop_2 = matrix_transposition(dop_1);

    for (int i = 0; i < M->n_rows; ++i)
    {
        for (int j = 0; j < M->n_columns; ++j)
        {
            dop_2->matrix[i][j] = dop_2->matrix[i][j] / determinant;
        }
    }
    *result = dop_2; //Теперь указатель(на указатель на структуру matrix_1) указывает на структуру dop_2
    remove_matrix(dop_1);
    //c_remove_matrix(dop_2); //А  здесь чистить память нельзя, т.к именно dop_2 указывает на необходимую структуру в памяти, а *result в свою очередь ссылается на неё
    return 0;
}



























