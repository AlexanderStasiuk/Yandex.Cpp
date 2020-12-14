#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <utility>
using namespace std;


// enum class TaskStatus {
//     NEW,          
//     IN_PROGRESS,  
//     TESTING,      
//     DONE
// };

// using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return tasks.at(person);
    };

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person) {
        tasks[person][TaskStatus::NEW] ++;
    };

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
        const string& person, int task_count) {
            map<string, TasksInfo> new_statuses;
            map<string, TasksInfo> old_statuses;
            int __val = 0;

            TasksInfo changed;
            TasksInfo not_changed;

            for (uint code=0; code<4; code++) {
                TaskStatus status = static_cast<TaskStatus>(code);
                TaskStatus next_status = static_cast<TaskStatus>(code+1);
                if (tasks[person].count(status) > 0) {
                    if (code == 3) {
                        old_statuses[person][status] = tasks[person][status];
                    } else if (task_count>0) {
                        if (tasks[person].at(status) - task_count >= 0) {
                            new_statuses[person][next_status] += task_count;
                            old_statuses[person][status] += tasks[person][status]-task_count;
                            task_count = 0;
                        } else {
                            new_statuses[person][next_status] += tasks[person][status];
                            task_count -= tasks[person][status];
                        }
                    } else {
                        old_statuses[person][status] += tasks[person][status];
                    }
                    
                }
            }

            
            for (uint code=0; code<4; code++) {
                TaskStatus status = static_cast<TaskStatus>(code);
                __val = 0;
                if (new_statuses[person].count(status) > 0 ) {
                    __val += new_statuses[person][status];
                    if (new_statuses[person].at(status) > 0) {
                        changed[status] = new_statuses[person][status];
                    }
                }
                if (old_statuses[person].count(status) > 0 ) {
                    __val += old_statuses[person][status];
                    if (old_statuses[person].at(status) > 0 && status != TaskStatus::DONE) {
                        not_changed[status] = old_statuses[person][status];
                    }
                }
                if (__val > 0) {
                    tasks[person][status] = __val;
                } else {
                    tasks[person].erase(status);
                }
            }
            
            return tie(changed, not_changed);
        };
private: 
    map<string, TasksInfo> tasks;
};


void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }

    TasksInfo updated_tasks, untouched_tasks;
    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);
    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);
    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Alice", 1);
    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);

    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }

    cout << "Only: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Alice", 2);
    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);

    cout << "Only: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Alice", 4);
    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);

    
    cout << "Only: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    return 0;
}