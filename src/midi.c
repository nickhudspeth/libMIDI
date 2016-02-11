/************************************************************************
Title:    Midi Standard Library
Author:   Nicholas Morrow <nickhudspeth@gmail.com> http://www.nickhudspeth.com
File:     midi.c
Software:
Hardware:
License:  GNU General Public License
Usage:    Refer to the header file midi.h for a description of the routines.
    See also example test_midi.c, if available.
LICENSE:
    Copyright (C) 2016 Nicholas Morrow

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

************************************************************************/

/**********************    INCLUDE DIRECTIVES    ***********************/

 #include "midi.h"


/*********************    CONSTANTS AND MACROS    **********************/


/***********************    GLOBAL VARIABLES    ************************/
/* List of MIDI devices */
struct midi_device *midi_device_list[];
uint8_t midi_num_devices;

/*******************    FUNCTION IMPLEMENTATIONS    ********************/

struct midi_message midi_message_create(void)
{
    struct midi_message m = {.type = NULL, .status = NULL, .data = {NULL}};
    return m;
}