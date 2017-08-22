#include <stdlib.h>
#include "data.h"
#include "error.h"

void r_header::print(uint len)
{
    printf(P_COLOR_RED "\nHeader (%d bytes):\n" P_COLOR_RESET, len);
    printf("\t%s\n\t%s\n\t%llu\n\t%f\n\t%f\n\t%u\n\t%ld\n", m_szMapName, m_szPlayerName);
}

void r_frame::print(uint fnum, bool diff, bool ignoreVecs, r_frame* prev)
{
    vec3 eyes, origin, offset;
    if (diff) {
        eyes.x = m_angEyeAngles.x - prev->m_angEyeAngles.x;
        eyes.y = m_angEyeAngles.y - prev->m_angEyeAngles.y;
        eyes.z = m_angEyeAngles.z - prev->m_angEyeAngles.z;
        origin.x = m_vPlayerOrigin.x - prev->m_vPlayerOrigin.x;
        origin.y = m_vPlayerOrigin.y - prev->m_vPlayerOrigin.y;
        origin.z = m_vPlayerOrigin.z - prev->m_vPlayerOrigin.z;
        offset.x = m_vPlayerViewOffset.x - prev->m_vPlayerViewOffset.x;
        offset.y = m_vPlayerViewOffset.y - prev->m_vPlayerViewOffset.y;
        offset.z = m_vPlayerViewOffset.z - prev->m_vPlayerViewOffset.z;
    }
    else {
        eyes.x = m_angEyeAngles.x;
        eyes.y = m_angEyeAngles.y;
        eyes.z = m_angEyeAngles.z;
        origin.x = m_vPlayerOrigin.x;
        origin.y = m_vPlayerOrigin.y;
        origin.z = m_vPlayerOrigin.z;
        offset.x = m_vPlayerViewOffset.x;
        offset.y = m_vPlayerViewOffset.y;
        offset.z = m_vPlayerViewOffset.z;
    }
    
    printf(P_COLOR_RED "Frame %d : ", fnum);
    if (!ignoreVecs) {
        printf(P_COLOR_RESET "%.2f %.2f %.2f", eyes.x, eyes.y, eyes.z);
        printf(P_COLOR_CYAN " || " P_COLOR_RESET "%.2f %.2f %.2f", origin.x, origin.y, origin.z);
        printf(P_COLOR_CYAN " || " P_COLOR_RESET "%.2f %.2f %.2f", offset.x, offset.y, offset.z);
        printf(P_COLOR_CYAN " || ");
    }
        printf(P_COLOR_RESET "%d\n", m_iPlayerButtons);
}

void r_runStats::print()
{
    printf(P_COLOR_RED "\nRun Stats block:");
    for (uint i = 0; i < m_iTotalZones; ++i) {
        printf(P_COLOR_CYAN"\n    Zone %d of %d%s\n" P_COLOR_RESET, i, m_iTotalZones, i ? "" : " (OVERALL)");
        printf("\t%d\n\t%d\n\t%f\n\t%f\n\t%f\n\t%f\n\t%f\n\t%f\n\t%f\n\t%f\n\t%f\n\t%f\n\t%f\n\n",
                m_iZoneJumps[i], m_iZoneStrafes[i], m_flZoneStrafeSyncAvg[i], m_flZoneStrafeSync2Avg[i], m_flZoneEnterTime[i], 
                m_flZoneTime[i], m_flZoneVelocityMax3D[i], m_flZoneVelocityMax2D[i], m_flZoneVelocityAvg3D[i],
                m_flZoneVelocityAvg2D[i], m_flZoneEnterSpeed3D[i], m_flZoneEnterSpeed2D[i], m_flZoneExitSpeed3D[i], 
                m_flZoneExitSpeed2D[i]);
    }
}