#pragma once
#ifndef CALCULATE_H
#define CALCULATE_H


#include<stdio.h>
#include<string.h>
#include<stack>
#include<iostream>
#include<string>
using namespace std;

void infix_to_suffix(char* infix, char* suffix);
double suffix_value(char* suffix);

#endif // !CALCULATE_H
