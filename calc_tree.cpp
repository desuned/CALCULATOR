//
// Created by danya on 13.05.2022.
//

#include "calc_tree.h"
#include "refs/refs.h"

CalcTree::CalcTree(sPtr eqPtr) {        // Constructor

    this->equation = *eqPtr;
    this->eqPtr = eqPtr;

}
