#include<iostream>
#include<fstream>
#include<conio.h>
#include <io.h>
using namespace std;


struct date {
	int d, m, y;
};

struct contact {
	char firstname[20];
	char lastname[20];
	char organization[50];
	char phone[12];
	date bd;
	date adddate;
	bool favorite;
	int gender; // 0 - male 1 - female 2 - unknown
};

void print(contact a[], int n) {
	// перебираем все контакты (элементы в массиве)
	for (size_t i = 0; i < n; i++)
	{
		// печатаем сообщение Contact #„исло
		cout << "Contact #" << i + 1 << endl;
		// ѕечатаем им€ фамили€
		cout << "\t" << a[i].firstname << " " << a[i].lastname << endl;
		cout << "\t" << a[i].bd.d << "." << a[i].bd.m << "." << a[i].bd.y << endl;
		// выводим остальные пол€ структуры
	}
	system("pause");
}

void add(contact a[], int& n) {
	// создаем новую структуру
	contact newcontact;

	// заполн€ем ее пол€ значени€ми с клавиатуры
	cout << "first name: ";
	cin >> newcontact.firstname;
	cout << "last name: ";
	cin >> newcontact.lastname;
	// вводим остальные пол€ структуры

	// добавл€ем новую структуру в массив
	a[n] = newcontact;
	// увеличиваем количество элементов в массиве на 1
	n++;
}

void findbyname(contact a[], int n) {
	char f[20];
	char l[20];
	cout << "Search:" << endl;
	cout << "\t first name:";
	cin >> f;
	cout << "\t last name:";
	cin >> l;

	// перебираем все контакты (элементы в массиве)
	for (size_t i = 0; i < n; i++)
		if (strcmp(f, a[i].firstname) == 0 && strcmp(l, a[i].lastname) == 0)
		{

			// печатаем сообщение Contact #„исло
			cout << "Contact #" << i + 1 << endl;
			// ѕечатаем им€ фамили€
			cout << "\t" << a[i].firstname << " " << a[i].lastname << endl;
			// выводим остальные пол€ структуры
		}
	system("pause");
}

void sortbyname(contact a[], int n) {
	for (size_t i = 0; i < n - 1; i++)
		for (size_t j = i + 1; j < n; j++)
			if (strcmp(a[i].lastname, a[j].lastname) > 0) {
				contact tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
}

void checkbirthday(contact a[], int n) {
	int d = 17, m = 6;

	// перебираем все контакты (элементы в массиве)
	for (size_t i = 0; i < n; i++)
		if (a[i].bd.d == d && a[i].bd.m == m)
		{

			// печатаем сообщение Contact #„исло
			cout << "Contact #" << i + 1 << endl;
			// ѕечатаем им€ фамили€
			cout << "\t" << a[i].firstname << " " << a[i].lastname << endl;
			// выводим остальные пол€ структуры
		}
	system("pause");
}


void statisticage(contact a[], int n) {
	int k18 = 0, k35 = 0, k65 = 0, k = 0;

	// перебираем все контакты (элементы в массиве)
	for (size_t i = 0; i < n; i++) {
		int r = 2022 - a[i].bd.y;
		if (r <= 18)
			k18++;
		else if (r > 18 && r <= 35)
			k35++;
		else if (r > 35 && r <= 65)
			k65++;
		else
			k++;
	}
	cout << "Age stat: " << endl;
	cout << "\t less 18: " << k18 << endl;
	cout << "\t 18-35: " << k35 << endl;
	cout << "\t 35-65: " << k65 << endl;
	cout << "\t 65+: " << k << endl;

}

void statisticgender(contact a[], int n) {
	int k0 = 0, k1 = 0, k2 = 0;

	// перебираем все контакты (элементы в массиве)
	for (size_t i = 0; i < n; i++)

		if (a[i].gender == 0)
			k0++;
		else if (a[i].gender == 1)
			k1++;
		else
			k2++;
	cout << "GEnderstat: " << endl;
	cout << "\t male: " << k0 << endl;
	cout << "\t female: " << k1 << endl;
	cout << "\t unknown: " << k2 << endl;

}

void statistics(contact a[], int n) {
	int k;
	cout << "statistic type: " << endl;
	cout << "\t 1 - age: " << endl;
	cout << "\t 2 - gender: " << endl;
	cin >> k;

	void (*pfunc)(contact a[], int n);

	if (k == 1)
		pfunc = statisticage;
	else
		pfunc = statisticgender;
	pfunc(a, n);

	system("pause");
}


void loaddata_bin(contact* c, int& n) {
	FILE* f;
	struct _finddata_t myfileinfo;//тип данных характеристика найденного файла
	intptr_t done = _findfirst("contacts.card", &myfileinfo);// 1 пар - маска файла который мы ищем, 2 - информацию которую мы ищем
	if (done == -1) {
		fopen_s(&f, "contacts.card", "wb");
		fclose(f);
	}

	fopen_s(&f, "contacts.card", "rb");
	while (!feof(f)) {
		fread(&c[n], sizeof(contact), 1, f);
		n++;
	}
	fclose(f);
	n--;

}

void savedata_bin(contact* c, int n) {
	FILE* f;

	fopen_s(&f, "contacts.card", "wb");
	fwrite(&c[0], sizeof(contact), n, f);
	fclose(f);
}

void backup() {

	contact b[1000];
	int n = 0;
	FILE* f;
	fopen_s(&f, "contacts.card", "rb");
	while (!feof(f)) {
		fread(&b[n], sizeof(contact), 1, f);
		n++;
	}
	fclose(f);
	n--;

	FILE* fout;
	fopen_s(&fout, "contacts.card.backup", "wb");
	fwrite(&b[0], sizeof(contact), n, fout);
	fclose(fout);


}

int main() {
	contact c[1000];
	int n = 0;
	int k;
	loaddata_bin(c, n);

	do {
		system("cls");
		cout << "1 - print" << endl;
		cout << "2 - add" << endl;
		cout << "3 - find by phone" << endl;
		cout << "4 - find by name" << endl;
		cout << "5 - sort by name" << endl;
		cout << "6 - check birthday" << endl;
		cout << "7 - delete" << endl;
		cout << "8 - statistics" << endl;
		cout << "9 - backup" << endl;
		cout << "0 - quit" << endl;
		cin >> k;

		switch (k) {
		case 1:
			print(c, n);
			break;
		case 2:
			add(c, n);
			break;
		case 4:
			findbyname(c, n);
			break;
		case 5:
			sortbyname(c, n);
			break;
		case 6:
			checkbirthday(c, n);
			break;
		case 8:
			statistics(c, n);
			break;
		case 9:
			backup();
			break;


		}
	} while (k != 0);

	savedata_bin(c, n);

	return 0;
}\