#include "datatime.h"
#include <iostream>

int main() {
    setlocale(LC_ALL, "Russian");
    DateTime today(2025, 3, 10, 14, 30, 32);
    std::cout << "Сегодня: ";
    today.printDate(2);
    std::cout << "День недели: " << today.dayOfWeek() << std::endl;

    DateTime tomorrow(2025, 3, 11);
    std::cout << "Завтра: ";
    tomorrow.printDate(2);
    std::cout << "Дней между сегодня и завтра: " << today.daysBetween(tomorrow) << std::endl;
    //invalidDate
    return 0;
}