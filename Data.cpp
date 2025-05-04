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

#include "Data.h"

Data::Data()
{
   maxclose = false;
   zeroclose = false;
};




void Data::computeSlopes()
{
   //80M
   countPerHertz[0] = ((float)workingData.bandLimitPositionCounts[0][1] - (float)workingData.bandLimitPositionCounts[0][0]) / ((float)HIGHEND80M - (float)LOWEND80M);
   //60M
   countPerHertz[1] = ((float)workingData.bandLimitPositionCounts[1][1] - (float)workingData.bandLimitPositionCounts[1][0]) / ((float)HIGHEND60M - (float)LOWEND60M);
   //40M
   countPerHertz[2] = ((float)workingData.bandLimitPositionCounts[2][1] - (float)workingData.bandLimitPositionCounts[2][0]) / ((float)HIGHEND40M - (float)LOWEND40M);
   //30M
   countPerHertz[3] = ((float)workingData.bandLimitPositionCounts[3][1] - (float)workingData.bandLimitPositionCounts[3][0]) / ((float)HIGHEND30M - (float)LOWEND30M);
   //20M
   countPerHertz[4] = ((float)workingData.bandLimitPositionCounts[4][1] - (float)workingData.bandLimitPositionCounts[4][0]) / ((float)HIGHEND20M - (float)LOWEND20M);
   //17M
   countPerHertz[5] = ((float)workingData.bandLimitPositionCounts[5][1] - (float)workingData.bandLimitPositionCounts[5][0]) / ((float)HIGHEND17M - (float)LOWEND17M);
   //15M
   countPerHertz[6] = ((float)workingData.bandLimitPositionCounts[6][1] - (float)workingData.bandLimitPositionCounts[6][0]) / ((float)HIGHEND15M - (float)LOWEND15M);
   //12M
   countPerHertz[7] = ((float)workingData.bandLimitPositionCounts[7][1] - (float)workingData.bandLimitPositionCounts[7][0]) / ((float)HIGHEND12M - (float)LOWEND12M);
   //10M
   countPerHertz[8] = ((float)workingData.bandLimitPositionCounts[8][1] - (float)workingData.bandLimitPositionCounts[8][0]) / ((float)HIGHEND10M - (float)LOWEND10M);


   //80M
   hertzPerStepperUnitVVC[0] = ((float)HIGHEND80M - (float)LOWEND80M) / ((float)workingData.bandLimitPositionCounts[0][1] - (float)workingData.bandLimitPositionCounts[0][0]);
   //60M
   hertzPerStepperUnitVVC[1] = ((float)HIGHEND60M - (float)LOWEND60M) / ((float)workingData.bandLimitPositionCounts[1][1] - (float)workingData.bandLimitPositionCounts[1][0]);
   //40M
   hertzPerStepperUnitVVC[2] = ((float)HIGHEND40M - (float)LOWEND40M) / ((float)workingData.bandLimitPositionCounts[2][1] - (float)workingData.bandLimitPositionCounts[2][0]);
   //30M
   hertzPerStepperUnitVVC[3] = ((float)HIGHEND30M - (float)LOWEND30M) / ((float)workingData.bandLimitPositionCounts[3][1] - (float)workingData.bandLimitPositionCounts[3][0]);
   //20M
   hertzPerStepperUnitVVC[4] = ((float)HIGHEND20M - (float)LOWEND20M) / ((float)workingData.bandLimitPositionCounts[4][1] - (float)workingData.bandLimitPositionCounts[4][0]);
   //17M
   hertzPerStepperUnitVVC[5] = ((float)HIGHEND17M - (float)LOWEND17M) / ((float)workingData.bandLimitPositionCounts[5][1] - (float)workingData.bandLimitPositionCounts[5][0]);
   //15M
   hertzPerStepperUnitVVC[6] = ((float)HIGHEND15M - (float)LOWEND15M) / ((float)workingData.bandLimitPositionCounts[6][1] - (float)workingData.bandLimitPositionCounts[6][0]);
   //12M
   hertzPerStepperUnitVVC[7] = ((float)HIGHEND12M - (float)LOWEND12M) / ((float)workingData.bandLimitPositionCounts[7][1] - (float)workingData.bandLimitPositionCounts[7][0]);
   //10M
   hertzPerStepperUnitVVC[8] = ((float)HIGHEND10M - (float)LOWEND10M) / ((float)workingData.bandLimitPositionCounts[8][1] - (float)workingData.bandLimitPositionCounts[8][0]);

}

void Data::writeDefaultValues()
{
   // These values are roughly evenly spaced points distrubuted over the bands.

   //80M
   workingData.presetFrequencies[0][0] = 3542857L;
   workingData.presetFrequencies[0][1] = 3585714L;
   workingData.presetFrequencies[0][2] = 3628571L;
   workingData.presetFrequencies[0][3] = 3671428L;
   workingData.presetFrequencies[0][4] = 3714285L;
   workingData.presetFrequencies[0][5] = 3757142L;
   //60M
   workingData.presetFrequencies[1][0] = 5363785L;
   workingData.presetFrequencies[1][1] = 5365571L;
   workingData.presetFrequencies[1][2] = 5367357L;
   workingData.presetFrequencies[1][3] = 5369142L;
   workingData.presetFrequencies[1][4] = 5370928L;
   workingData.presetFrequencies[1][5] = 5372714L;
   //40M  
   workingData.presetFrequencies[2][0] = 7028571L;
   workingData.presetFrequencies[2][1] = 7057142L;
   workingData.presetFrequencies[2][2] = 7085714L;
   workingData.presetFrequencies[2][3] = 7114285L;
   workingData.presetFrequencies[2][4] = 7142857L;
   workingData.presetFrequencies[2][5] = 7171428L;
   //30M
   workingData.presetFrequencies[2][0] = 10107142L;
   workingData.presetFrequencies[2][1] = 10114285L;
   workingData.presetFrequencies[2][2] = 10121428L;
   workingData.presetFrequencies[2][3] = 10128571L;
   workingData.presetFrequencies[2][4] = 10135714L;
   workingData.presetFrequencies[2][5] = 10142857L;
   //20M
   workingData.presetFrequencies[2][0] = 14050000L;
   workingData.presetFrequencies[2][1] = 14100000L;
   workingData.presetFrequencies[2][2] = 14150000L;
   workingData.presetFrequencies[2][3] = 14200000L;
   workingData.presetFrequencies[2][4] = 14250000L;
   workingData.presetFrequencies[2][5] = 14300000L;
   //17M
   workingData.presetFrequencies[2][0] = 18082285L;
   workingData.presetFrequencies[2][1] = 18096571L;
   workingData.presetFrequencies[2][2] = 18110857L;
   workingData.presetFrequencies[2][3] = 18125142L;
   workingData.presetFrequencies[2][4] = 18139428L;
   workingData.presetFrequencies[2][5] = 18153714L;
   //15M
   workingData.presetFrequencies[2][0] = 21064286L;
   workingData.presetFrequencies[2][1] = 21128571L;
   workingData.presetFrequencies[2][2] = 21192857L;
   workingData.presetFrequencies[2][3] = 21257143L;
   workingData.presetFrequencies[2][4] = 21321429L;
   workingData.presetFrequencies[2][5] = 21385714L;
   //12M
   workingData.presetFrequencies[2][0] = 24904286L;
   workingData.presetFrequencies[2][1] = 24918571L;
   workingData.presetFrequencies[2][2] = 24932857L;
   workingData.presetFrequencies[2][3] = 24947143L;
   workingData.presetFrequencies[2][4] = 24961429L;
   workingData.presetFrequencies[2][5] = 24975714L;
   //10M
   workingData.presetFrequencies[2][0] = 28242857L;
   workingData.presetFrequencies[2][1] = 28485714L;
   workingData.presetFrequencies[2][2] = 28728571L;
   workingData.presetFrequencies[2][3] = 28971429L;
   workingData.presetFrequencies[2][4] = 29214286L;
   workingData.presetFrequencies[2][5] = 29457143L;


   //80M
   workingData.bandLimitPositionCounts[0][0] = 0;
   workingData.bandLimitPositionCounts[0][1] = 0;
   //60M
   workingData.bandLimitPositionCounts[1][0] = 0;
   workingData.bandLimitPositionCounts[1][1] = 0;
   //40M
   workingData.bandLimitPositionCounts[2][0] = 0;
   workingData.bandLimitPositionCounts[2][1] = 0;
   //30M
   workingData.bandLimitPositionCounts[3][0] = 0;
   workingData.bandLimitPositionCounts[3][1] = 0;
   //20M
   workingData.bandLimitPositionCounts[4][0] = 0;
   workingData.bandLimitPositionCounts[4][1] = 0;
   //17M
   workingData.bandLimitPositionCounts[5][0] = 0;
   workingData.bandLimitPositionCounts[5][1] = 0;
   //15M
   workingData.bandLimitPositionCounts[6][0] = 0;
   workingData.bandLimitPositionCounts[6][1] = 0;
   //12M
   workingData.bandLimitPositionCounts[7][0] = 0;
   workingData.bandLimitPositionCounts[7][1] = 0;
   //10M
   workingData.bandLimitPositionCounts[8][0] = 0;
   workingData.bandLimitPositionCounts[8][1] = 0;


   //80M
   workingData.bandEdges[0][0] = LOWEND80M;
   workingData.bandEdges[0][1] = HIGHEND80M;
   //60M
   workingData.bandEdges[1][0] = LOWEND60M;
   workingData.bandEdges[1][1] = HIGHEND60M;
   //40M
   workingData.bandEdges[2][0] = LOWEND40M;
   workingData.bandEdges[2][1] = HIGHEND40M;
   //30M
   workingData.bandEdges[3][0] = LOWEND30M;
   workingData.bandEdges[3][1] = HIGHEND30M;
   //20M
   workingData.bandEdges[4][0] = LOWEND20M;
   workingData.bandEdges[4][1] = HIGHEND20M;
   //17M
   workingData.bandEdges[5][0] = LOWEND17M;
   workingData.bandEdges[5][1] = HIGHEND17M;
   //15M
   workingData.bandEdges[6][0] = LOWEND15M;
   workingData.bandEdges[6][1] = HIGHEND15M;
   //12M
   workingData.bandEdges[7][0] = LOWEND12M;
   workingData.bandEdges[7][1] = HIGHEND12M;
   //10M
   workingData.bandEdges[8][0] = LOWEND10M;
   workingData.bandEdges[8][1] = HIGHEND10M;


   //80M
   workingData.lastFreq[0] = (LOWEND80M+HIGHEND80M)/2;
   //60M
   workingData.lastFreq[1] =  (LOWEND60M+HIGHEND60M)/2;
   //40M
   workingData.lastFreq[2] =  7150000;
   //30M
   workingData.lastFreq[3] =   (LOWEND30M+HIGHEND30M)/2;
   //20M
   workingData.lastFreq[4] =  (LOWEND20M+HIGHEND20M)/2;
   //17M
   workingData.lastFreq[5] =  (LOWEND17M+HIGHEND17M)/2;
   //15M
   workingData.lastFreq[6] =   (LOWEND15M+HIGHEND15M)/2;
   //12M
   workingData.lastFreq[7] =  (LOWEND12M+HIGHEND12M)/2;
   //10M
   workingData.lastFreq[8] =  (LOWEND10M+HIGHEND10M)/2;


   workingData.currentBand = 2;
   workingData.currentFrequency = 7150000;
   workingData.initialized = 0x55555555;  // 0x55555555 means the workingData struct has been initialized.
   workingData.calibrated = 0x00000000;   // Set to something other than 0 if calibrated.
   workingData.hardware = 0x00000000;     // 0 means hardware not accepted. 0x55555555 is accepted hardware.

   workingData.zero_offset = 1000;  // zero offset
   workingData.backlash = 60;       // backlash
   workingData.coarse_sweep = 20;   // coarse tune
   workingData.accel = 2000;        // acceleration
   workingData.speed = 500;         // speed
}
