/* A "proof of concept" project to replace the STM32F103 "Blue Pill"
   which is used in the "Magnetic Loop Controller" described in the book
   "Microcontroller Projects for Amateur Radio by Jack Purdum, W8TEE, and
   Albert Peter, AC8GY" with the Raspberry Pi Pico.
   Copyright (C) 2022  Gregory Raven

                                                    LICENSE AGREEMENT

  This program source code and its associated hardware design at subject to the GNU General Public License version 2,
                  https://opensource.org/licenses/GPL-2.0
  with the following additional conditions:
    1. Any commercial use of the hardware or software is prohibited without express, written, permission of the authors.
    2. This entire comment, unaltered, must appear at the top of the primary source file. In the Arduino IDE environemnt, this comment must
       appear at the top of the INO file that contains setup() and loop(). In any other environmentm, it must appear in the file containing
       main().
    3. This notice must appear in any derivative work, regardless of language used.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    A copy of the GPL-2.0 license is included in the repository as file LICENSE.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#pragma once
#include <stdint.h>
#include <string>
#include <vector>

//  This class is intended to manage various frequency and position related constants and variables.
//  The single object will be referenced by most or maybe all of the other class objects.

class Data
{

public:

const std::string version = "main";
const std::string releaseDate = "8-26-24";

  // Flags used to indicate switch closures.
  bool maxclose;
  bool zeroclose;

  //  These are fundamental size definitions used throughout the project.
  const int PRESETSPERBAND = 6; // Allow this many preset frequencies on each band
  const int MAXBANDS = 3;       // Can only process this many frequency bands
  const int MAXMENUES = 3;
  const int PIXELWIDTH = 320;   // Display pixels width.
  const int PIXELHEIGHT = 240;  // Display pixels height.

  // Bands used:

  std::vector<std::string> bands = {"80M","60M","40M","30M","20M","17M","15M","12M","10M"};

  //80M
  static const uint32_t LOWEND80M = 3500000;
  static const uint32_t HIGHEND80M = 3800000;

  //60M
  // Playing safe here as the UK band is split (5354000 to 5358000) and (5362000 to 5374500) and don't want to transmit broadcast out of band.  
  static const uint32_t LOWEND60M = 5362000;
  static const uint32_t HIGHEND60M = 5374500;
  
   //40M
  static const uint32_t LOWEND40M = 7000000;
  static const uint32_t HIGHEND40M = 7200000;
   //30M
  static const uint32_t LOWEND30M = 10100000;
  static const uint32_t HIGHEND30M = 10150000;
   //20M
  static const uint32_t LOWEND20M = 14000000;
  static const uint32_t HIGHEND20M = 14350000;
   //17M
  static const uint32_t LOWEND17M = 18068000;
  static const uint32_t HIGHEND17M = 18168000;
   //15M
  static const uint32_t LOWEND15M = 21000000;
  static const uint32_t HIGHEND15M = 21450000;
   //12M
  static const uint32_t LOWEND12M = 24890000;
  static const uint32_t HIGHEND12M = 24990000;
   //10M
  static const uint32_t LOWEND10M = 28000000;
  static const uint32_t HIGHEND10M = 29700000;


  // Preset frequency constants in the dataStruct are initial defaults; these defaults are saved to the
  // EEPROM initially, but they can be overwritten later if the user desires.  The presets will always
  // be read from the EEPROM.
  struct dataStruct
  {
    uint32_t presetFrequencies[9][6] =
        {
            {3542857L, 3585714L, 3628571L, 3671428L, 3714285L, 3757142L}, // 80M
            {5363785L, 5365571L, 5367357L, 5369142L, 5370928L, 5372714L}, // 60M
            {7028571L, 7057142L, 7085714L, 7114285L, 7142857L, 7171428L}, // 40M

            {10107142L, 10114285L, 10121428L, 10128571L, 10135714L, 10142857L}, // 30M
            {14050000L, 14100000L, 14150000L, 14200000L, 14250000L, 14300000L}, // 20M
            {18082285L, 18096571L, 18110857L, 18125142L, 18139428L, 18153714L}, // 17M
            
            {21064286L, 21128571L, 21192857L, 21257143L, 21321429L, 21385714L}, // 15M
            {24904286L, 24918571L, 24932857L, 24947143L, 24961429L, 24975714L}, // 12M
            {28242857L, 28485714L, 28728571L, 28971429L, 29214286L, 29457143L} // 10M

    };
    uint32_t bandLimitPositionCounts[9][2];
    uint32_t bandEdges[9][2]; // = { // Band edges in Hz
                              //   {LOWEND40M, HIGHEND40M},
                              //   {LOWEND30M, HIGHEND30M},
                              //   {LOWEND20M, HIGHEND20M}};
    uint32_t currentBand = 0;
    uint32_t currentFrequency = 7150000;
    uint32_t lastFreq[3];  // Used to remember the last autotune frequency.
    uint32_t initialized = 0x55555555;
    uint32_t calibrated; //  Please run Initial Calibration! if not set to correct value.
    uint32_t hardware;   //  0x55555555 means hardware is accepted.
  // The following are parameters which must be "tuned" to the particular mechanics in use.
  // Refer to the documentation for setting these values.
  int zero_offset = 0; // 600 for full step.  1000 for half-step.  270 for dummy with 1/16 step.
  int backlash = 0;
  int coarse_sweep = 1;
  int accel = 2000;
  int speed = 500;
  bool rotation = true;
  } workingData;

  //  This should be made variable length arrays.
  float countPerHertz[3];
  float hertzPerStepperUnitVVC[3]; // Voltage Variable Cap

  // GPIO assignments.
  //  Buttons
  int enterButton = 6;
  int autotuneButton = 7;
  int exitButton = 9;
  // Zero and Maximum switches.
  int zeroswitch = 10;
  int maxswitch = 11;
  // Stepper position.  This is here because it is not always convenient to interogate the stepper object.
  int32_t position;
  //  Power controls
  const int STEPPERSLEEPNOT = 9;
  const int OPAMPPOWER = 3;
  const int RFAMPPOWER = 2;
  const int RFRELAYPOWER = 19;
  //  Interface for the DDS object.
  const int DDS_RST = 4;
  const int DDS_DATA = 5;
  const int DDS_FQ_UD = 12;
  const int WLCK = 22;

  Data();

  void computeSlopes();

  void writeDefaultValues();
};