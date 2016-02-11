/*************************************************************************
Title:    midi.h - Standard MIDI 1.0 Library
Author:   Nicholas Morrow <nickhudspeth@gmail.com> http://www.nickhudspeth.com
File:     midi.h
Software:
Hardware:
License:  GNU General Public License

DESCRIPTION:
    What does this module do? How does it work?

USAGE:
    See Doxygen manual

NOTES:
    None

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

*************************************************************************/

/**********************    INCLUDE DIRECTIVES    ***********************/
#include <stdio.h>
#include <string.h>
#define MIDI_BAUD_RATE 31250
#define MIDI_TYPE_MASK 0xF0
#define MIDI_CHANNEL_MASK 0x0F
#define OMNI 99

/**************    CONSTANTS, MACROS, & DATA STRUCTURES    ***************/
typedef enum midi_msg_type {
    NULL = 0x00 ,
    /* CHANNEL VOICE MESSAGES */
    NOTE_OFF = 0x80,
    NOTE_ON = 0x90,
    AFTERTOUCH = 0xA0,
    CONTROL_CHANGE = 0xB0,
    PROGRAM_CHANGE  = 0xC0,
    CHANNEL_PRESSURE = 0xD0,
    PITCH_BEND = 0xE0,
    /* CHANNEL_MODE MESSAGES */
    ALL_SOUND_OFF = 0xB0,
    RESET_CONTROLLERS = 0xB0,
    LOCAL_CONTROL = 0xB0,
    ALL_NOTES_OFF = 0xB0,
    /* SYSTEM COMMON MESSAGES */
    SYSTEM_EXCLUSIVE = 0xF0,
    MTC_QUARTER_FRAME = 0xF1,
    SONG_POSITION_POINTER = 0xF2,
    SONG_SELECT = 0xF3,
    TUNE_REQUEST = 0xF6,
    SYSTEM_EXCLUSIVE_END = 0xF7,
    /* SYSTEM REAL-TIME MESSAGES */
    TIMING_CLOCK = 0xF8,
    START = 0xFA,
    CONTINUE = 0xFB,
    STOP = 0xFC,
    ACTIVE_SENSING = 0xFE,
    RESET = 0xFF,
};

// uint8_t midi_message_status_lut[] = {
//     0x00, // 00000000 - NULL
//     0x80, // 10000000 - NOTE OFF
//     0x90, // 10010000 - NOTE ON
//     0xA0, // 10100000 - POLYPHONIC KEY PRESSURE (AFTERTOUCH)
//     0xB0, // 10110000 - CONTROL CHANGE
//     0xC0, // 11000000 - PROGRAM CHANGE
//     0xD0, // 11010000 - CHANNEL PRESSURE (AFTERTOUCH)
//     0xE0, // 11100000 - PITCH BEND
//     0xB0, // 10110000 - ALL SOUND OFF
//     0xB0, // 10110000 - RESET ALL CONTROLLERS
//     0xB0, // 10110000 - LOCAL CONTROL
//     0xB0, // 10110000 - ALL NOTES OFF
//     0xF0, // 11110000 - SYSTEM EXCLUSIVE
//     0xF1, // 11110001 - MTC QUARTER FRAME
//     0xF2, // 11110010 - SONG POSITION POINTER
//     0xF3, // 11110011 - SONG SELECT
//     0xF6, // 11110110 - TUNE REQUEST
//     0xF7, // 11110111 - END OF SYSTEM EXCLUSIVE MESSAGE
//     0xF8, // 11111000 - TIMING CLOCK
//     0xFA, // 11111010 - START
//     0xFB, // 11111011 - CONTINUE
//     0xFC, // 11111100 - STOP
//     0xFE, // 11111110 - ACTIVE SENSING
//     0xFF, // 11111111 - RESET
// }

typedef void (*midi_func_t)(struct midi_device *d, uint8_t status,
                            uint8_t *data, uint16_t count);

struct midi_input_handler {
    /* CHANNEL VOICE MESSAGE CALLBACKS */
    midi_func_t note_off_callback;
    midi_func_t note_on_callback;
    midi_func_t aftertouch_callback;
    midi_func_t control_change_callback;
    midi_func_t program_change_callback;
    midi_func_t channel_pressure_callback;
    midi_func_t pitch_bend_callback;
    /* CHANNEL MODE MESSAGE CALLBACKS */
    midi_func_t all_sound_off_callback;
    midi_func_t reset_all_controllers_callback;
    midi_func_t local_control_callback;
    midi_func_t all_notes_off_callback;
    /* SYSTEM COMMON MESSAGE CALLBACKS */
    midi_func_t system_exclusive_callback;
    midi_func_t mtc_quarter_frame_callback;
    midi_func_t song_position_pointer_callback;
    midi_func_t song_select_callback;
    midi_func_t tune_request_callback;
    midi_func_t system_exclusive_end_callback;
    /* SYSTEM REAL-TIME CALLBACK FUNCTIONS */
    midi_func_t timing_clock_callback;
    midi_func_t start_callback;
    midi_func_t continue_callback;
    midi_func_t stop_callback;
    midi_func_t active_sensing_callback;
    midi_func_t reset_callback;
};

struct midi_output_handler {
    void (* midi_send_byte_func)(uint8_t byte);
    /* CHANNEL VOICE MESSAGE SEND FUNCTIONS */
    midi_func_t note_off_send;
    midi_func_t note_on_callback;
    midi_func_t aftertouch_send;
    midi_func_t control_change_send;
    midi_func_t program_change_send;
    midi_func_t channel_pressure_send;
    midi_func_t pitch_bend_send;
    /* CHANNEL MODE MESSAGE SENSD FUNCTIONS */
    midi_func_t all_sound_off_send;
    midi_func_t reset_all_controllers_send;
    midi_func_t local_control_send;
    midi_func_t all_notes_off_send;
    /* SYSTEM COMMON MESSAGE SENSD FUNCTIONS */
    midi_func_t system_exclusive_send;
    midi_func_t mtc_quarter_frame_send;
    midi_func_t song_position_pointer_send;
    midi_func_t song_select_send;
    midi_func_t tune_request_send;
    midi_func_t system_exclusive_end_send;
    /* SYSTEM REAL-TIME SEND FUNCTIONS */
    midi_func_t timing_clock_send;
    midi_func_t start_send;
    midi_func_t continue_send;
    midi_func_t stop_send;
    midi_func_t active_sensing_send;
    midi_func_t reset_send;
};

struct midi_msg {
    uint8_t status;  // Status byte containing message type and channel number
    uint8_t[3] data; // Message data payload
};

struct midi_device {
    uint8_t rcv_chan; /* Channel on which to listen for MIDI messages */
    struct midi_input_handler input;
    struct midi_output_handler output;
};

/***********************    FUNCTION PROTOTYPES    ***********************/
typedef void (*midi_func_t)(uint8_t *data, uint16_t count);
/*************************************************************************
 * Function :    midi_device_create()
 * Purpose  :    Creates and initializes a new MIDI device
 *               Registers the MIDI new MIDI device
 * Input    :    uint8_t reg - Boolean value. Should device be registered
 *                             immediately?
 * Returns  :    struct midi_device *
 *************************************************************************/
struct midi_device *midi_device_create(uint8_t reg)
{
    struct midi_device *dev = (struct midi_device *)calloc(1,
                              sizeof(struct midi_device));
    dev->rcv_chan = OMNI;
    dev->input.note_off_callback = NULL;
    dev->input.note_on_callback = NULL;
    dev->input.aftertouch_callback = NULL;
    dev->input.control_change_callback = NULL;
    dev->input.program_change_callback = NULL;
    dev->input.channel_pressure_callback = NULL;
    dev->input.pitch_bend_callback = NULL;
    dev->input.all_sound_off_callback = NULL;
    dev->input.reset_all_controllers_callback = NULL;
    dev->input.local_control_callback = NULL;
    dev->input.all_notes_off_callback = NULL;
    dev->input.system_exclusive_callback = NULL;
    dev->input.mtc_quarter_frame_callback = NULL;
    dev->input.song_position_pointer_callback = NULL;
    dev->input.song_select_callback = NULL;
    dev->input.tune_request_callback = NULL;
    dev->input.system_exclusive_end_callback = NULL;
    dev->input.timing_clock_callback = NULL;
    dev->input.start_callback = NULL;
    dev->input.continue_callback = NULL;
    dev->input.stop_callback = NULL;
    dev->input.active_sensing_callback = NULL;
    dev->output.note_off_send = NULL;
    dev->output.note_on_callback = NULL;
    dev->output.aftertouch_send = NULL;
    dev->output.control_change_send = NULL;
    dev->output.program_change_send = NULL;
    dev->output.channel_pressure_send = NULL;
    dev->output.pitch_bend_send = NULL;
    dev->output.all_sound_off_send = NULL;
    dev->output.reset_all_controllers_send = NULL;
    dev->output.local_control_send = NULL;
    dev->output.all_notes_off_send = NULL;
    dev->output.system_exclusive_send = NULL;
    dev->output.mtc_quarter_frame_send = NULL;
    dev->output.song_position_pointer_send = NULL;
    dev->output.song_select_send = NULL;
    dev->output.tune_request_send = NULL;
    dev->output.system_exclusive_end_send = NULL;
    dev->output.timing_clock_send = NULL;
    dev->output.start_send = NULL;
    dev->output.continue_send = NULL;
    dev->output.stop_send = NULL;
    dev->output.active_sensing_send = NULL;
    dev->output.reset_send = NULL;
    dev->output.midi_send_byte_func = NULL;
    if (reg) {
        midi_register_device(dev);
    }
    return dev;
}
/*************************************************************************
 * Function :    midi_message_create()
 * Purpose  :    What does this function do?
 * Input    :    void
 * Returns  :    struct midi_message
 *************************************************************************/
struct midi_message *midi_message_create(void)
{
    struct midi_msg *m = (struct midi_msg *)calloc(1, sizeof(struct midi_msg));
    return m;
}

/*************************************************************************
 * Function :    midi_msg_delete()
 * Purpose  :    Frees heap allocation for midi_msg
 * Input    :    struct midi_msg *m
 * Returns  :    void
 *************************************************************************/
void midi_msg_delete(struct midi_msg *m)
{
    free(m);
}

/*************************************************************************
 * Function :    midi_register_callback()
 * Purpose  :    What does this function do?
 * Input    :    struct midi_device *dev, uint8_t type, midi_func_t func
 * Returns  :    void
 *************************************************************************/
void midi_register_callback(struct midi_device *dev, uint8_t type,
                            midi_func_t func)
{
    switch (type) {
        case NOTE_OFF:
            dev->input.note_off_callback = func;
            break;
        case NOTE_ON:
            dev->input.note_on_callback = func;
            break;
        case AFTERTOUCH:
            dev->input.aftertouch_callback = func;
            break;
        case CONTROL_CHANGE:
            dev->input.control_change_callback = func;
            break;
        case PROGRAM_CHANGE :
            dev->input.program_change_callback = func;
            break;
        case CHANNEL_PRESSURE:
            dev->input.channel_pressure_callback = func;
            break;
        case PITCH_BEND:
            dev->input.pitch_bend_callback = func;
            break;
        case ALL_SOUND_OFF:
            dev->input.all_sound_off_callback = func;
            break;
        case RESET_CONTROLLERS:
            dev->input.reset_controllers_callback = func;
            break;
        case LOCAL_CONTROL:
            dev->input.local_control_callback = func;
            break;
        case ALL_NOTES_OFF:
            dev->input.all_notes_off_callback = func;
            break;
        case SYSTEM_EXCLUSIVE:
            dev->input.system_exclusive_callback = func;
            break;
        case MTC_QUARTER_FRAME:
            dev->input.mtc_quarter_frame_callback = func;
            break;
        case SONG_POSITION_POINTER:
            dev->input.song_position_pointer_callback = func;
            break;
        case SONG_SELECT:
            dev->input.song_select_callback = func;
            break;
        case TUNE_REQUEST:
            dev->input.tune_request_callback = func;
            break;
        case SYSTEM_EXCLUSIVE_END:
            dev->input.system_exclusive_end_callback = func;
            break;
        case TIMING_CLOCK:
            dev->input.timing_clock_callback = func;
            break;
        case START:
            dev->input.start_callback = func;
            break;
        case CONTINUE:
            dev->input.continue_callback = func;
            break;
        case STOP:
            dev->input.stop_callback = func;
            break;
        case ACTIVE_SENSING:
            dev->input.active_sensing_callback = func;
            break;
        case RESET:
            dev->input.reset_callback = func;
            break;
    }
}

/*************************************************************************
 * Function :    midi_message_set_type()
 * Purpose  :    What does this function do?
 * Input    :    enum midi_message_type
 * Returns  :    void
 *************************************************************************/
void midi_message_set_type(struct midi_message *m, midi_message_type t)
{
    m.type = t;
}

/*************************************************************************
 * Function :    midi_message_set_status()
 * Purpose  :    What does this function do?
 * Input    :    struct midi_message *m, midi_message_Type t
 * Returns  :    void
 *************************************************************************/
void midi_message_set_status(struct midi_message *m, uint8_t s)
{
    m.status = s;
}

/*************************************************************************
 * Function :    midi_message_set_data()
 * Purpose  :    What does this function do?
 * Input    :    <parameterList>
 * Returns  :    void
 *************************************************************************/
void midi_message_set_data(struct midi_msg *m; uint8_t *d, uint8_t len)
{
    uint8_t i;
    // ERROR: Invalid pointer to MIDI message received
    if (m == NULL) { return;}
    // ERROR: Invalid pointer to data array received
    if (d == NULL) { return;}
    for (i = 0; i < len; i++) {
        m->data[i] = d[i];
    }
}

/*************************************************************************
 * Function :    midi_process_input()
 * Purpose  :    Parses incoming MIDI message
 *               Calls appropriate callback function
 *               Deletes MIDI message
 * Input    :    struct midi_device *
 *               struct midi_msg *
 * Returns  :    void
 *************************************************************************/
void midi_process_input(struct midi_device *d, struct midi_msg *m)
{
    uint8_t data_buf[3];
    uint8_t mask = m->status & MIDI_CHANNEL_MASK;
    /* Check if device at index i is listening on this channel */
    if ((d.rcv_chan != OMNI) && (mask != d.rcv_chan)) {
        break; // Skip if message is for device on different channel
    }
    else {
        mask = m->status & MIDI_TYPE_MASK;
        switch (mask) {
            case NOTE_OFF: // = 0x80,
                data_buf[0] = m->data[0];
                data_buf[1] = m->data[1];
                if (d->input.note_off_callback != NULL) {
                    d->input.note_off_callback(d, m->status, data_buf, 2);
                } break;
            case NOTE_ON: // = 0x90,
                data_buf[0] = m->data[0];
                data_buf[1] = m->data[1];
                if (d->input.note_on_callback != NULL) {
                    d->input.note_on_callback(d, m->status, data_buf, 2);
                } break;
            case AFTERTOUCH: // = 0xA0,
                data_buf[0] = m->data[0];
                data_buf[1] = m->data[1];
                if (d->input.aftertouch_callback != NULL) {
                    d->input.aftertouch_callback(d, m->status, data_buf, 2);
                } break;
            case CONTROL_CHANGE: // = 0xB0,
                data_buf[0] = m->data[0];
                data_buf[1] = m->data[1];
                if (d->input.control_change_callback != NULL) {
                    d->input.control_change_callback(d, m->status, data_buf, 2);
                } break;
            case PROGRAM_CHANGE : // = 0xC0,
                data_buf[0] = m->data[0];
                if (d->input.program_change_callback != NULL) {
                    d->input.program_change_callback(d, m->status, data_buf, 1);
                } break;
            case CHANNEL_PRESSURE: // = 0xD0,
                data_buf[0] = m->data[0];
                if (d->input.channel_pressure_callback != NULL) {
                    d->input.channel_pressure_callback(d, m->status, data_buf, 1);
                } break;
            case PITCH_BEND: // = 0xE0,
                data_buf[0] = m->data[0];
                data_buf[1] = m->data[1];
                if (d->input.pitch_bend_callback != NULL) {
                    d->input.pitch_bend_callback(d, m->status, data_buf, 2);
                } break;
            case ALL_SOUND_OFF: // = 0xB0,
                data_buf[0] = m->data[0];
                data_buf[1] = m->data[1];
                if (d->input.all_sound_off_callback != NULL) {
                    d->input.all_sound_off_callback(d, m->status, data_buf, 2);
                } break;
            case RESET_CONTROLLERS: // = 0xB0,
                data_buf[0] = m->data[0];
                data_buf[1] = m->data[1];
                if (d->input.reset_controllers_callback != NULL) {
                    d->input.reset_controllers_callback(d, m->status, data_buf, 2);
                } break;
            case LOCAL_CONTROL: // = 0xB0,
                data_buf[0] = m->data[0];
                data_buf[1] = m->data[1];
                if (d->input.local_control_callback != NULL) {
                    d->input.local_control_callback(d, m->status, data_buf, 2);
                } break;
            case ALL_NOTES_OFF: // = 0xB0,
                data_buf[0] = m->data[0];
                data_buf[1] = m->data[1];
                if (d->input.all_notes_off_callback != NULL) {
                    d->input.all_notes_off_callback(d, m->status, data_buf, 2);
                } break;
            case SYSTEM_EXCLUSIVE: // = 0xF0,
                /* SYSEX NOT CURRENTLY SUPPORTED! */
                break;
            case MTC_QUARTER_FRAME: // = 0xF1,
                data_buf[0] = m->data[0];
                if (d->input.mtc_quarter_frame_callback != NULL) {
                    d->input.mtc_quarter_frame_callback(d, m->status, data_buf, 1);
                } break;
            case SONG_POSITION_POINTER: // = 0xF2,
                data_buf[0] = m->data[0];
                if (d->input.song_position_pointer_callback != NULL) {
                    d->input.song_position_pointer_callback(d, m->status, data_buf, 1);
                } break;
            case SONG_SELECT: // = 0xF3,
                data_buf[0] = m->data[0];
                if (d->input.song_select_callback != NULL) {
                    d->input.song_select_callback(d, m->status, data_buf, 1);
                } break;
            case TUNE_REQUEST: // = 0xF6,
                if (d->input.tune_request_callback != NULL) {
                    d->input.tune_request_callback(d, m->status, data_buf, 0);
                } break;
            case SYSTEM_EXCLUSIVE_END: // = 0xF7,
                /* SYSEX NOT CURRENTLY SUPPORTED! */
                break;
            case TIMING_CLOCK: // = 0xF8,
                if (d->input.timing_clock_callback != NULL) {
                    d->input.timing_clock_callback(d, m->status, data_buf, 0);
                } break;
            case START: // = 0xFA,
                if (d->input.start_callback != NULL) {
                    d->input.start_callback(d, m->status, data_buf, 0);
                } break;
            case CONTINUE: // = 0xFB,
                if (d->input.continue_callback != NULL) {
                    d->input.continue_callback(d, m->status, data_buf, 0);
                } break;
            case STOP: // = 0xFC,
                if (d->input.stop_callback != NULL) {
                    d->input.stop_callback(d, m->status, data_buf, 0);
                } break;
            case ACTIVE_SENSING: // = 0xFE,
                if (d->input.active_sensing_callback != NULL) {
                    d->input.active_sensing_callback(d, m->status, data_buf, 0);
                } break;
            case RESET: // = 0xFF,
                if (d->input.reset_callback != NULL) {
                    d->input.reset_callback(d, m->status, data_buf, 0);
                } break;
        }
    }
    midi_msg_delete(m);
}

/*************************************************************************
 * Function :    midi_note_off_send()
 * Purpose  :    Sends NOTE_OFF message
 * Input    :    struct midi_device *, uint8_t channel, uint8_t key, uint8_t vel
 * Returns  :    void
 *************************************************************************/
void midi_note_off_send(struct midi_device *d, uint8_t channel, uint8_t *data,
                        uint16_t count)
{
    uint8_t status = 0x80 | channel;
    d->midi_send_byte_func(status);
    if (count < 2) {
        /* ERROR: Data buffer is of incorrect size for message */
        return;
    }
    d->midi_send_byte_func(data[0]);
    d->midi_send_byte_func(data[1]);
}

/*************************************************************************
 * Function :    midi_note_on_send()
 * Purpose  :    Sends NOTE_ON message
 * Input    :    struct midi_device *, uint8_t channel, uint8_t key, uint8_t vel
 * Returns  :    void
 *************************************************************************/
void midi_note_on_send(struct midi_device *d, uint8_t status, uint8_t *data, uint16_t count)
{
    uint8_t status = 0x90 | channel;
    d->midi_send_byte_func(status);
    if (count < 2) {
        /* ERROR: Data buffer is of incorrect size for message */
        return;
    }
    d->midi_send_byte_func(data[0]);
    d->midi_send_byte_func(data[1]);
}

/*************************************************************************
 * Function :    midi_aftertouch_send()
 * Purpose  :    Sends AFTERTOUCH message
 * Input    :    struct midi_device *, uint8_t channel, uint8_t key, uint8_t pres
 * Returns  :    void
 *************************************************************************/
void midi_aftertouch_send(struct midi_device *d, uint8_t channel, uint8_t *data,
                        uint16_t count)
{
    uint8_t status = 0xA0 | channel;
    d->midi_send_byte_func(status);
    d->midi_send_byte_func(key);
    d->midi_send_byte_func(pres);
}

/*************************************************************************
 * Function :    midi_control_change_send()
 * Purpose  :    Sends CONTROL_CHANGE message
 * Input    :    struct midi_device *, uint8_t channel, uint8_t num, uint8_t val
 * Returns  :    void
 *************************************************************************/
void midi_control_change_send(struct midi_device *d, uint8_t channel, uint8_t *data,
                        uint16_t count)
{
    uint8_t status = 0xB0 | channel;
    d->midi_send_byte_func(status);
    d->midi_send_byte_func(num);
    d->midi_send_byte_func(val);
}

/*************************************************************************
 * Function :    midi_program_change_send()
 * Purpose  :    Sends PROGRAM_CHANGE message
 * Input    :    struct midi_device *, uint8_t channel, uint8_t num
 * Returns  :    void
 *************************************************************************/
void midi_program_change_send(struct midi_device *d, uint8_t channel, uint8_t *data,
                        uint16_t count)
{
    uint8_t status = 0xC0 | channel;
    d->midi_send_byte_func(status);
    d->midi_send_byte_func(key);
    d->midi_send_byte_func(vel);
}

/*************************************************************************
 * Function :    midi_channel_pressure_send()
 * Purpose  :    Sends CHANNEL_PRESSURE message
 * Input    :    struct midi_device *, uint8_t channel, uint8_t pres
 * Returns  :    void
 *************************************************************************/
void midi_channel_pressure_send(struct midi_device *d, uint8_t channel, uint8_t *data,
                        uint16_t count)
{
    uint8_t status = 0xD0 | channel;
    d->midi_send_byte_func(status);
    d->midi_send_byte_func(key);
    d->midi_send_byte_func(vel);
}

/*************************************************************************
 * Function :    midi_pitch_bend_send()
 * Purpose  :    Sends PITCH_BEND message
 * Input    :    struct midi_device *, uint8_t channel, uint8_t hval, uint8_t lval
 * Returns  :    void
 *************************************************************************/
void midi_pitch_bend_send(struct midi_device *d, uint8_t channel, uint8_t *data,
                        uint16_t count)
{
    uint8_t status = 0xE0 | channel;
    d->midi_send_byte_func(status);
    d->midi_send_byte_func(hval);
    d->midi_send_byte_func(lval);
}

/*************************************************************************
 * Function :    midi_all_sound_off_send()
 * Purpose  :    Sends ALL_SOUND_OFF message
 * Input    :    struct midi_device *d, uint8_t channel, uint8_t
 * Returns  :    void
 *************************************************************************/
void midi_all_sound_off_send(struct midi_device *d, uint_t channel)
{
    uint8_t status = 0xB0 | channel;
    d->midi_send_byte_func(status);
    d->midi_send_byte_func(120);
    d->midi_send_byte_func(0);
}

/*************************************************************************
 * Function :    midi_reset_all_controllers_send()
 * Purpose  :    Sends RESET_ALL_CONTROLLERS message
 * Input    :    struct midi_device *d, uint8_t val
 * Returns  :    void
 *************************************************************************/
void midi_reset_all_controllers_send(struct midi_device *d, uint8_t channel,
                                     uint8_t val)
{
    uint8_t status = 0xB0 | channel;
    d->midi_send_byte_func(status);
    d->midi_send_byte_func(121);
    d->midi_send_byte_func(val);
}

/*************************************************************************
 * Function :    midi_local_control_send()
 * Purpose  :    Sends LOCAL_CONTROL message
 * Input    :    struct midi_device *d, uint8_t val (BOOLEAN)
 * Returns  :    void
 *************************************************************************/
void midi_local_control_send(struct midi_device *d, uint8_t val)
{
    uint8_t status = 0xB0 | channel;
    d->midi_send_byte_func(status);
    d->midi_send_byte_func(122);
    if (val > 0) {
        d->midi_send_byte_func(127);
    }
    else {
        d->midi_send_byte_func(0);
    }
}

/*************************************************************************
 * Function :    midi_all_notes_off_send()
 * Purpose  :    Sends ALL_NOTES_OFF message
 * Input    :    struct midi_device *d
 * Returns  :    void
 *************************************************************************/
void midi_all_notes_off_send(struct midi_device *d)
{
    uint8_t status = 0xB0 | channel;
    d->midi_send_byte_func(status);
    d->midi_send_byte_func(120);
    d->midi_send_byte_func(0);
}

/*************************************************************************
 * Function :    midi_system_exclusive_send()
 * Purpose  :    What does this function do?
 * Input    :    struct midi_device *d
 * Returns  :    void
 *************************************************************************/
void midi_system_exclusive_send(struct midi_device *d)
{
}

// midi_func_t all_sound_off_send;
// midi_func_t reset_all_controllers_send;
// midi_func_t local_control_send;
// midi_func_t all_notes_off_send;
// /* SYSTEM COMMON MESSAGE SENSD FUNCTIONS */
// midi_func_t system_exclusive_send;
// midi_func_t mtc_quarter_frame_send;
// midi_func_t song_position_pointer_send;
// midi_func_t song_select_send;
// midi_func_t tune_request_send;
// midi_func_t system_exclusive_end_send;
// /* SYSTEM REAL-TIME SEND FUNCTIONS */
// midi_func_t timing_clock_send;
// midi_func_t start_send;
// midi_func_t continue_send;
// midi_func_t stop_send;
// midi_func_t active_sensing_send;
// midi_func_t reset_send;