#include "simpleopt.h"
#include "error.h"
#include "data.h"
#include <stdio.h>
#include <string.h>
#include "assert.h"

#define REPLAY_MAGIC_LE 0x524D4F4D
#define REPLAY_MAGIC_BE 0x4D4F4D52

enum { OPT_HELP, OPT_FLAG, OPT_ARG };

CSimpleOpt::SOption g_Options[] =
{
    {OPT_FLAG, "-f", SO_NONE},
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

bool parseHeader(FILE* file, r_header* header)
{
    char buf[sizeof(r_header)];
    fread(buf, 1, sizeof(r_header), file);
    
    int magic = REPLAY_MAGIC_BE;
    if (!strncmp(buf, (const char*)&magic, 4))
        soft("Invalid REPLAY_MAGIC");
    
    printf("Replay version: %d\n", buf[4]);
    
    // Read map name
    uint i = 5;
    uint16 size = buf[i];
    i += sizeof(uint16);
    memcpy(header->m_szMapName, &buf[i], size);
    header->m_szMapName[size] = '\0';
    i += size;
    
    //Read player name
    size = buf[i];
    i += sizeof(uint16);
    memcpy(header->m_szPlayerName, &buf[i], size);
    header->m_szPlayerName[size] = '\0';
    
    i += size;
    memcpy(&header->m_ulSteamID, &buf[i], sizeof(uint64) + sizeof(float) + sizeof(float) + sizeof(uint32) + sizeof(time_t) + sizeof(int));
    
    return 1;
}

int main(int argc, char* argv[])
{
    CSimpleOpt args(argc, argv, g_Options);
    
    while (args.Next()) {
        if (args.LastError() == SO_SUCCESS) {
            if (args.OptionId() == OPT_FLAG) {
                if (args.OptionText() == "-f")
                    printf("f!!!\n");
            }
        }
        else {
            fatal("Invalid argument: %s\n", args.OptionText());
        }
    }
    
    if (args.FileCount() == 0) {
        fatal("No replay file provided\n");
        return 1;
    }
    
    if (args.FileCount() > 1)
        soft("Multiple files recieved; accepting only the first one");
        
    FILE* replayFile = fopen(args.Files()[0], "r");
    r_header header;
    if (parseHeader(replayFile, &header))
        header.print();
    else
        soft("Unknown error parsing header"); //Not possible... yet
    
    fclose(replayFile);
    
    return 0;
}