#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <mutex>
#include <condition_variable>

using namespace std;
int ACCOUNT = 0;
bool event = 0;
mutex mtx1;

void Print() {
	while (true) {
		while (event == 1) {
			cout << "‚ведите новое значение: " << ACCOUNT << endl;
			event = 0;
		}
	}
}

void Inc() {
	srand(time(NULL));
	int randtime, randinc;
	while (true) {
		//unique_lock<std::mutex> ul(A);
		randtime = rand() % 2900 + 100;
		randinc = rand() % 99 + 1;
		mtx1.lock();
		ACCOUNT += randinc;
		event = 1;
		mtx1.unlock();
		this_thread::sleep_for(chrono::milliseconds(1));
		//st = Status::ready;
		//check.notify_all();
		this_thread::sleep_for(chrono::milliseconds(randtime));
	}
	
}

void Dec() {
	srand(time(NULL));
	int randtime, randdec;
	while (true) {
		
		randtime = rand() % 2900 + 100;
		randdec = rand() % 99 + 1;
		mtx1.lock();
		ACCOUNT -= randdec;
		event = 1;
		mtx1.unlock();
		this_thread::sleep_for(chrono::milliseconds(1));
	
		//st = Status::ready;
		//check.notify_all();
		//ul.unlock();
		this_thread::sleep_for(chrono::milliseconds(randtime));
	}
}

int main() {
	setlocale(LC_ALL, ".1251");
	srand(time(NULL));
	thread threadPrint(Print);
	thread threadInc(Inc);
	thread threadDec(Dec);
	while (true) {
		if (ACCOUNT > 10000 || ACCOUNT < -10000) {
			cout << "З‡начение ACCOUNT вышло за границы" << endl;
			return 1;
		}
		this_thread::sleep_for(chrono::milliseconds(10));
	}
	threadInc.join();
	threadDec.join();
	threadPrint.join();
	return 0;
}