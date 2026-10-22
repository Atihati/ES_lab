#include <msp430.h>
#include "unity.h"
#include "testHalTimerB0.h"
#include "halTimerB0.h"
#include "halGPIO.h"
#include "halUCS.h"

// ##### Hilfsfunktionen #####

static unsigned char backlightIsOn(void)
{
    return (P8OUT & LCD_BL) ? 1 : 0;
}

static unsigned int timerCountsWithin(unsigned int ms)
{
    unsigned int before = TB0R;
    delayMsBlocked(ms);
    return TB0R - before;
}

// ##### Konfiguration #####

static void timerSourceIsSMCLK(void)
{
    TEST_ASSERT_EQUAL_UINT(TBSSEL__SMCLK, TB0CTL & TBSSEL_2);
}

static void timerRunsInUpMode(void)
{
    TEST_ASSERT_EQUAL_UINT(MC__UP, TB0CTL & MC);
}

static void inputDividerIsEight(void)
{
    TEST_ASSERT_EQUAL_UINT(ID__8, TB0CTL & ID);
}

static void expansionDividerIsEight(void)
{
    TEST_ASSERT_EQUAL_UINT(TBIDEX__8, TB0EX0 & TBIDEX);
}

static void compareInterruptIsEnabled(void)
{
    TEST_ASSERT_BITS_HIGH(CCIE, TB0CCTL0);
}

static void compareValueMatchesCalculation(void)
{
    TEST_ASSERT_EQUAL_UINT(TimerB0SetDesTime, TB0CCR0);
}

// ##### Verhalten #####

static void timerIsCounting(void)
{
    TEST_ASSERT_GREATER_THAN(0, timerCountsWithin(10));
}

static void backlightTogglesWithinHalfPeriod(void)
{
    unsigned char before = backlightIsOn();

    delayMsBlocked(300);

    TEST_ASSERT_NOT_EQUAL(before, backlightIsOn());
}

void testHalTimerB0Run(void)
{
    RUN_TEST(timerSourceIsSMCLK);
    RUN_TEST(timerRunsInUpMode);
    RUN_TEST(inputDividerIsEight);
    RUN_TEST(expansionDividerIsEight);
    RUN_TEST(compareInterruptIsEnabled);
    RUN_TEST(compareValueMatchesCalculation);
    RUN_TEST(timerIsCounting);
    RUN_TEST(backlightTogglesWithinHalfPeriod);
}
