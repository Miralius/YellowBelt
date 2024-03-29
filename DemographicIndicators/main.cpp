#include <iostream>
// The #if is needed for stepik check system submitting if we use the whole file
#if __GNUC__ == 13 && __GNUC_MINOR__ == 2
#include "DemographicUtilities.h"
#endif


void PrintStats(vector<Person> persons) {
    int peopleMedianAge = ComputeMedianAge(persons.cbegin(), persons.cend());

    auto firstWoman = partition(persons.begin(), persons.end(), [](const auto &person) {
        return person.gender == Gender::MALE;
    });
    int femaleMedianAge = ComputeMedianAge(firstWoman, persons.end());
    int maleMedianAge = ComputeMedianAge(persons.begin(), firstWoman);

    auto firstUnemployedWoman = partition(firstWoman, persons.end(), [](const auto &woman) {
        return woman.is_employed;
    });
    int employedFemaleMedianAge = ComputeMedianAge(firstWoman, firstUnemployedWoman);
    int unemployedFemaleMedianAge = ComputeMedianAge(firstUnemployedWoman, persons.end());

    auto firstUnemployedMan = partition(persons.begin(), firstWoman, [](const auto &man) {
        return man.is_employed;
    });
    int employedMaleMedianAge = ComputeMedianAge(persons.begin(), firstUnemployedMan);
    int unemployedMaleMedianAge = ComputeMedianAge(firstUnemployedMan, firstWoman);

    cout << "Median age = " << peopleMedianAge << "\nMedian age for females = " << femaleMedianAge
         << "\nMedian age for males = " << maleMedianAge << "\nMedian age for employed females = "
         << employedFemaleMedianAge << "\nMedian age for unemployed females = " << unemployedFemaleMedianAge
         << "\nMedian age for employed males = " << employedMaleMedianAge << "\nMedian age for unemployed males = "
         << unemployedMaleMedianAge;
}

int main() {
    vector<Person> persons = {
            {31, Gender::MALE, false},
            {40, Gender::FEMALE, true},
            {24, Gender::MALE, true},
            {20, Gender::FEMALE, true},
            {80, Gender::FEMALE, false},
            {78, Gender::MALE, false},
            {10, Gender::FEMALE, false},
            {55, Gender::MALE, true},
    };
    PrintStats(persons);
    return 0;
}