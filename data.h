#pragma once

#include <time.h>
#include "error.h"

typedef unsigned long long  uint64;
typedef unsigned int        uint32;
typedef unsigned short      uint16;

#define MAX_STAGES 64

struct vec3
{
    float x;
    float y;
    float z;
};

struct r_header
{
    void print()
    {
        printf(P_COLOR_CYAN "\nHeader:\n");
        printf("\t%s\n\t%s\n\t%llu\n\t%f\n\t%f\n\t%u\n\t%ld\n", m_szMapName, m_szPlayerName);
    }
    
    char m_szMapName[256];    // The map the run was done in.
    char m_szPlayerName[256]; // The name of the player that did this run.
    uint64 m_ulSteamID;       // The steamID of the player that did this run.
    float m_fTickInterval;    // The tickrate of the run.
    float m_fRunTime;         // The total runtime of the run in seconds.
    uint32 m_iRunFlags;       // The flags the player ran with.
    time_t m_iRunDate;        // The date this run was achieved.
    int m_iStartDif;          // The difference between the tick of the start timer and record
};

struct r_frame
{
    vec3 m_angEyeAngles;
    vec3 m_vPlayerOrigin;
    vec3 m_vPlayerViewOffset;
    int m_iPlayerButtons;
};

/*
struct data 
{
    // Note: Passing 0 as the index to any of these will return the overall stat, i.e during the entire run.
    
    uint8 m_iTotalZones; // Required for the operator= overload

    // Keypress
    uint32 m_iZoneJumps[MAX_STAGES + 1], // Amount of jumps per stage/checkpoint
        m_iZoneStrafes[MAX_STAGES + 1];  // Amount of strafes per stage/checkpoint

    // Time
    float m_flZoneTime[MAX_STAGES + 1], // The amount of time (seconds) you spent to accomplish (stage) -> (stage + 1)
        m_flZoneEnterTime[MAX_STAGES + 1]; // The time in seconds that you entered the given stage/checkpoint

    // Sync
    float m_flZoneStrafeSyncAvg[MAX_STAGES + 1], // The average sync1 you had over the given stage/checkpoint
        m_flZoneStrafeSync2Avg[MAX_STAGES + 1];  // The average sync2 you had over the given stage/checkpoint

    // Velocity
    float m_flZoneEnterSpeed3D[MAX_STAGES + 1], m_flZoneEnterSpeed2D[MAX_STAGES + 1],// The 3D velocity with which you started the stage (exit this stage's start trigger)
        m_flZoneVelocityMax3D[MAX_STAGES + 1], m_flZoneVelocityMax2D[MAX_STAGES + 1],// Max velocity for a stage/checkpoint
        m_flZoneVelocityAvg3D[MAX_STAGES + 1], m_flZoneVelocityAvg2D[MAX_STAGES + 1],// Average velocity in a stage/checkpoint
        m_flZoneExitSpeed3D[MAX_STAGES + 1], m_flZoneExitSpeed2D[MAX_STAGES + 1];// The velocity with which you exit the stage (this stage -> next)
};*/