//
//  EGGIN.hpp
//  EGGIN
//
//  Created by Elektro-Volk on 29/06/2018.
//
//

#pragma once

#include <stdio.h>

namespace EGGIN {
    extern bool isWork;

    int initEngine();
    void frame();
    void shutdown();
};
