#ifndef USER_H
#define USER_H

#include "Activity.h"
#include <vector>
#include <utility>

class User {
    std::vector<std::pair<Activity, int>> activities;
public:
    void addActivity(const Activity &activity, int frequency);
    double calculateTotalWaterFootprint() const;
};

#endif
