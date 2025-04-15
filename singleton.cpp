#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class StudentManager
{
private:
    static StudentManager *instance;
    vector<string> students;

    // Private constructor
    StudentManager() {}

public:
    // Get singleton instance
    static StudentManager *getInstance()
    {
        if (!instance)
            instance = new StudentManager();
        return instance;
    }

    void addStudent(const string &name)
    {
        students.push_back(name);
    }

    bool removeStudent(const string &name)
    {
        auto it = find(students.begin(), students.end(), name);
        if (it != students.end())
        {
            students.erase(it);
            return true;
        }
        return false;
    }

    void displayStudents()
    {
        cout << "Student List:" << endl;
        for (const auto &name : students)
        {
            cout << "- " << name << endl;
        }
    }

    void clear()
    {
        students.clear();
    }

    vector<string> getAllStudents()
    {
        return students;
    }
};

// Initialize static member
StudentManager *StudentManager::instance = nullptr;

// ✅ Main function to run the program
int main()
{
    StudentManager *mgr = StudentManager::getInstance();

    mgr->addStudent("Alice");
    mgr->addStudent("Bob");

    cout << "After adding Alice and Bob:" << endl;
    mgr->displayStudents();

    mgr->removeStudent("Alice");

    cout << "\nAfter removing Alice:" << endl;
    mgr->displayStudents();

    return 0;
}
