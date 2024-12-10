//
// Created by pc on 12/6/2024.
//

#include "queryParser.h"
queryParser::queryParser(std::string &query) {
  stringstream ss(query);
  string word;
  while (ss >> word) tokens.push_back(word);
}

void queryParser::handleSelect() {
  string field = tokens[1];
  string table = tokens[3];
  string conditionField = tokens[5];
  string conditionVal = tokens[7].substr(1, tokens[7].size() - 2);

}