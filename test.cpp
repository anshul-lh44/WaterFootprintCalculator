#include "Activity.h"

Activity::Activity(const std::string &name, double waterUsage)
    : name(name), waterUsage(waterUsage) {}

void Activity::setWaterUsage(double waterUsage) {
    this->waterUsage = waterUsage;
}

std::string Activity::getName() const {
    return name;
}

double Activity::getWaterUsage() const {
    return waterUsage;
}
#include "User.h"

void User::addActivity(const Activity &activity, int frequency) {
    activities.push_back(std::make_pair(activity, frequency));
}

double User::calculateTotalWaterFootprint() const {
    double totalFootprint = 0;
    for (const auto &activity : activities) {
        totalFootprint += activity.first.getWaterUsage() * activity.second;
    }
    return totalFootprint;
}
#include "WaterFootprintCalculator.h"

WaterFootprintCalculator::WaterFootprintCalculator() {
    activityList.push_back(Activity("Taking a bath"));
    activityList.push_back(Activity("Bathroom sink"));
    activityList.push_back(Activity("Cooking and Drinking"));
    activityList.push_back(Activity("Laundry"));
    activityList.push_back(Activity("Dishwashing"));
}

void WaterFootprintCalculator::run() {
    User user;
    int choice;

    while (true) {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                collectFrequencies();
                addUserActivities(user);
                break;
            case 2:
                calculateFootprint(user);
                break;
            case 3:
                std::cout << "Exiting...\n";
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

void WaterFootprintCalculator::displayMenu() const {
    std::cout << "\n******** MENU ********\n"
              << "1. Add Activities\n"
              << "2. Calculate Water Footprint\n"
              << "3. Exit\n"
              << "************************\n";
}

void WaterFootprintCalculator::collectFrequencies() {
    int frequency;
    frequencies.clear();

    for (size_t i = 0; i < activityList.size(); ++i) {
        std::cout << "Enter the frequency per week for " << activityList[i].getName() << ": ";
        std::cin >> frequency;

        if (frequency < 0) {
            std::cout << "Invalid frequency. Please enter a non-negative number.\n";
            --i; // Repeat this iteration
        } else {
            frequencies.push_back(frequency);
        }
    }
}

void WaterFootprintCalculator::addUserActivities(User &user) {
    for (size_t i = 0; i < activityList.size(); ++i) {
        double waterUsage = estimateWaterUsage(activityList[i].getName());
        activityList[i].setWaterUsage(waterUsage);

        user.addActivity(activityList[i], frequencies[i]);
    }

    std::cout << "Activities added successfully!\n";
}

double WaterFootprintCalculator::estimateWaterUsage(const std::string &activityName) const {
    double waterUsage = 0;

    if (activityName == "Taking a bath") {
        int choice, minutes;
        std::cout << "Do you use a bucket(1) or shower(2) for taking a bath? ";
        std::cin >> choice;
        if (choice == 1) {
            waterUsage = 10; // Example: 10 liters per bucket bath
        } else if (choice == 2) {
            std::cout << "How long do you bathe for? (in minutes) ";
            std::cin >> minutes;
            if (minutes < 0) {
                std::cout << "Invalid duration. Please enter a non-negative number.\n";
                return 0;
            }
            waterUsage = minutes * 9; // Example: 9 liters per minute shower
        } else {
            std::cout << "Invalid choice!\n";
            return 0;
        }
    } else if (activityName == "Bathroom sink") {
        int minutes;
        std::cout << "How long do you leave the sink running? (in minutes) ";
        std::cin >> minutes;
        if (minutes < 0) {
            std::cout << "Invalid duration. Please enter a non-negative number.\n";
            return 0;
        }
        waterUsage = minutes * 10; // Example: 10 liters per minute
    } else if (activityName == "Cooking and Drinking") {
        int mealsPerDay, litersDrinking;
        std::cout << "How many meals do you have in a day? ";
        std::cin >> mealsPerDay;
        if (mealsPerDay < 0) {
            std::cout << "Invalid number of meals. Please enter a non-negative number.\n";
            return 0;
        }
        std::cout << "How many liters of water do you drink per day? ";
        std::cin >> litersDrinking;
        if (litersDrinking < 0) {
            std::cout << "Invalid amount of water. Please enter a non-negative number.\n";
            return 0;
        }
        waterUsage = (mealsPerDay * 7) + (litersDrinking * 7); // Example: water for meals and drinking per week
    } else if (activityName == "Laundry") {
        int choice, bucketCount, loadCount;
        std::cout << "Do you do the laundry by hand(1), washing machine(2), or both(3)? ";
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "How many buckets do you use? ";
            std::cin >> bucketCount;
            if (bucketCount < 0) {
                std::cout << "Invalid bucket count. Please enter a non-negative number.\n";
                return 0;
            }
            waterUsage = bucketCount * 10; // Example: 10 liters per bucket
        } else if (choice == 2) {
            std::cout << "How many loads of laundry do you do in a week? ";
            std::cin >> loadCount;
            if (loadCount < 0) {
                std::cout << "Invalid load count. Please enter a non-negative number.\n";
                return 0;
            }
            waterUsage = loadCount * 50; // Example: 50 liters per load
        } else if (choice == 3) {
            std::cout << "How many buckets do you use? ";
            std::cin >> bucketCount;
            if (bucketCount < 0) {
                std::cout << "Invalid bucket count. Please enter a non-negative number.\n";
                return 0;
            }
            std::cout << "How many loads of laundry do you do in a week (with the washing machine)? ";
            std::cin >> loadCount;
            if (loadCount < 0) {
                std::cout << "Invalid load count. Please enter a non-negative number.\n";
                return 0;
            }
            waterUsage = (bucketCount * 10) + (loadCount * 50);
        } else {
            std::cout << "Invalid choice!\n";
            return 0;
        }
    } else if (activityName == "Dishwashing") {
        int choice, loadCount;
        std::cout << "Do you use a dishwasher(1), wash by hand(2), or both(3)? ";
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "How many loads of the dishwasher per week? ";
            std::cin >> loadCount;
            if (loadCount < 0) {
                std::cout << "Invalid load count. Please enter a non-negative number.\n";
                return 0;
            }
            waterUsage = loadCount * 15; // Example: 15 liters per load
        } else if (choice == 2) {
            int frequency;
            std::cout << "How many times do you wash the dishes in a week by hand? ";
            std::cin >> frequency;
            if (frequency < 0) {
                std::cout << "Invalid frequency. Please enter a non-negative number.\n";
                return 0;
            }
            waterUsage = frequency * 56; // Example: 56 liters per hand wash session
        } else if (choice == 3) {
            int frequency;
            std::cout << "How many loads of the dishwasher per week? ";
            std::cin >> loadCount;
            if (loadCount < 0) {
                std::cout << "Invalid load count. Please enter a non-negative number.\n";
                return 0;
            }
            std::cout << "How many times do you wash the dishes in a week by hand? ";
            std::cin >> frequency;
            if (frequency < 0) {
                std::cout << "Invalid frequency. Please enter a non-negative number.\n";
                return 0;
            }
            waterUsage = (loadCount * 15) + (frequency * 56);
        } else {
            std::cout << "Invalid choice!\n";
            return 0;
        }
    }

    return waterUsage;
}

void WaterFootprintCalculator::calculateFootprint(const User &user) const {
    double totalFootprint = user.calculateTotalWaterFootprint();
    std::cout << "Total Water Footprint: " << totalFootprint << " liters per week\n";
}

#include "WaterFootprintCalculator.h"

int main() {
    WaterFootprintCalculator calculator;
    calculator.run();
    return 0;
}
