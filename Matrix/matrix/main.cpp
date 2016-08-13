#include "matrixlib.h"

bool MemoryIsUsed = false;

int main() {
	setlocale(LC_ALL, "rus");
	int ** MatrixA = NULL;
	int Ma, Na;
	int MatrixBa, MatrixBb, MatrixBdl;
	char e;
	while (1) {
		cout << "--------------------------------\n0. Выход\n1. Ввести матрицу А\n";
		cout << "2. Показать матрицу А\n3. Показать матрицу B\n";
		cout << "4. Повернуть матрицу\n5. Транспонировать матрицу\n";
		cout << "6. Обход матрицы\n7. Сортировка матрицы\n";
		cout << "q. Загрузка тестовых данных 1\nw. Загрузка тестовых данных 2\n";
		cout << "e. Загрузка тестовых данных 3\n--------------------------------\n";
		e = _getch();
		switch (e) {
		case '0':
			if (MemoryIsUsed) {
				Delete_Matrix(MatrixA, Ma);
				MemoryIsUsed = false;
			}
			cout << "Выходим...";
			return 0;
		case '1':
			cout << "Ввод матрицы с клавиатуры" << endl;
			if (MemoryIsUsed) {
				Delete_Matrix(MatrixA, Ma);
				MemoryIsUsed = false;
			}
			Enter_Matrix(MatrixA, Ma, Na);
			Calculate_B(MatrixA, Ma, Na, MatrixBa, MatrixBb, MatrixBdl);
			MemoryIsUsed = true;
			break;
		case '2':
			cout << "Матрица A\n";
			if (!MemoryIsUsed)
				cout << "Ошибка. Матрица ещё не загружена\n";
			else
				Show_Matrix(MatrixA, 0, 0, Ma, Na);
			break;
		case '3':
			cout << "Матрица B\n";
			if (!MemoryIsUsed)
				cout << "Ошибка. Матрица ещё не загружена\n";
			else
				Show_Matrix(MatrixA, MatrixBa, MatrixBb, MatrixBdl, MatrixBdl);
			break;
		case '4':
			cout << "Поворачиваем матрицу на 90 градусов...\n";
			Turn_Matrix(MatrixA, MatrixBa, MatrixBb, MatrixBdl);
			cout << "Успех!\n";
			break;
		case '5':
			cout << "Транспонируем матрицу...\n";
			Transponate_Matrix(MatrixA, MatrixBa, MatrixBb, MatrixBdl);
			cout << "Успех!\n";
			break;
		case '6':
			cout << "Вычисляем вектор матрицы...\n";
			Go(MatrixA, MatrixBa, MatrixBb, MatrixBdl);
			break;
		case '7':
			cout << "Сортируем матрицу...\n"; 
			Bubble_Sort(MatrixA, MatrixBa, MatrixBb, MatrixBdl);
			cout << "Успех!\n";
			break;
		case 'q':
		case 'w':
		case 'e':
			if (MemoryIsUsed) {
				Delete_Matrix(MatrixA, Ma);
				MemoryIsUsed = false;
			}
			Load_Matrix_From_File(MatrixA, Ma, Na, e);
			Calculate_B(MatrixA, Ma, Na, MatrixBa, MatrixBb, MatrixBdl);
			MemoryIsUsed = true;
			break;
		default:
			cout << "Неверный ввод" << endl;
		}
	}
}

