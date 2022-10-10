#include <iostream>
#include <windows.h>
#include <ctime>
#include <string>
#include <chrono>

using namespace std;

void setTextColor(int textColorIndex) { // Смена цвета текста
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, (0 << 4) + textColorIndex);
}

void quicksort(int* arr, int end, int begin)
{
    int mid;
    int f = begin;
    int l = end;
    mid = arr[(f + l) / 2];
    while (f < l)
    {
        while (arr[f] < mid) f++;
        while (arr[l] > mid) l--;
        if (f <= l)
        {
            swap(arr[f], arr[l]);
            f++;
            l--;
        }
    }
    if (begin < l) quicksort(arr, l, begin);
    if (f < end) quicksort(arr, end, f);
}

bool isRestartNeeded() { // Функция перезапуска программы
    cin.clear(); // Очистка ввода от ошибок
    cin.sync();
    cout << "Перезагрузить программу? [";
    setTextColor(2);
    cout << "Y";
    setTextColor(15);
    cout << "/";
    setTextColor(4);
    cout << "любой другой символ";
    setTextColor(15);
    cout << "] ";
    string answer;
    cin >> answer;
    if (answer == "y" || answer == "Y")
        return true;
    else
        return false;
}

bool notCorrectInput() { // Остановка программы при ошибочном вводе
    if (cin.fail()) {
        setTextColor(4);
        cout << "Введён неверный тип данных!" << endl;
        setTextColor(15);
        cout << "Программа будет завершена через 2 с.";
        double nowTime;
        nowTime = time(0);
        while (time(0) - nowTime != 2) {}
        return true;
    }
    return false;
}

int main() {
    const int N = 100;
    setlocale(0, ""); // Верное отображение русского языка
    int array[N];
    int arraySorted[N];
    srand(time(0));
    cout << '[';
    for (int i = 0; i < N; i++) { // Заполнение массива случайными числами от -99 до 99
        array[i] = rand() % 199 - 99;
        arraySorted[i] = array[i];
        if (i != N - 1)
            cout << array[i] << ", ";
        else
            cout << array[i];
    }
    cout << ']';
    cout << '\n';
    cout << '\n';
    
    quicksort(arraySorted, N - 1, 0); // Быстрая сортировка
    cout << '[';
    for (int i = 0; i < N; i++) {
        if (i != N - 1)
            cout << arraySorted[i] << ", ";
        else
            cout << arraySorted[i];
    }
    cout << ']';
    cout << '\n';
    cout << '\n';
    auto startTime = chrono::high_resolution_clock::now(); // Замер времени с сортировкой
    int minimal = arraySorted[0];
    int maximal = arraySorted[N - 1];
    auto endTime = chrono::high_resolution_clock::now();
    cout << "Минимальный элемент : " << minimal << '\n' << "Максимальный элемент: " << maximal << '\n';
    cout << "Время, потраченное на поиск в отсортированном массиве: " << chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count() << "нс." << '\n';

    auto startTime1 = chrono::high_resolution_clock::now(); 
    float min = 9999;
    float max = -9999;
    for (int i = 0; i < N; i++) {
        if (array[i] < min)
            min = array[i];
        if (array[i] > max)
            max = array[i];
    }
    auto endTime1 = chrono::high_resolution_clock::now();
    cout << "Время, потраченное на поиск в неотсортированном массиве: " << chrono::duration_cast<chrono::nanoseconds>(endTime1 - startTime1).count() << "нс." << '\n';

    int middle = round((min + max) / 2);
    cout << "Среднее из минимального и максимального: " << middle << '\n';
    int counter = 0;
    for (int i = 0; i < N; i++) {
        if (arraySorted[i] == middle)
            counter++;
    }
    cout << "Количество элементов, равных среднему из минимального и максимального: " << counter << '\n';

    cout << "Введите число a: ";
    int a;
    cin >> a;
    if (notCorrectInput())
        return 0;
    counter = 0;
    for (int i = 0; i < N; i++) {
        if (arraySorted[i] < a)
            counter++;
    }
    cout << "Количество элементов меньше a равно " << counter << '\n';

    cout << "Введите число b: ";
    int b;
    cin >> b;
    if (notCorrectInput())
        return 0;
    counter = 0;
    for (int i = 0; i < N; i++) {
        if (arraySorted[i] > b)
            counter++;
    }
    cout << "Количество элементов больше b равно " << counter << '\n';

    cout << "Введите число c: ";
    int c;
    cin >> c;
    if (notCorrectInput())
        return 0;
    startTime = chrono::high_resolution_clock::now();
    int leftBorder = 0;
    int rightBorder = N;
    int medium = rightBorder / 2;
    while (leftBorder + 1 < rightBorder) {
        if (c >= arraySorted[medium])
            leftBorder = medium;
        else
            rightBorder = medium;
        medium = (rightBorder + leftBorder) / 2;
    }
    endTime = chrono::high_resolution_clock::now();
    if (arraySorted[leftBorder] == c)
        cout << "Число " << c << " есть в массиве." << '\n';
    else
        cout << "Числа " << c << " нет в массиве." << '\n';
    cout << "Бинпоиск по массиву занял " << chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count() << "нс." << '\n';

    startTime = chrono::high_resolution_clock::now();
    bool flag = false;
    for (int i = 0; i < N; i++) {
        if (arraySorted[i] == c)
            flag = true;
        if (flag)
            break;
    }
    endTime = chrono::high_resolution_clock::now();
    cout << "Стандартный поиск по массиву занял " << chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count() << "нс." << '\n';

    cout << "Введите в строку 2 индекса элемента массива, которые вы хотите поменять местами: ";
    int firstElement;
    int secondElement;
    cin >> firstElement >> secondElement;
    if (notCorrectInput())
        return 0;
    if (firstElement >= 0 and firstElement <= N - 1 and secondElement >= 0 and secondElement <= N - 1) {
        startTime = chrono::high_resolution_clock::now();
        swap(arraySorted[firstElement], arraySorted[secondElement]);
        endTime = chrono::high_resolution_clock::now();
        cout << "Замена элементов массива заняла " << chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count() << "нс." << '\n';
        cout << '[';
        for (int i = 0; i < N; i++) {
            if (i == firstElement or i == secondElement) {
                setTextColor(4);
                cout << arraySorted[i];
                setTextColor(15);
            }
            else {
                cout << arraySorted[i];
            }
            if (i != N - 1)
                cout << ", ";
        }
        cout << ']';
        cout << '\n';
        cout << '\n';
    }
    else
        cout << "Неверные индексы!" << '\n';

    if (isRestartNeeded()) {
        cout << '\n' << "Перезапуск программы..." << '\n' << '\n';
        // Остановка времени на 2с
        double nowTime;
        nowTime = time(0);
        while (time(0) - nowTime != 2) {}
        // Перезапуск программы
        main();
    }
    else { // Выход  из программы
        return 0;
    }
}