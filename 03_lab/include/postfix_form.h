#pragma once
#include "stacklist.h"
#include "stack.h"
#include <iostream>
#include <map>
#include <vector>

using namespace std;

string getPost(const string& simpleForm);

vector<char> getOper(const string& simpleForm);

int Calc(const string& postForm, map<char, int>& values);
