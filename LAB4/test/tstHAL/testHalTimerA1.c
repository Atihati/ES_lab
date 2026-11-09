/*
 * testHalTimerA1.c
 *
 *  Created on: 09.11.2026
 *      Author: hrabo
 */
#include <msp430.h>
#include "unity.h"
#include "testHalTimerA1.h"
#include "halTimerA1.h"
#include "halGPIO.h"
#include "halUCS.h"

static void timerSourceIsSMCLK(void)
{
    TEST_ASSERT_EQUAL_UINT(TASSEL__SMCLK, TA1CTL & TASSEL_3);
}


static void compareValueMatchesCalculation(void)
{
    TEST_ASSERT_EQUAL_UINT(PWM_60HZ, TA1CCR0);
}

static void channelsAreInRightOutputMode(void)
{
    TEST_ASSERT_EQUAL_UINT(OUTMOD_7, TA1CCTL1 & OUTMOD_7);
    TEST_ASSERT_EQUAL_UINT(OUTMOD_7, TA1CCTL2 & OUTMOD_7);
}

static void compareRegistersAreZeroAfterInit(void)
{
    TEST_ASSERT_EQUAL_UINT(0, TA1CCR1);
    TEST_ASSERT_EQUAL_UINT(0, TA1CCR2);
}

void testHalTimerA1Run(void)
{
    RUN_TEST(timerSourceIsSMCLK);
    RUN_TEST(compareValueMatchesCalculation);
    RUN_TEST(channelsAreInRightOutputMode);
    RUN_TEST(compareRegistersAreZeroAfterInit);
    /*RUN_TEST(inputDividerIsEight);
    RUN_TEST(expansionDividerIsEight);
    RUN_TEST(compareInterruptIsEnabled);
    RUN_TEST(compareValueMatchesCalculation);
    RUN_TEST(timerIsCounting);
    RUN_TEST(backlightTogglesWithinHalfPeriod);
    */
}

