#ifndef EMBMIDIFILE_INCLUDED
#define EMBMIDIFILE_INCLUDED

#include "embMIDI.h"
#include <stdint.h>
#include <stdlib.h>

#define MAX_TRACKS 32 // Maximum number of tracks supported
#define FPSHIFT 16 // Fixed-point precision (16 fractional bits)
#define FIXED_ONE (1 << FPSHIFT) // Represents 1.0 in fixed-point
typedef struct {
    unsigned char* data;       // Pointer to the track data
    int size;                  // Size of the track data
    int position;              // Current read position in the track
    int currentTime;           // Current time in ticks for this track
    unsigned char runningStatus; // Running status for this track
} MidiTrack;

typedef struct {
    unsigned char* data;       // Pointer to the MIDI file data
    int size;                  // Size of the MIDI file
    int samplerate;            // Sample rate for playback
    int ticksPerQuarterNote;   // Ticks per quarter note (from the header)
    int currentTime;           // Global current time in ticks
	int currentTimeFraction;
	int ticksPerSampleShifted;
    int tempo;                 // Tempo in microseconds per quarter note
    int numTracks;             // Number of tracks in the MIDI file
    MidiTrack tracks[MAX_TRACKS]; // Array of tracks
} MidiFile;

MidiFile midiFile;


int calcTPFS(){
	// Calculate ticks per second
    int ticksPerQuarterNote = midiFile.ticksPerQuarterNote;
    int tempo = midiFile.tempo; // Tempo in microseconds per quarter note

    // ticksPerSecond = (ticksPerQuarterNote * 1,000,000) / tempo
    int ticksPerSecond = (ticksPerQuarterNote * 10000) / (tempo/100);

    // Calculate ticksPerSampleShifted with 16-bit fractional precision
    int ticksPerSampleShifted = (ticksPerSecond << FPSHIFT) / midiFile.samplerate;
	return ticksPerSampleShifted;
	
}
// Helper function to read a variable-length quantity (VLQ)
int readVLQ(unsigned char* data, int* position) {
    int value = 0;
    unsigned char byte;
    do {
        byte = data[(*position)++];
        value = (value << 7) | (byte & 0x7F);
    } while (byte & 0x80);
    return value;
}

// Helper function to read a fixed-length value (e.g., 1, 2, or 4 bytes)
uint32_t readFixed(unsigned char* data, int* position, int length) {
    uint32_t value = 0;
    for (int i = 0; i < length; i++) {
        value = (value << 8) | data[(*position)++];
    }
    return value;
}

// Initialize the MIDI file player
void embmidifil_init(int samplerate, unsigned char *data, int size) {
    midiFile.data = data;
    midiFile.size = size;
    midiFile.samplerate = samplerate;
    midiFile.currentTime = 0;
    midiFile.tempo = 500000; // Default tempo (120 BPM)
    midiFile.numTracks = 0;

    // Parse the MIDI header
    if (midiFile.size < 14) {
        return; // Invalid MIDI file
    }

    // Check the header chunk type
    if (data[0] != 'M' || data[1] != 'T' || data[2] != 'h' || data[3] != 'd') {
        return; // Invalid MIDI header
    }

    // Get the number of tracks and ticks per quarter note
    midiFile.ticksPerQuarterNote = (data[12] << 8) | data[13];
    midiFile.numTracks = (data[10] << 8) | data[11];

    // Initialize tracks
    int pos = 14; // Start after the header
    for (int i = 0; i < midiFile.numTracks && i < MAX_TRACKS; i++) {
        if (pos + 8 > midiFile.size) {
            break; // Invalid track chunk
        }

        // Check for track chunk header
        if (data[pos] != 'M' || data[pos + 1] != 'T' || data[pos + 2] != 'r' || data[pos + 3] != 'k') {
            break; // Invalid track chunk
        }

        // Get the track size
        int trackSize = (data[pos + 4] << 24) | (data[pos + 5] << 16) | (data[pos + 6] << 8) | data[pos + 7];
        pos += 8;

        // Initialize the track
        midiFile.tracks[i].data = data + pos;
        midiFile.tracks[i].size = trackSize;
        midiFile.tracks[i].position = 0;
        midiFile.tracks[i].currentTime = 0;
        midiFile.tracks[i].runningStatus = 0;

        pos += trackSize; // Move to the next track
    }
	
	midiFile.ticksPerSampleShifted=calcTPFS();
	printf("succeess\n");
}

// Process the next event in a track
void processTrackEvent(MidiTrack* track) {
	printf("event\n");
    if (track->position >= track->size) {
        return; // No more events in this track
    }

    // Read delta time
    int deltaTime = readVLQ(track->data, &track->position);
    track->currentTime += deltaTime;

    // Read the status byte
    unsigned char status = track->data[track->position];
    if (status & 0x80) {
        // New status byte, update running status
        track->runningStatus = status;
        track->position++;
    } else {
        // Use running status
        status = track->runningStatus;
    }

    unsigned char eventType = status & 0xF0;
    unsigned char channel = status & 0x0F;

    switch (eventType) {
        case 0x80: // Note Off
        {
            unsigned char note = track->data[track->position++];
            unsigned char velocity = track->data[track->position++];
            noteOff(channel, note);
            break;
        }
        case 0x90: // Note On
        {
            unsigned char note = track->data[track->position++];
            unsigned char velocity = track->data[track->position++];
            if (velocity == 0) {
                noteOff(channel, note); // Note On with velocity 0 is equivalent to Note Off
            } else {
                noteOn(channel, note, velocity);
            }
            break;
        }
        case 0xA0: // Polyphonic Aftertouch
        {
            unsigned char note = track->data[track->position++];
            unsigned char pressure = track->data[track->position++];
            // Not used, but parsed correctly
            break;
        }
        case 0xB0: // Control Change
        {
            unsigned char control = track->data[track->position++];
            unsigned char value = track->data[track->position++];
            controlChange(channel, control, value);
            break;
        }
        case 0xC0: // Program Change
        {
            unsigned char program = track->data[track->position++];
            programChange(channel, program);
            break;
        }
        case 0xD0: // Channel Aftertouch
        {
            unsigned char pressure = track->data[track->position++];
            // Not used, but parsed correctly
            break;
        }
        case 0xE0: // Pitch Bend
        {
            unsigned char lsb = track->data[track->position++];
            unsigned char msb = track->data[track->position++];
            /*int bend = ((msb << 7) | lsb) - 8192; // Convert to signed 14-bit value*/
			int bend = ((msb << 7) | lsb);
			pitchBend(channel,bend);
            // Not used, but parsed correctly
            break;
        }
        case 0xF0: // System Exclusive or Meta Event
        {
            if (status == 0xFF) { // Meta Event
                unsigned char metaType = track->data[track->position++];
                unsigned char length = track->data[track->position++];
                switch (metaType) {
                    case 0x51: // Set Tempo
                        midiFile.tempo = readFixed(track->data, &track->position, 3);
						midiFile.ticksPerSampleShifted=calcTPFS();
                        break;
                    default:
                        // Skip other meta events
                        track->position += length;
                        break;
                }
            } else if (status == 0xF0||status==0xF7) { // SysEx
                // Skip SysEx data
                int length = readVLQ(track->data, &track->position);
                track->position += length;
				//while((track->position++)!=0xF7);
				//track->position++;
				//track->position += 1;
            }
            break;
        }
        default:
            // Unsupported event type, skip
            track->position++;
            break;
    }
}

// Play the next batch of samples
/*void embmidifil_playsamples(int samples) {
    float ticksPerSample = (float)(midiFile.ticksPerQuarterNote * midiFile.tempo) / (float)(midiFile.samplerate * 1000000.0);
    int targetTime = midiFile.currentTime + samples * ticksPerSample;
	printf("tpqn: %d tempo: %d\n",midiFile.ticksPerQuarterNote,midiFile.tempo);
	printf("curtime: %d target: %d\n",midiFile.currentTime,targetTime);
    while (midiFile.currentTime < targetTime) {
        // Find the track with the earliest event
        int nextTrack = -1;
        int nextTime = targetTime;

        for (int i = 0; i < midiFile.numTracks; i++) {
            if (midiFile.tracks[i].position < midiFile.tracks[i].size && midiFile.tracks[i].currentTime < nextTime) {
                nextTrack = i;
                nextTime = midiFile.tracks[i].currentTime;
            }
        }

        if (nextTrack == -1) {
            break; // No more events in any track
        }

        // Process the event from the selected track
        processTrackEvent(&midiFile.tracks[nextTrack]);

        // Update the global time
        midiFile.currentTime = nextTime;
    }
}*/


/*#define FPSHIFT 8 // Fixed-point precision (16 fractional bits)
#define FIXED_ONE (1 << FPSHIFT) // Represents 1.0 in fixed-point

void embmidifil_playsamples(int samples) {
    // Calculate ticksPerSample using fixed-point math
    int ticksPerQuarterNote = midiFile.ticksPerQuarterNote;
    int tempo = midiFile.tempo;
    int samplerate = midiFile.samplerate;

    // Fixed-point calculation:
    // ticksPerSample = (ticksPerQuarterNote * tempo) / (samplerate * 1000000)
    // To avoid overflow, break it into smaller steps.

    // Step 1: Scale numerator and denominator to avoid overflow
    int numerator = ticksPerQuarterNote * (tempo / 1000 ) * FIXED_ONE; // Reduce tempo by 1000
    int denominator = samplerate * 1000; // Scale denominator by the same factor

    // Step 2: Calculate ticksPerSample in fixed-point
    int ticksPerSample = (numerator / denominator) ; // Initial integer part
    int remainder = (numerator) % denominator; // Remainder for fractional part
    ticksPerSample += (remainder) / denominator; // Add fractional part

    // Step 3: Calculate targetTime in fixed-point
    int targetTime = midiFile.currentTime + ((samples * ticksPerSample) >> FPSHIFT);

    // Process events until targetTime is reached
    while (midiFile.currentTime < targetTime) {
        // Find the track with the earliest next event
        int nextTrack = -1;
        int nextEventTime = targetTime; // Initialize to the target time

        for (int i = 0; i < midiFile.numTracks; i++) {
            if (midiFile.tracks[i].position < midiFile.tracks[i].size) {
                // Calculate the time of the next event in this track
                int deltaTime = readVLQ(midiFile.tracks[i].data, &midiFile.tracks[i].position);
                int trackNextEventTime = midiFile.tracks[i].currentTime + deltaTime;

                // Check if this event is the earliest
                if (trackNextEventTime < nextEventTime) {
                    nextTrack = i;
                    nextEventTime = trackNextEventTime;
                }

                // Rewind the position to before the delta time (since we only peeked)
                midiFile.tracks[i].position -= deltaTime < 0x80 ? 1 : deltaTime < 0x4000 ? 2 : deltaTime < 0x200000 ? 3 : 4;
            }
        }

        if (nextTrack == -1) {
            break; // No more events in any track
        }

        // Process the event from the selected track
        processTrackEvent(&midiFile.tracks[nextTrack]);

        // Update the global time to the time of the processed event
        midiFile.currentTime = nextEventTime;

        // Update the current time of the track
        midiFile.tracks[nextTrack].currentTime = nextEventTime;
    }
	midiFile.currentTime = targetTime;
}*/



void embmidifil_playsamples(int samples) {


    // Accumulate fractional ticks
    int deltaTicksShifted = midiFile.currentTimeFraction + (midiFile.ticksPerSampleShifted * samples);
    midiFile.currentTimeFraction = deltaTicksShifted & 0x0000FFFF; // Keep fractional part
    int deltaTicks = deltaTicksShifted >> FPSHIFT; // Extract integer part
    int targetTime = midiFile.currentTime + deltaTicks;

    // Process events until currentTime reaches the target time
    while (midiFile.currentTime < targetTime) {
        // Find the track with the earliest next event
        int nextTrack = -1;
        int nextEventTime = targetTime; // Initialize to the target time

        for (int i = 0; i < midiFile.numTracks; i++) {
            if (midiFile.tracks[i].position < midiFile.tracks[i].size) {
                // Calculate the time of the next event in this track
                int deltaTime = readVLQ(midiFile.tracks[i].data, &midiFile.tracks[i].position);
                int trackNextEventTime = midiFile.tracks[i].currentTime + deltaTime;

                // Check if this event is the earliest
                if (trackNextEventTime < nextEventTime) {
                    nextTrack = i;
                    nextEventTime = trackNextEventTime;
                }

                // Rewind the position to before the delta time (since we only peeked)
                midiFile.tracks[i].position -= deltaTime < 0x80 ? 1 : deltaTime < 0x4000 ? 2 : deltaTime < 0x200000 ? 3 : 4;
            }
        }

        if (nextTrack == -1 || nextEventTime > targetTime) {
            break; // No more events in any track or no events before the target time
        }

        // Process the event from the selected track
        processTrackEvent(&midiFile.tracks[nextTrack]);

        // Update the current time of the track
        midiFile.tracks[nextTrack].currentTime = nextEventTime;

        // Update the global currentTime to the time of the processed event
        midiFile.currentTime = nextEventTime;
    }

    // Update the global currentTime and currentTimeFraction
    midiFile.currentTime = targetTime;
    midiFile.currentTimeFraction = deltaTicksShifted & 0x0000FFFF; // Keep fractional part
}
#endif // EMBMIDIFILE_INCLUDED