//
// Created by alexa on 09.01.2022.
//


#pragma once

#ifndef _IMETHODS_H
#define _IMETHODS_H

namespace MyStudentGroup {
    class IMethods {
        virtual int GetAverageScore(const LessonSeven::FullName &name) = 0;

        virtual std::string GetAllInfo(const LessonSeven::FullName &name) = 0;

        virtual std::string GetAllInfo() = 0;
    };
}

#endif //_IMETHODS_H