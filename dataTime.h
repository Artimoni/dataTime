#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
#include <string>
#include <chrono>

class DateTime {
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

public:
    DateTime();
    DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);

    void inputDate();
    void printDate(int format) const;
    int daysBetween(const DateTime& other) const;
    std::string dayOfWeek() const;
    bool isValidDate() const;
    void setTime(int hour, int minute, int second);

    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    //геттеры/пасха
};

#endif