
#include <gtest.h>
#include "../include/postfix_form.h"


TEST(getPost, can_create_single_operand_example) {
	char* st = "A+C";
	string a = getPost(st);
	EXPECT_EQ(a, "AC+");
}
TEST(getPost, can_create_single_operand_with_brackets_example) {
	char* st = "(A+C)";
	string a = getPost(st);
	EXPECT_EQ(a, "AC+" );
}
TEST(getPost, can_create_example_with_prioritized_with_brackets) {
	char* st = "(A+C)*B";
	char* st1 = "AC+B*";
	string a = getPost(st);
	EXPECT_EQ(a, st1);
}
TEST(getPost, can_create_example_with_prioritized_and_more_arguments) {
	char* st = "T*A+C*B";
	char* st1 = "TA*CB*+";
	string a = getPost(st);
	EXPECT_EQ(a, st1);
}
TEST(getPost, can_create_example_with_prioritized_and_more_arguments_with_more_brackets) {
	char* st = "(A+C)*(B-G/Q)-((W/E)+P)";
	char* st1 = "AC+BGQ/-*WE/P+-";
	string a = getPost(st);
	EXPECT_EQ(a, st1);
}



TEST(getOper, can_getoperand_vector) {
	char* st = "A+B";
	vector<char> v = { 'A','B' };
	string a = getPost(st);
	vector<char> v1 = getOper(st);
	EXPECT_EQ(v, v1);
}




TEST(Calc, can_sum_two_elements) {
	char* st = "A+C";
	map<char, int> s;
	s.insert({ 'A', 2 });
	s.insert({ 'C', 5 });
	string a = getPost(st);
	EXPECT_EQ(7, Calc(a, s));
}
TEST(Calc, can_subtract_two_elements) {
	char* st = "C-A";
	map<char, int> s;
	s.insert({ 'A', 2 });
	s.insert({ 'C', 5 });
	string a = getPost(st);
	EXPECT_EQ(3, Calc(a, s));
}
TEST(Calc, can_subtract_two_elements_with_negative_answer) {
	char* st = "A-C";
	map<char, int> s;
	s.insert({ 'A', 2 });
	s.insert({ 'C', 5 });
	string a = getPost(st);
	EXPECT_EQ(-3, Calc(a, s));
}
TEST(Calc, can_divide_two_elements) {
	char* st = "A/C";
	map<char, int> s;
	s.insert({ 'A', 9 });
	s.insert({ 'C', 3 });
	string a = getPost(st);
	EXPECT_EQ(3, Calc(a, s));
}
TEST(Calc, can_sum_three_elements_with_brackets) {
	char* st = "(A+C)+B";
	map<char, int> s;
	s.insert({ 'A', 2 });
	s.insert({ 'C', 5 });
	s.insert({ 'B', 3 });
	string a = getPost(st);
	EXPECT_EQ(10, Calc(a, s));
}
TEST(Calc, can_sum_and_subtract_three_elements_with_brackets) {
	char* st = "(A+C)-B";
	map<char, int> s;
	s.insert({ 'A', 2 });
	s.insert({ 'C', 5 });
	s.insert({ 'B', 3 });
	string a = getPost(st);
	EXPECT_EQ(4, Calc(a, s));
}
TEST(Calc, can_subtract_and_sum_three_elements_with_brackets) {
	char* st = "(C-A)+B";
	map<char, int> s;
	s.insert({ 'A', 2 });
	s.insert({ 'C', 5 });
	s.insert({ 'B', 3 });
	string a = getPost(st);
	EXPECT_EQ(6, Calc(a, s));
}
TEST(Calc, can_sum_and_multiply_three_elements_with_brackets) {
	char* st = "(C+A)*B";
	map<char, int> s;
	s.insert({ 'A', 2 });
	s.insert({ 'C', 5 });
	s.insert({ 'B', 3 });
	string a = getPost(st);
	EXPECT_EQ(21, Calc(a, s));
}
TEST(Calc, can_multiply_and_sum_three_elements_with_brackets) {
	char* st = "(C*A)+B";
	map<char, int> s;
	s.insert({ 'A', 2 });
	s.insert({ 'C', 5 });
	s.insert({ 'B', 3 });
	string a = getPost(st);
	EXPECT_EQ(13, Calc(a, s));
}
TEST(Calc, can_sum_and_multiply_three_elements) {
	char* st = "C+A*B";
	map<char, int> s;
	s.insert({ 'A', 2 });
	s.insert({ 'C', 5 });
	s.insert({ 'B', 3 });
	string a = getPost(st);
	EXPECT_EQ(11, Calc(a, s));
}
TEST(Calc, can_multiply_and_multiply_three_elements) {
	char* st = "C*A*B";
	map<char, int> s;
	s.insert({ 'A', 2 });
	s.insert({ 'C', 5 });
	s.insert({ 'B', 3 });
	string a = getPost(st);
	EXPECT_EQ(30, Calc(a, s));
}
TEST(Calc, can_multiply_brackets) {
	char* st = "(A+C)*(B-T)";
	map<char, int> s;
	s.insert({ 'A', 2 });
	s.insert({ 'C', 5 });
	s.insert({ 'B', 3 });
	s.insert({ 'T', 1 });
	string a = getPost(st);
	EXPECT_EQ(14, Calc(a, s));
}
TEST(Calc, can_divide_and_subtract_elements) {
	char* st = "A/B-C";
	map<char, int> s;
	s.insert({ 'A', 6 });
	s.insert({ 'C', 5 });
	s.insert({ 'B', 3 });
	string a = getPost(st);
	EXPECT_EQ(-3, Calc(a, s));
}
TEST(Calc, can_subtract_and_divide_elements) {
	char* st = "C-A/B";
	map<char, int> s;
	s.insert({ 'A', 6 });
	s.insert({ 'C', 5 });
	s.insert({ 'B', 3 });
	string a = getPost(st);
	EXPECT_EQ(3, Calc(a, s));
}
