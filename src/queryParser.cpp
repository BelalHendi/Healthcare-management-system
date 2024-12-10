#include <iostream>
#include "queryParser.h"

#include <DoctorIndexService.h>

#include "PrimaryIndexService.h"
#include "doctorFileService.h"
#include "offsetService.h"
using namespace std;

queryParser::queryParser(std::string &query) {
    this->tokens = splitCommand(query);
}

void queryParser::handleSelect() {
    string field = tokens[1];
    string table = tokens[3];
    string conditionField = tokens[5];
    string conditionVal = tokens[7].substr(1, tokens[7].size() - 2);
    if(table == "Doctors") {
        DoctorIndexService doctorservice;
        if(conditionField == "DoctorID"){
            vector<int> id;
            id.push_back(doctorservice.getById(conditionVal));
            offsetService offs;
            vector<doctor> docs = offs.offsetToDoctors(id);
            if(field == "all") {
                for(int i = 0; i < docs.size(); i++) {
                    cout << "ID: " << docs[i].id << "|" << "Name: " << docs[i].name << "|" << "Address: " << docs[i].address << endl;
                }
            } else if(field == "DoctorName") {
                for(int i = 0; i < docs.size(); i++) {
                    cout << "Name: " << docs[i].name << endl;
                }
            } else if(field == "DoctorAddress") {
                for(int i = 0; i < docs.size(); i++) {
                    cout << "Address: " << docs[i].address << endl;
                }
            } else if(field == "DoctorID") {
                for(int i = 0; i < docs.size(); i++) {
                    cout << "ID: " << docs[i].id << endl;
                }
            }
        } else {
            vector<int> secID;
        }
    }
}


vector<string> queryParser::splitCommand(const string& input) {
    vector<string> parts;
    string currentPart;
    bool insideQuotes = false;

    for (char ch : input) {
        if (ch == '\"' || ch == '\'') {
            insideQuotes = !insideQuotes; // Toggle the insideQuotes flag
        } else if (ch == ' ' && !insideQuotes) {
            if (!currentPart.empty()) {
                parts.push_back(currentPart);
                currentPart.clear();
            }
        } else {
            currentPart += ch;
        }
    }

    if (!currentPart.empty()) {
        parts.push_back(currentPart);
    }

    return parts;
}