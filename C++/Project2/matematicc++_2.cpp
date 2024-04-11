#include "matematicc++.h"

matrix::matrix() : n_rows(0), n_columns(0)
{
	matrix_0 = nullptr;
}

matrix::matrix(int rows, int columns) : n_rows(rows), n_columns(columns)
{
	matrix_0 = (double**)new double[rows]; 
	//Выделяю память для указателей на строки целым куском
	for (int i = 0; i < rows; ++i)
	{
		matrix_0[i] = (double*)new double[columns]; 
		//Выделяю память для столбцов; matrix_0[i] указатель на подмассив элементов типа double, память выделяю целым куском
	}
}

void matrix::remove_matrix() //Чистка памяти
{
	for (int i = 0; i < n_rows; i++)
	{
		delete[] matrix_0[i]; //Высвободить память из под указателей на столбцы
	}
	delete[] matrix_0; //Высвободить память из под указателей на строки
	n_rows = 0;
	n_columns = 0;
}

int matrix::prompt_input() //Запрос ввода
{
	for (int i = 0; i < n_rows; ++i)
	{
		for (int j = 0; j < n_columns; ++j)
		{
			if (!(std::cin >> matrix_0[i][j]))
			{
				std::cout << "Only numbers!\n"; //Только цифры!
			}
		}
	}
	std::cout << "matrix entered!\n";
	return 0;
}

void matrix::print_matrix() //Печать матрицы
{
	for (int i = 0; i < n_rows; ++i)
	{
		for (int j = 0; j < n_columns; ++j)
		{
			std::cout << "  " << matrix_0[i][j];
		}
		std::cout << "\n\n";
	}	
}

matrix* matrix::operator=(const matrix& a) // Оператор присваивания
{
	this->n_rows = a.n_rows; this->n_columns = a.n_columns;
	this->matrix_0 = (double**)new double[n_rows];
	//Выделяю память для указателей на строки целым куском
	for (int i = 0; i < n_rows; ++i)
	{
		this->matrix_0[i] = (double*)new double[n_columns];
		//Выделяю память для столбцов; matrix_0[i] указатель на подмассив элементов типа double, память выделяю целым куском
	}
	for (int i = 0; i < a.n_rows; ++i)
	{
		for (int j = 0; j < a.n_columns; ++j)
		{
			this->matrix_0[i][j] = a.matrix_0[i][j];
		}
	}
	return this;
}

matrix* matrix::operator+(const matrix& a)
{
	/*Складывать и вычитать матрицы можно только одинаковой размерности. При сумме или разности будет получаться матрица
	C такой же размерности как и слагаемые (вычитаемые) матрицы A и B.
	Если матрицы A и B отличаются друг от друга размерами, то сложение (вычитание) таких матриц будет ошибкой!
	*/
	if (this->matrix_0 == nullptr || a.matrix_0 == nullptr) //Такая ситуация может быть в случаи если при нахождении обратной матрицы детерминант равен 0 и память под одну из матриц не выдилилась или её не выделил пользователь
	{
		return nullptr;
	}
	if (this->n_rows <= 0 && a.n_columns <= 0)
	{
		std::cout << "Matrix is empty, error!\n"; //Матрица пуста, ошибка!
		return nullptr;
	}
	if (this->n_rows != a.n_rows || this->n_columns != a.n_columns)
	{
		std::cout << "Matrices of different sizes, error!\n"; //Матрицы разных размеров, ошибка!
		return nullptr;
	}
	for (int i = 0; i < n_rows; ++i)
	{
		for (int j = 0; j < n_columns; ++j)
		{
			this->matrix_0[i][j] = this->matrix_0[i][j] + a.matrix_0[i][j];
		}
	}
	return this;
}

matrix* matrix::operator-(const matrix& a)
{
	/*Складывать и вычитать матрицы можно только одинаковой размерности. При сумме или разности будет получаться матрица
	C такой же размерности как и слагаемые (вычитаемые) матрицы A и B.
	Если матрицы A и B отличаются друг от друга размерами, то сложение (вычитание) таких матриц будет ошибкой!
	*/
	if (this->matrix_0 == nullptr || a.matrix_0 == nullptr) //Такая ситуация может быть в случаи если при нахождении обратной матрицы детерминант равен 0 и память под одну из матриц не выдилилась или её не выделил пользователь
	{
		return nullptr;
	}
	if (this->n_rows <= 0 && a.n_columns <= 0)
	{
		std::cout << "Matrix is empty, error!\n"; //Матрица пуста, ошибка!
		return nullptr;
	}
	if (this->n_rows != a.n_rows || this->n_columns != a.n_columns)
	{
		std::cout << "Matrices of different sizes, error!\n"; //Матрицы разных размеров, ошибка!
		return nullptr;
	}
	for (int i = 0; i < n_rows; ++i)
	{
		for (int j = 0; j < n_columns; ++j)
		{
			this->matrix_0[i][j] = this->matrix_0[i][j] - a.matrix_0[i][j];
		}
	}
	return this;
}


matrix* matrix::operator*(const matrix& a) //Умножение матрицы на матрицу
{
	/*Матрицу M1 можно умножить на матрицу M2 только в том случае, если число столбцов матрицы M1
	равняется числу строк матрицы M2. Матрицы, для которых данное условие не выполняется,
	умножать нельзя. Матрицы могут быть разных размеров.
	Мы будем умножать столбец первой матрицы на строку второй матрицы и т.д.
	Поменять матрицы местами в вызове функции нельзя, т.к нарушится условие соответствия столбцов и строк
	*/
	if (this->matrix_0 == nullptr || a.matrix_0 == nullptr) //Такая ситуация может быть в случаи если при нахождении обратной матрицы детерминант равен 0 и память под одну из матриц не выдилилась или её не выделил пользователь
	{
		return nullptr;
	}
	if (n_rows <= 0 && n_columns <= 0)
	{
		std::cout << "Matrix is empty, error!\n"; //Матрица пуста, ошибка!
		return nullptr;
	}
	if (n_columns != n_rows)
	{
		std::cout << "The number of columns does not match the number of rows\n"; //Число столбцов не соответствует числу строк
		return nullptr;
	}

	matrix M_0(this->n_rows, a.n_columns);

	for (int i = 0; i < this->n_rows; ++i) //Указатель на строку
	{
		for (int j = 0; j < a.n_columns; ++j) //Указатель на столбец
		{
			M_0.matrix_0[i][j] = 0;
			for (int q = 0; q < this->n_columns; ++q) //Для вертикального прохода по второй матрице
				M_0.matrix_0[i][j] += this->matrix_0[i][q] * a.matrix_0[q][j];
		}
	}
	*this = M_0;
	return this;
}

matrix* matrix::operator*(double a) //Умножение матрицы на число
{
	/*Результатом умножения матрицы M на любое число n, не равное нулю, является матрица того же порядка
	(размера), элементы которой равны произведению соответствующих элементов исходной матрицы на
	данное число.*/
	if (this == NULL) //Память не выделена
		return NULL;
	if (this->n_rows <= 0 && this->n_columns <= 0)
	{
		std::cout << "The matrix is empty, error!\n"; //Матрица пуста, ошибка! 
		return NULL;
	}

	for (int i = 0; i < this->n_rows; ++i)
	{
		for (int j = 0; j < this->n_columns; ++j)
		{
			this->matrix_0[i][j] = this->matrix_0[i][j] * a;
		}
	}
	return this;
}

matrix* matrix::operator^(int a) //Возведение матрицы в степень
{
	/*Операция возведения в степень k определена только для квадратных матриц,
	т.е. матриц размера k×k — 2×2, 3×3 и т.д. Кроме того, показатель степени
	(число в которое мы возводим матрицу) должен быть натуральным:… 1,2,3,4,5
	Алгоритм работы - первую строчку * первый столбец, после складываем.
	*/

	if (a == 1) //Если матрица в первой степени
		return this;
	if (this->n_columns != this->n_rows)
	{
		std::cout << "Exponentiations for square matrices only!\n"; //Возведения в степень только для квадратных матриц 
		return nullptr;
	}

	static matrix result(this->n_rows, this->n_columns);
	static matrix result_1(this->n_rows, this->n_columns);
	//matrix* res = &result;

	for (int i = 0; i < this->n_rows; ++i)
	{
		for (int j = 0; j < this->n_columns; ++j)
		{
			result.matrix_0[i][j] = 0;
			for (int q = 0; q < this->n_columns; ++q)
				result.matrix_0[i][j] += this->matrix_0[q][j] * this->matrix_0[i][q];
		}
	}

	if (a == 2) //Если матрица во второй степени
	{
		*this = result;
		return this;
	}


	//Если матрица возводится в 3 и большую степень
	--a;
	while ((a = a - 1) != 0)
	{
		for (int i = 0; i < this->n_rows; ++i)
		{
			for (int j = 0; j < this->n_columns; ++j)
			{
				result_1.matrix_0[i][j] = 0; //Всегда зануляем, т.к нужно вернуть только последнее значение
				for (int q = 0; q < this->n_columns; ++q)
				{
					result_1.matrix_0[i][j] += this->matrix_0[q][j] * result.matrix_0[i][q]; //При возведении в степень нужно вернуть только последние значения
				}
			}
		}

		result.n_rows = result_1.n_rows;
		result.n_columns = result_1.n_columns;

		for (int i = 0; i < result.n_rows; ++i)
		{
			for (int j = 0; j < result.n_columns; ++j)
			{
				result.matrix_0[i][j] = result_1.matrix_0[i][j];
			}
		} // Будем умножать именно result на исходную матрицу
	}
	*this = result_1;
	return this;
}

void matrix::matrix_transposition() //Транспонирование матриц
{
	int rows = n_rows;
	/*Матрица, полученная из данной заменой каждой ее строки столбцом с этим же номером,
	называется матрицей транспонированной данной.*/
	matrix result(n_rows, n_columns); 
	for (int i = 0; i < n_rows; ++i)
	{
		for (int j = 0; j < n_columns; ++j)
			result.matrix_0[i][j] = matrix_0[i][j];
	}
	n_rows = n_columns; //При транспониролвании меняем местами столбцы со строками.
	n_columns = rows;
	matrix_0 = (double**)new double[n_rows];
	//Выделяю память для указателей на строки целым куском
	for (int i = 0; i < n_rows; ++i)
	{
		matrix_0[i] = (double*)new double[n_columns];
		//Выделяю память для столбцов; matrix_0[i] указатель на подмассив элементов типа double, память выделяю целым куском
	}

	for (int i = 0; i < n_columns; ++i)
	{
		for (int j = 0; j < n_rows; ++j)
			matrix_0[j][i] = result.matrix_0[i][j];
	}
}

matrix matrix::minor_matrix(matrix& M, int state_1, int state_2) //Вычисление минора матрицы
{
	/*Минор матрицы - это определитель n−1 порядка, составленный путём вычеркивания i-ой строки и j-го столбца из
	матрицы M порядка n. Обозначается минор Mij*/

	
	matrix minor_matrix(M.n_rows - 1, M.n_columns - 1); //Возвращаем матрицу меньше на 1 столбец и на 1 строчку

	for (int i = 0, x = 0; i < M.n_rows; ++i)
	{
		if (state_1 != i)
		{
			for (int j = 0, y = 0; j < M.n_columns; ++j)
			{
				if (state_2 != j)
				{
					minor_matrix.matrix_0[x][y] = M.matrix_0[i][j];
					++y;
				}
			}
			++x;
		}
	}
	return minor_matrix;
}

int matrix::matrix_determinant(matrix& M, double& result) //Вычисление детерминанта или определителя матрицы
{
	/*Определитель может быть вычислен только для квадратной матрицы.
	Детерминант или определитель - это некоторое число, которое ставится в соответствие каждой квадратной матрице.
	Определитель матрицы равен сумме произведений элементов строки или столбца на соответствующие алгебраическиое дополнение.*/
	/*Данная функция реализована с помощью рекурсии, которая залорженна в цикл for (),
	когда 1-й минор полностью посчитан, исходный(главный) цикл for запускает подсчёт следующего минора самой первой матрицы, т.е ++i
	В данном случае использовано разложение определителя по элементам строки (столбца)*/

	matrix minor(0, 0);
	double determinant = 0.0;
	double fin_result = 0.0;

	if (M.matrix_0 != nullptr && M.n_columns > 0 && M.n_rows > 0)
	{
		if (M.n_columns == M.n_rows)
		{
			if (M.n_rows == 1) //В последний шаг рекурсии (при подсчёте соответствующего минора) функция вернёт крайнее правое значение матрицы (одну цифру), а в следующий проход сдвинемся влево на один шаг
			{
				result = M.matrix_0[0][0];
			}
			else if (M.n_rows > 1)
			{
				result = 0;

				for (int i = 0; i < M.n_rows; ++i)
				{
					minor = minor_matrix(M, 0, i); //Мы будем брать всегда именно первую строчку матрицы и полностью считать минор относительно этой первой строки
					matrix_determinant(minor, determinant); //Рекурсивный вызов
					fin_result = M.matrix_0[0][i] * determinant; //Шагаем по первой строчке матрицы

					if ((2 + i) % 2 == 1)
						fin_result *= -1;
					result += fin_result;
					minor.remove_matrix();
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

int matrix::algebraic_matrix_complement(matrix& M, matrix& result) //Вычисление алгеброического дополнения к матрице
{
	/*Алгебраическое дополнение элемента матрицы — это число, которое получается из определителя матрицы,
	из которой исключили строку и столбец элемента,
	умноженного на (-1) в степени суммы номера строки и столбца элемента.*/
	matrix minor(0, 0);
	double determinant = 0.0;

	if (M.matrix_0 != nullptr && M.n_columns > 0 && M.n_rows > 0)
	{
		if (M.n_columns == M.n_rows)
		{
			for (int i = 0; i < result.n_rows; ++i) //Переход на строчку  ниже
			{
				for (int j = 0; j < result.n_columns; ++j) //Гуляем по этой строчке
				{
					minor = minor_matrix(M, j, i); //Мы берём всегда именно первые строчки матрицы и полностью считаем минор относительно их
					matrix_determinant(minor, determinant); //Рекурсивный вызов

					result.matrix_0[j][i] = determinant;

					if ((i + j) % 2 == 1)
					{
						result.matrix_0[j][i] *= -1;
					}

					minor.remove_matrix();
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

int matrix::inverse_matrix(matrix& M, matrix& result) //Вычисление обратной матрицы
{
	/*Обратная матрица - это матрица, которая при умножении на исходную матрицу дает единичную матрицу.*/

	// *result = malloc_matrix(M->n_rows, M->n_columns); Память выделять не нужно, т.к работаем с указателем на указатель на структуру matrix_1
	static matrix dop_1(M.n_rows, M.n_columns);
	static matrix dop_2(M.n_rows, M.n_columns);

	static double determinant = 0.0;
	matrix_determinant(M, determinant);
	if (determinant == 0)
	{
		std::cout << "Determinant == 0, matrix inverse does not exist\n"; //Детерминант == 0, обратной матрицы несуществует
		return 0;
	}
	algebraic_matrix_complement(M, dop_1);
	dop_1.matrix_transposition();
	dop_2 = dop_1;

	for (int i = 0; i < M.n_rows; ++i)
	{
		for (int j = 0; j < M.n_columns; ++j)
		{
			dop_2.matrix_0[i][j] = dop_2.matrix_0[i][j] / determinant;
		}
	}
	result = dop_2; 
	dop_1.remove_matrix();
	return 0;
}

