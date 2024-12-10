#include <iostream>
#include "queryParser.h"

#include <AppointmentIndexService.h>
#include <DoctorIndexService.h>
#include <SI.h>

#include "PrimaryIndexService.h"
#include "doctorFileService.h"
#include "offsetService.h"
using namespace std;

void queryParser::querySplitter(std::string &query) {
    this->splitCommand(query);
}

void queryParser::parseQuery() {
    string field = this->tokens[1];
    string table = this->tokens[3];
    string conditionField = this->tokens[5];
    string conditionVal = this->tokens[7];
    if(table == "Doctors") {

        vector<doctor> docs;
        vector<int> id;
        offsetService offs;
        if(conditionField == "DoctorID"){
            id.push_back(DoctorIndexService::getInstance()->getById(conditionVal));
            docs = offs.offsetToDoctors(id);
        } else {
            vector<string> secID;
            SI secIndex(DOCTOR);
            secID = secIndex.search(conditionVal);
            for (int i = 0; i < secID.size(); i++) {
                id.push_back(DoctorIndexService::getInstance()->getById(secID[i]));
            }
            docs = offs.offsetToDoctors(id);
        }
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
    } else if(table == "Appointments") {

        vector<appointment> docs;
        offsetService offs;
        vector<int> id;
        if(conditionField == "AppointmentID"){
            id.push_back(AppointmentIndexService::getInstance()->getById(conditionVal));
            docs = offs.offsetToAppointments(id);
        } else {
            vector<string> secID;
            SI secIndex(APPOINTMENT);
            secID = secIndex.search(conditionField);
            for (int i = 0; i < secID.size(); i++) {
                id.push_back(AppointmentIndexService::getInstance()->getById(secID[i]));
            }
            docs = offs.offsetToAppointments(id);
        }
        if(field == "all") {
            for(int i = 0; i < docs.size(); i++) {
                cout << "ID: " << docs[i].AppointmentID << "|" << "Appointment Date: " << docs[i].AppointmentDate << "|" << "DoctorID: " << docs[i].DoctorID << endl;
            }
        } else if(field == "AppointmentID") {
            for(int i = 0; i < docs.size(); i++) {
                cout <<  "ID: " << docs[i].AppointmentID << endl;
            }
        } else if(field == "AppointmentDate") {
            for(int i = 0; i < docs.size(); i++) {
                cout << "Appointment Date: " << docs[i].AppointmentDate << endl;
            }
        } else if(field == "DoctorID") {
            for(int i = 0; i < docs.size(); i++) {
                cout << "DoctorID: " << docs[i].DoctorID << endl;
            }
        }
    }
}


void queryParser::splitCommand(const string& input) {
    string currentPart;
    bool insideQuotes = false;

    for (char ch : input) {
        if (ch == '\"' || ch == '\'') {
            insideQuotes = !insideQuotes; // Toggle the insideQuotes flag
        } else if (ch == ' ' && !insideQuotes) {
            if (!currentPart.empty()) {
                this->tokens.push_back(currentPart);
                currentPart.clear();
            }
        } else {
            currentPart += ch;
        }
    }

    if (!currentPart.empty()) {
        this->tokens.push_back(currentPart);
    }
}