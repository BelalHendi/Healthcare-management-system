//
// Created by pc on 12/6/2024.
//

#ifndef HEALTHCARE_MANAGEMENT_SYSTEM_QUERYPARSER_TPP
#define HEALTHCARE_MANAGEMENT_SYSTEM_QUERYPARSER_TPP

#include <string>
#include <sstream>
#include <vector>
using namespace std;
class queryParser {
public:
    vector<string> tokens;
    queryParser(string &query);
    void handleSelect();
};


#endif //HEALTHCARE_MANAGEMENT_SYSTEM_QUERYPARSER_TPP
