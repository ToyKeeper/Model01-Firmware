// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#define DEBUG_SERIAL false

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif

// comment this out to disable oneshot
//#define USE_ONESHOT
// comment this out to disable tapdance
//#define USE_TAPDANCE

/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */


// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"
#include "MouseWrapper.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for "Numpad" mode, which is mostly just the Numpad specific LED mode
//#include "Kaleidoscope-NumPad.h"

// Support for an "LED off mode"
#include "LED-Off.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
//#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for LED modes that set all LEDs to a single color
#include "Kaleidoscope-LEDEffect-SolidColor.h"

// Support for an LED mode that makes all the LEDs 'breathe'
#include "Kaleidoscope-LEDEffect-Breathe.h"

// Support for an LED mode that makes a red pixel chase a blue pixel across the keyboard
#include "Kaleidoscope-LEDEffect-Chase.h"

// Support for LED modes that pulse the keyboard's LED in a rainbow pattern
#include "Kaleidoscope-LEDEffect-Rainbow.h"

// Support for an LED mode that lights up the keys as you press them
#include "Kaleidoscope-LED-Stalker.h"

// ToyKeeper's water effect
#include "Kaleidoscope-LED-Wavepool.h"

// Support for an LED mode that prints the keys you press in letters 4px high
//#include "Kaleidoscope-LED-AlphaSquare.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-Model01-TestMode.h"

// make the shift keys double as paren keys
#include "Kaleidoscope-SpaceCadet.h"

//#include "kaleidoscope/hid.h"

#ifdef USE_ONESHOT
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-LED-ActiveModColor.h"
#endif

#ifdef USE_TAPDANCE
#include <Kaleidoscope-TapDance.h>
#endif

/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

//#define MACRO_VERSION_INFO 1
//#define Macro_VersionInfo M(MACRO_VERSION_INFO)
//#define MACRO_ANY 2
////#define NUMPAD_KEYMAP 2
enum { MACRO_VERSION_INFO,
       MACRO_ANY
     };
#define Macro_Any M(MACRO_ANY)



/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   the special nature of the PROG key
  *   keeping NUM and FN consistent and accessible on all layers
  *
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */

//enum { QWERTY, NUMPAD, FUNCTION }; // layers

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

/*
#define GENERIC_FN2  KEYMAP_STACKED ( \
___,      Key_F1,           Key_F2,      Key_F3,     Key_F4,        Key_F5,           XXX,         \
Key_Tab,  ___,              Key_mouseUp, ___,        Key_mouseBtnR, Key_mouseWarpEnd, Key_mouseWarpNE, \
Key_Home, Key_mouseL,       Key_mouseDn, Key_mouseR, Key_mouseBtnL, Key_mouseWarpNW,                   \
Key_End,  Key_PrintScreen,  Key_Insert,  ___,        Key_mouseBtnM, Key_mouseWarpSW,  Key_mouseWarpSE, \
                                            Key_LeftControl, Key_Delete, Key_LeftGui, Key_LeftShift,  \
                                                                ___,   \
\
Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                  Key_F9,          Key_F10,          Key_F11, \
Consumer_PlaySlashPause,    Consumer_ScanNextTrack, Key_LeftCurlyBracket,     Key_RightCurlyBracket,   Key_LeftBracket, Key_RightBracket, Key_F12, \
                            Key_LeftArrow,          Key_DownArrow,            Key_UpArrow,             Key_RightArrow,  ___,              ___, \
Key_Menu,                   Consumer_Mute,          Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,            Key_Backslash,    Key_Pipe, \
Key_RightShift, Key_RightAlt, Key_Enter, Key_RightControl, \
___ \
)
*/
#define GENERIC_FN2  KEYMAP_STACKED ( \
Key_Backslash,Key_F1,    Key_F2,            Key_F3,       Key_F4,            Key_F5,           XXX, \
Key_Tab,      ___,       Key_mouseScrollUp, Key_mouseUp,  Key_mouseScrollDn, ___,              ___, \
Key_Home,     ___,       Key_mouseL,        Key_mouseDn,  Key_mouseR,        ___,                   \
Key_End,      ___,       Key_mouseBtnL,     Key_mouseBtnM,Key_mouseBtnR,     ___,              ___, \
                                            ___, Key_Delete, ___, ___,  \
                                                                ___,   \
\
___,            Key_F6,                 Key_F7,                   Key_F8,                  Key_F9,          Key_F10,          Key_F11, \
___,            ___,                    ___,                      Key_UpArrow,             ___,             ___,              Key_RightBracket, \
                ___,                    Key_LeftArrow,            Key_DownArrow,           Key_RightArrow,  ___,              Key_Enter, \
Key_Menu,       ___,                    ___,                      ___,                     ___,             ___,              ___, \
___, ___, ___, ___, \
___ \
)

#if 0
const Key keymaps[][ROWS][COLS] PROGMEM = {

  [QWERTY] = KEYMAP_STACKED
  (___,          Key_1, Key_2, Key_3, Key_4, Key_5, Key_LEDEffectNext,
   Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
   Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
   Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
   ShiftToLayer(FUNCTION),

   M(MACRO_ANY),  Key_6, Key_7, Key_8,     Key_9,         Key_0,         LockLayer(NUMPAD),
   Key_Enter,     Key_Y, Key_U, Key_I,     Key_O,         Key_P,         Key_Equals,
                  Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_Quote,
   Key_RightAlt,  Key_N, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
   Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
   ShiftToLayer(FUNCTION)),


  [NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   M(MACRO_VERSION_INFO),  ___, Key_Keypad7, Key_Keypad8,   Key_Keypad9,        Key_KeypadSubtract, ___,
   ___,                    ___, Key_Keypad4, Key_Keypad5,   Key_Keypad6,        Key_KeypadAdd,      ___,
                           ___, Key_Keypad1, Key_Keypad2,   Key_Keypad3,        Key_Equals,         Key_Quote,
   ___,                    ___, Key_Keypad0, Key_KeypadDot, Key_KeypadMultiply, Key_KeypadDivide,   Key_Enter,
   ___, ___, ___, ___,
   ___),

  [FUNCTION] =  KEYMAP_STACKED
  (___,      Key_F1,           Key_F2,      Key_F3,     Key_F4,        Key_F5,           XXX,
   Key_Tab,  ___,              Key_mouseUp, ___,        Key_mouseBtnR, Key_mouseWarpEnd, Key_mouseWarpNE,
   Key_Home, Key_mouseL,       Key_mouseDn, Key_mouseR, Key_mouseBtnL, Key_mouseWarpNW,
   Key_End,  Key_PrintScreen,  Key_Insert,  ___,        Key_mouseBtnM, Key_mouseWarpSW,  Key_mouseWarpSE,
   ___, Key_Delete, ___, ___,
   ___,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   Consumer_PlaySlashPause,    Consumer_ScanNextTrack, Key_LeftCurlyBracket,     Key_RightCurlyBracket,    Key_LeftBracket, Key_RightBracket, Key_F12,
                               Key_LeftArrow,          Key_DownArrow,            Key_UpArrow,              Key_RightArrow,  ___,              ___,
   Key_PcApplication,          Consumer_Mute,          Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             Key_Backslash,    Key_Pipe,
   ___, ___, Key_Enter, ___,
   ___)

};

#endif  // if 0, default keymap

#ifdef USE_ONESHOT
#define My_LeftCtrl OSM(LeftControl)
#define My_RightCtrl OSM(RightControl)
#define My_LeftShift OSM(LeftShift)
#define My_RightShift OSM(RightShift)
#define My_LeftAlt OSM(LeftAlt)
#define My_LeftGui OSM(LeftGui)
#define My_Fn OSL(1)
#else
#define My_LeftCtrl Key_LeftControl
#define My_RightCtrl Key_RightControl
#define My_LeftShift Key_LeftShift
#define My_RightShift Key_RightShift
#define My_LeftAlt Key_LeftAlt
#define My_LeftGui Key_LeftGui
#define My_Fn Key_Keymap1_Momentary
#endif

#ifdef USE_TAPDANCE
#define Key_Moon TD(0)
#define Key_Sun TD(1)
#else
#define Key_Moon Key_Minus
#define Key_Sun Key_Equals
#endif

enum { TK_QWERTY, FUNCTION }; // layers

const Key keymaps[][ROWS][COLS] PROGMEM = {

  [TK_QWERTY] = KEYMAP_STACKED
  (
    Key_Escape,   Key_1, Key_2, Key_3, Key_4, Key_5, Key_LEDEffectNext,
    Key_Tab,      Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Moon,
    Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G,
    Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Insert,
    My_LeftCtrl, Key_Backspace, My_LeftShift, My_LeftGui,
    My_Fn,

    Macro_Any, Key_6, Key_7, Key_8,     Key_9,      Key_0,         Key_Backtick,
    Key_Sun,   Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_LeftBracket,
               Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,
    Key_Minus, Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Equals,
    My_LeftAlt, My_RightShift, Key_Spacebar, My_RightCtrl,
    My_Fn
  ),


  [FUNCTION] =  KEYMAP_STACKED
  (
    Key_Backslash,Key_F1, Key_F2,            Key_F3,       Key_F4,            Key_F5, XXX,
    Key_Tab,      ___,    Key_mouseScrollUp, Key_mouseUp,  Key_mouseScrollDn, ___,    ___,
    Key_Home,     ___,    Key_mouseL,        Key_mouseDn,  Key_mouseR,        ___,
    Key_End,      ___,    Key_mouseBtnL,     Key_mouseBtnM,Key_mouseBtnR,     ___,    ___,
    ___, Key_Delete, ___, ___,
    ___,

    ___,      Key_F6, Key_F7,        Key_F8,        Key_F9,         Key_F10, Key_F11,
    ___,      ___,    ___,           Key_UpArrow,   ___,            ___,     Key_RightBracket,
              ___,    Key_LeftArrow, Key_DownArrow, Key_RightArrow, ___,     Key_Enter,
    Key_Menu, ___,    ___,           ___,           ___,            ___,     ___,
    ___, ___, ___, ___,
    ___
  )

};

/*
#define NUMPAD KEYMAP_STACKED  (\
    ___, ___, ___, ___, ___, ___, ___,  \
    ___, ___, ___, ___, ___, ___, ___,  \
    ___, ___, ___, ___, ___, ___,       \
    ___, ___, ___, ___, ___, ___, ___,  \
               ___, ___, ___, ___,  \
                 Key_Keymap1_Momentary, \
\
\
    Macro_VersionInfo,  ___, Key_Keypad7, Key_Keypad8,   Key_Keypad9,        Key_KeypadSubtract, ___, \
    ___, ___, Key_Keypad4, Key_Keypad5,   Key_Keypad6,        Key_KeypadAdd,      ___, \
         ___, Key_Keypad1, Key_Keypad2,   Key_Keypad3,        Key_Equals,         Key_Quote, \
    ___, ___, Key_Keypad0, Key_KeypadDot, Key_KeypadMultiply, Key_KeypadDivide,   Key_Enter, \
    ___, ___, ___, ___, \
    Key_Keymap1_Momentary \
)
*/

/*
#define QWERTY KEYMAP_STACKED ( \
    ___,          Key_1, Key_2, Key_3, Key_4, Key_5, Key_LEDEffectNext, \
    Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,           \
    Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G,                    \
    Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,        \
    Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,         \
                          Key_KeymapNext_Momentary,     \
\
    Macro_Any,       Key_6, Key_7, Key_8,     Key_9,      Key_0,         Key_ToggleNumlock, \
    Key_Enter,     Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_Equals,       \
                   Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,       \
    Key_RightAlt,  Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Minus,       \
    Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,                   \
    Key_KeymapNext_Momentary \
)
*/

#define TK_QWERTY KEYMAP_STACKED ( \
    Key_Escape,   Key_1, Key_2, Key_3, Key_4, Key_5, Key_LEDEffectNext, \
    Key_Tab,      Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Moon,          \
    Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G,                    \
    Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Insert,        \
    My_LeftCtrl, Key_Backspace, My_LeftShift, My_LeftGui,         \
    My_Fn, \
\
    Macro_Any,     Key_6, Key_7, Key_8,     Key_9,      Key_0,         Key_Backtick,      \
    Key_Sun,       Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_LeftBracket,   \
                   Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,         \
    Key_Minus,     Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Equals,        \
    My_LeftAlt,  My_RightShift, Key_Spacebar, My_RightCtrl, \
    My_Fn \
)

/*
const Key keymaps[][ROWS][COLS] PROGMEM = {
  TK_QWERTY,
  GENERIC_FN2,
  //NUMPAD
};
*/

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */

static void anyKeyMacro(uint8_t keyState) {
  static Key lastKey;
  if (keyToggledOn(keyState))
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey);
}


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(keyState);
    break;

  case MACRO_ANY:
    anyKeyMacro(keyState);
    break;
  }
  return MACRO_NONE;
}

#ifdef USE_TAPDANCE
void tapDanceAction(uint8_t tap_dance_index, uint8_t tap_count, 
                    kaleidoscope::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_index) {
  case 0:
    return tapDanceActionKeys(tap_count, tap_dance_action,
                              Key_LeftParen, Key_Minus, LSHIFT(Key_Minus));
  case 1:
    return tapDanceActionKeys(tap_count, tap_dance_action,
                              Key_RightParen, Key_Equals, LSHIFT(Key_Equals));
  }
}
#endif


// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.


static kaleidoscope::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::LEDSolidColor solidViolet(130, 0, 120);



/** The 'setup' function is one of the two standard Arduino sketch functions.
  * It's called when your keyboard first powers up. This is where you set up
  * Kaleidoscope and any plugins.
  */

void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // Next, tell Kaleidoscope which plugins you want to use.
  // The order can be important. For example, LED effects are
  // added in the order they're listed here.
  Kaleidoscope.use(
    // The boot greeting effect pulses the LED button for 10 seconds after the keyboard is first connected
    //&BootGreetingEffect,

    // The hardware test mode, which can be invoked by tapping Prog, LED and the left Fn button at the same time.
    &TestMode,

    // LEDControl provides support for other LED modes
    &LEDControl,

    // We start with the LED effect that turns off all the LEDs.
    &LEDOff,

    &WavepoolEffect,

    // The rainbow effect changes the color of all of the keyboard's keys at the same time
    // running through all the colors of the rainbow.
    &LEDRainbowEffect,

    // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
    // and slowly moves the rainbow across your keyboard
    &LEDRainbowWaveEffect,

    // The chase effect follows the adventure of a blue pixel which chases a red pixel across
    // your keyboard. Spoiler: the blue pixel never catches the red pixel
    &LEDChaseEffect,

    // These static effects turn your keyboard's LEDs a variety of colors
    &solidRed, &solidOrange, &solidYellow, &solidGreen, &solidBlue, &solidIndigo, &solidViolet,

    // The breathe effect slowly pulses all of the LEDs on your keyboard
    &LEDBreatheEffect,

    // The AlphaSquare effect prints each character you type, using your
    // keyboard's LEDs as a display
    //&AlphaSquareEffect,

    // The stalker effect lights up the keys you've pressed recently
    &StalkerEffect,

    // The numpad plugin is responsible for lighting up the 'numpad' mode
    // with a custom LED effect
    //&NumPad,

    // The macros plugin adds support for macros
    &Macros,

    // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
    &MouseKeys,

    #ifdef USE_ONESHOT
    &OneShot,
    &ActiveModColorEffect,
    #endif
    #ifdef USE_TAPDANCE
    &TapDance,
    #endif
    &SpaceCadet,
    NULL);

  //Layer.repeat_first_press = true;

  /*
  MouseKeys.speed = 1;         // pixels per frame
  MouseKeys.speedDelay = 1;    // ms per frame
  MouseKeys.accelSpeed = 1;    // increase in pixels per accel step
  MouseKeys.accelDelay = 64;  // ms per accel step
  */
  MouseWrapper.speedLimit = 250;  // max pixels per speedDelay
  //MouseKeys.wheelSpeed = 1;    // scroll ticks per step
  //MouseKeys.wheelDelay = 100;   // ms per scroll step

  //NumLock.numPadLayer = NUMPAD_KEYMAP;

  // We configure the AlphaSquare effect to use RED letters
  //AlphaSquare.color = { 255, 0, 0 };

  LEDRainbowEffect.brightness(100);
  LEDRainbowWaveEffect.brightness(100);
  // The LED Stalker mode has a few effects. The one we like is
  // called 'BlazingTrail'. For details on other options,
  // see https://github.com/keyboardio/Kaleidoscope-LED-Stalker
  StalkerEffect.variant = STALKER(BlazingTrail);

  #ifdef USE_ONESHOT
  ActiveModColorEffect.highlight_color = CRGB(0xff, 0xff, 0xff);
  OneShot.time_out = 3000;  // 3s timeout for the OneShot effect
  OneShot.hold_time_out = 500;  // don't oneshot if held longer than 500ms
  #endif

  //LEDOff.activate();
  //LEDRainbowWaveEffect.activate();
  WavepoolEffect.idle_timeout = 5000;
  WavepoolEffect.activate();
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
