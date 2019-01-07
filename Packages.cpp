//
// Created by Michał Laskowski on 06/01/2019.
//

#include "Packages.h"
#include <stdlib.h>
#include <time.h>

int randomNumber(int from, int length){
    return rand() % length + from;
}