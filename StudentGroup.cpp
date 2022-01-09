//
// Created by alexa on 09.01.2022.
//

#include "StudentGroup.h"

void MyStudentGroup::StudentGroup::AddStudent(const LessonSeven::Student& student){
    students.push_back(student);
}

void MyStudentGroup::StudentGroup::Save(){
    std::ofstream out("myStudents.bin", std::ios_base::binary);

    for(auto& s : students){
        s.SerializePartialToOstream(&out);
    }
    out.close();
}

void MyStudentGroup::StudentGroup::Open(){
    std::ifstream in("myStudents.bin", std::ios_base::binary);

    while(!in.eof()){
        LessonSeven::Student student;
        if(student.ParseFromIstream(&in)){
            students.push_back(std::move(student));
        }
    }
    in.close();
}

int MyStudentGroup::StudentGroup::GetAverageScore(const LessonSeven::FullName& name){
    auto average = std::find_if(students.begin(), students.end(), [&](LessonSeven::Student student){
        if(student.fullname().surname() != name.surname()){
            return false;
        }
        else if(student.fullname().name() != name.name()){
            return  false;
        }
        else if(student.fullname().patronymic() != name.patronymic()){
            return false;
        }
        return true;
    });

    if(average != students.end()){
        return average->averagescore();
    }

    return 0;
}

std::string MyStudentGroup::StudentGroup::GetAllInfo(const LessonSeven::FullName &name){
    auto stdnt = std::find_if(students.begin(), students.end(), [&](LessonSeven::Student student){
        if(student.fullname().surname() != name.surname()){
            return false;
        }
        else if(student.fullname().name() != name.name()){
            return  false;
        }
        else if(student.fullname().patronymic() != name.patronymic()){
            return false;
        }
        return true;
    });

    if(stdnt != students.end()){
        std::string temp;
        temp += stdnt->fullname().surname() + " " + stdnt->fullname().name();

        if(stdnt->fullname().has_patronymic()){
            temp += " " + stdnt->fullname().patronymic();
        }

        temp += " " + std::to_string(stdnt->averagescore());
        return temp;
    }
    else{
        return "Not find this name!";
    }
}

std::string MyStudentGroup::StudentGroup::GetAllInfo(){
    std::string temp;
    for(auto& sG : students){
        temp += sG.fullname().surname() + " " + sG.fullname().name();

        if(sG.fullname().has_patronymic()){
            temp += " " + sG.fullname().patronymic();
        }

        temp += " " + std::to_string(sG.averagescore());
        temp += "\n";
    }

    return temp;
}