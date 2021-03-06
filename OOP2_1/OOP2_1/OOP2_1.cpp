// OOP2_1.cpp: определяет точку входа для консольного приложения.
//шаблоны иноследования

#include "stdafx.h"

#define _CRT_SECURE_NO_WARNINGS true
#include<stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;


class Tours
{
public:
	//конструктор 
	Tours() {}
	//?
	Tours(char ent_name[50], char ent_city[50],int ent_days, int ent_price){
		name = ent_name;
		city = ent_city;
		days = ent_days;
		price = ent_price;
		reserv_point = false;
	}
	//?
	//конструктор копирования
	Tours(Tours & object1) {
		reserv_point = object1.reserv_point;
		int size_n = strlen(object1.name);
		name = new char[size_n];
		strcpy(name, object1.name);
		int size_c = strlen(object1.city);
		city = new char[size_c];
		strcpy(city, object1.city);
		days = object1.days;
		price = object1.price;
		identify = object1.identify;
	}

	void func_disp_f();
	//дружественный оператор 
	friend Tours operator+=(Tours ob1, Tours ob2);
	
	Tours operator=(const Tours);
	Tours operator=(const int);
	Tours operator/(const int);
	Tours operator*(const int);
	Tours operator>(const Tours);
	bool operator== (const Tours);
	
	//геттеры и сеттеры для данных
	void _set_name(char pop[])
	{
		name = pop;
	}
	void _set_city(char pop[])
	{
		city = pop;
	}
	void _set_days(int pop)
	{
		days = pop;
	}
	void _set_price(int pop)
	{
		price = pop;
	}
	char* _get_name()
	{
		return name;
	}
	char* _get_city()
	{
		return city;
	}
	int _get_days()
	{
		return days;
	}
	int _get_price()
	{
		return price;
	}
	int identify;
	bool reserv_point;

private:
	char *name;
	char *city;
	int days;
	int price;
};
//реализация дружественного оператора 

Tours operator+=(Tours ob1, Tours ob2)
{
	strcpy(ob1.name, ob2.name);
	strcpy(ob1.city, ob2.city);
	ob1.days += ob2.days;
	ob1.price += ob2.price;
	return ob1;
}
//перегрузка сравнения (в 4 реализациях)

Tours Tours::operator=(Tours ob1)
{
	char ent_name[50], ent_city[50];
	strcpy(ent_name, ob1.name);
	strcpy(ent_city, ob1.city);
	_set_name(ent_name);
	_set_city(ent_city);
	days = ob1.days;
	price = ob1.price;
	return ob1;
}

Tours Tours::operator=(int num)
{
	days += num;
	price += num;
	return *this;
}

Tours Tours::operator*(int ob1)
{

	days *= ob1;
	return *this;
}

Tours Tours::operator/(int ob1)
{
	price /= ob1;
	return *this;
}

Tours Tours::operator>(Tours ob1)
{
	if ((days > ob1.days) && (price > ob1.price))
		return *this;
	else
		return ob1;
}

bool Tours::operator==(Tours ob1)
{
	if ((strcmp(name, ob1.name) == 0) && (strcmp(city, ob1.city) == 0) && days == ob1.days && price == ob1.price)
		return true;
	else
		return false;
}


class Conten_tours {
private:
	int pop_q;
	Tours *pop_tour;
public: 

	void set_pop_q(int pop)
	{pop_q = pop;}

	int get_pop_q()
	{return pop_q;}

	void set_pop_tour(Tours *popich)
	{		for (int i = 0; i < pop_q; i++)
		{
			pop_tour[i] = popich[i];
		}
	}
	Tours get_pop_tour(int i)
	{
		return pop_tour[i];
	}

	void search_s();// производит поиск по 4 полям
	void search_s(char* pop_n, char* pop_c, char* pop_d, char* pop_p);
	void search_s(Tours searchTour);
	void reservation(int ent_ident); // функция бронирования(бронирует по идентификатору)
	void func_disp();
	void reserv_disp();
    char* cin(int size);
	char* cin();

	Conten_tours(int q) : pop_q(q), pop_tour(new Tours[q])
	{
	}
};

void Tours::func_disp_f()
{
	cout << "Name: " << _get_name() << endl;
	cout << "City: " << _get_city() << endl;
	cout << "Days: " << _get_days() << endl;
	cout << "Price: " << _get_price() << endl;
	cout << "Identificator: " <<identify << endl;
	cout << endl;

}

char* Conten_tours::cin(const int size) {
    char* list = new char[size];
    int i = 0;
    char input;
    while (i < size) {
        input = getchar();
		if (input == '\n') {
			list[i] = '\0';
			break;
		}
        list[i] = input;
        i++;
    }
	char *time_str = new char[strlen(list) + 1];
	strcpy(time_str, list);
	return time_str;
}

char* Conten_tours::cin() {
	return cin(100);
}

void Conten_tours::search_s()
{
	const size_t size = 100;
	char *s = cin(size);// заглушка для того чтобы работал ввод 
	cout << "Now let's search your tour!\n";
	cout << "Enter name for searching: ";
	char *pop_n = cin(size);
	cout << "Enter city for searching: ";
	char *pop_c = cin(size);
	cout << "Enter days for searching: ";
	char *pop_d = cin(size);
	cout << "Enter price for searching: ";
	char *pop_p = cin(size);
	search_s(pop_n, pop_c, pop_d, pop_p);
}

void Conten_tours::search_s(char* pop_n, char* pop_c, char* pop_d, char* pop_p) {
	Tours searchTour;
	searchTour._set_name(pop_n);
	searchTour._set_city(pop_c);
	searchTour._set_days(atoi(pop_d));
	searchTour._set_price(atoi(pop_p));
	search_s(searchTour);
}

void Conten_tours::search_s(Tours searchTour)// производит поиск по 4 полям
{
	char *searchName = { searchTour._get_name() };
    char *searchCity = { searchTour._get_city() };
	int searchCounter = 0;

	if (!(searchName[0] == '\0')) {
		searchCounter++;
	}
	if(!(searchCity[0] == '\0')) {
		searchCounter++;
	}
	if(!(searchTour._get_days() == 0)) {
		searchCounter++;
	}
	if(!(searchTour._get_price() == 0)) {
		searchCounter++;
	}

	for (int i = 0; i < pop_q; i++) {
		int counter = 0;
		char *name = { pop_tour[i]._get_name() };
		char *city = { pop_tour[i]._get_city() };
		if (strcmp(searchName, name) == 0) {
			counter++;
		}
		if(strcmp(searchCity, city) == 0) {
			counter++;
		}
		if(searchTour._get_days() == pop_tour[i]._get_days()) {
			counter++;
		}
		if(searchTour._get_price() == pop_tour[i]._get_price()) {
			counter++;
		}
        if (searchCounter == counter)
        {
			cout << "Naideno!\n";
            pop_tour[i].func_disp_f();
		}
	}
}

char* readText() {
	char *text = (char*)malloc(255);
	char c;
	int numOfChars = 0;
	cin >> text;
	while ((c = getchar()) != '\n') {
		realloc(text, numOfChars + 1);
		text[numOfChars] = c;
		numOfChars++;
	}
	return text;
}
void func_operators()
{
	const int hot_p = 3;
	int butt_ex;
	cout << "Enter your choise: 1-= 12 -= 2-/ 3-* 4-> 5-== " << endl;
	cin >> butt_ex;
	char mas1[] = "_Golden_1";
	char mas2[] = "_Golden_2";
	Tours temp_t_1(mas1, mas1, 12, 20);
	Tours temp_t_2(mas2, mas2, 4, 11);

	//Tours temp_t_1("_Golden_1", "_Golden_1", 12, 20);
	//Tours temp_t_2("_Golden_2", "_Golden_2", 4, 11);

	switch (butt_ex)
	{
	case 1:
		(temp_t_2 = temp_t_1).func_disp_f();// success +1
		break;
	case 12:
		temp_t_1 = hot_p;//success +1
		temp_t_1.func_disp_f();
		break;
	case 2:
		temp_t_1 / hot_p;//success + 1
		temp_t_1.func_disp_f();
		temp_t_2 / hot_p;
		temp_t_2.func_disp_f();
		break;
	case 3:
		temp_t_1 * hot_p;//success +1
		temp_t_1.func_disp_f();
		temp_t_2 * hot_p;
		temp_t_2.func_disp_f();
		break;
	case 4:
		(temp_t_2 > temp_t_1).func_disp_f();//success +1
		(temp_t_1 > temp_t_2).func_disp_f();
		//Оператор сравнения должен возвращать boolean а не тот object который больше. Но раз ты уже написала, то пускай так и остается.
		break;
	case 5:
		std::cout << "first test false: -> " << (bool)(temp_t_1 == temp_t_2) << std::endl;//success +1
		temp_t_1._set_city(temp_t_2._get_city());
		temp_t_1._set_days(temp_t_2._get_days());
		temp_t_1._set_name(temp_t_2._get_name());
		temp_t_1._set_price(temp_t_2._get_price());
		std::cout << "second test true: -> " << (bool)(temp_t_1 == temp_t_2) << std::endl;
		break;
	default:
		break;
	}
}

void Conten_tours::func_disp()
{
	cout << "Let's watch on tour!" << endl;
	for (int i = 0; i < get_pop_q(); i++)
	{
		int ii = i;
		cout << "Tour:" <<ii+1 << endl;
		cout << "Name: " << get_pop_tour(i)._get_name()<<endl;
		cout << "City: " << get_pop_tour(i)._get_city()<< endl;
		cout << "Days: " << get_pop_tour(i)._get_days()<< endl;
		cout << "Price: " << get_pop_tour(i)._get_price()<< endl;
		cout << "Identificator: " << pop_tour[i].identify << endl;

		cout << endl;
	}
}


void Conten_tours:: reservation(int ent_ident) // функция бронирования(бронирует по идентификатору)
{
	for (int i = 0; i < get_pop_q(); i++) {
		if (ent_ident == pop_tour[i].identify)
		{
			pop_tour[i].reserv_point = true;
			cout << "Your rezervation is suckcess!" << endl;
		}
	}
	//если такого идентификатора нет 
	cout << "This number is not in the card index. Enter exiting identifier!" << endl;
}
void Conten_tours:: reserv_disp()
{
	for (int i = 0; i < get_pop_q(); i++) {
		if (pop_tour[i].reserv_point == true) pop_tour[i].func_disp_f();
	}
}

/*какое-то чудовище, а не функция
по идее она должна дать пользователю выбор , какую операцию он хочет сделать со всем массивом туров
но что-то видимо у меня переклинило, и я написал вот это - простибте*/

// создание класса с свойствами и методами
int main()
{
	cout << "Hi? i am Mike. What do you want? /n See yesterday's tours(use costructor with arguments) -1/n Write today tours -2 ";
	int cons;
	cin >> cons;
	if (cons == 1) {
		//юзаем конструктор с параметрами и копирующий конструктор
		char str1[] = "Mountain_of_candy";
		char str2[] = "Monako";
		Tours yester_tour(str1, str2, 12, 200);
		yester_tour.identify = 1;
		Tours arr_yes(yester_tour);
		arr_yes.func_disp_f();

		/*for (int i = 0; i < 5; i++)
		{
			arr_yes[i] = yester_tour;
			func_disp_f(arr_yes[i]);
		}*/
	}
		cout << "Lets make tours !\n Enter quantity of subjects:" << endl;
		int qant_point;
		cin >> qant_point;
		Conten_tours spis(qant_point);
		spis.set_pop_q(qant_point);

		Tours *tour = new Tours[qant_point];
		for (int i = 0; i < qant_point; i++)
		{
			if (i > 0)cout << "Next tour" << endl;
			cout << "Enter name: ";
			char *name = readText();

			tour[i]._set_name(name);//?

			cout << "Enter city: ";

			char *city = readText();
			tour[i]._set_city(city);//?

			cout << "Enter days: "; int pop_d;
			cin >> pop_d;
			tour[i]._set_days(pop_d);

			cout << "Enter price: "; int pop_p;
			cin >> pop_p;
			tour[i]._set_price(pop_p);
			tour[i].identify = i + 1;
			tour[i].reserv_point = false;
			cout << endl;
		}
		spis.set_pop_tour(tour);
	
	//реализация меню
	bool stop_button = true;
	while (stop_button)
	{
		cout << "Enter your priority:\n 1 - display affordable tours\n 2 - find a tour\n 3 - book a tour\n 4- display reserve tours" << endl;
		cout << "5 - doing smth with tour \n 0 - exit"<< endl;
		short decision;
		cin >> decision;
		switch (decision)
		{
		case 1:spis.func_disp(); break;
		case 2:spis.search_s(); break;
		case 3: cout << "Enter identification number of tour: " << endl;
			int id; cin >> id;
			spis.reservation(id); break;
		case 4: spis.reserv_disp(); break;
		case 5: func_operators(); break;
		case 0:stop_button = false; break;
		default: cout << "Enter another number!\n" << endl; break;
		}
	}

	system("pause");
	return 0;
}
/*
приложения шаблонов класса реализация смарт-указателя (похож на конструктор копирования)
классы поддерживающие механизм транзакций 
*/


 