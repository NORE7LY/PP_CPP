#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>
#include "activity.h"

class CoreTracker
{
private:
    std::vector<Activity> activities;
    std::vector<Goal> goals;
    const std::string ACTIVITIES_FILE = "activities_cpp.csv";
    const std::string GOALS_FILE = "activities_goals_cpp.csv";

public:
    CoreTracker()
    {
        loadActivities();
        loadGoals();
    }

    ~CoreTracker()
    {
        saveActivities();
        saveGoals();
    }

    // Convert string to ActivityType
    ActivityType stringToActivityType(const std::string &str)
    {
        std::string lower = str;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

        if (lower == "running")
            return ActivityType::RUNNING;
        if (lower == "walking")
            return ActivityType::WALKING;
        if (lower == "swimming")
            return ActivityType::SWIMMING;
        if (lower == "cardio")
            return ActivityType::CARDIO;
        if (lower == "strength")
            return ActivityType::STRENGTH;
        return ActivityType::UNKNOWN;
    }

    // Convert ActivityType to string
    std::string activityTypeToString(ActivityType type)
    {
        switch (type)
        {
        case ActivityType::RUNNING:
            return "Running";
        case ActivityType::WALKING:
            return "Walking";
        case ActivityType::SWIMMING:
            return "Swimming";
        case ActivityType::CARDIO:
            return "Cardio";
        case ActivityType::STRENGTH:
            return "Strength";
        default:
            return "Unknown";
        }
    }

    // Load activities from CSV
    void loadActivities()
    {
        std::ifstream file(ACTIVITIES_FILE);
        if (!file.is_open())
            return;

        std::string line;
        std::getline(file, line); // Skip header if exists

        while (std::getline(file, line))
        {
            if (line.empty())
                continue;

            std::stringstream ss(line);
            std::string cell;
            std::vector<std::string> row;

            while (std::getline(ss, cell, ','))
            {
                row.push_back(cell);
            }

            if (row.size() >= 5)
            {
                Activity activity;
                activity.type = stringToActivityType(row[0]);
                activity.date = row[1];
                activity.duration = std::stod(row[2]);
                activity.distance = std::stod(row[3]);
                activity.repetitions = std::stoi(row[4]);
                activities.push_back(activity);
            }
        }
        file.close();
    }

    // Save activities to CSV
    void saveActivities()
    {
        std::ofstream file(ACTIVITIES_FILE);
        if (!file.is_open())
            return;

        file << "ActivityType,Date,Duration,Distance,Repetitions\n";
        for (const auto &activity : activities)
        {
            file << activityTypeToString(activity.type) << ","
                 << activity.date << ","
                 << activity.duration << ","
                 << activity.distance << ","
                 << activity.repetitions << "\n";
        }
        file.close();
    }

    // Load goals from CSV
    void loadGoals()
    {
        std::ifstream file(GOALS_FILE);
        if (!file.is_open())
            return;

        std::string line;
        std::getline(file, line); // Skip header if exists

        while (std::getline(file, line))
        {
            if (line.empty())
                continue;

            std::stringstream ss(line);
            std::string cell;
            std::vector<std::string> row;

            while (std::getline(ss, cell, ','))
            {
                row.push_back(cell);
            }

            if (row.size() >= 7)
            {
                Goal goal;
                goal.type = stringToActivityType(row[0]);
                goal.description = row[1];
                goal.deadline = row[2];
                goal.targetDistance = std::stod(row[3]);
                goal.targetDuration = std::stod(row[4]);
                goal.targetReps = std::stoi(row[5]);
                goal.achieved = (row[6] == "1" || row[6] == "true");
                goals.push_back(goal);
            }
        }
        file.close();
    }

    // Save goals to CSV
    void saveGoals()
    {
        std::ofstream file(GOALS_FILE);
        if (!file.is_open())
            return;

        file << "ActivityType,Description,Deadline,TargetDistance,TargetDuration,TargetReps,Achieved\n";
        for (const auto &goal : goals)
        {
            file << activityTypeToString(goal.type) << ","
                 << goal.description << ","
                 << goal.deadline << ","
                 << goal.targetDistance << ","
                 << goal.targetDuration << ","
                 << goal.targetReps << ","
                 << (goal.achieved ? "1" : "0") << "\n";
        }
        file.close();
    }

    // Add activity with ID
    void addActivity(int id)
    {
        std::cout << "=== Add New Activity (ID: " << id << ") ===\n";

        Activity activity;
        std::string typeStr;

        std::cout << "Available activity types: Running, Walking, Swimming, Cardio, Strength\n";
        std::cout << "Enter activity type: ";
        std::cin >> typeStr;
        activity.type = stringToActivityType(typeStr);

        if (activity.type == ActivityType::UNKNOWN)
        {
            std::cout << "Invalid activity type!\n";
            return;
        }

        std::cout << "Enter date (YYYY-MM-DD): ";
        std::cin >> activity.date;

        std::cout << "Enter duration (minutes): ";
        std::cin >> activity.duration;

        std::cout << "Enter distance (km, 0 if not applicable): ";
        std::cin >> activity.distance;

        std::cout << "Enter repetitions (0 if not applicable): ";
        std::cin >> activity.repetitions;

        activities.push_back(activity);
        saveActivities();

        std::cout << "Activity added successfully!\n";
    }

    // View specific activity by ID
    void viewActivity(int id)
    {
        if (id < 0 || id >= static_cast<int>(activities.size()))
        {
            std::cout << "Activity ID " << id << " not found!\n";
            return;
        }

        const auto &activity = activities[id];
        std::cout << "=== Activity Details (ID: " << id << ") ===\n";
        std::cout << "Type: " << activityTypeToString(activity.type) << "\n";
        std::cout << "Date: " << activity.date << "\n";
        std::cout << "Duration: " << activity.duration << " minutes\n";
        std::cout << "Distance: " << activity.distance << " km\n";
        std::cout << "Repetitions: " << activity.repetitions << "\n";
    }

    // View all activities
    void viewActivities()
    {
        std::cout << "=== All Activities ===\n";
        if (activities.empty())
        {
            std::cout << "No activities recorded.\n";
            return;
        }

        std::cout << std::left << std::setw(5) << "ID"
                  << std::setw(12) << "Type"
                  << std::setw(12) << "Date"
                  << std::setw(10) << "Duration"
                  << std::setw(10) << "Distance"
                  << std::setw(8) << "Reps" << "\n";
        std::cout << std::string(60, '-') << "\n";

        for (size_t i = 0; i < activities.size(); ++i)
        {
            const auto &activity = activities[i];
            std::cout << std::left << std::setw(5) << i
                      << std::setw(12) << activityTypeToString(activity.type)
                      << std::setw(12) << activity.date
                      << std::setw(10) << activity.duration
                      << std::setw(10) << activity.distance
                      << std::setw(8) << activity.repetitions << "\n";
        }
    }

    // Add goal
    void addGoal(int goalId, int activityId, const std::string &description,
                 const std::string &deadline, int targetReps, double targetDuration, double targetDistance)
    {

        // Convert activityId to ActivityType (assuming 0=Running, 1=Walking, etc.)
        ActivityType type = static_cast<ActivityType>(activityId);
        if (activityId < 0 || activityId > 4)
        {
            type = ActivityType::UNKNOWN;
        }

        Goal goal(type, description, deadline, targetDistance, targetDuration, targetReps);
        goals.push_back(goal);
        saveGoals();

        std::cout << "Goal added successfully with ID: " << goalId << "\n";
    }

    // View specific goal by ID
    void viewGoal(int id)
    {
        if (id < 0 || id >= static_cast<int>(goals.size()))
        {
            std::cout << "Goal ID " << id << " not found!\n";
            return;
        }

        const auto &goal = goals[id];
        std::cout << "=== Goal Details (ID: " << id << ") ===\n";
        std::cout << "Activity Type: " << activityTypeToString(goal.type) << "\n";
        std::cout << "Description: " << goal.description << "\n";
        std::cout << "Deadline: " << goal.deadline << "\n";
        std::cout << "Target Distance: " << goal.targetDistance << " km\n";
        std::cout << "Target Duration: " << goal.targetDuration << " minutes\n";
        std::cout << "Target Repetitions: " << goal.targetReps << "\n";
        std::cout << "Achieved: " << (goal.achieved ? "Yes" : "No") << "\n";
    }

    // View all goals
    void viewGoals()
    {
        std::cout << "=== All Goals ===\n";
        if (goals.empty())
        {
            std::cout << "No goals set.\n";
            return;
        }

        std::cout << std::left << std::setw(5) << "ID"
                  << std::setw(12) << "Type"
                  << std::setw(20) << "Description"
                  << std::setw(12) << "Deadline"
                  << std::setw(10) << "Achieved" << "\n";
        std::cout << std::string(70, '-') << "\n";

        for (size_t i = 0; i < goals.size(); ++i)
        {
            const auto &goal = goals[i];
            std::cout << std::left << std::setw(5) << i
                      << std::setw(12) << activityTypeToString(goal.type)
                      << std::setw(20) << goal.description.substr(0, 18)
                      << std::setw(12) << goal.deadline
                      << std::setw(10) << (goal.achieved ? "Yes" : "No") << "\n";
        }
    }

    // Modify goal
    void modifyGoal(int goalId, int activityId, const std::string &description,
                    const std::string &deadline, int targetReps, double targetDuration, double targetDistance)
    {

        if (goalId < 0 || goalId >= static_cast<int>(goals.size()))
        {
            std::cout << "Goal ID " << goalId << " not found!\n";
            return;
        }

        Goal &goal = goals[goalId];
        goal.type = static_cast<ActivityType>(activityId);
        goal.description = description;
        goal.deadline = deadline;
        goal.targetReps = targetReps;
        goal.targetDuration = targetDuration;
        goal.targetDistance = targetDistance;

        saveGoals();
        std::cout << "Goal modified successfully!\n";
    }
};

int main(int argc, char *argv[])
{
    CoreTracker tracker;

    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <command> [arguments]\n";
        std::cout << "Commands:\n";
        std::cout << "  add_activity <activity_ID>\n";
        std::cout << "  view_activity <activity_ID>\n";
        std::cout << "  view_activities\n";
        std::cout << "  add_goal <goal_ID> <activity_ID> <description> <deadline> <target_reps> <target_duration> <target_distance>\n";
        std::cout << "  view_goal <goal_ID>\n";
        std::cout << "  view_goals\n";
        std::cout << "  modify_goal <goal_ID> <activity_ID> <description> <deadline> <target_reps> <target_duration> <target_distance>\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "add_activity" && argc >= 3)
    {
        int id = std::stoi(argv[2]);
        tracker.addActivity(id);
    }
    else if (command == "view_activity" && argc >= 3)
    {
        int id = std::stoi(argv[2]);
        tracker.viewActivity(id);
    }
    else if (command == "view_activities")
    {
        tracker.viewActivities();
    }
    else if (command == "add_goal" && argc >= 9)
    {
        int goalId = std::stoi(argv[2]);
        int activityId = std::stoi(argv[3]);
        std::string description = argv[4];
        std::string deadline = argv[5];
        int targetReps = std::stoi(argv[6]);
        double targetDuration = std::stod(argv[7]);
        double targetDistance = std::stod(argv[8]);
        tracker.addGoal(goalId, activityId, description, deadline, targetReps, targetDuration, targetDistance);
    }
    else if (command == "view_goal" && argc >= 3)
    {
        int id = std::stoi(argv[2]);
        tracker.viewGoal(id);
    }
    else if (command == "view_goals")
    {
        tracker.viewGoals();
    }
    else if (command == "modify_goal" && argc >= 9)
    {
        int goalId = std::stoi(argv[2]);
        int activityId = std::stoi(argv[3]);
        std::string description = argv[4];
        std::string deadline = argv[5];
        int targetReps = std::stoi(argv[6]);
        double targetDuration = std::stod(argv[7]);
        double targetDistance = std::stod(argv[8]);
        tracker.modifyGoal(goalId, activityId, description, deadline, targetReps, targetDuration, targetDistance);
    }
    else
    {
        std::cout << "Invalid command or insufficient arguments.\n";
        return 1;
    }

    return 0;
}