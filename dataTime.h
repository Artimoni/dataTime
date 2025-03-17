#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <limits> 

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
    void inputISODate();
    void printDate(int format) const;
    int daysBetween(const DateTime& other) const;
    std::string dayOfWeek() const;
    bool isValidDate() const;
    std::string toISOString() const;
    void setTime(int hour, int minute, int second);
    void addSeconds(int seconds);
    DateTime easterDate() const;

    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    int getSecond() const { return second; }
};

std::chrono::system_clock::time_point toTimePoint(int year, int month, int day, int hour, int minute, int second);

#endif