#include "phone_number.h"
#include "../TestRunner/TestRunner.h"

int main() {
    TestRunner runner;
    {
        string countryCode{"7"};
        string cityCode{"495"};
        string localNumber{"111-22-33"};
        string internationalNumber{"+" + countryCode + "-" + cityCode + "-" + localNumber};
        runner.RunTest([&countryCode, &cityCode, &localNumber, &internationalNumber]() {
            PhoneNumber phoneNumber(internationalNumber);
            AssertEqual(phoneNumber.GetCountryCode(), countryCode, "Wrong country code +" + countryCode);
            AssertEqual(phoneNumber.GetCityCode(), cityCode, "Wrong city code " + cityCode);
            AssertEqual(phoneNumber.GetLocalNumber(), localNumber, "Wrong local number " + localNumber);
            AssertEqual(phoneNumber.GetInternationalNumber(), internationalNumber,
                        "Wrong international number " + internationalNumber);
        }, internationalNumber + " tests");
    }
    {
        string countryCode{"7"};
        string cityCode{"495"};
        string localNumber{"1112233"};
        string internationalNumber{"+" + countryCode + "-" + cityCode + "-" + localNumber};
        runner.RunTest([&countryCode, &cityCode, &localNumber, &internationalNumber]() {
            PhoneNumber phoneNumber(internationalNumber);
            AssertEqual(phoneNumber.GetCountryCode(), countryCode, "Wrong country code +" + countryCode);
            AssertEqual(phoneNumber.GetCityCode(), cityCode, "Wrong city code " + cityCode);
            AssertEqual(phoneNumber.GetLocalNumber(), localNumber, "Wrong local number " + localNumber);
            AssertEqual(phoneNumber.GetInternationalNumber(), internationalNumber,
                        "Wrong international number " + internationalNumber);
        }, internationalNumber + " tests");
    }
    {
        string countryCode{"323"};
        string cityCode{"22"};
        string localNumber{"460002"};
        string internationalNumber{"+" + countryCode + "-" + cityCode + "-" + localNumber};
        runner.RunTest([&countryCode, &cityCode, &localNumber, &internationalNumber]() {
            PhoneNumber phoneNumber(internationalNumber);
            AssertEqual(phoneNumber.GetCountryCode(), countryCode, "Wrong country code +" + countryCode);
            AssertEqual(phoneNumber.GetCityCode(), cityCode, "Wrong city code " + cityCode);
            AssertEqual(phoneNumber.GetLocalNumber(), localNumber, "Wrong local number " + localNumber);
            AssertEqual(phoneNumber.GetInternationalNumber(), internationalNumber,
                        "Wrong international number " + internationalNumber);
        }, internationalNumber + " tests");
    }
    {
        string countryCode{"1"};
        string cityCode{"2"};
        string localNumber{"coursera-cpp"};
        string internationalNumber{"+" + countryCode + "-" + cityCode + "-" + localNumber};
        runner.RunTest([&countryCode, &cityCode, &localNumber, &internationalNumber]() {
            PhoneNumber phoneNumber(internationalNumber);
            AssertEqual(phoneNumber.GetCountryCode(), countryCode, "Wrong country code +" + countryCode);
            AssertEqual(phoneNumber.GetCityCode(), cityCode, "Wrong city code " + cityCode);
            AssertEqual(phoneNumber.GetLocalNumber(), localNumber, "Wrong local number " + localNumber);
            AssertEqual(phoneNumber.GetInternationalNumber(), internationalNumber,
                        "Wrong international number " + internationalNumber);
        }, internationalNumber + " tests");
    }
    {
        string countryCode{"1"};
        string cityCode{"2"};
        string localNumber{"333"};
        runner.RunTest([&countryCode, &cityCode, &localNumber]() {
            bool exceptionOccurred{};
            try {
                PhoneNumber phoneNumber(countryCode + "-" + cityCode + "-" + localNumber);
            }
            catch (const invalid_argument& ex)
            {
                exceptionOccurred = true;
            }
            Assert(exceptionOccurred, "invalid_argument exception wasn't caught!");
        }, countryCode + "-" + cityCode + "-" + localNumber + " tests");
    }
    {
        string countryCode{"7"};
        string cityCode{"1233"};
        runner.RunTest([&countryCode, &cityCode]() {
            bool exceptionOccurred{};
            try {
                PhoneNumber phoneNumber("+" + countryCode + "-" + cityCode);
            }
            catch (const invalid_argument& ex)
            {
                exceptionOccurred = true;
            }
            Assert(exceptionOccurred, "invalid_argument exception wasn't caught!");
        }, "+" + countryCode + "-" + cityCode + " tests");
    }
    return 0;
}