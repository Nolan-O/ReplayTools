#include <stdlib.h>
#include <cstdio>
#include <string.h>
#include "data.h"
#include "error.h"
#include "options.h"

tempStatInfo g_statInfo;

void r_header::print(uint len)
{
    printf(P_COLOR_RED "\nHeader (%d bytes):\n" P_COLOR_RESET, len);
    printf("\t%s\n\t%s\n\t%llu\n\t%f\n\t%f\n\t%u\n\t%ld\n", m_szMapName, m_szPlayerName,
                m_ulSteamID, m_fTickInterval, m_fRunTime, m_iRunFlags, m_iRunDate, m_iStartDif);
}

uint frameToColorString(char* buf, uint fnum, r_frame* prev, r_frame* cur) {
    bool diff = g_options.pDiffOpt;
    bool ignoreVecs = g_options.pIgnoreVecOpt;
    bool numericKeys = g_options.pNumericKeys;

    vec3 eyes, origin, offset;

    if (diff) {
        eyes.x = cur->m_angEyeAngles.x - prev->m_angEyeAngles.x;
        eyes.y = cur->m_angEyeAngles.y - prev->m_angEyeAngles.y;
        eyes.z = cur->m_angEyeAngles.z - prev->m_angEyeAngles.z;
        origin.x = cur->m_vPlayerOrigin.x - prev->m_vPlayerOrigin.x;
        origin.y = cur->m_vPlayerOrigin.y - prev->m_vPlayerOrigin.y;
        origin.z = cur->m_vPlayerOrigin.z - prev->m_vPlayerOrigin.z;
        offset.x = cur->m_vPlayerViewOffset.x - prev->m_vPlayerViewOffset.x;
        offset.y = cur->m_vPlayerViewOffset.y - prev->m_vPlayerViewOffset.y;
        offset.z = cur->m_vPlayerViewOffset.z - prev->m_vPlayerViewOffset.z;
    }
    else {
        eyes.x = cur->m_angEyeAngles.x;
        eyes.y = cur->m_angEyeAngles.y;
        eyes.z = cur->m_angEyeAngles.z;
        origin.x = cur->m_vPlayerOrigin.x;
        origin.y = cur->m_vPlayerOrigin.y;
        origin.z = cur->m_vPlayerOrigin.z;
        offset.x = cur->m_vPlayerViewOffset.x;
        offset.y = cur->m_vPlayerViewOffset.y;
        offset.z = cur->m_vPlayerViewOffset.z;
    }

    //Making these const supresses a warning
    //Seems like g++ is treating it as ' ' instead of " " since it's
    //only one byte. Thus char* is the wrong type, but it shouldn't be.
    const char* keymsg = " ";
    const char* dirmsg = " ";
    char transmsg[4] = "  ";
    uint printed = 0;

    if (cur->meta.keyChanged)
        keymsg = P_COLOR_GREEN "*" P_COLOR_RESET;

    if (cur->meta.dirChanged)
        dirmsg = P_COLOR_GREEN "*" P_COLOR_RESET;

    if (cur->meta.transCompleted) {
        const char* tmp = (g_statInfo.transLen < 0 || g_statInfo.transLen > 9) ? "%d" : "%d ";
        sprintf(transmsg, tmp, g_statInfo.transLen);
    }

    printed += sprintf(buf + printed, "%s%s%s", keymsg, dirmsg, transmsg);

    printed += sprintf(buf + printed, P_COLOR_RED "Frame %d ", fnum);
    if (!ignoreVecs) {
        printed += sprintf(buf + printed, P_COLOR_RESET "%.2f %.2f %.2f", eyes.x, eyes.y, eyes.z);
        printed += sprintf(buf + printed, P_COLOR_CYAN " || " P_COLOR_RESET "%.2f %.2f %.2f", origin.x, origin.y, origin.z);
        printed += sprintf(buf + printed, P_COLOR_CYAN " || " P_COLOR_RESET "%.2f %.2f %.2f", offset.x, offset.y, offset.z);
        printed += sprintf(buf + printed, P_COLOR_CYAN " || ");
    }
    if (numericKeys) {
        printed += sprintf(buf + printed, P_COLOR_RESET "%d\n", cur->m_iPlayerButtons);
    }
    else {
        const char* a = cur->m_iPlayerButtons & IN_ATTACK ? "ATTACK " : "";
        const char* b = cur->m_iPlayerButtons & IN_JUMP ? "JUMP " : "";
        const char* c = cur->m_iPlayerButtons & IN_DUCK ? "DUCK " : "";
        const char* d = cur->m_iPlayerButtons & IN_FORWARD ? "FORWARD " : "";
        const char* e = cur->m_iPlayerButtons & IN_BACK ? "BACK " : "";
        const char* f = cur->m_iPlayerButtons & IN_USE ? "USE " : "";
        const char* g = cur->m_iPlayerButtons & IN_CANCEL ? "CANCEL " : "";
        const char* h = cur->m_iPlayerButtons & IN_LEFT ? "LEFT " : "";
        const char* i = cur->m_iPlayerButtons & IN_RIGHT ? "RIGHT " : "";
        const char* j = cur->m_iPlayerButtons & IN_MOVELEFT ? "MOVELEFT " : "";
        const char* k = cur->m_iPlayerButtons & IN_MOVERIGHT ? "MOVERIGHT " : "";
        const char* l = cur->m_iPlayerButtons & IN_ATTACK2 ? "ATTACK2 " : "";
        const char* m = cur->m_iPlayerButtons & IN_RUN ? "RUN " : "";
        const char* n = cur->m_iPlayerButtons & IN_RELOAD ? "RELOAD " : "";
        const char* o = cur->m_iPlayerButtons & IN_ALT1 ? "ALT1 " : "";
        const char* p = cur->m_iPlayerButtons & IN_ALT2 ? "ALT2 " : "";
        const char* q = cur->m_iPlayerButtons & IN_SCORE ? "SCORE " : "";
        const char* r = cur->m_iPlayerButtons & IN_SPEED ? "SPEED " : "";
        const char* s = cur->m_iPlayerButtons & IN_WALK ? "WALK " : "";
        const char* t = cur->m_iPlayerButtons & IN_ZOOM ? "ZOOM " : "";
        const char* u = cur->m_iPlayerButtons & IN_WEAPON1 ? "WEAPON1 " : "";
        const char* v = cur->m_iPlayerButtons & IN_WEAPON2 ? "WEAPON2 " : "";
        const char* w = cur->m_iPlayerButtons & IN_BULLRUSH ? "BULLRUSH " : "";
        const char* x = cur->m_iPlayerButtons & IN_GRENADE1 ? "GRENADE1 " : "";
        const char* y = cur->m_iPlayerButtons & IN_GRENADE2 ? "GRENADE2 " : "";
        const char* z = cur->m_iPlayerButtons & IN_ATTACK3 ? "ATTACK3 " : "";
        printed += sprintf(buf + printed, P_COLOR_RESET "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z);
    }
    return printed;
}

uint frameToString(char* buf, uint fnum, r_frame* prev, r_frame* cur) {
    bool diff = g_options.pDiffOpt;
    bool ignoreVecs = g_options.pIgnoreVecOpt;
    bool numericKeys = g_options.pNumericKeys;

    vec3 eyes, origin, offset;

    if (diff) {
        eyes.x = cur->m_angEyeAngles.x - prev->m_angEyeAngles.x;
        eyes.y = cur->m_angEyeAngles.y - prev->m_angEyeAngles.y;
        eyes.z = cur->m_angEyeAngles.z - prev->m_angEyeAngles.z;
        origin.x = cur->m_vPlayerOrigin.x - prev->m_vPlayerOrigin.x;
        origin.y = cur->m_vPlayerOrigin.y - prev->m_vPlayerOrigin.y;
        origin.z = cur->m_vPlayerOrigin.z - prev->m_vPlayerOrigin.z;
        offset.x = cur->m_vPlayerViewOffset.x - prev->m_vPlayerViewOffset.x;
        offset.y = cur->m_vPlayerViewOffset.y - prev->m_vPlayerViewOffset.y;
        offset.z = cur->m_vPlayerViewOffset.z - prev->m_vPlayerViewOffset.z;
    }
    else {
        eyes.x = cur->m_angEyeAngles.x;
        eyes.y = cur->m_angEyeAngles.y;
        eyes.z = cur->m_angEyeAngles.z;
        origin.x = cur->m_vPlayerOrigin.x;
        origin.y = cur->m_vPlayerOrigin.y;
        origin.z = cur->m_vPlayerOrigin.z;
        offset.x = cur->m_vPlayerViewOffset.x;
        offset.y = cur->m_vPlayerViewOffset.y;
        offset.z = cur->m_vPlayerViewOffset.z;
    }

    //Making these const supresses a warning
    //Seems like g++ is treating it as ' ' instead of " " since it's
    //only one byte. Thus char* is the wrong type, but it shouldn't be.
    const char* keymsg = " ";
    const char* dirmsg = " ";
    char transmsg[4] = "  ";
    uint printed = 0;

    if (cur->meta.keyChanged)
        keymsg =  "*" ;

    if (cur->meta.dirChanged)
        dirmsg =  "*" ;

    if (cur->meta.transCompleted) {
        const char* tmp = (g_statInfo.transLen < 0 || g_statInfo.transLen > 9) ? "%d" : "%d ";
        sprintf(transmsg, tmp, g_statInfo.transLen);
    }

    printed += sprintf(buf + printed, "%s%s%s", keymsg, dirmsg, transmsg);

    printed += sprintf(buf + printed,  "Frame %d ", fnum);
    if (!ignoreVecs) {
        printed += sprintf(buf + printed,  "%.2f %.2f %.2f", eyes.x, eyes.y, eyes.z);
        printed += sprintf(buf + printed,  " || "  "%.2f %.2f %.2f", origin.x, origin.y, origin.z);
        printed += sprintf(buf + printed,  " || "  "%.2f %.2f %.2f", offset.x, offset.y, offset.z);
        printed += sprintf(buf + printed,  " || ");
    }
    if (numericKeys) {
        printed += sprintf(buf + printed,  "%d\n", cur->m_iPlayerButtons);
    }
    else {
        const char* a = cur->m_iPlayerButtons & IN_ATTACK ? "ATTACK " : "";
        const char* b = cur->m_iPlayerButtons & IN_JUMP ? "JUMP " : "";
        const char* c = cur->m_iPlayerButtons & IN_DUCK ? "DUCK " : "";
        const char* d = cur->m_iPlayerButtons & IN_FORWARD ? "FORWARD " : "";
        const char* e = cur->m_iPlayerButtons & IN_BACK ? "BACK " : "";
        const char* f = cur->m_iPlayerButtons & IN_USE ? "USE " : "";
        const char* g = cur->m_iPlayerButtons & IN_CANCEL ? "CANCEL " : "";
        const char* h = cur->m_iPlayerButtons & IN_LEFT ? "LEFT " : "";
        const char* i = cur->m_iPlayerButtons & IN_RIGHT ? "RIGHT " : "";
        const char* j = cur->m_iPlayerButtons & IN_MOVELEFT ? "MOVELEFT " : "";
        const char* k = cur->m_iPlayerButtons & IN_MOVERIGHT ? "MOVERIGHT " : "";
        const char* l = cur->m_iPlayerButtons & IN_ATTACK2 ? "ATTACK2 " : "";
        const char* m = cur->m_iPlayerButtons & IN_RUN ? "RUN " : "";
        const char* n = cur->m_iPlayerButtons & IN_RELOAD ? "RELOAD " : "";
        const char* o = cur->m_iPlayerButtons & IN_ALT1 ? "ALT1 " : "";
        const char* p = cur->m_iPlayerButtons & IN_ALT2 ? "ALT2 " : "";
        const char* q = cur->m_iPlayerButtons & IN_SCORE ? "SCORE " : "";
        const char* r = cur->m_iPlayerButtons & IN_SPEED ? "SPEED " : "";
        const char* s = cur->m_iPlayerButtons & IN_WALK ? "WALK " : "";
        const char* t = cur->m_iPlayerButtons & IN_ZOOM ? "ZOOM " : "";
        const char* u = cur->m_iPlayerButtons & IN_WEAPON1 ? "WEAPON1 " : "";
        const char* v = cur->m_iPlayerButtons & IN_WEAPON2 ? "WEAPON2 " : "";
        const char* w = cur->m_iPlayerButtons & IN_BULLRUSH ? "BULLRUSH " : "";
        const char* x = cur->m_iPlayerButtons & IN_GRENADE1 ? "GRENADE1 " : "";
        const char* y = cur->m_iPlayerButtons & IN_GRENADE2 ? "GRENADE2 " : "";
        const char* z = cur->m_iPlayerButtons & IN_ATTACK3 ? "ATTACK3 " : "";
        printed += sprintf(buf + printed, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z);
    }
    return printed;
}

//Throws out some undesireable key transition detections
inline static bool EvaluateTransition_Keys(int dir, float dtAng, bool otherStatus)
{
    if (!otherStatus)
        return true;
    else if (dir == IN_MOVERIGHT && dtAng <= 0)
        return true;
    else if (dir == IN_MOVELEFT && dtAng >= 0)
        return true;
        
    return false;
}

//Throws out some undesireable angle transition detections
inline static bool EvaluateTransition_Ang(int keys, float dtAng, bool otherStatus)
{
    if (!otherStatus)
        return true;
    else if (keys & IN_MOVERIGHT && !(keys & IN_MOVELEFT) && dtAng <= 0)
        return true;
    else if (keys & IN_MOVELEFT && !(keys & IN_MOVERIGHT) && dtAng >= 0)
        return true;
        
    return false;
}

void r_frame::discreteStatStep(r_frame* prev, uint tick)
{
    float dtAng = m_angEyeAngles.y - prev->m_angEyeAngles.y;
    if (dtAng > 180.0)
        dtAng -= 360;
    else if (dtAng < -180.0)
        dtAng += 360;
    
    meta.dtAng = dtAng;
    
    if (!(m_iPlayerButtons & IN_MOVERIGHT && m_iPlayerButtons & IN_MOVELEFT))
    {
        if (m_iPlayerButtons & IN_MOVELEFT) {
            if ((prev->m_iPlayerButtons & IN_MOVERIGHT && prev->m_iPlayerButtons & IN_MOVELEFT) || !(prev->m_iPlayerButtons & IN_MOVELEFT))
            {
                g_statInfo.keyChanged = EvaluateTransition_Keys(IN_MOVELEFT, dtAng, g_statInfo.dirChanged);
                if (g_statInfo.keyChanged) {
                    g_statInfo.keyTransTick = tick;
                    meta.keyChanged = true;
                }
                else
                    g_statInfo.dirChanged = false;
            }
        }
        else if (m_iPlayerButtons & IN_MOVERIGHT) {
            if ((prev->m_iPlayerButtons & IN_MOVERIGHT && prev->m_iPlayerButtons & IN_MOVELEFT) || !(prev->m_iPlayerButtons & IN_MOVERIGHT))
            {
                g_statInfo.keyChanged = EvaluateTransition_Keys(IN_MOVERIGHT, dtAng, g_statInfo.dirChanged);
                if (g_statInfo.keyChanged) {
                    g_statInfo.keyTransTick = tick;
                    meta.keyChanged = true;
                }
                else
                    g_statInfo.dirChanged = false;
            }
        }
    }
    if (dtAng != 0.0 && ((dtAng < 0.0 && prev->meta.dtAng > 0.0) || (dtAng > 0.0 && prev->meta.dtAng < 0.0) || prev->meta.dtAng == 0.0))
    {
        g_statInfo.dirChanged = EvaluateTransition_Ang(m_iPlayerButtons, dtAng, g_statInfo.keyChanged);
        if (g_statInfo.dirChanged) {
            g_statInfo.angTransTick = tick;
            meta.dirChanged = true;
        }
        else
            g_statInfo.keyChanged = false;
    }
    if (g_statInfo.keyChanged && g_statInfo.dirChanged)
    {
        int t = g_statInfo.keyTransTick - g_statInfo.angTransTick;
        g_statInfo.keyChanged = false;
        g_statInfo.dirChanged = false;
        if (t > -26 && t < 26)
        {
            g_statInfo.transLen = t;
            meta.transCompleted = true;
        }
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
