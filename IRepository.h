//
// Created by alexa on 09.01.2022.
//

#pragma once

#ifndef _IREPOSITORY_H
#define _IREPOSITORY_H

namespace MyStudentGroup {
    class IRepository {
        virtual void Open() = 0;

        virtual void Save() = 0;

    };
}

#endif //_IREPOSITORY_H