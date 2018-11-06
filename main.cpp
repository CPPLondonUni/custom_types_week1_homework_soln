
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

namespace {

int id_counter = 0;

struct Student {
    std::string first_name{};
    std::string surname{};
    int id = ++id_counter;

    void print() const
    {
        std::cout << first_name << " " << surname << " " << id;
    }
};

struct ModuleRecord {
    Student student{};
    int grade = 0;
};

bool compare_grades(const ModuleRecord& a, const ModuleRecord& b)
{
    return a.grade > b.grade;
}

struct Module {
    std::string name{};
    std::vector<ModuleRecord> grades{};

    void add_record(const Student& student, int grade)
    {
        grades.push_back({student, grade});
    }

    void print() const
    {
        for (const auto& rec : grades) {
            rec.student.print();
            std::cout << '\t' << rec.grade << '\n';
        }
    }

    void print_ordered() const
    {
        auto grades_copy = grades;

        std::sort(grades_copy.begin(), grades_copy.end(), compare_grades);

        for (const auto& rec : grades_copy) {
            rec.student.print();
            std::cout << '\t' << rec.grade << '\n';
        }
    }
};




// Test that we can create a student instance
void test_create_student()
{
    const Student s{"James", "Bond", 007};
    assert(s.first_name == "James");
    assert(s.surname == "Bond");
    assert(s.id == 7);
}

// Test that Students have automatically-assigned ids
void test_student_ids()
{
    const Student tom{"Tom", "Breza"};
    const Student tristan{"Tristan", "Brindle"};
    assert(tom.id == 1);
    assert(tristan.id == 2);
}

// Test that we have implemented student::print() correctly
void test_print_student()
{
    const Student s{"Sherlock", "Holmes", 221};
    s.print();
    std::cout << '\n';
}

// Test that we can create a ModuleRecord
void test_create_module_record()
{
    const ModuleRecord rec{
            {"Sherlock", "Holmes", 221}, 100
    };
    assert(rec.student.first_name == "Sherlock");
    assert(rec.student.surname == "Holmes");
    assert(rec.student.id == 221);
    assert(rec.grade == 100);
}

// Test that we can create a Module
void test_create_module()
{
    id_counter = 0;

    const Module mod {
        "Initial C++",
         {
             { {"Tristan", "Brindle"}, 70 },
             { {"Tom", "Breza"}, 99}
        }
    };

    assert(mod.name == "Initial C++");
    assert(mod.grades.size() == 2);
    assert(mod.grades[0].student.first_name == "Tristan");
    assert(mod.grades[0].student.surname == "Brindle");
    assert(mod.grades[0].student.id == 1);
    assert(mod.grades[0].grade == 70);
}

// Test that module::add_record() works as expected
void test_module_add_record()
{
    id_counter = 0;

    Module mod {
            "Initial C++",
            {
                    { {"Tristan", "Brindle"}, 70 }
            }
    };

    assert(mod.grades.size() == 1);

    mod.add_record({"Tom", "Breza"}, 99);

    assert(mod.grades.size() == 2);
    assert(mod.grades[1].student.first_name == "Tom");
    assert(mod.grades[1].student.surname == "Breza");
    assert(mod.grades[1].student.id == 2);
    assert(mod.grades[1].grade == 99);
}

// Test that module::print() works as expected
void test_print_module_unordered()
{
    id_counter = 0;

    const Module mod {
            "Initial C++",
            {
                    { {"Annie", "Appleby"}, 70 },
                    { {"Benjamin", "Button"}, 10 },
                    { {"Claire", "Cotton"}, 99}
            }
    };

    std::cout << '\n';
    mod.print();
    std::cout << '\n';
}

void test_print_module_ordered()
{
    id_counter = 0;

    const Module mod {
            "Initial C++",
            {
                    { {"Annie", "Appleby"}, 70 },
                    { {"Benjamin", "Button" }, 10 },
                    { {"Claire", "Cotton"}, 99}
            }
    };

    mod.print_ordered();
}

}

int main()
{
    test_create_student();
    test_student_ids();
    test_print_student();
    test_create_module_record();
    test_create_module();
    test_module_add_record();
    test_print_module_unordered();
    test_print_module_ordered();
}