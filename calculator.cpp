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
#include <iostream> // For std::cout and std::cin

WaterFootprintCalculator::WaterFootprintCalculator() {
    activityList.push_back(Activity("Taking a bath"));
    activityList.push_back(Activity("Bathroom sink"));
    activityList.push_back(Activity("Cooking and Drinking"));
    activityList.push_back(Activity("Laundry"));
    activityList.push_back(Activity("Dishwashing"));
    activityList.push_back(Activity("Driving"));
    activityList.push_back(Activity("Shopping"));
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
                addUserActivity(user);
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
              << "1. Add Activity\n"
              << "2. Calculate Water Footprint\n"
              << "3. Exit\n"
              << "************************\n";
}

void WaterFootprintCalculator::addUserActivity(User &user) {
    int activityChoice;
    double waterUsage;
    int frequency = 0;

    while (true) {
        std::cout << "Choose an activity:\n";
        for (size_t i = 0; i < activityList.size(); ++i) {
            std::cout << i + 1 << ". " << activityList[i].getName() << "\n";
        }
        std::cout << activityList.size() + 1 << ". Done adding activities\n";
        std::cout << "Enter the number of the activity: ";
        std::cin >> activityChoice;

        if (activityChoice < 1 || activityChoice > static_cast<int>(activityList.size() + 1)) {
            std::cout << "Invalid activity choice.\n";
            continue;
        }

        if (activityChoice == static_cast<int>(activityList.size() + 1)) {
            break;
        }

        waterUsage = estimateWaterUsage(activityList[activityChoice - 1].getName(), frequency);
        activityList[activityChoice - 1].setWaterUsage(waterUsage);

        user.addActivity(activityList[activityChoice - 1], frequency);

        std::cout << "Activity added successfully!\n";
    }
}

double WaterFootprintCalculator::estimateWaterUsage(const std::string &activityName, int &frequency) const {
    double waterUsage = 0;

    if (activityName == "Taking a bath") {
        int choice, minutes;
        std::cout << "Do you use a bucket(1) or shower(2) for taking a bath? ";
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "How many times do you take a bath with a bucket per week? ";
            std::cin >> frequency;
            waterUsage = 10;
        } else if (choice == 2) {
            std::cout << "How long do you bathe for? (in minutes) ";
            std::cin >> minutes;
            std::cout << "How many times do you take a bath with a shower per week? ";
            std::cin >> frequency;
            waterUsage = minutes * 9;
        } else {
            std::cout << "Invalid choice!\n";
            return 0;
        }
    } else if (activityName == "Bathroom sink") {
        int minutes;
        std::cout << "How long do you leave the sink running per day? (in minutes) ";
        std::cin >> minutes;
        waterUsage = minutes * 10 * 7;
    } else if (activityName == "Cooking and Drinking") {
        int meals;
        std::cout << "How many meals do you have in a day? ";
        std::cin >> meals;
        waterUsage = (meals * 7) + (4 * 7);
    } else if (activityName == "Laundry") {
        int choice, bucketCount, loadCount;
        std::cout << "Do you do the laundry by hand(1), washing machine(2), or both(3)? ";
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "How many buckets do you use per laundry session? ";
            std::cin >> bucketCount;
            std::cout << "How many times do you do laundry by hand per week? ";
            std::cin >> frequency;
            waterUsage = bucketCount * 10 * frequency;
        } else if (choice == 2) {
            std::cout << "How many loads of laundry do you do per week? ";
            std::cin >> loadCount;
            waterUsage = loadCount * 50; 
        } else if (choice == 3) {
            std::cout << "How many buckets do you use per laundry session? ";
            std::cin >> bucketCount;
            std::cout << "How many loads of laundry do you do per week (with the washing machine)? ";
            std::cin >> loadCount;
            std::cout << "How many times do you do laundry by hand per week? ";
            std::cin >> frequency;
            waterUsage = ((bucketCount * 10) + (loadCount * 50)) * frequency;
        } else {
            std::cout << "Invalid choice!\n";
            return 0;
        }
    } else if (activityName == "Dishwashing") {
        int choice, loadCount, washCount;
        std::cout << "Do you use a dishwasher(1), wash by hand(2), or both(3)? ";
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "How many loads of the dishwasher per week? ";
            std::cin >> loadCount;
            waterUsage = loadCount * 15;
        } else if (choice == 2) {
            std::cout << "How many times do you wash the dishes by hand per week? ";
            std::cin >> washCount;
            waterUsage = washCount * 56; 
        } else if (choice == 3) {
            std::cout << "How many loads of the dishwasher per week? ";
            std::cin >> loadCount;
            std::cout << "How many times do you wash the dishes by hand per week? ";
            std::cin >> washCount;
            waterUsage = (loadCount * 15) + (washCount * 56);
        } 
    } else if (activityName == "Driving") {
        int choice;
        double distance;
        std::cout << "Do you drive a motor vehicle yes(1) or no(2)? ";
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "How many kilometers do you drive by vehicle? ";
            std::cin >> distance;
            waterUsage = distance * 0.41 * 22.38; 
        } else if (choice == 2) {
            waterUsage = 0;
        }
    } else if (activityName == "Shopping") {
        int choice;
        std::cout << "What is your shopping habit?\n Shopaholic(1) Just the basics(2) or Shopping for Fun(3)? ";
        std::cin >> choice;
        if (choice == 1) {
            waterUsage = 18300 * 5;
        } else if (choice == 2) {
            waterUsage = 18300;
        } else if (choice == 3) {
            waterUsage = 18300 * 3;
        }    
    } else {
        std::cout << "Invalid choice!\n";
        return 0;
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