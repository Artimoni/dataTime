#include "dataTime.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <limits>

DateTime::DateTime() : year(1970), month(1), day(1), hour(0), minute(0), second(0) {}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second) :
    year(year), month(month), day(day), hour(hour), minute(minute), second(second) {}

void DateTime::inputDate() {
    char dot1, dot2;
    std::cout << "Введите дату в формате дд.мм.гггг: ";
    std::cin >> std::ws;
    if (!(std::cin >> day >> dot1 >> month >> dot2 >> year) || dot1 != '.' || dot2 != '.') {
        std::cout << "Неверный формат даты" << std::endl;
        year = 1970;
        month = 1;
        day = 1;
        hour = 0;
        minute = 0;
        second = 0;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cout << "Введите час: ";
    if (!(std::cin >> hour)) {
        std::cout << "Неверное значение часа!" << std::endl;
        hour = 0;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Введите минуту: ";
    if (!(std::cin >> minute)) {
        std::cout << "Неверное значение минуты!" << std::endl;
        minute = 0;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Введите секунду: ";
    if (!(std::cin >> second)) {
        std::cout << "Неверное значение секунды" << std::endl;
        second = 0;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (!isValidDate()) {
        std::cout << "Неправильная дата" << std::endl;
        year = 1970;
        month = 1;
        day = 1;
        hour = 0;
        minute = 0;
        second = 0;
    }
}

void DateTime::inputISODate() {
    std::string isoDate;
    std::cout << "Введите дату в формате yyyy-MM-ddThh:mm:ss: ";
    std::cin >> isoDate;

    if (isoDate.length() != 19 || isoDate[4] != '-' || isoDate[7] != '-' || isoDate[10] != 'T' || isoDate[13] != ':' || isoDate[16] != ':') {
        std::cout << "Неправильный формат даты" << std::endl;
        year = 1970;
        month = 1;
        day = 1;
        hour = 0;
        minute = 0;
        second = 0;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    try {
        year = std::stoi(isoDate.substr(0, 4));
        month = std::stoi(isoDate.substr(5, 2));
        day = std::stoi(isoDate.substr(8, 2));
        hour = std::stoi(isoDate.substr(11, 2));
        minute = std::stoi(isoDate.substr(14, 2));
        second = std::stoi(isoDate.substr(17, 2));
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка преобразования даты: " << e.what() << std::endl;
        year = 1970;
        month = 1;
        day = 1;
        hour = 0;
        minute = 0;
        second = 0;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    if (!isValidDate()) {
        std::cout << "Неправильная дата" << std::endl;
        year = 1970;
        month = 1;
        day = 1;
        hour = 0;
        minute = 0;
        second = 0;
    }
}

void DateTime::printDate(int format) const {
    std::string time = " " + std::to_string(hour) + ":" + (minute < 10 ? "0" : "") + std::to_string(minute) + ":" + (second < 10 ? "0" : "") + std::to_string(second);
    switch (format) {
    case 1:
        std::cout << std::setw(2) << std::setfill('0') << day << "."
            << std::setw(2) << std::setfill('0') << month << "." << year << time << std::endl;
        break;
    case 2: {
        const char* monthNames[] = { "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь",
                                     "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь" };
        std::cout << day << " " << monthNames[month - 1] << " " << year << time << std::endl;
        break;
    }
    case 3:
        std::cout << std::setw(2) << std::setfill('0') << day << "."
            << std::setw(2) << std::setfill('0') << month << "." << (year % 100) << time << std::endl;
        break;
    default:
        std::cout << "Неправильный формат" << std::endl;
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
        throw std::runtime_error("Не удалось преобразовать");
    }
    return std::chrono::system_clock::from_time_t(tt);
}

int DateTime::daysBetween(const DateTime& other) const {
    try {
        auto timePoint1 = toTimePoint(year, month, day, 0, 0, 0); // Игнорируем время для подсчёта дней
        auto timePoint2 = toTimePoint(other.year, other.month, other.day, 0, 0, 0);

        auto duration = std::chrono::duration_cast<std::chrono::duration<int, std::ratio<3600 * 24>>>(timePoint2 - timePoint1);
        return duration.count();
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка вычисления: " << e.what() << std::endl;
        return 0;
    }
}

std::string DateTime::dayOfWeek() const {
    if (!isValidDate()) {
        return "Ошибка: некорректная дата";
    }

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
        return "Ошибка вычисления дня недели";
    }

    std::tm* local = localtime(&tt);
    if (local == nullptr) {
        return "Ошибка: не удалось определить день недели";
    }

    int weekday = local->tm_wday;
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

std::string DateTime::toISOString() const {
    std::stringstream ss;
    ss << std::setw(4) << std::setfill('0') << year << "-"
        << std::setw(2) << std::setfill('0') << month << "-"
        << std::setw(2) << std::setfill('0') << day << "T"
        << std::setw(2) << std::setfill('0') << hour << ":"
        << std::setw(2) << std::setfill('0') << minute << ":"
        << std::setw(2) << std::setfill('0') << second;
    return ss.str();
}

void DateTime::setTime(int hour, int minute, int second) {
    if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59) {
        this->hour = hour;
        this->minute = minute;
        this->second = second;
    }
    else {
        std::cout << "Неправильное время" << std::endl;
    }
}

void DateTime::addSeconds(int seconds) {
    try {
        auto timePoint = toTimePoint(year, month, day, hour, minute, second);
        timePoint += std::chrono::seconds(seconds);

        std::time_t tt = std::chrono::system_clock::to_time_t(timePoint);
        std::tm* t = std::localtime(&tt);

        year = t->tm_year + 1900;
        month = t->tm_mon + 1;
        day = t->tm_mday;
        hour = t->tm_hour;
        minute = t->tm_min;
        second = t->tm_sec;

        if (!isValidDate()) {
            std::cout << "Результат выходит за допустимые пределы" << std::endl;
            year = 1970;
            month = 1;
            day = 1;
            hour = 0;
            minute = 0;
            second = 0;
        }
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка добавления секунд: " << e.what() << std::endl;
        year = 1970;
        month = 1;
        day = 1;
        hour = 0;
        minute = 0;
        second = 0;
    }
}

DateTime DateTime::easterDate() const {
    int year = this->year;
    int a = year % 19;
    int b = year / 100;
    int c = year % 100;
    int d = b / 4;
    int e = b % 4;
    int f = (b + 8) / 25;
    int g = (b - f + 1) / 3;
    int h = (19 * a + b - d - g + 15) % 30;
    int i = c / 4;
    int k = c % 4;
    int l = (32 + 2 * e + 2 * i - h - k) % 7;
    int m = (a + 11 * h + 22 * l) / 451;
    int month = (h + l - 7 * m + 114) / 31;
    int day = ((h + l - 7 * m + 114) % 31) + 1;

    DateTime easter(year, month, day);
    if (!easter.isValidDate()) {
        std::cout << "Ошибка вычисления даты Пасхи" << std::endl;
        return DateTime(1970, 1, 1);
    }
    return easter;
}