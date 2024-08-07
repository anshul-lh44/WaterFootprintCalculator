#ifndef ACTIVITY_H
#define ACTIVITY_H
#include <string>

class Activity{
    std::string name;
    double waterUsage;
public:
    Activity(const std::string &name, double waterUsage = 0);
    void setWaterUsage(double waterUsage);
    std::string getName() const;
    double getWaterUsage() const;
};

#endif 
