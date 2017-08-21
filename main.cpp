#include "simpleopt.h"
#include "error.h"
#include "data.h"
#include <stdio.h>
#include <string.h>
#include "assert.h"

#define REPLAY_MAGIC_LE 0x524D4F4D
#define REPLAY_MAGIC_BE 0x4D4F4D52

enum { OPT_HELP, OPT_FIN = 100};

CSimpleOpt::SOption g_Options[] =
{
    {1, "-h", SO_NONE},
    {2, "-r", SO_NONE},
    {3, "-f", SO_NONE},
    {4, "-n", SO_NONE},
    {4, "--none", SO_NONE},
    {5, "--nocolor", SO_NONE},
    {OPT_HELP, "--help", SO_NONE},
    SO_END_OF_OPTIONS
};

/*
 * Searches a buffer up until the buffer's end or an arbitrary
 * maximum length, starting at an index in the buffer
 *
int idxstrlen(char* mem, uint max_buf, uint max_len, uint idx)
{
    assert(idx < max_len);
    
    int n = 0;
    max_len -= idx;
    while (mem[idx] != '\0' && idx <= max_buf && n <= max_len) {
        ++idx;
        ++n;
    }
    ++n; // The null is part of the string, to this function
    if (n > max_len || idx > max_buf)
        return -1;

    return n;
} */

void showUsage()
{
    printf(
        "Usage: rpts [options] file\n"
        "\n"
        "-h                 Prints header data\n"
        "-r                 Prints the data in the run stats block\n"
        "-f                 Prints data in every frame\n"
        "\n"
    );
    exit(EXIT_SUCCESS);
}

uint parseHeader(FILE* file, r_header* header)
{
    char buf[512];
    fread(buf, 256, 2, file);
    
    int magic = REPLAY_MAGIC_BE;
    if (!strncmp(buf, (const char*)&magic, 4))
        soft("Invalid REPLAY_MAGIC");
    
    printf("Replay version: %d\n", buf[4]);
    
    // Note: string sizes are stored before them
    // Read map name
    uint i = 5;
    uint16 size = buf[i];
    i += sizeof(uint16);
    memcpy(header->m_szMapName, &buf[i], size);
    header->m_szMapName[size] = '\0';
    i += size;
    
    // Read player name
    size = buf[i];
    i += sizeof(uint16);
    memcpy(header->m_szPlayerName, &buf[i], size);
    header->m_szPlayerName[size] = '\0';
    i += size;
    
    // Read other metadata, starting with the steamid
    fread(&header->m_ulSteamID, sizeof(uint64), 1, file);
    fread(&header->m_fTickInterval, sizeof(float), 1, file);
    fread(&header->m_fRunTime, sizeof(float), 1, file);
    fread(&header->m_iRunFlags, sizeof(uint32), 1, file);
    fread(&header->m_iRunDate, sizeof(time_t), 1, file);
    fread(&header->m_iStartDif, sizeof(int), 1, file);
    
    return i + sizeof(uint64) + sizeof(float) + sizeof(float) + sizeof(uint32) + sizeof(time_t) + sizeof(int);
}

void parseRunStats(FILE* file, r_runStats* stats)
{
    stats->m_iTotalZones = fgetc(file);
    //stats->m_iTotalZones = static_cast<uint8>(stats->m_iTotalZones);
    for (uint i = 0; i <= stats->m_iTotalZones; ++i) {
        for (uint n = 0; n < 14; ++n) {
            //Sure would be nice if the data was stored contiguiously...
            uint offset = 65 * n;
            fread(stats->m_iZoneJumps + i + offset, 4, 1, file);
        }
    }
}

void parseFrame(FILE* file, r_frame* frame)
{
    fread(&frame->m_angEyeAngles.x, 4, 1, file);
    fread(&frame->m_angEyeAngles.y, 4, 1, file);
    fread(&frame->m_angEyeAngles.z, 4, 1, file);
    fread(&frame->m_vPlayerOrigin.x, 4, 1, file);
    fread(&frame->m_vPlayerOrigin.y, 4, 1, file);
    fread(&frame->m_vPlayerOrigin.z, 4, 1, file);
    fread(&frame->m_vPlayerViewOffset.x, 4, 1, file);
    fread(&frame->m_vPlayerViewOffset.y, 4, 1, file);
    fread(&frame->m_vPlayerViewOffset.z, 4, 1, file);
    fread(&frame->m_iPlayerButtons, 4, 1, file);
}

int main(int argc, char* argv[])
{
    CSimpleOpt args(argc, argv, g_Options);
    
    bool pHeaderOpt = false, pStatsOpt = false, pFramesOpt = false;
    bool pNone = false;
    
    while (args.Next()) {
        if (args.LastError() == SO_SUCCESS) {
            switch (args.OptionId()) {
                case 1:
                    pHeaderOpt = true;
                    break;
                case 2:
                    pStatsOpt = true;
                    break;
                case 3:
                    pFramesOpt = true;
                    break;
                case 4:
                    pNone = true;
                    break;
                case OPT_HELP:
                    showUsage();
            }
        }
        else {
            showUsage();
        }
    }
    
    if (args.FileCount() == 0) {
        fatal("No replay file provided\n");
        return 1;
    }
    
    if (args.FileCount() > 1)
        soft("Multiple files recieved; accepting only the first one");
        
    FILE* replayFile = fopen(args.Files()[0], "r");
    fseek(replayFile, 0, SEEK_SET);
    r_header header;
    uint headerlen = parseHeader(replayFile, &header);
    if (headerlen) {
        if (pHeaderOpt)
            header.print(headerlen);
    }
    else {
        soft("Unknown error parsing header"); //Not possible... yet
    }
    
    //Read a single byte that tells us if there are run stats
    fseek(replayFile, headerlen, SEEK_SET);
    char rs = fgetc(replayFile);
    
    r_runStats runStats;
    if (bool(rs)) {
        parseRunStats(replayFile, &runStats);
        if (pStatsOpt)
            runStats.print();
    }
    
    uint frames;
    fread(&frames, 4, 1, replayFile);
    r_frame frame;
    for (uint i = 1; i <= frames; ++i) {
        parseFrame(replayFile, &frame);
        if (pFramesOpt)
            frame.print(i);
    }
    
    fclose(replayFile);
    
    return 0;
}