#include <iostream>

using namespace std;

int is_arm(int n) {
	int b = 0;//true or false
	int p = 0;
	int e = n;
	_asm {
		mov eax, n;
		mov bx, 1;//с помощью bx будем считать количество цифр
		mov ecx, 10;
	mp1:				//находим количество цифр
		cdq;
		idiv ecx;
		cmp eax, 0;
		je mend;//если равно 0, то уходим отсюда
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
	lm : mov eax, e;      //Находим сумму и сравниваем с самим числом
		mov cx, 10;
		cdq;//увеличиваем для деления 
		idiv ecx;
		mov e, eax;//целая часть
		cmp eax, 0;
		je mendk;
		mov cx, bx;
		mov eax, edx;
		mov p, edx;
		dec cx;
	lm1: mul p;        // умножаем цифры n раз//хранится в eax
		loop lm1;
		push eax;
		jmp lm;
	mendk://подготовка к работе с первым разрядом
		mov eax, edx;//заносим в еаикс остаток, т.е. первый разряд
		mov cx, bx;//количество разрядов
		mov p, edx;//делаем это, чтобы возвести в степень
		//cmp cx, 1;//если один разряд, то не будет это 
		//je m1;
		dec cx;
	m1://работа с первым разрядом
	lm12 : mul p;
		loop lm12;
		push eax;
		xor edx, edx;
		mov cx, bx;
	l2: pop eax;           //извлекаем из стека и суммируем
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
	cout << "Введите число N, чтобы найти числа Армтстронга, меньшие N, - ";
	int N;
	cin >> N;
	if (N > 1)
	{
		bool c = 0;//да или нет
		int p;//результат
		cout << "Числа Армстронга, меньшие " << N << ":" << endl;
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
		cout << "Чисел Армстронга до числа " << N << " нет" << endl;
	}
	system("pause");
	return 0;
}