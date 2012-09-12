// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2012
// Glenn P. Downing
// --------------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    HelperMacros.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -lcppunit -ldl -Wall TestCollatz.c++ -o TestCollatz.c++.app
    % valgrind TestCollatz.c++.app >& TestCollatz.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Collatz.h"

// -----------
// TestCollatz
// -----------

struct TestCollatz : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read_1 () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}
		
    void test_read_2 () {
        std::istringstream r("46 1026\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    46);
        CPPUNIT_ASSERT(j ==   1026);}
		
    void test_read_3 () {
        std::istringstream r("4522 10222\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    4522);
        CPPUNIT_ASSERT(j ==   10222);}
		
    void test_read_4 () {
        std::istringstream r("4511111 10111112\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    4511111);
        CPPUNIT_ASSERT(j ==   10111112);}

    // ----
    // eval - tests for arrayEval unneeded, since eval just calls arrayEval
    // ----

    void test_eval_1 () {
        const int v = collatz_eval(1, 10);
        CPPUNIT_ASSERT(v == 20);}

    void test_eval_2 () {
        const int v = collatz_eval(100, 200);
        CPPUNIT_ASSERT(v == 125);}

    void test_eval_3 () {
        const int v = collatz_eval(201, 210);
        CPPUNIT_ASSERT(v == 89);}

    void test_eval_4 () {
        const int v = collatz_eval(900, 1000);
        CPPUNIT_ASSERT(v == 174);}

    void test_eval_5 () {
        const int v = collatz_eval(6, 6);
        CPPUNIT_ASSERT(v == 9);}
		
    void test_eval_6 () {
        const int v = collatz_eval(1, 999999);
        CPPUNIT_ASSERT(v == 525);}
		
    void test_eval_7 () {
        const int v = collatz_eval(12, 4531);
        CPPUNIT_ASSERT(v == 238);}

	//----------
	//solveRange
	//----------
	
	void test_solveRange_1 () {
        const int v = solveRange(1, 10);
        CPPUNIT_ASSERT(v == 20);}

    void test_solveRange_2 () {
        const int v = solveRange(100, 200);
        CPPUNIT_ASSERT(v == 125);}

    void test_solveRange_3 () {
        const int v = solveRange(201, 210);
        CPPUNIT_ASSERT(v == 89);}

    void test_solveRange_4 () {
        const int v = solveRange(900, 1000);
        CPPUNIT_ASSERT(v == 174);}

    void test_solveRange_5 () {
        const int v = solveRange(6, 6);
        CPPUNIT_ASSERT(v == 9);}
		
    void test_solveRange_6 () {
        const int v = solveRange(1, 999999);
        CPPUNIT_ASSERT(v == 525);}
		
    void test_solveRange_7 () {
        const int v = solveRange(12, 4531);
        CPPUNIT_ASSERT(v == 238);}
		
    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    void test_print_2 () {
        std::ostringstream w;
        collatz_print(w, 5, 85, 20);
        CPPUNIT_ASSERT(w.str() == "5 85 20\n");}

    void test_print_3 () {
        std::ostringstream w;
        collatz_print(w, 9, 9, 9);
        CPPUNIT_ASSERT(w.str() == "9 9 9\n");}

    void test_print_4 () {
        std::ostringstream w;
        collatz_print(w, 2, 2, 22);
        CPPUNIT_ASSERT(w.str() == "2 2 22\n");}
		
	// ---------
	// fillArray
	// ---------
	void test_fillArray_1(){
		fillArray(2000);
		CPPUNIT_ASSERT(ranges[0] == solveRange(1,1000));
		CPPUNIT_ASSERT(ranges[1] == solveRange(1001,2000));
		CPPUNIT_ASSERT(ranges[2] != solveRange(2001,3000));
	}
	void test_fillArray_2(){
		CPPUNIT_ASSERT(ranges[0] == solveRange(1,1000));
		CPPUNIT_ASSERT(ranges[1] == solveRange(1001,2000));
		fillArray(5000);
		CPPUNIT_ASSERT(ranges[2] == solveRange(2001,3000));
	}
	void test_fillArray_3(){
		CPPUNIT_ASSERT(ranges[3] == solveRange(3001,4000));
	}

    // -----
    // solve
    // -----
	
    void test_solve_1 () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
		
    void test_solve_2 () {
		std::istringstream r("1 1000\n1001 2000\n2001 3000\n3001 4000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1000 179\n1001 2000 182\n2001 3000 217\n3001 4000 238\n");}

		
    void test_solve_3 () {
        std::istringstream r("1 12345\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 12345 268\n");}

		
    void test_solve_4 () {
        std::istringstream r("900 1000\n201 210\n100 200\n1 10\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "900 1000 174\n201 210 89\n100 200 125\n1 10 20\n");}


    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_4);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_eval_7);
    CPPUNIT_TEST(test_fillArray_1);
    CPPUNIT_TEST(test_fillArray_2);
    CPPUNIT_TEST(test_fillArray_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_print_4);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_4);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestCollatz.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestCollatz::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
