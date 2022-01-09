//
// Created by alexa on 09.01.2022.
//

#pragma once

#ifndef _STUDENTGROUP_H
#define _STUDENTGROUP_H
#include <fstream>
#include <sstream>
#include "cmake-build-debug/LessonSeven.pb.h"
#include "IMethods.h"
#include "IRepository.h"

namespace MyStudentGroup{
    class StudentGroup : public IMethods,public IRepository{
    public:

        void AddStudent(const LessonSeven::Student& student);

        void Save() override;

        void Open() override;

        int GetAverageScore(const LessonSeven::FullName& name) override;

        std::string GetAllInfo(const LessonSeven::FullName &name) override;

        std::string GetAllInfo() override;

    private:
        std::vector<LessonSeven::Student> students;
    };
}


#endif //_STUDENTGROUP_H