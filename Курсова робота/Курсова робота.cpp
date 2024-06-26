#include <iostream>
#include <Windows.h>
#include<fstream>
#include<algorithm>
#include<string>
#include <vector>
#include <ctime>
using namespace std;

struct Spiv {
    string pib;
    string posad;
    string phone;
    string email;
};

struct Avto {
    string nazva;
    int rik;
    string model;
    double vart;
    double cina;
};

struct Date {
    int day;
    int month;
    int year;
};

struct Prod {
    Spiv spiv;
    Avto avto;
    Date date;
    double real;

};
vector<Spiv> spivs;
vector<Avto> avtos;
vector<Prod> prods;

void addSpiv(const Spiv& spiv) {
    spivs.push_back(spiv);
}

void removeSpiv(const string& name) {
    spivs.erase(remove_if(spivs.begin(), spivs.end(),[&](const Spiv& e) { return e.pib == name; }),spivs.end());
}
void addAvto(const Avto& car) {
    avtos.push_back(car);
}
void removeAvto(const string& model) {
    avtos.erase(remove_if(avtos.begin(), avtos.end(),[&](const Avto& c) { return c.model == model; }),avtos.end());
}
void addProd(const Prod& prod) {
    prods.push_back(prod);
}
void removeProd(int index) {
    if (index >= 0 && index < prods.size()) {
        prods.erase(prods.begin() + index);
    }
}
void printSpiv() {
    for (const auto& spiv : spivs) {
        cout << "ПІБ: " << spiv.pib << endl;
        cout << "Посада: " << spiv.posad << endl;
        cout << "Телефон: " << spiv.phone << endl;
        cout << "Email: " << spiv.email << endl << endl;
    }
}

void printAvto() {
    for (const auto& avto : avtos) {
        cout << "Назва виробника: " << avto.nazva << endl;
        cout << "Рік випуску: " << avto.rik << endl;
        cout << "Модель: " << avto.model << endl;
        cout << "Собівартість: " << avto.vart << endl;
        cout << "Потенційна ціна продажу: " << avto.cina << endl << endl;
    }
}

void printProd() {
    for (const auto& prod : prods) {
        cout << "Співробітник: " << prod.spiv.pib << endl;
        cout << "Автомобіль: " << prod.avto.nazva << " " << prod.avto.model << endl;
        cout << "Дата продажу: " << prod.date.day << "-" << prod.date.month << "-" << prod.date.year << endl;
        cout << "Реальна ціна продажу: " << prod.real << endl << endl;
    }
}

void printProdByDate(const Date& date) {
    for (const auto& prod : prods) {
        if (prod.date.day == date.day && prod.date.month == date.month && prod.date.year == date.year) {
            cout << "Співробітник: " << prod.spiv.pib << endl;
            cout << "Aвтомобіль: " << prod.avto.nazva << " " << prod.avto.model << endl;
            cout << "Дата продажу: " << prod.date.day << "-" << prod.date.month << "-" << prod.date.year << endl;
            cout << "Реальна ціна продажу: " << prod.real << endl << endl;
        }
    }
}

void printProdByPeriod(const Date& startDate, const Date& endDate) {
    for (const auto& prod : prods) {
        if ((prod.date.year > startDate.year ||
            (prod.date.year == startDate.year && prod.date.month > startDate.month) ||
            (prod.date.year == startDate.year && prod.date.month == startDate.month && prod.date.day >= startDate.day)) &&
            (prod.date.year < endDate.year ||
            (prod.date.year == endDate.year && prod.date.month < endDate.month) ||
            (prod.date.year == endDate.year && prod.date.month == endDate.month && prod.date.day <= endDate.day))) {
            cout << "Співробітник: " << prod.spiv.pib << endl;
            cout << "Aвтомобіль: " << prod.avto.nazva << " " << prod.avto.model << endl;
            cout << "Дата продажу: " << prod.date.day << "-" << prod.date.month << "-" << prod.date.year << endl;
            cout << "Реальна ціна продажу: " << prod.real << endl << endl;
        }
    }
}

void printProdBySpiv(const string& spivPib) {
    for (const auto& prod : prods) {
        if (prod.spiv.pib == spivPib) {
            cout << "Співробітник: " << prod.spiv.pib << endl;
            cout << "Aвтомобіль: " << prod.avto.nazva << " " << prod.avto.model << endl;
            cout << "Дата продажу: " << prod.date.day << "-" << prod.date.month << "-" << prod.date.year << endl;
            cout << "Реальна ціна продажу: " << prod.real << endl << endl;
        }
    }
}

void printMostPopularAvto(const Date& startDate, const Date& endDate) {
    vector < pair < string, int >> avtoCount;
    for (const auto& prod : prods) {
        if ((prod.date.year > startDate.year ||
            (prod.date.year == startDate.year && prod.date.month > startDate.month) ||
            (prod.date.year == startDate.year && prod.date.month == startDate.month && prod.date.day >= startDate.day)) &&
            (prod.date.year < endDate.year ||
            (prod.date.year == endDate.year && prod.date.month < endDate.month) ||
            (prod.date.year == endDate.year && prod.date.month == endDate.month && prod.date.day <= endDate.day))) {
            string avtoName = prod.avto.nazva + " " + prod.avto.model;
            bool found = false;
            for (auto& pair : avtoCount) {
                if (pair.first == avtoName) {
                    pair.second++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                avtoCount.push_back(make_pair(avtoName, 1));
            }
        }
    }

    string mostPopularAvto;
    int maxCount = 0;
    for (const auto& pair : avtoCount) {
        if (pair.second > maxCount) {
            mostPopularAvto = pair.first;
            maxCount = pair.second;
        }
    }

    if (!mostPopularAvto.empty()) {
        cout << "Найпопулярніший автомобіль: " << mostPopularAvto << " з " << maxCount << " продажами" << endl;
    }
    else {
        cout << "Продажі автомобілів за вказаний період не здійснювалися" << endl;
    }
}

void printTopSpiv(const Date& startDate, const Date& endDate) {
    vector<pair<string, double>> spivSales;

    for (const auto& prod : prods) {
        if ((prod.date.year > startDate.year ||
            (prod.date.year == startDate.year && prod.date.month > startDate.month) ||
            (prod.date.year == startDate.year && prod.date.month == startDate.month && prod.date.day >= startDate.day)) &&
            (prod.date.year < endDate.year ||
            (prod.date.year == endDate.year && prod.date.month < endDate.month) ||
            (prod.date.year == endDate.year && prod.date.month == endDate.month && prod.date.day <= endDate.day))) {

            string spivName = prod.spiv.pib;
            double profit = prod.real - prod.avto.vart;
            bool found = false;
            for (auto& pair : spivSales) {
                if (pair.first == spivName) {
                    pair.second += profit;
                    found = true;
                    break;
                }
            }
            if (!found) {
                spivSales.push_back(make_pair(spivName, profit));
            }
        }
    }

    string topSpiv;
    double maxProfit = 0;
    for (const auto& pair : spivSales) {
        if (pair.second > maxProfit) {
            topSpiv = pair.first;
            maxProfit = pair.second;
        }
    }

    if (!topSpiv.empty()) {
        cout << "Найкращий співробітник: " << topSpiv << " з прибутком у розмірі " << maxProfit << endl;
    }
    else {
        cout << "Немає продажів за вказаний період" << endl;
    }
}

void printTotalProfit(const Date& startDate, const Date& endDate) {
    double totalProfit = 0;
    for (const auto& prod : prods) {
        if ((prod.date.year > startDate.year ||
            (prod.date.year == startDate.year && prod.date.month > startDate.month) ||
            (prod.date.year == startDate.year && prod.date.month == startDate.month && prod.date.day >= startDate.day)) &&
            (prod.date.year < endDate.year ||
            (prod.date.year == endDate.year && prod.date.month < endDate.month) ||
            (prod.date.year == endDate.year && prod.date.month == endDate.month && prod.date.day <= endDate.day))) {
            totalProfit += prod.real - prod.avto.vart;
        }
    }

    cout << "Загальний прибуток: " << totalProfit << endl;
}


void saveDataToFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << spivs.size() << endl;
        for (const auto& spiv : spivs) {
            file << spiv.pib << endl << spiv.posad << endl << spiv.phone << endl << spiv.email << endl;
        }

        file << avtos.size() << endl;
        for (const auto& avto : avtos) {
            file << avto.nazva << endl << avto.rik << endl << avto.model << endl << avto.vart << endl << avto.cina << endl;
        }

        file << prods.size() << endl;
        for (const auto& prod : prods) {
            file << prod.spiv.pib << endl << prod.spiv.posad << endl << prod.spiv.phone << endl << prod.spiv.email << endl
                << prod.avto.nazva << endl << prod.avto.rik << endl << prod.avto.model << endl << prod.avto.vart << endl << prod.avto.cina << endl
                << prod.real << endl << prod.date.day << "-" << prod.date.month << "-" << prod.date.year << endl
                << printTotalProfit << endl << printTopSpiv << endl << printMostPopularAvto << endl << printProdBySpiv << endl << printProdByPeriod << endl << printProdByDate << endl;
        }
        file.close();
    }
}

void loadDataFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        int count;

        file >> count;
        file.ignore();
        spivs.clear();
        for (int i = 0; i < count; ++i) {
            Spiv spiv;
            getline(file, spiv.pib);
            getline(file, spiv.posad);
            getline(file, spiv.phone);
            getline(file, spiv.email);
            spivs.push_back(spiv);
        }

        file >> count;
        file.ignore();
        avtos.clear();
        for (int i = 0; i < count; ++i) {
            Avto avto;
            getline(file, avto.nazva);
            file >> avto.rik;
            file.ignore();
            getline(file, avto.model);
            file >> avto.vart >> avto.cina;
            file.ignore();
            avtos.push_back(avto);
        }

        file >> count;
        file.ignore();
        prods.clear();
        for (int i = 0; i < count; ++i) {
            Prod prod;
            getline(file, prod.spiv.pib);
            getline(file, prod.avto.nazva);
            file >> prod.avto.rik;
            file.ignore();
            getline(file, prod.avto.model);
            file >> prod.real;
            file >> prod.date.day >> prod.date.month >> prod.date.year;
            file.ignore();
            prods.push_back(prod);
        }
        file.close();
    }
}

Date inputDate() {
    Date date;
    cout << "Введіть дату продажу (DD ММ YYY): ";
    cin >> date.day >> date.month >> date.year;
    cin.ignore();
    return date;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;
    do {
        cout << "\nОблік продажу автомобілів в автосалоні\n";
        cout << "1. Додати співробітника\n";
        cout << "2. Видалити співробітника\n";
        cout << "3. Додати авто\n";
        cout << "4. Видалити авто\n";
        cout << "5. Додати продажі\n";
        cout << "6. Видалити продажі\n";
        cout << "7. Показати всіх співробітників\n";
        cout << "8. Показати всі авто\n";
        cout << "9. Показаті всі продажі\n";
        cout << "10. Показати продажі за датою\n";
        cout << "11. Показати продажі за періодами\n";
        cout << "12. Show Sales by Employee\n";
        cout << "13. Показати продажі за співробітниками\n";
        cout << "14. Показати найкращих працівників за періодами\n";
        cout << "15. Показати загальний прибуток за періодами\n";
        cout << "16. Збереження даних у файл\n";
        cout << "17. Завантаження даних із файлу\n";
        cout << "18. Завершення роботи\n";
        cout << "Введіть свій вибір: ";
        cin >> choice;
        cin.ignore();
        cout << endl;

        switch (choice) {
        case 1: {
            Spiv spiv;
            cout << "Введіть ПІБ співробітника: ";
            getline(cin, spiv.pib);
            cout << "Введіть посаду співробітника: ";
            getline(cin, spiv.posad);
            cout << "Введіть телефон співробітника: ";
            getline(cin, spiv.phone);
            cout << "Введіть email співробітника: ";
            getline(cin, spiv.email);
            addSpiv(spiv);
            break;
        }
        case 2: {
            string name;
            cout << "Введіть ім'я співробітника, якого потрібно видалити: ";
            getline(cin, name);
            removeSpiv(name);
            break;
        }
        case 3: {
            Avto avto;
            cout << "Введіть виробника автомобіля: ";
            getline(cin, avto.nazva);
            cout << "Введіть рік випуску автомобіля: ";
            cin >> avto.rik;
            cin.ignore();
            cout << "Введіть модель автомобіля: ";
            getline(cin, avto.model);
            cout << "Введіть вартість автомобіля: ";
            cin >> avto.vart;
            cout << "Введіть потенційну ціну продажу автомобіля: ";
            cin >> avto.cina;
            cin.ignore();
            addAvto(avto);
            break;
        }
        case 4: {
            string model;
            cout << "Введіть модель автомобіля для видалення: ";
            getline(cin, model);
            removeAvto(model);
            break;
        }
        case 5: {
            Prod prod;
            cout << "Введіть ПІБ співробітника: ";
            getline(cin, prod.spiv.pib);
            cout << "Введіть виробника автомобіля: ";
            getline(cin, prod.avto.nazva);
            cout << "Введіть рік випуску автомобіля для продажу: ";
            cin >> prod.avto.rik;
            cin.ignore();
            cout << "Введіть модель автомобіля для продажу: ";
            getline(cin, prod.avto.model);
            cout << "Введіть реальну ціну продажу: ";
            cin >> prod.real;
            cin.ignore();
            prod.date = inputDate();
            addProd(prod);
            break;
        }
        case 6: {
            int index;
            cout << "Введіть індекс продажу, щоб видалити: ";
            cin >> index;
            cin.ignore();
            removeProd(index);
            break;
        }
        case 7:
            printSpiv();
            break;
        case 8:
            printAvto();
            break;
        case 9:
            printProd();
            break;
        case 10: {
            Date date = inputDate();
            printProdByDate(date);
            break;
        }
        case 11: {
            Date startDate, endDate;
            cout << "Введіть дату початку (DD MM YYYY): ";
            cin >> startDate.day >> startDate.month >> startDate.year;
            cout << "Введіть дату кінця (DD MM YYYY): ";
            cin >> endDate.day >> endDate.month >> endDate.year;
            printProdByPeriod(startDate, endDate);
            break;
        }
        case 12: {
            string spivName;
            cout << "Введіть ім'я співробітника, щоб переглянути продажі: ";
            getline(cin, spivName);
            printProdBySpiv(spivName);
            break;
        }
        case 13: {
            Date startDate, endDate;
            cout << "Введіть дату початку (DD MM YYYY): ";
            cin >> startDate.day >> startDate.month >> startDate.year;
            cout << "Введіть дату кінця (DD MM YYYY): ";
            cin >> endDate.day >> endDate.month >> endDate.year;
            printMostPopularAvto(startDate, endDate);
            break;
        }
        case 14: {
            Date startDate, endDate;
            cout << "Введіть дату початку (DD MM YYYY): ";
            cin >> startDate.day >> startDate.month >> startDate.year;
            cout << "Введіть дату кінця (DD MM YYYY): ";
            cin >> endDate.day >> endDate.month >> endDate.year;
            printTopSpiv(startDate, endDate);
            break;
        }
        case 15: {
            Date startDate, endDate;
            cout << "Введіть дату початку (DD MM YYYY): ";
            cin >> startDate.day >> startDate.month >> startDate.year;
            cout << "Введіть дату кінця (DD MM YYYY): ";
            cin >> endDate.day >> endDate.month >> endDate.year;
            printTotalProfit(startDate, endDate);
            break;
        }
        case 16: {
            string filename;
            cout << "Введіть ім'я файлу для збереження даних: ";
            getline(cin, filename);
            saveDataToFile(filename);
            break;
        }
        case 17: {
            string filename;
            cout << "Введіть ім'я файлу для завантаження даних: ";
            getline(cin, filename);
            loadDataFromFile(filename);
            break;
        }
        case 18:
            cout << "До побачення\n";
            break;
        default:
            cout << "Неправильний вибір! Спробуйте ще раз.\n";
            break;
        }
    } while (choice != 18);

    return 0;

    

}

