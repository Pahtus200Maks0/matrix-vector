#include "vector_1.h"

void  c_remove_matrix(vector_minor* M)
{
	for (int i = 0; i < M->n_rows; i++)
	{
		free(M->minor_vector[i]);
	}

	/* free cols */
	free(M->minor_vector);
	M->n_rows = 0;
	M->n_columns = 0;
}

vector_minor* malloc_matrix_vector(const int rows, const int columns) //Создание матрицы и выделение памяти
{
	vector_minor* result = NULL;
	if (rows <= 0 || columns <= 0)
	{
		puts("Rows and columns must be >= 0"); //Строки и столбцы должны быть >= 0
		return NULL;
	}

	result = (vector_minor*)malloc(sizeof(vector_minor));
	if (!result)
	{
		perror("Error");
		free(result);
		printf("Errno number %d\n", errno); //Числовой код ошибки
		return NULL;
	}

	result->n_rows = rows;
	result->n_columns = columns;
	result->minor_vector = (double**)malloc(rows * sizeof(double*)); //Выделяю память для указателей на строки
	if (!result->minor_vector)
	{
		perror("Error");
		free(result->minor_vector);
		free(result);
		printf("Errno number %d\n", errno);
		return NULL;
	}

	for (int i = 0; i < rows; i++)
	{
		result->minor_vector[i] = (double*)malloc(columns * sizeof(double)); //Выделяю память для строк; matrix[i] указатель на подмассив элементов типа double
		//В памяти будет выглядеть так: rows[1]->columns[1][2][3], rows[2]->columns[1][2][3] .....
		if (!result->minor_vector[i])
		{
			for (int j = 0; j < i; ++j)
			{
				free(result->minor_vector[j]); //Чистка памяти под столбцы
			}
			free(result->minor_vector); //Чистка памяти под указатели на столбцы
			free(result);  //Чистка памяти под указатель на структуру
			perror("Error");
			printf("Errno number %d\n", errno);
			exit(1);
		}
	}

	return result;
}

vector_1* malloc_vector(double state1, double state2, double state3)
{
	vector_1* result = NULL;
	result = (vector_1*)malloc(sizeof(vector_1));
	if (!result)
	{
		perror("Error");
		free(result);
		printf("Errno number %d\n", errno); //Числовой код ошибки
		exit(1);
	}

	result->v_1 = state1;
	result->v_2 = state2;
	result->v_3 = state3;
	return result;
}


void print_vector(vector_1* M) //Печать вектора
{
	printf("vector x = %.3lf\n", M->v_1);
	printf("vector y = %.3lf\n", M->v_2);
	printf("vector z = %.3lf\n", M->v_3);
}

vector_1* summ_vector(vector_1* M1, vector_1* M2) //Суммирование векторов
{
	vector_1* result = NULL;
	result = malloc_vector(M1->v_1, M1->v_2, M1->v_3);
	if (result == NULL)
		return NULL;
	result->v_1 = M1->v_1 + M2->v_1;
	result->v_2 = M1->v_2 + M2->v_2;
	result->v_3 = M1->v_3 + M2->v_3;

	return result;
}

vector_1* subtraction_vector(vector_1* M1, vector_1* M2) //Вычитание векторов
{
	vector_1* result = NULL;
	result = malloc_vector(M1->v_1, M1->v_2, M1->v_3);
	if (result == NULL)
		return NULL;
	result->v_1 = M1->v_1 - M2->v_1;
	result->v_2 = M1->v_2 - M2->v_2;
	result->v_3 = M1->v_3 - M2->v_3;

	return result;
}

vector_1* multiplying_vector_1(vector_1* M, double state) //Умножение векторов на число
{
	vector_1* result = NULL;
	result = malloc_vector(M->v_1, M->v_2, M->v_3);
	if (result == NULL)
		return NULL;
	result->v_1 = M->v_1 * state;
	result->v_2 = M->v_2 * state;
	result->v_3 = M->v_3 * state;

	return result;
}

double vector_multip_scal_vector(vector_1* M1, vector_1* M2) //Умножение вектора на вектор (скалярное произведение)
{
	double result = 0.0;
	result += M1->v_1 * M2->v_1;
	result += M1->v_2 * M2->v_2;
	result += M1->v_3 * M2->v_3;

	return result;
}

double modulus_vector(vector_1* M) //Длина (модуль) вектора
{
	double result = 0.0;
	result = sqrt(pow(M->v_1, 2) + pow(M->v_2, 2) + pow(M->v_3, 2));
	return result;
}

double angle_vectors(vector_1* M1, vector_1* M2) //Угол между векторами
{
	double result = 0.0;
	double state1 = 0.0;
	double state2 = 0.0;
	double state3 = 0.0;

	state1 = vector_multip_scal_vector(M1, M2);
	state2 = modulus_vector(M1);
	state3 = modulus_vector(M2);
	result = (state1 / (state2 * state3));
	return (((acosl(result)) * 180.0) / M_PI); //Чтобы перевести радианы в градусы необходимо угол в радианах умножить на 180 и разделить на число Пи
}

double dvector_projection(vector_1* M1, vector_1* M2) //Проекция вектор на вектор
{
	double result = 0.0;
	double state1 = 0.0;

	result = vector_multip_scal_vector(M1, M2);
	state1 = modulus_vector(M2);
	return result / state1;
}

vector_minor* minor_matrix(vector_minor* M, int state_1, int state_2) //Вычисление минора матрицы
{
	/*Минор матрицы - это определитель n−1 порядка, составленный путём вычеркивания i-ой строки и j-го столбца из
	матрицы M порядка n. Обозначается минор Mij*/

	vector_minor* minor = NULL;
	minor = malloc_matrix_vector(M->n_rows - 1, M->n_columns - 1);
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
					minor->minor_vector[x][y] = M->minor_vector[i][j];
					++y;
				}
			}
			++x;
		}
	}
	return minor;
}

int matrix_determinant(vector_minor* M, double* result) //Вычисление детерминанта или определителя матрицы
{
	/*Определитель может быть вычислен только для квадратной матрицы.
	Детерминант или определитель - это некоторое число, которое ставится в соответствие каждой квадратной матрице.
	Определитель матрицы равен сумме произведений элементов строки или столбца на соответствующие алгебраическиое дополнение.*/
	/*Данная функция реализована с помощью рекурсии, которая залорженна в цикл for (),
	когда 1-й минор полностью посчитан, исходный(главный) цикл for запускает подсчёт следующего минора самой первой матрицы, т.е ++i
	В данном случае использовано разложение определителя по элементам строки (столбца)*/

	vector_minor* minor = NULL;
	double determinant = 0.0;
	double fin_result = 0.0;

	if (M->minor_vector != NULL && M->n_columns > 0 && M->n_rows > 0)
	{
		if (M->n_columns == M->n_rows)
		{
			if (M->n_rows == 1) //В последний шаг рекурсии (при подсчёте соответствующего минора) функция вернёт крайнее правое значение матрицы (одну цифру)
			{
				*result = M->minor_vector[0][0];
			}
			else if (M->n_rows > 1)
			{
				*result = 0;

				for (int i = 0; i < M->n_rows; ++i)
				{
					minor = minor_matrix(M, 0, i); //Мы будем брать всегда именно первую строчку матрицы и полностью считать минор относительно этой первой строки
					matrix_determinant(minor, &determinant); //Рекурсивный вызов
					fin_result = M->minor_vector[0][i] * determinant; //Шагаем по первой строчке матрицы

					if ((2 + i) % 2 == 1)
						fin_result *= -1;

					*result += fin_result;
					c_remove_matrix(minor);
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

vector_1* vector_multip_vect_vector(vector_1* M1, vector_1* M2) //Умножение вектора на вектор (векторное произведение )
{
	//Мы просто считаем три раза определители матрицы
	vector_1* vector_result = malloc_vector(0, 0, 0);
	vector_minor* result = malloc_matrix_vector(2, 2);
	double ress = 0.0;

	result = malloc_matrix_vector(2, 2);
	result->minor_vector[0][0] = M1->v_2;
	result->minor_vector[1][0] = M1->v_3;
	result->minor_vector[0][1] = M2->v_2;
	result->minor_vector[1][1] = M2->v_3;
	matrix_determinant(result, &ress);
	vector_result->v_1 = ress;

	result->minor_vector[0][0] = M1->v_1;
	result->minor_vector[1][0] = M1->v_3;
	result->minor_vector[0][1] = M2->v_1;
	result->minor_vector[1][1] = M2->v_3;
	matrix_determinant(result, &ress);
	vector_result->v_2 = (-1) * ress;

	result->minor_vector[0][0] = M1->v_1;
	result->minor_vector[1][0] = M1->v_2;
	result->minor_vector[0][1] = M2->v_1;
	result->minor_vector[1][1] = M2->v_2;
	matrix_determinant(result, &ress);
	vector_result->v_3 = ress;

	return vector_result;
}

void mixed_of_vectors(vector_1* M1, vector_1* M2, vector_1* M3, double* state1) //Смешанное произведение векторов
{
	//Мы просто находим определитель матрицы 3X3
	vector_minor* result = malloc_matrix_vector(3, 3);
	result->minor_vector[0][0] = M1->v_1;
	result->minor_vector[1][0] = M1->v_2;
	result->minor_vector[2][0] = M1->v_3;

	result->minor_vector[0][1] = M2->v_1;
	result->minor_vector[1][1] = M2->v_2;
	result->minor_vector[2][1] = M2->v_3;

	result->minor_vector[0][2] = M3->v_1;
	result->minor_vector[1][2] = M3->v_2;
	result->minor_vector[2][2] = M3->v_3;

	matrix_determinant(result, *(&state1)); //Разыменовали и передали адрес
}

void area_of_​​a_triangle(vector_1* M1, vector_1* M2, double* state1) //Площадь треугольника построенного на векторах
{
	//1-е действие - находим векторное произведение векторов
	//2-е найходим длину (модуль) вектора
	//3-е найдем площадь треугольника (0.5 на модуль)
	vector_1* result = malloc_vector(0, 0, 0);
	result = vector_multip_vect_vector(M1, M2);
	*state1 = (modulus_vector(result) * 0.5);
}

void area_of_a_parallelogram(vector_1* M1, vector_1* M2, double* state1) //Площадь параллелограмма построенного на векторах
{
	//1-е действие - находим векторное произведение векторов
	//2-е найходим длину (модуль) вектора
	//3-е найдем площадь параллелограмма - это и есть модуль
	vector_1* result = malloc_vector(0, 0, 0);
	result = vector_multip_vect_vector(M1, M2);
	*state1 = modulus_vector(result);
}

void volume_of_a_pyramid(vector_1* M1, vector_1* M2, vector_1* M3, double* state1) //Объем пирамиды построенного на векторах
{
	//Определитель матрицы 3X3 умножаем на 0.1666666
	mixed_of_vectors(M1, M2, M3, *(&state1));
	if ((*state1) < 0)
	{
		*state1  = ((*state1) * (-1));
	}
	*state1 = (*state1 * (0.1666666));
}