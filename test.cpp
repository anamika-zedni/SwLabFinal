#include "pch.h"  // Include only if your project uses precompiled headers
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

// Singleton StudentManager
class StudentManager {
private:
    static StudentManager* instance;
    vector<string> students;

    StudentManager() {}

public:
    static StudentManager* getInstance() {
        if (!instance)
            instance = new StudentManager();
        return instance;
    }

    void addStudent(const string& name) {
        students.push_back(name);
        cout << "Added student: " << name << endl;
    }

    bool removeStudent(const string& name) {
        auto it = find(students.begin(), students.end(), name);
        if (it != students.end()) {
            students.erase(it);
            cout << "Removed student: " << name << endl;
            return true;
        }
        cout << "Student not found: " << name << endl;
        return false;
    }

    vector<string> getAllStudents() {
        return students;
    }

    void clear() {
        students.clear();
    }
};

// Initialize static pointer
StudentManager* StudentManager::instance = nullptr;

// === Google Test Cases ===

TEST(StudentManagerTest, AddStudents) {
    StudentManager* mgr = StudentManager::getInstance();
    mgr->clear();  // Clear before test

    testing::internal::CaptureStdout();
    mgr->addStudent("Anamika");
    mgr->addStudent("Zedni");
    string output = testing::internal::GetCapturedStdout();

    vector<string> list = mgr->getAllStudents();
    ASSERT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], "Anamika");
    EXPECT_EQ(list[1], "Zedni");

    EXPECT_NE(output.find("Added student: Anamika"), string::npos);
    EXPECT_NE(output.find("Added student: Zedni"), string::npos);
}

TEST(StudentManagerTest, RemoveStudent) {
    StudentManager* mgr = StudentManager::getInstance();
    mgr->clear();

    mgr->addStudent("Monzurul");

    testing::internal::CaptureStdout();
    EXPECT_TRUE(mgr->removeStudent("Monzurul"));
    string output = testing::internal::GetCapturedStdout();

    vector<string> list = mgr->getAllStudents();
    EXPECT_EQ(list.size(), 0);

    EXPECT_NE(output.find("Removed student: Monzurul"), string::npos);
}

// === Run all tests ===
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}