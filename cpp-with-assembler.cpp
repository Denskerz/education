#include <iostream>

using namespace std;

int is_arm(int n) {
	int b = 0;//true or false
	int p = 0;
	int e = n;
	_asm {
		mov eax, n;
		mov bx, 1;//� ������� bx ����� ������� ���������� ����
		mov ecx, 10;
	mp1:				//������� ���������� ����
		cdq;
		idiv ecx;
		cmp eax, 0;
		je mend;//���� ����� 0, �� ������ ������
		inc bx;
		jmp mp1;
	mend:
	cmp bx, 1
	je one_sign
	jne more_signs
	one_sign:
	mov b, 1
	jmp ek
	more_signs:
	lm : mov eax, e;      //������� ����� � ���������� � ����� ������
		mov cx, 10;
		cdq;//����������� ��� ������� 
		idiv ecx;
		mov e, eax;//����� �����
		cmp eax, 0;
		je mendk;
		mov cx, bx;
		mov eax, edx;
		mov p, edx;
		dec cx;
	lm1: mul p;        // �������� ����� n ���//�������� � eax
		loop lm1;
		push eax;
		jmp lm;
	mendk://���������� � ������ � ������ ��������
		mov eax, edx;//������� � ����� �������, �.�. ������ ������
		mov cx, bx;//���������� ��������
		mov p, edx;//������ ���, ����� �������� � �������
		//cmp cx, 1;//���� ���� ������, �� �� ����� ��� 
		//je m1;
		dec cx;
	m1://������ � ������ ��������
	lm12 : mul p;
		loop lm12;
		push eax;
		xor edx, edx;
		mov cx, bx;
	l2: pop eax;           //��������� �� ����� � ���������
		add edx, eax;
		loop l2;
		cmp edx, n;
		jne ek;
		mov b, 1;
	ek:
	}
	return b;
}

int main(){
	int a = 1;
	setlocale(LC_ALL, ".1251");
	cout << "������� ����� N, ����� ����� ����� �����������, ������� N, - ";
	int N;
	cin >> N;
	if (N > 1)
	{
		bool c = 0;//�� ��� ���
		int p;//���������
		cout << "����� ����������, ������� " << N << ":" << endl;
		__asm {
			mov ebx, a;
		mb:
			push ebx;
			call is_arm;
			pop ebx;
			cmp eax, 1;
			jne ma;
			mov p, ebx;
			mov c, 1;
		}
		cout << p << " ";
		__asm {
		ma: inc ebx;
			cmp ebx, N;
			je mend;
			jne mb;
		mend:
		}
		if (c == 0) {
			cout << "No Armstrong numbers";
		}
		cout << endl;
	}
	else
	{
		cout << "����� ���������� �� ����� " << N << " ���" << endl;
	}
	system("pause");
	return 0;
}