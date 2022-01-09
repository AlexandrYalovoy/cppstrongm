#include <iostream>
#include <numeric>
#include "cmake-build-debug/LessonSeven.pb.h"
#include "StudentGroup.h"

void TaskTwo() {
    LessonSeven::FullName fullname;
    fullname.set_surname("Buev");
    fullname.set_name("Mikhail");
    fullname.set_patronymic("Vasilevich");

    LessonSeven::Student studentOne;
    *studentOne.mutable_fullname() = fullname;
    studentOne.add_grade(4);
    studentOne.add_grade(5);
    studentOne.add_grade(5);
    studentOne.add_grade(4);
    studentOne.add_grade(3);
    studentOne.set_averagescore(
            std::accumulate(studentOne.grade().begin(), studentOne.grade().end(), 0) / studentOne.grade().size());

    LessonSeven::StudentGroup studentGroup;
    *studentGroup.add_students() = studentOne;

    std::cout << "Before serialize: " << std::endl;
    for (auto &sG: studentGroup.students()) {
        std::cout << sG;
    }
    std::cout << std::endl;

    std::ofstream out("data.bin", std::ios_base::binary);
    studentGroup.SerializeToOstream(&out);
    out.close();

    LessonSeven::StudentGroup studentGroupOne;
    std::ifstream in("data.bin", std::ios_base::binary);
    if (studentGroupOne.ParseFromIstream(&in)) {
        std::cout << "After deserialize: " << std::endl;
        for (auto &sGO: studentGroupOne.students()) {
            std::cout << sGO;
        }
        std::cout << std::endl;
    } else {
        std::cout << "Error!" << std::endl;
    }
    in.close();
}

void TaskThree() {
    LessonSeven::FullName fullnameOne;
    fullnameOne.set_surname("Buev");
    fullnameOne.set_name("Mikhail");
    fullnameOne.set_patronymic("Vasilevich");

    LessonSeven::Student studentOne;
    *studentOne.mutable_fullname() = fullnameOne;
    studentOne.add_grade(4);
    studentOne.add_grade(5);
    studentOne.add_grade(5);
    studentOne.add_grade(4);
    studentOne.add_grade(3);
    studentOne.set_averagescore(
            std::accumulate(studentOne.grade().begin(), studentOne.grade().end(), 0) / studentOne.grade().size());

    MyStudentGroup::StudentGroup studentGroup;
    studentGroup.AddStudent(studentOne);

    LessonSeven::FullName fullnameTwo;
    fullnameTwo.set_surname("Ivanov");
    fullnameTwo.set_name("Petr");
    fullnameTwo.set_patronymic("Semenovich");

    LessonSeven::Student studentTwo;
    *studentTwo.mutable_fullname() = fullnameTwo;
    studentTwo.add_grade(3);
    studentTwo.add_grade(3);
    studentTwo.add_grade(4);
    studentTwo.add_grade(4);
    studentTwo.add_grade(5);
    studentTwo.add_grade(3);
    studentTwo.set_averagescore(
            std::accumulate(studentTwo.grade().begin(), studentTwo.grade().end(), 0) / studentTwo.grade().size());

    studentGroup.AddStudent(studentTwo);

    LessonSeven::FullName fullnameThree;
    fullnameThree.set_surname("Sidorov");
    fullnameThree.set_name("Stepan");

    LessonSeven::Student studentThree;
    *studentThree.mutable_fullname() = fullnameThree;
    studentThree.add_grade(5);
    studentThree.add_grade(5);
    studentThree.add_grade(5);

    studentThree.set_averagescore(
            std::accumulate(studentThree.grade().begin(), studentThree.grade().end(), 0) / studentThree.grade().size());

    studentGroup.AddStudent(studentThree);

    std::cout << "Before serialize: " << std::endl;
    std::cout << studentGroup.GetAllInfo();
    studentGroup.Save();


    MyStudentGroup::StudentGroup studentGroupOne;
    studentGroupOne.Open();

    std::cout << "After serialize: " << std::endl;
    std::cout << studentGroup.GetAllInfo();

    std::cout << " Output: " << studentGroup.GetAverageScore(fullnameOne) << std::endl;
    std::cout << studentGroup.GetAllInfo(fullnameTwo);
    std::cout << std::endl;
    std::cout << studentGroup.GetAllInfo(fullnameThree);
}

int main() {
    //TaskTwo();
    TaskThree();

    return 0;
}