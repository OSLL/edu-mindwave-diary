#include "values.h"

int Meditation = rand() % 100;
int Concentration = rand() % 100;

int getMeditationValue()
{
    Meditation += rand() % 5 - 2;
    return Meditation;
}

int getConcentrationValue()
{
    Concentration += rand() % 5 - 2;
    return Concentration;
}
