#include "tests.h"
#include <exception>

void TestCorrectInput() {
    PhoneNumber ph_number("+1-2-3");

    try {
        ph_number = PhoneNumber("1-dsd-asassd");
        AssertEqual(true, false, "Error in TestCorrectInput");
    } catch (invalid_argument& ex) {
        AssertEqual(true, true, "");
    }

    try {
        ph_number = PhoneNumber("1-dsdasassd");
        AssertEqual(true, false, "Error in TestCorrectInput");
    } catch (invalid_argument& ex) {
        AssertEqual(true, true, "");
    }

    try {
        ph_number = PhoneNumber("+1dsd-asassd");
        AssertEqual(true, false, "Error in TestCorrectInput");
    } catch (invalid_argument& ex) {
        AssertEqual(true, true, "");
    }

    try {
        ph_number = PhoneNumber("+1dsdasassd");
        AssertEqual(true, false, "Error in TestCorrectInput");
    } catch (invalid_argument& ex) {
        AssertEqual(true, true, "");
    }

    try {
        ph_number = PhoneNumber("+--");
        AssertEqual(true, false, "Error in TestCorrectInput");
    } catch (invalid_argument& ex) {
        AssertEqual(true, true, "");
    }
    
};

void TestNumerical() {
    PhoneNumber ph_number("+1-2-3");
    AssertEqual(ph_number.GetCountryCode(), "1", "");
    AssertEqual(ph_number.GetCityCode(), "2", "");
    AssertEqual(ph_number.GetLocalNumber(), "3", "");
    AssertEqual(ph_number.GetInternationalNumber(), "+1-2-3", "");

    Assert(ph_number.GetCountryCode() != "2", "");

    ph_number = PhoneNumber("+7-495-111-22-33");
    AssertEqual(ph_number.GetCountryCode(), "7", "");
    AssertEqual(ph_number.GetCityCode(), "495", "");
    AssertEqual(ph_number.GetLocalNumber(), "111-22-33", "");
    AssertEqual(ph_number.GetInternationalNumber(), "+7-495-111-22-33", "");

    ph_number = PhoneNumber("+375-29-1234567");
    AssertEqual(ph_number.GetCountryCode(), "375", "");
    AssertEqual(ph_number.GetCityCode(), "29", "");
    AssertEqual(ph_number.GetLocalNumber(), "1234567", "");
    AssertEqual(ph_number.GetInternationalNumber(), "+375-29-1234567", "");
};

void TestAnyCharacters() {
    PhoneNumber ph_number("+1-dsd-asassd");
    AssertEqual(ph_number.GetCountryCode(), "1", "");
    AssertEqual(ph_number.GetCityCode(), "dsd", "");
    AssertEqual(ph_number.GetLocalNumber(), "asassd", "");
    AssertEqual(ph_number.GetInternationalNumber(), "+1-dsd-asassd", "");
    
    Assert(ph_number.GetCountryCode() != "2", "");
};

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestCorrectInput, "TestCorrectInput");
    tr.RunTest(TestNumerical, "TestNumerical");
    tr.RunTest(TestAnyCharacters, "TestAnyCharacters");
}