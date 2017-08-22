#pragma once

#include <time.h>

#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)	// grenade 1
#define IN_GRENADE2		(1 << 24)	// grenade 2
#define	IN_ATTACK3		(1 << 25)

typedef unsigned long long  uint64;
typedef unsigned int        uint32;
typedef unsigned short      uint16;
typedef unsigned char       uint8;

#define MAX_STAGES 64

struct vec3
{
    float x;
    float y;
    float z;
};

struct r_header
{
    void print(uint len);
    
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
    void print(uint fnum, bool diff, bool ignoreVecs, bool numericKeys, r_frame* prev);
    
    vec3 m_angEyeAngles;
    vec3 m_vPlayerOrigin;
    vec3 m_vPlayerViewOffset;
    int m_iPlayerButtons;
};


struct r_runStats 
{
    void print();
    
    // Note: Passing 0 as the index to any of these will return the overall stat, i.e during the entire run.
    
    uint8 m_iTotalZones; // Required for the operator= overload

    // Keypress
    uint32 m_iZoneJumps[MAX_STAGES + 1], // Amount of jumps per stage/checkpoint
        m_iZoneStrafes[MAX_STAGES + 1];  // Amount of strafes per stage/checkpoint

    // Sync
    float m_flZoneStrafeSyncAvg[MAX_STAGES + 1], // The average sync1 you had over the given stage/checkpoint
        m_flZoneStrafeSync2Avg[MAX_STAGES + 1];  // The average sync2 you had over the given stage/checkpoint

    // Time
    float m_flZoneEnterTime[MAX_STAGES + 1], // The amount of time (seconds) you spent to accomplish (stage) -> (stage + 1)
        m_flZoneTime[MAX_STAGES + 1]; // The time in seconds that you entered the given stage/checkpoint

    // Velocity
    float m_flZoneVelocityMax3D[MAX_STAGES + 1], m_flZoneVelocityMax2D[MAX_STAGES + 1],// The 3D velocity with which you started the stage (exit this stage's start trigger)
        m_flZoneVelocityAvg3D[MAX_STAGES + 1], m_flZoneVelocityAvg2D[MAX_STAGES + 1],// Max velocity for a stage/checkpoint
        m_flZoneEnterSpeed3D[MAX_STAGES + 1], m_flZoneEnterSpeed2D[MAX_STAGES + 1],// Average velocity in a stage/checkpoint
        m_flZoneExitSpeed3D[MAX_STAGES + 1], m_flZoneExitSpeed2D[MAX_STAGES + 1];// The velocity with which you exit the stage (this stage -> next)
};