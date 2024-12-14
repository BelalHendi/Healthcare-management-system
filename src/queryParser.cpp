#include <iostream>
#include "queryParser.h"

#include <AppointmentIndexService.h>
#include <appointmentSecondryIndexService.h>
#include <DoctorIndexService.h>
#include <DoctorSecondryIndexService.h>
#include <SI.h>
#include <regex>
#include "PrimaryIndexService.h"
#include "doctorFileService.h"
#include "offsetService.h"
using namespace std;

void queryParser::querySplitter(std::string &query) {
    this->splitCommand(query);
}

void queryParser::parseQuery() {
    regex digitRegex("^[0-9]+$");
    if(this->tokens[3] == "Doctors") {
        vector<doctor> docs;
        vector<int> id;
        offsetService offs;
        if(this->tokens[5] == "DoctorID"){
            if(!regex_match(this->tokens[7], digitRegex)) {
                cout << "This should only contain Integer values\n";
                cout << "Write the query correctly\n";
                this->tokens.clear();
                return;
            }
            id.push_back(DoctorIndexService::getInstance()->getById(this->tokens[7]));
            if (id.empty()) {
                cout << "This Doctor does not exist\n";
                this->tokens.clear();
                return;
            }
            docs = offs.offsetToDoctors(id);
        } else {
            if(regex_match(this->tokens[7], digitRegex)) {
                cout << "This should only contain String values\n";
                cout << "Write the query correctly\n";
                this->tokens.clear();
                return;
            }
            vector<string> secID;
            secID = doctorSecondryIndexService::getInstance()->search(this->tokens[7]);
            if (secID.empty()) {
                cout << "Doctors with such " << this->tokens[5] << " do not exist\n";
                this->tokens.clear();
                return;
            }
            for (int i = 0; i < secID.size(); i++) {
                id.push_back(DoctorIndexService::getInstance()->getById(secID[i]));
            }
            docs = offs.offsetToDoctors(id);
        }
        if(this->tokens[1] == "all") {
            for(int i = 0; i < docs.size(); i++) {
                cout << "DoctorID: " << docs[i].id << " | " << "DoctorName: " << docs[i].name << " | " << "DoctorAddress: " << docs[i].address << endl;
            }
        } else if(this->tokens[1] == "DoctorName") {
            for(int i = 0; i < docs.size(); i++) {
                cout << "DoctorName: " << docs[i].name << endl;
            }
        } else if(this->tokens[1] == "DoctorAddress") {
            for(int i = 0; i < docs.size(); i++) {
                cout << "DoctorAddress: " << docs[i].address << endl;
            }
        } else if(this->tokens[1] == "DoctorID") {
            for(int i = 0; i < docs.size(); i++) {
                cout << "DoctorID: " << docs[i].id << endl;
            }
        }
    } else if(this->tokens[3] == "Appointments") {

        vector<appointment> docs;
        offsetService offs;
        vector<int> id;
        if(this->tokens[5] == "AppointmentID"){
            if(!regex_match(this->tokens[7], digitRegex)) {
                cout << "This should only contain Integer values\n";
                cout << "Write the query correctly\n";
                this->tokens.clear();
                return;
            }
            id.push_back(AppointmentIndexService::getInstance()->getById(this->tokens[7]));
            if (id[0] == -1) {
                cout << "This Appointment does not exist\n";
                this->tokens.clear();
                return;
            }
            docs = offs.offsetToAppointments(id);
        } else {
            if(regex_match(this->tokens[7], digitRegex)){
                if (this->tokens[5] != "DoctorID") {
                    cout << "This should only contain String values\n";
                    cout << "Write the query correctly\n";
                    this->tokens.clear();
                    return;
                }
            }
            vector<string> secID;
            secID = appointmentSecondryIndexService::getInstance()->search(this->tokens[7]);
            if (secID.empty()) {
                cout << "Appointments with such " << this->tokens[5] << " do not exist\n";
                this->tokens.clear();
                return;
            }
            for (int i = 0; i < secID.size(); i++) {
                id.push_back(AppointmentIndexService::getInstance()->getById(secID[i]));
            }
            docs = offs.offsetToAppointments(id);
        }
        if(this->tokens[1] == "all") {
            for(int i = 0; i < docs.size(); i++) {
                cout << "AppointmentID: " << docs[i].AppointmentID << " | " << "AppointmentDate: " << docs[i].AppointmentDate << " | " << "DoctorID: " << docs[i].DoctorID << endl;
            }
        } else if(this->tokens[1] == "AppointmentID") {
            for(int i = 0; i < docs.size(); i++) {
                cout <<  "AppointmentID: " << docs[i].AppointmentID << endl;
            }
        } else if(this->tokens[1] == "AppointmentDate") {
            for(int i = 0; i < docs.size(); i++) {
                cout << "AppointmentDate: " << docs[i].AppointmentDate << endl;
            }
        } else if(this->tokens[1] == "DoctorID") {
            for(int i = 0; i < docs.size(); i++) {
                cout << "DoctorID: " << docs[i].DoctorID << endl;
            }
        }
    }
    this->tokens.clear();
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