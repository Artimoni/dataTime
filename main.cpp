#include "dataTime.h"
#include <iostream>
#ifdef _WIN64
#include <windows.h> 
#endif

int main() {
#ifdef _WIN64
    SetConsoleOutputCP(CP_UTF8); 
    SetConsoleCP(CP_UTF8); 
#endif

    DateTime today(2025, 3, 10, 14, 30, 32);
    std::cout << "Сегодня: ";
    today.printDate(2);
    std::cout << "Формат ISO: " << today.toISOString() << std::endl;
    std::cout << "День недели: " << today.dayOfWeek() << std::endl;

    DateTime tomorrow(2025, 3, 11);
    std::cout << "Завтра: ";
    tomorrow.printDate(2);
    std::cout << "Дней между сегодня и завтра: " << today.daysBetween(tomorrow) << std::endl;

    DateTime invalidDate(2025, 2, 30);
    std::cout << "Дата invalidDate корректна? " << (invalidDate.isValidDate() ? "Да" : "Нет") << std::endl;

    DateTime userDate;
    std::cout << "Введите дату в формате дд.мм.гггг: " << std::endl;
    userDate.inputDate();
    std::cout << "Вы ввели (формат 1): ";
    userDate.printDate(1);

    std::cout << "Введите дату в формате ISO: " << std::endl;
    userDate.inputISODate();
    std::cout << "Вы ввели (формат 2): ";
    userDate.printDate(2);

    std::cout << "Установка времени 15:45:20 для today: ";
    today.setTime(15, 45, 20);
    today.printDate(1);

    std::cout << "Добавление 3600 секунд (1 час) к today: ";
    today.addSeconds(3600);
    today.printDate(1);

    DateTime easter2025(2025, 1, 1);
    DateTime easterDate2025 = easter2025.easterDate();
    std::cout << "Дата Пасхи 2025: ";
    easterDate2025.printDate(2);

    return 0;
}