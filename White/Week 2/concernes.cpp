#include <iostream>
#include <vector>
#include <string>
using namespace std;


void Dump(const vector<vector<string>>& taskList, const int& day) {
    cout << taskList[day-1].size() << " ";
    for (string task: taskList[day-1]) {
        cout << task << " ";
    }
    cout << endl;
}

void Add(vector<vector<string>>& taskList, int day, string newTask) {
    taskList[day-1].push_back(newTask);
}

void Next(vector<vector<string>>& taskList, const vector<int>& monthsDays, int& currentMonth) {
    int different = monthsDays[currentMonth+1] - monthsDays[currentMonth];
    if (different > 0) {
        vector<vector<string>> newTaskList(different);
        taskList.insert(end(taskList), begin(newTaskList), end(newTaskList));
    } 
    if (different < 0) {
        for (int i=monthsDays[currentMonth+1]+1; i<=monthsDays[currentMonth]; i++) {
            for (string task: taskList[i-1]) {
                taskList[monthsDays[currentMonth+1]-1].push_back(task);
            }
        }
        taskList.resize(monthsDays[currentMonth+1]);
    }
    if (currentMonth == 11) {
        currentMonth = 0;
    } else {
        currentMonth++;
    }
}


int main() {
    vector<int> monthsDays = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,    31}; // last number in list - trick for cycle.
    int currentMonth = 0;
    vector<vector<string>> taskList(monthsDays[currentMonth]);

    string command;
    int day;
    string task;


    int n;
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> command;
        if (command == "NEXT") {
            Next(taskList, monthsDays, currentMonth);
        } else if (command == "DUMP") {
            cin >> day;
            Dump(taskList, day);
        } else if (command == "ADD") {
            cin >> day;
            cin >> task;
            Add(taskList, day, task);
        }
    }

	return 0;
}