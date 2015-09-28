#include "comparisonresult.h"

ComparisonResult::ComparisonResult(){
    perfectCount = 0;
    wrongDataCount = 0;
    tooFewDataHereCount = 0;
    tooMuchDataHereCount = 0;
}

void ComparisonResult::increasePerfect(){
    perfectCount++;
}

void ComparisonResult::increaseWrongData(){
    wrongDataCount++;
}

void ComparisonResult::increaseTooFewData(){
    tooFewDataHereCount++;
}

void ComparisonResult::increaseTooMuchData(){
    tooMuchDataHereCount++;
}

unsigned int ComparisonResult::sum(){
    return perfectCount + wrongDataCount + tooFewDataHereCount + tooMuchDataHereCount;
}

