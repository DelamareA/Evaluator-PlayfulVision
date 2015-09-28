#ifndef COMPARISONRESULT_H
#define COMPARISONRESULT_H


class ComparisonResult {

    public:
        ComparisonResult();

        void increasePerfect();
        void increaseWrongData();
        void increaseTooFewData();
        void increaseTooMuchData();

    private:
        unsigned int sum();

        unsigned int perfectCount;
        unsigned int wrongDataCount; // good position but wrong data
        unsigned int tooFewDataHereCount; // a data is not at a position where a data should be
        unsigned int tooMuchDataHereCount; // a data is at a position where no data should be

};

#endif // COMPARISONRESULT_H
