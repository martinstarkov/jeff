#pragma once

#include <Arduino.h>

#include "AllocationMetrics.h"

#define __ASSERT_USE_STDERR

#include <assert.h>

inline void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp) {
    // transmit diagnostic informations through serial link. 
    Serial.println(__func);
    Serial.println(__file);
    Serial.println(__lineno, DEC);
    Serial.println(__sexp);
    Serial.flush();
    // abort program execution.
    abort();
}

#define LOG(x) { Serial.println(x); }
#define LOG_(x) { Serial.print(x); }