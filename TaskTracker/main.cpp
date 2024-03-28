#include <string>
#include <iostream>
// The #if is needed for stepik check system submitting if we use the whole file
#if __GNUC__ == 13 && __GNUC_MINOR__ == 2
#include "TaskInfo.h"
#endif

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    [[nodiscard]] const TasksInfo &GetPersonTasksInfo(const string &person) const {
        return _teamTasks.find(person)->second;
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчика
    void AddNewTask(const string &person) {
        _teamTasks[person][TaskStatus::NEW]++;
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string &person, int task_count) {
        auto personTasksIt = _teamTasks.find(person);
        TasksInfo updated;
        TasksInfo untouched;
        if (personTasksIt != _teamTasks.end())
        {
            for (const auto& [taskStatus, number] : personTasksIt->second)
            {
                if (taskStatus != TaskStatus::DONE)
                {
                    const auto nextTaskStatus = TaskStatus(static_cast<int>(taskStatus) + 1);
                    if (task_count > number)
                    {
                        updated[nextTaskStatus] = number;
                        task_count -= number;
                    }
                    else if (task_count > 0)
                    {
                        updated[nextTaskStatus] = task_count;
                        untouched[taskStatus] = number - task_count;
                        task_count = 0;
                    }
                    else
                    {
                        untouched[taskStatus] = number;
                    }
                }
            }

            for (const auto& [taskStatus, number] : updated)
            {
                const auto previousTaskStatus = TaskStatus(static_cast<int>(taskStatus) - 1);
                personTasksIt->second[taskStatus] += number;
                personTasksIt->second[previousTaskStatus] -= number;
            }
        }
        return { updated, untouched };
    }

private:
    map<string, TasksInfo> _teamTasks;
};

//// Принимаем словарь по значению, чтобы иметь возможность
//// обращаться к отсутствующим ключам с помощью [] и получать 0,
//// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
         ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
         ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
         ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}