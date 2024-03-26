//
// Created by Yaroslav Svitlytskyi on 18.03.2024.
//

#include "indicator.h"

void Indicator::handle_check() {

}

/**
     * Indicated initialization process success.
     */
static void toggle_initialization_success();

/**
 * Indicated initialization process failure.
 */
static void toggle_initialization_failure();

/**
 * Indicated operation action success.
 */
static void toggle_action_success();

/**
 * Indicated operation action failure.
 */
static void toggle_action_failure();