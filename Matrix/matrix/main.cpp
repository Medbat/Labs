#include "matrixlib.h"

bool MemoryIsUsed = false;

int main() {
	setlocale(LC_ALL, "rus");
	int ** MatrixA = NULL;
	int Ma, Na;
	int MatrixBa, MatrixBb, MatrixBdl;
	char e;
	while (1) {
		cout << "--------------------------------\n0. �����\n1. ������ ������� �\n";
		cout << "2. �������� ������� �\n3. �������� ������� B\n";
		cout << "4. ��������� �������\n5. ��������������� �������\n";
		cout << "6. ����� �������\n7. ���������� �������\n";
		cout << "q. �������� �������� ������ 1\nw. �������� �������� ������ 2\n";
		cout << "e. �������� �������� ������ 3\n--------------------------------\n";
		e = _getch();
		switch (e) {
		case '0':
			if (MemoryIsUsed) {
				Delete_Matrix(MatrixA, Ma);
				MemoryIsUsed = false;
			}
			cout << "�������...";
			return 0;
		case '1':
			cout << "���� ������� � ����������" << endl;
			if (MemoryIsUsed) {
				Delete_Matrix(MatrixA, Ma);
				MemoryIsUsed = false;
			}
			Enter_Matrix(MatrixA, Ma, Na);
			Calculate_B(MatrixA, Ma, Na, MatrixBa, MatrixBb, MatrixBdl);
			MemoryIsUsed = true;
			break;
		case '2':
			cout << "������� A\n";
			if (!MemoryIsUsed)
				cout << "������. ������� ��� �� ���������\n";
			else
				Show_Matrix(MatrixA, 0, 0, Ma, Na);
			break;
		case '3':
			cout << "������� B\n";
			if (!MemoryIsUsed)
				cout << "������. ������� ��� �� ���������\n";
			else
				Show_Matrix(MatrixA, MatrixBa, MatrixBb, MatrixBdl, MatrixBdl);
			break;
		case '4':
			cout << "������������ ������� �� 90 ��������...\n";
			Turn_Matrix(MatrixA, MatrixBa, MatrixBb, MatrixBdl);
			cout << "�����!\n";
			break;
		case '5':
			cout << "������������� �������...\n";
			Transponate_Matrix(MatrixA, MatrixBa, MatrixBb, MatrixBdl);
			cout << "�����!\n";
			break;
		case '6':
			cout << "��������� ������ �������...\n";
			Go(MatrixA, MatrixBa, MatrixBb, MatrixBdl);
			break;
		case '7':
			cout << "��������� �������...\n"; 
			Bubble_Sort(MatrixA, MatrixBa, MatrixBb, MatrixBdl);
			cout << "�����!\n";
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
			cout << "�������� ����" << endl;
		}
	}
}

