#include <iomanip>
#include <iostream>
#include <cmath>

using namespace std;

int max_iter = 150;

int iter = 0;

// Функция (x^4)/4 - 2*x^2
double function(double x) {
    return (pow(x, 4) / 4) - 2 * pow(x, 2);
}

// Производная функции
double derivative(double x) {
    return pow(x, 3) - 4 * x;
}

// Вторая производная функции
double second_derivative(double x) {
    return 3 * pow(x, 2) - 4;
}

// Метод поразрядного поиска
double bitwiseSearch(double a, double b, double epsilon) {

    iter = 0;

    double step = (b - a) / 2; // Начальный шаг
    double x = a; // Поиск начинается от левой границы массива
    double min_x = x;
    double min_f = function(x);

    while (step > epsilon) {

        

        // Поиск вправо с большим шагом
        cout << "Поиск вправо:\n\n";
        while (x + step <= b) {
            iter++;
            if (iter == max_iter) return min_x;
            x += step; // Увеличиваем х
            double current_f = function(x);
            cout << "Итерация " << left << setw(4) << iter << " Шаг: " << left << setw(4) << step << " | x = " << left << setw(10) << x << " f(x) = " << left << setw(10) << current_f << "\n";
            if (current_f < min_f) { // Сравниваем значения функции в новой и старой точках
                min_f = current_f;
                min_x = x;
            }
            else {
                break; // Функция начала увеличиваться
            }
        }

        // Уменьшение шага
        step /= 2;

        cout << "\nПоиск влево:\n\n";

        // Поиск влево с уменьшенным шагом
        while (x - step >= a) {
            iter++;
            if (iter == max_iter) return min_x;
            x -= step; // Уменьшаем x
            double current_f = function(x); // Находим значение функции в новой точке
            cout << "Итерация " << left << setw(4) << iter << " Шаг: " << left << setw(4) << step << " | x = " << left << setw(10) << x << " f(x) = " << left << setw(10) << current_f << "\n";
            if (current_f < min_f) { // Сравниваем значения в новой и старой точках
                min_f = current_f;
                min_x = x;
            }
            else {
                break; // Функция начала увеличиваться
            }
        }

        // Уменьшение шага
        step /= 2;

        cout << endl;
    }

    cout << "\n------------\nИтераций - " << iter << endl;

    return min_x;
}

// Метод дихотомии
double dichotomy(double a, double b, double e) {
    iter++;
    if (iter == max_iter) { cout << "\n------------\nИтераций - " << iter << endl;  return (a + b) / 2;}
    float E = 0.02;
    if ((b - a) / 2 <= e) { // Условие остановки
        cout << "\n------------\nИтераций - " << iter << endl;  return (a + b) / 2;
    }
    float x1 = (a + b - E) / 2;
    float x2 = (a + b + E) / 2;

    cout << "Итерация " << left << setw(4) << iter << "| a = " << setw(15) << left << a << " b = " << setw(15) << b << " x1 = " << setw(15) << x1
        << " x2 = " << setw(15) << x2 << " f(x1) = " << setw(15) << function(x1) << " f(x2) = " << setw(15) << function(x2) << endl;
    if (function(x1) <= function(x2)) {
        // Вывод текущих значений интервала и точек
        dichotomy(a, x2, e); // Рекурсивный вызов для левой части интервала
    }
    else {
        dichotomy(x1, b, e); // Рекурсивный вызов для правой части интервала
    }
}

// Метод золотого сечения для поиска минимума функции
double goldenSectionSearch(double a, double b, double tol) {
    const double phi = (sqrt(5) - 1) / 2;  // Коэффициент золотого сечения (~0.618)

    double x1 = a + (1 - phi) * (b - a);
    double x2 = a + phi * (b - a);
    double f1 = function(x1);
    double f2 = function(x2);

    iter = 0; // Зануляем счетчик итераций
    
    while (fabs(b - a) > tol) { // Проверка условия точности
        iter++;
        if (iter == max_iter) return (a + b) / 2;
        cout << "Итерация " << left << setw(4) << iter
            << "| a = " << left << setw(15) << a << " b = " << left << setw(15) << b
            << " x1 = " << left << setw(15) << x1 << " x2 = " << left << setw(15) << x2
            << " f(x1) = " << left << setw(15) << f1 << " f(x2) = " << left << setw(14) << f2 << endl;

        if (f1 < f2) {
            b = x2;
            x2 = x1;
            f2 = f1;
            x1 = a + b - x2;
            f1 = function(x1);
        }
        else {
            a = x1;
            x1 = x2;
            f1 = f2;
            x2 = a + b - x1;
            f2 = function(x2);
        }
    }
    cout << "\n------------\nИтераций - " << iter << endl;
    return (a + b) / 2; // Возвращаем найденное значение минимума
}


// Функция для нахождения минимума методом средней точки
double middle_point(double a, double b, double tol) {
    double ak = a; // Начало интервала
    double bk = b; // Конец интервала
    double xk;     // Средняя точка интервала
    iter = 0; // Зануляем счетчик итераций

    // Продолжаем сужать интервал, пока его длина не станет меньше 2*tol
    while ((bk - ak) / 2 > tol) {
        xk = (ak + bk) / 2; // Вычисляем среднюю точку
        double df_xk = derivative(xk); // Вычисляем производную в средней точке
        iter++;

        if (iter == max_iter) return xk;

        // Вывод текущего значения x, значения функции и количества итераций
        cout << "Итерация " << left << setw(4) << iter << left << setw(5) << "| a = " << left << setw(15) << ak << "b = " << left << setw(15) << bk << "x = " << left << setw(15) << xk << "f'(x) = " << left << setw(15) << derivative(xk) << endl;

        // Если производная близка к нулю (в пределах точности), завершаем поиск
        if (abs(df_xk) < tol) {
            break;
        }

        // Если производная отрицательная, минимум находится в правой половине интервала
        if (df_xk < 0) {
            ak = xk;
        }
        // Если производная положительная, минимум находится в левой половине интервала
        else {
            bk = xk;
        }
    }
    cout << "\n------------\nИтераций - " << iter << endl;
    // Возвращаем среднюю точку последнего интервала как приближение к точке минимума
    return (ak + bk) / 2;
}

// Метод хорд
double chord_method(double a, double b, double tol) {
    double x_tilda;
    iter = 0; // Зануляем счетчик итераций
    if (derivative(a) < 0 && derivative(b) < 0) return b;
    if (derivative(a) > 0 && derivative(b) > 0) return a;
    while (fabs(b - a) > tol) {
        iter++; // Увеличиваем счётчик итераций

        if (iter == max_iter) return x_tilda;
        // Проверка на деление на ноль
        if (fabs(derivative(a) - derivative(b)) < 1e-9) {
            cerr << "Ошибка: деление на ноль при вычислении x_tilda" << endl;
            return (a + b) / 2;
        }

        // Вычисляем новую точку по формуле метода хорд
        x_tilda = a - derivative(a) * (a - b) / (derivative(a) - derivative(b));

        cout << "Итерация " << left << setw(4) << iter
            << " | a = " << left << setw(15) << a << " b = " << left << setw(15) << b << " x = " << left << setw(15) << x_tilda
            << "f'(x) = " << left << setw(15) << derivative(x_tilda)
            << "f(x) = " << left << setw(15) << function(x_tilda) << endl;

        // Проверяем условие завершения
        if (fabs(derivative(x_tilda)) <= tol) {
            return x_tilda;
        }

        // Определяем новый интервал поиска
        if (derivative(x_tilda) > 0) {
            b = x_tilda;
        }
        else {
            a = x_tilda;
        }
    }

    cout << "\n------------\nИтераций - " << iter << endl;

    return (a + b) / 2; // Возвращаем середину оставшегося интервала
}


// Метод Ньютона
double newton_method(double x0, double tol) {
    double x = x0;
    iter = 0; // Зануляем счетчик итераций
    while (abs(derivative(x)) > tol) { // Проверяем условие выхода из цикла
        iter++;

        if (iter == max_iter) return x;
        cout << "Итерация " << left << setw(4) << iter
            << "| x = " << left << setw(15) << x << "f'(x) = " << left << setw(15) << derivative(x) << "f''(x) = " << left << setw(15) << second_derivative(x) << "f(x) = " << left << setw(15) << function(x) << endl; // Выводим итерации
        if (fabs(second_derivative(x)) < 1e-9) { cout << "Вторая производная слишком мала для данного метода"; return -1; } // Защита от деления на ноль
        x = x - (derivative(x) / second_derivative(x)); // Вычисляем следующее значение x

    }
    return x; // Возвращаем последнее найденное значение
}

int menu(double a, double b, double e) { // функция для вызова меню
    cout << "Метод дихотомии -> 1\nМетод золотого сечения -> 2\nМетод поразрядного поиска -> 3\nМетод средней точки -> 4\nМетод хорд -> 5\nМетод Ньютона -> 6\nВвод максимального количества итераций -> 7\n\nДля ввода других границ интеравала или точности введите любое другое значение\n\n";
    int c;
    cin >> c;
    cin.ignore();
    system("cls");
    bool flag = true;
    double min_x = 0;
    switch (c) {
    case 1: {
        cout << "Метод дихотомии\n\n";
        iter = 0;
        min_x = dichotomy(a, b, e);
        break;
    }
    case 2: {
        cout << "Метод золотого сечения\n\n";
        min_x = bitwiseSearch(a, b, e);
        break;
    }
    case 3: {
        cout << "Метод поразрядного поиска\n\n";
        min_x = goldenSectionSearch(a, b, e);
        break;
    }
    case 4: {
        cout << "Метод средней точки\n\n";
        min_x = middle_point(a, b, e);
        break;
    }
    case 5: {
        cout << "Метод хорд\n\n";
        min_x = chord_method(a, b, e);
        break;
    }
    case 6:
        double x0;
        cout << "Введите начальное приближение: ";
        cin >> x0;
        cout << "Метод Ньютона\n\n";
        min_x = newton_method(x0, e);
        break;
    case 7: 
        cout << "Максимальное кол-во итераций сейчас: " << max_iter << endl;
        cout << "Введите максимальное количество итераций: ";
        cin >> max_iter;
        flag = false;
        break;
    default: return -1;
    }
    if (flag) { cout << endl << "x = " << min_x << " f(x) = " << function(min_x) << endl; system("pause"); }
    system("cls");
    menu(a, b, e);
}

int main() {
    setlocale(LC_ALL, "RU"); // Устанавливаем русскую локализацию
    system("cls");
    double a, b; // Интервал поиска минимума
    double e; // Точность
    // Ввод границ и точности с клавиатуры
    cout << "Введите левую границу: ";
    cin >> a;
    cout << "Введите правую границу: ";
    cin >> b;
    cout << "Введите нужную точность: ";
    cin >> e;
    cin.ignore();
    system("cls");
    int temp = menu(a, b, e); // Заходим в меню, записываем какое значение она вернула
    if (temp == -1) main(); // Если функция меню вернула -1, то вызываем main
    return 0;
}
