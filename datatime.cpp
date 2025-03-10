#include "dataTime.h"
#include <ctime>
#include <sstream>
#include <iomanip>

DateTime::DateTime() : year(1970), month(1), day(1), hour(0), minute(0), second(0) {}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second) :
    year(year), month(month), day(day), hour(hour), minute(minute), second(second) {}

void DateTime::inputDate() {
    char dot1, dot2;
    std::cout << "Введите дату в формате дд.мм.гггг: ";
    std::cin >> day >> dot1 >> month >> dot2 >> year;
    std::cout << "Введите час: ";
    std::cin >> hour;
    std::cout << "Введите минуту: ";
    std::cin >> minute;
    std::cout << "Введите секунду: ";
    std::cin >> second;

    if (dot1 != '.' || dot2 != '.' || !isValidDate()) {
        std::cout << "Неверный формат даты!" << std::endl;
        year = 1970;
        month = 1;
        day = 1;
        hour = 0;
        minute = 0;
        second = 0;
    }
}

void DateTime::printDate(int format) const {
    switch (format) {
    case 1:
        std::cout << std::setw(2) << std::setfill('0') << day << "."
                  << std::setw(2) << std::setfill('0') << month << "." << year << std::endl;
        break;
    case 2: {
        const char* monthNames[] = { "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь",
                                   "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь" };
        std::cout << day << " " << monthNames[month - 1] << " " << year << std::endl;
        break;
    }
    //дд.мм.гг
    default:
        std::cout << "Неверный формат" << std::endl;
    }
}

std::chrono::system_clock::time_point toTimePoint(int year, int month, int day, int hour, int minute, int second) {
    std::tm t{};
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = second;
    t.tm_isdst = -1;

    std::time_t tt = mktime(&t);
    if (tt == -1) {
        throw std::runtime_error("Failed to convert to time_t");
    }
    return std::chrono::system_clock::from_time_t(tt);
}

int DateTime::daysBetween(const DateTime& other) const {
    auto timePoint1 = toTimePoint(year, month, day, hour, minute, second);
    auto timePoint2 = toTimePoint(other.year, other.month, other.day, other.hour, other.minute, other.second);

    std::chrono::duration<int, std::ratio<3600 * 24>> duration = 
        std::chrono::duration_cast<std::chrono::duration<int, std::ratio<3600 * 24>>>(timePoint2 - timePoint1);
    return duration.count();
}

std::string DateTime::dayOfWeek() const {
    std::tm t{};
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = second;
    t.tm_isdst = -1;
    std::time_t tt = mktime(&t);

    if (tt == -1) {
        return "Ошибка";
    }
    localtime(&tt); //Ошибка
    int weekday = t.tm_wday;

    std::string dayNames[] = { "Воскресенье", "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота" };
    return dayNames[weekday];
}

bool DateTime::isValidDate() const {
    if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31 ||
        hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59) {
        return false;
    }

    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        daysInMonth[2] = 29;
    }
    return day <= daysInMonth[month];
}

void DateTime::setTime(int hour, int minute, int second) {
    if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59) {
        this->hour = hour;
        this->minute = minute;
        this->second = second;
    } else {
        std::cout << "Неверное время" << std::endl;
    }
}

//ISO, addSeconds, easterDate 