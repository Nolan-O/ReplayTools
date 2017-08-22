#include <stdlib.h>
#include "data.h"
#include "error.h"

void r_header::print(uint len)
{
    printf(P_COLOR_RED "\nHeader (%d bytes):\n" P_COLOR_RESET, len);
    printf("\t%s\n\t%s\n\t%llu\n\t%f\n\t%f\n\t%u\n\t%ld\n", m_szMapName, m_szPlayerName);
}

void r_frame::print(uint fnum, bool diff, bool ignoreVecs, bool numericKeys, r_frame* prev)
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
    if (numericKeys) {
        printf(P_COLOR_RESET "%d\n", m_iPlayerButtons);
    }
    else {
        const char* a = m_iPlayerButtons & IN_ATTACK ? "ATTACK " : "";
        const char* b = m_iPlayerButtons & IN_JUMP ? "IN_JUMP " : "";
        const char* c = m_iPlayerButtons & IN_DUCK ? "IN_DUCK " : "";
        const char* d = m_iPlayerButtons & IN_FORWARD ? "IN_FORWARD " : "";
        const char* e = m_iPlayerButtons & IN_BACK ? "IN_BACK " : "";
        const char* f = m_iPlayerButtons & IN_USE ? "IN_USE " : "";
        const char* g = m_iPlayerButtons & IN_CANCEL ? "IN_CANCEL " : "";
        const char* h = m_iPlayerButtons & IN_LEFT ? "IN_LEFT " : "";
        const char* i = m_iPlayerButtons & IN_RIGHT ? "IN_RIGHT " : "";
        const char* j = m_iPlayerButtons & IN_MOVELEFT ? "IN_MOVELEFT " : "";
        const char* k = m_iPlayerButtons & IN_MOVERIGHT ? "IN_MOVERIGHT " : "";
        const char* l = m_iPlayerButtons & IN_ATTACK2 ? "IN_ATTACK2 " : "";
        const char* m = m_iPlayerButtons & IN_RUN ? "IN_RUN " : "";
        const char* n = m_iPlayerButtons & IN_RELOAD ? "IN_RELOAD " : "";
        const char* o = m_iPlayerButtons & IN_ALT1 ? "IN_ALT1 " : "";
        const char* p = m_iPlayerButtons & IN_ALT2 ? "IN_ALT2 " : "";
        const char* q = m_iPlayerButtons & IN_SCORE ? "IN_SCORE " : "";
        const char* r = m_iPlayerButtons & IN_SPEED ? "IN_SPEED " : "";
        const char* s = m_iPlayerButtons & IN_WALK ? "IN_WALK " : "";
        const char* t = m_iPlayerButtons & IN_ZOOM ? "IN_ZOOM " : "";
        const char* u = m_iPlayerButtons & IN_WEAPON1 ? "IN_WEAPON1 " : "";
        const char* v = m_iPlayerButtons & IN_WEAPON2 ? "IN_WEAPON2 " : "";
        const char* w = m_iPlayerButtons & IN_BULLRUSH ? "IN_BULLRUSH " : "";
        const char* x = m_iPlayerButtons & IN_GRENADE1 ? "IN_GRENADE1 " : "";
        const char* y = m_iPlayerButtons & IN_GRENADE2 ? "IN_GRENADE2 " : "";
        const char* z = m_iPlayerButtons & IN_ATTACK3 ? "IN_ATTACK3 " : "";
        printf(P_COLOR_RESET "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z);
    }
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