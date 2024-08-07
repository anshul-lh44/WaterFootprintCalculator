#ifndef WATERFOOTPRINTCALCULATOR_H
#define WATERFOOTPRINTCALCULATOR_H

#include <vector>
#include "User.h"
#include "Activity.h"
#include <iostream>

class WaterFootprintCalculator {
public:
    WaterFootprintCalculator();
    void run();

private:
    void displayMenu() const;
    void collectFrequencies();
    void addUserActivities(User &user);
    double estimateWaterUsage(const std::string &activityName) const;
    void calculateFootprint(const User &user) const;

    std::vector<Activity> activityList;
    std::vector<int> frequencies;
};
#endif