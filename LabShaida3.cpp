
#include <iostream>
#include <vector>
#include <ctime>
#include "windows.h"
#include <forward_list>
#include <string>

using namespace std;

void set_cur(int x, int y);
void custom_clear();

//Скрыть курсор
void remove_cur()
{
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}
//Перечисление цветов Black, Blue, Green и т.д.
enum Colors 
{ 
    Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray,
    DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
}; 

template<Colors txt = LightGray, Colors bg = Black> ostream& color(ostream& text);
void rand_init_list(forward_list<int>& lst, int count);
void user_init_list(forward_list<int>& lst, int count);

void print_list(forward_list<int>& lst);

void find_elem(forward_list<int> lst);

void find_more_than_average(forward_list<int> lst);

template<typename type >type getValue(string s);

int main()
{
    srand(time(0));//Задание зерна ПСГЧ
    setlocale(LC_ALL, "");//Кириллица в консоле
    remove_cur();//Не показывать курсор
    forward_list<int> lst;
    int list_size = 0;

    while(list_size <= 0) list_size = getValue<int>("Введите размер списка");
    rand_init_list(lst, list_size);
    //user_init_list(lst, list_size);

    print_list(lst);
    find_elem(lst);
    find_more_than_average(lst);
    system("pause");
}

//Шаблон безопасного считывания данных со стандартного потока istream и вывод
template<typename type > type getValue(string s)
{
    while (true) // Цикл продолжается до тех пор, пока пользователь не введёт корректное значение
    {
        cout << s << ": ";
        type a;
        cin >> a;
        if (cin.fail()) // Если предыдущее извлечение оказалось неудачным,
        {
            system("cls");
            cin.clear(); // То возвращаем cin в 'обычный' режим работы
            cin.ignore(32767, '\n'); // Удаляем значения предыдущего ввода из входного буфера
        }
        else // Eсли всё хорошо, то возвращаем a
            return a;
    }
}

//Установка позиции курсора
void set_cur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Установка позиции курсора в координаты [0,0]
void custom_clear()
{
    set_cur(0, 0);
}

//Шаблон функции задания цвета вывода выходного потока ostream
template<Colors txt = LightGray, Colors bg = Black> ostream& color(ostream& text) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | txt));
    return text;
}

//Инициазиация массива случайными значениями с зерном time(0)
void rand_init_list(forward_list<int>& lst, int count)
{
    


    for (size_t i = 0; i < count; i++)
    {
        lst.push_front(rand() % 101-50);
    }
        
    lst.sort();
}

void user_init_list(forward_list<int>& lst, int count)
{

    for (size_t i = 0; i < count; i++)
    {
        lst.push_front(getValue<int>("Введите " + std::to_string(i) + " элемент"));
    }

    lst.sort();
}

void print_list(forward_list<int>& lst)
{
    auto elem = lst.begin();
    while (elem != lst.end())
    {
        cout << *elem++ << " ";
    }
    cout << endl;
}

void find_elem(forward_list<int> lst)
{
    bool isFind = false;
    int iter = 0;
    auto elem = lst.begin();
    while (elem != lst.end())
    {
        if (*elem == 10) 
        {
            isFind = true;
            break;
        }
        *elem++;
        iter++;
    }
    if (isFind) cout << "Элемент c номером варианта(10) найден под индексом " << iter << "!" << endl;
    else cout << "Элемент c номером варианта(10) не найден" << endl;
}

void find_more_than_average(forward_list<int> lst)
{
    int iter = 0;
    int sum = 0;
    int founded = 0;
    auto elem = lst.begin();
    while (elem != lst.end())
    {
        sum += *elem;
        *elem++;
        iter++;
    }
    cout << "Среднее значение равно " << sum / (float)iter << endl;

    elem = lst.begin();
    while (elem != lst.end())
    {
        if (*elem > (sum / (float)iter))founded++;
        *elem++;
    }
    cout << "Элементов которые превышают среднее значение всех элементов списка:" << founded << endl;
    
}


//Бинарный поиск
//arr - Вектор int
//key - искомый ключ
//log - вывод хода поиска
//animate - режим вывода хода поиска

//Безопасное считывание из потока istream
int getValue()
{
    while (true) // Цикл продолжается до тех пор, пока пользователь не введёт корректное значение
    {
        int a;
        cin >> a;
        if (cin.fail()) // Если предыдущее извлечение оказалось неудачным,
        {
            cin.clear(); // То возвращаем cin в 'обычный' режим работы
            cin.ignore(32767, '\n'); // Удаляем значения предыдущего ввода из входного буфера
        }
        else // Eсли всё хорошо, то возвращаем a
            return a;
    }
}

