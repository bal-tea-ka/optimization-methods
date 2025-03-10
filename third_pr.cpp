#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

int iter = 0;

// ������� ��� ���������� �������� ������� �������
// ���������� �������� ������� (x^4)/4 - 2*x^2
double function(double x) {
    return (pow(x, 4) / 4) - 2 * pow(x, 2);
}

// ����������� ����������� �������
double derivative(double x) {
    return pow(x, 3) - 4 * x;
}

double second_derivative(double x) {
    return 3 * pow(x, 2) - 4;
}

// ����� ������������ ������ ��������
double bitwiseSearch(double a, double b, double epsilon) {
    
    iter = 0;

    double step = (b - a) / 2; // ��������� ���
    double x = a;
    double min_x = x;
    double min_f = function(x);

    while (step > epsilon) {

        

        // ����� ������ � ������� �����
        cout << "����� ������:\n\n";
        while (x + step <= b) {
            iter++;
            x += step;
            double current_f = function(x);
            cout << "�������� " << left << setw(4) << iter << " ���: " << left << setw(4) << step << " | x = " << left << setw(10) << x << " f(x) = " << left << setw(10) << current_f << "\n";
            if (current_f < min_f) {
                min_f = current_f;
                min_x = x;
            }
            else {
                break; // ������� ������ �������������
            }
        }

        // ���������� ����
        step /= 2;
        
        cout << "\n����� �����:\n\n";

        // ����� ����� � ����������� �����
        while (x - step >= a) {
            iter++;
            x -= step;
            double current_f = function(x);
            cout << "�������� " << left << setw(4) << iter << " ���: " << left << setw(4) << step << " | x = " << left << setw(10) << x << " f(x) = " << left << setw(10) << current_f << "\n";
            if (current_f < min_f) {
                min_f = current_f;
                min_x = x;
            }
            else {
                break; // ������� ������ �������������
            }
        }

        // ���������� ����
        step /= 2;

        cout << endl;
    }

    cout << "\n------------\n�������� - " << iter << endl;

    return min_x;
}

// ����� ��������� (�������� ����� �������� �������)
// a, b - ������� ���������, e - ��������, counter - ������� ��������
float dichotomy(float a, float b, float e) {
    iter++;
    float en = (b - a) / 2; // �������� �������� ���������
    float E = 0.02;
    if (en <= e) { // ������� ���������
        cout << "\n------------\n�������� - " << iter << "\nx = " << setw(15) << (a + b) / 2 << " f(x) = " << function((a + b) / 2);
        return 0;
    }
    float x1 = (a + b - E) / 2;
    float x2 = (a + b + E) / 2;

    cout << "�������� " << left << setw(4) << iter << "| a = " << setw(15) << left << a << " b = " << setw(15) << b << " x1 = " << setw(15) << x1
        << " x2 = " << setw(15) << x2 << " f(x1) = " << setw(15) << function(x1) << " f(x2) = " << setw(15) << function(x2) << endl;
    if (function(x1) <= function(x2)) {
        // ����� ������� �������� ��������� � �����
        dichotomy(a, x2, e); // ����������� ����� ��� ����� ����� ���������
    }
    else {
        dichotomy(x1, b, e); // ����������� ����� ��� ������ ����� ���������
    }
}

// ����� �������� ������� ��� ������ �������� �������
// a, b - ������� ���������, tol - ��������
// ���������� ��������� �������� x �������� �������
double goldenSectionSearch(double a, double b, double tol) {
    const double phi = (sqrt(5) - 1) / 2;  // ����������� �������� ������� (~0.618)

    double x1 = a + (1 - phi) * (b - a);
    double x2 = a + phi * (b - a);
    double f1 = function(x1);
    double f2 = function(x2);

    iter = 0; // �������� ������� ��������

    while (fabs(b - a) > tol) { // �������� ������� ��������
        iter++;
        cout << "�������� " << left << setw(4) << iter
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
    cout << "\n------------\n�������� - " << iter << endl;
    return (a + b) / 2; // ���������� ��������� �������� ��������
}


// ������� ��� ���������� �������� ������� ������� �����
double middle_point(double a, double b, double tol) {
    double ak = a; // ������ ���������
    double bk = b; // ����� ���������
    double xk;     // ������� ����� ���������
    iter = 0; // ������� ��������

    // ���������� ������ ��������, ���� ��� ����� �� ������ ������ 2*tol
    while ((bk - ak) / 2 > tol) {
        xk = (ak + bk) / 2; // ��������� ������� �����
        double df_xk = derivative(xk); // ��������� ����������� � ������� �����
        iter++;

        // ����� �������� �������� x, �������� ������� � ���������� ��������
        cout << "�������� " << left << setw(4) << iter << left << setw(5) << "| a = " << left << setw(15) << ak << "b = " << left << setw(15) << bk << "x = " << left << setw(15) << xk << "f'(x) = " << left << setw(15) << derivative(xk) << endl;

        // ���� ����������� ������ � ���� (� �������� ��������), ��������� �����
        if (abs(df_xk) < tol) {
            break;
        }

        // ���� ����������� �������������, ������� ��������� � ������ �������� ���������
        if (df_xk < 0) {
            ak = xk;
        }
        // ���� ����������� �������������, ������� ��������� � ����� �������� ���������
        else {
            bk = xk;
        }
    }
    cout << "\n------------\n�������� - " << iter << endl;
    // ���������� ������� ����� ���������� ��������� ��� ����������� � ����� ��������
    return (ak + bk) / 2;
}


double chord_method(double a, double b, double tol) {
    double x_tilda;
    iter = 0;
    if (derivative(a) < 0 && derivative(b) < 0) return b;
    if (derivative(a) > 0 && derivative(b) > 0) return a;
    while (fabs(b - a) > tol) {
        iter++; // ����������� ������� ��������
        // �������� �� ������� �� ����
        if (fabs(derivative(a) - derivative(b)) < 1e-9) {
            cerr << "������: ������� �� ���� ��� ���������� x_tilda" << endl;
            return (a + b) / 2;
        }

        // ��������� ����� ����� �� ������� ������ ����
        x_tilda = a - derivative(a) * (a - b) / (derivative(a) - derivative(b));

        cout << "�������� " << left << setw(4) << iter
            << " | a = " << left << setw(15) << a << " b = " << left << setw(15) << b << " x = " << left << setw(15) << x_tilda
            << "f'(x) = " << left << setw(15) << derivative(x_tilda)
            << "f(x) = " << left << setw(15) << function(x_tilda) << endl;

        // ��������� ������� ����������
        if (fabs(derivative(x_tilda)) <= tol) {
            return x_tilda;
        }

        // ���������� ����� �������� ������
        if (derivative(x_tilda) > 0) {
            b = x_tilda;
        }
        else {
            a = x_tilda;
        }
    }

    cout << "\n------------\n�������� - " << iter << endl;

    return (a + b) / 2; // ���������� �������� ����������� ���������
}

double newton_method(double x0, double tol) {
    double x = x0; 
    iter = 0; // �������� ������� ��������
    while (abs(derivative(x)) > tol) { // ��������� ������� ������ �� �����
        iter++;
        cout << "�������� " << left << setw(4) << iter
            << "| x = " << left << setw(15) << x << "f'(x) = " << left << setw(15) << derivative(x) << "f''(x) = " << left << setw(15) << second_derivative(x) << "f(x) = " << left << setw(15) << function(x) << endl; // ������� ��������
        if (fabs(second_derivative(x)) < 1e-9) { cout << "������ ����������� ������� ���� ��� ������� ������"; return -1; } // ������ �� ������� �� ����
        x = x - (derivative(x) / second_derivative(x)); // ��������� ��������� �������� x
        
    }
    return x; // ���������� ��������� ��������� ��������
}

int menu(double a, double b, double tol) { // ������� ��� ������ ����
    cout << "����� ��������� -> 1\n����� �������� ������� -> 2\n����� ������������ ������ -> 3\n����� ������� ����� -> 4\n����� ���� -> 5\n����� ������� -> 6\n\n��� ����� ������ ������ ���������� ��� �������� ������� ����� ������ ��������\n";
    int c;
    cin >> c;
    cin.ignore();
    double min_x = 0;
    switch (c) {
    case 1:
        system("cls");
        cout << "����� ���������\n\n";
        dichotomy(a, b, tol);
        cout << "\n";
        system("pause");
        system("cls");
        menu(a, b, tol);
        break;
    case 2:
        system("cls");
        cout << "����� �������� �������\n\n";
        min_x = goldenSectionSearch(a, b, tol);
        cout << "x = " << setw(15) << min_x << " f(x) = " << setw(10) << function(min_x) << endl;
        system("pause");
        system("cls");
        menu(a, b, tol);
        break;
    case 3:
        system("cls");
        cout << "����� ������������ ������\n\n";
        min_x = bitwiseSearch(a, b, tol);
        cout << "x = " << setw(15) << min_x << " f(x) = " << setw(10) << function(min_x) << endl;
        system("pause");
        system("cls");
        menu(a, b, tol);
        break;
    case 4:
        system("cls");
        cout << "����� ������� �����\n\n";
        min_x = middle_point(a, b, tol);
        cout << "x = " << setw(15) << min_x << " f(x) = " << setw(10) << function(min_x) << endl;
        system("pause");
        system("cls");
        menu(a, b, tol);
        break;
    case 5:
        system("cls");
        cout << "����� ����\n\n";
        min_x = chord_method(a, b, tol);
        cout << "x = " << left << setw(15) << min_x << " f(x) = " << left << setw(10) << function(min_x) << endl;
        system("pause");
        system("cls");
        menu(a, b, tol);
        break;
    case 6:
        system("cls");
        int x0;
        cout << "������� ��������� �����������: ";
        cin >> x0;
        system("cls");
        cout << "����� �������\n\n";
        min_x = newton_method(x0, tol);
        cout << "x = " << left << setw(15) << min_x << " f(x) = " << left << setw(10) << function(min_x) << endl;
        system("pause");
        system("cls");
        menu(a, b, tol);
        break;
    default: // ���� ����� ������ �������� ������� ���������� -1
        return -1;
    }
}

int main() {
    setlocale(LC_ALL, "RU"); // ������������� ������� �����������
    system("cls");
    double a, b; // �������� ������ ��������
    double tol; // ��������
    // ���� ������ � �������� � ����������
    cout << "������� ����� �������: ";
    cin >> a;
    cout << "������� ������ �������: ";
    cin >> b;
    cout << "������� ������ ��������: ";
    cin >> tol;
    cin.ignore();
    system("cls");
    int temp = menu(a, b, tol); // ������� � ����, ���������� ����� �������� ��� �������
    if (temp == -1) main(); // ���� ������� ���� ������� -1, �� ������ ������� � main � ������ ������������ ������ ������ �������
    return 0;
}
