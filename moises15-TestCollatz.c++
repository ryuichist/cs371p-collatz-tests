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

struct TestCollatz : CppUnit::TestFixture 
{

	// -----
    // cycle length
    // -----
	void test_cycle_length_1 () 
	{
		int length = cycle_length(1);
		CPPUNIT_ASSERT(length == 1);
	}
	void test_cycle_length_2 () 
	{
		int length = cycle_length(1000000);
		CPPUNIT_ASSERT(length == 153);
	}
	void test_cycle_length_3 () 
	{
		int length = cycle_length(500000);
		CPPUNIT_ASSERT(length == 152);
	}
	void test_cycle_length_4 () 
	{
		int length = cycle_length(777);
		CPPUNIT_ASSERT(length == 34);
	}
	void test_cycle_length_5 () 
	{
		int length = cycle_length(666);
		CPPUNIT_ASSERT(length == 114);
	}
    // ----
    // read
    // ----

    void test_read_1 () 
	{
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);
	}
	
	void test_read_2 () 
	{
        std::istringstream r("100 200\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    100);
        CPPUNIT_ASSERT(j ==    200);
	}
	
	void test_read_3 () 
	{
        std::istringstream r("201 210\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    201);
        CPPUNIT_ASSERT(j ==    210);
	}

	void test_read_4 () 
	{
        std::istringstream r("900 1000\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    900);
        CPPUNIT_ASSERT(j ==   1000);
	}

	void test_read_5 () 
	{
        std::istringstream r("");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);
	}

    // ----
    // eval
    // ----

    void test_eval_1 () 
	{
        const int v = collatz_eval(1, 10);
        CPPUNIT_ASSERT(v == 20);
	}

    void test_eval_2 () 
	{
        const int v = collatz_eval(100, 200);
        CPPUNIT_ASSERT(v == 125);
	}

    void test_eval_3 () 
	{
        const int v = collatz_eval(201, 210);
        CPPUNIT_ASSERT(v == 89);}

    void test_eval_4 () 
	{
        const int v = collatz_eval(900, 1000);
        CPPUNIT_ASSERT(v == 174);
	}
	void test_eval_5 () 
	{
        const int v = collatz_eval(777, 666);
        CPPUNIT_ASSERT(v == 171);
	}
	
	

    // -----
    // print
    // -----

    void test_print_1 () 
	{
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");
	}
	void test_print_2 () 
	{
        std::ostringstream w;
        collatz_print(w, 100, 200, 125);
        CPPUNIT_ASSERT(w.str() == "100 200 125\n");
	}
	void test_print_3 () 
	{
        std::ostringstream w;
        collatz_print(w, 201, 210, 89);
        CPPUNIT_ASSERT(w.str() == "201 210 89\n");
	}
	void test_print_4 () 
	{
        std::ostringstream w;
        collatz_print(w, 900, 1000, 174);
        CPPUNIT_ASSERT(w.str() == "900 1000 174\n");
	}
	void test_print_5 () 
	{
        std::ostringstream w;
        collatz_print(w, 777, 666, 171);
        CPPUNIT_ASSERT(w.str() == "777 666 171\n");
	}

    // -----
    // solve
    // -----

    void test_solve () 
	{
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
	}

    // -----
    // suite
    // -----
    CPPUNIT_TEST_SUITE(TestCollatz);
	CPPUNIT_TEST(test_cycle_length_1);
	CPPUNIT_TEST(test_cycle_length_2);
	CPPUNIT_TEST(test_cycle_length_3);
	CPPUNIT_TEST(test_cycle_length_4);
	CPPUNIT_TEST(test_cycle_length_5);
    CPPUNIT_TEST(test_read_1);
	CPPUNIT_TEST(test_read_2);
	CPPUNIT_TEST(test_read_3);
	CPPUNIT_TEST(test_read_4);
	CPPUNIT_TEST(test_read_5);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
	CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_print_1);
	CPPUNIT_TEST(test_print_2);
	CPPUNIT_TEST(test_print_3);
	CPPUNIT_TEST(test_print_4);
	CPPUNIT_TEST(test_print_5);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () 
{
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestCollatz.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestCollatz::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
