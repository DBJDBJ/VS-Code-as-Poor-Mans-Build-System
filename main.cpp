/*\
 * test-dir.c
 *
 * Copyright (c) 2014 - Geoff R. McLane
 * Licence: GNU GPL version 2
 *
\*/

#include "common.h"
#include <string>
#include <vector>

typedef std::vector<std::string> vSTG;

// utils

// TODO: not yet used to present nice numbers
// void nice_num( char * dst, char * src ) // get nice number, with commas
// {
//    size_t i;
//    size_t len = strlen(src);
//    size_t rem = len % 3;
//    size_t cnt = 0;
//    for( i = 0; i < len; i++ )
//    {
//       if( rem ) {
//          *dst++ = src[i];
//          rem--;
//          if( ( rem == 0 ) && ( (i + 1) < len ) )
//             *dst++ = ',';
//       } else {
//          *dst++ = src[i];
//          cnt++;
//          if( ( cnt == 3 ) && ( (i + 1) < len ) ) {
//             *dst++ = ',';
//             cnt = 0;
//          }
//       }
//    }
//    *dst = 0;
// }


void fix_directory( std::string &dir )
{
    size_t pos = dir.rfind(PATH_SEP);
    if (pos != dir.size())
        dir += PATH_SEP;
}

int enumerate_dir(const char *dir, int dep)
{
    int count = 0;
    DIR *dp = opendir(dir);
    
    if (!dp) {
        printf("%s: Failed to opendir(%s)\n", module, dir);
        return 1;
    }

    std::string s(dir);
    std::string ff;
    struct dirent *pe;
    int typ;
    vSTG vDirs;
    fix_directory(s);

    uint64_t files = 0;
    uint64_t dirs  = 0;
    uint64_t bytes = 0;

    while ((pe = readdir(dp)) != 0) {
        if (strcmp(pe->d_name,".") == 0)
            continue;
        if (strcmp(pe->d_name,"..") == 0)
            continue;

        ff = s;
        ff += pe->d_name;
        typ = dep;
        while(typ--) {
            // printf(" ");
        }

        typ = is_file_or_directory32( ff.c_str() );
        if ((typ == DT_DIR)||(typ == DT_FILE)) {
            if (count == 0) {
                printf("\n");
                printf("  Directory of %s\n", dir);
            }
            count++;
            output_stat();
            printf("%s\n", pe->d_name);
            if (typ == DT_DIR) {
                if (recursive) {
                    vDirs.push_back(ff);
                }
                dirs++;
                total_dirs++;
            } else {
                files++;
                bytes += get_last_file_size();
                total_files++;
                total_bytes += get_last_file_size();
            }
        } 
    }
    closedir(dp);
    // show stats for this directory
    printf("      %14I64u  files, %14I64u bytes\n", files, bytes);
    printf("      %14I64u  dirs\n", dirs);

    size_t ii,max = vDirs.size();
    for (ii = 0; ii < max; ii++) {
        ff = vDirs[ii];
        typ = enumerate_dir( ff.c_str(), (dep+1) );
        if (typ)
            return typ;
    }

    if ((dep == 0) && recursive) {
        printf("\n");
        printf("     Total Files Listed:\n");
        printf("      %14I64u  files, %14I64u bytes\n", total_files, total_bytes);
        printf("      %14I64u  dirs ", total_dirs);
        if (dir[1] == ':') {
            char rp[3];
            DWORD SectorsPerCluster, BytesPerSector, NumberOfFreeClusters, TotalNumberOfClusters;
            rp[0] = dir[0];
            rp[1] = ':';
            rp[2] = 0;
            if (GetDiskFreeSpace( rp, &SectorsPerCluster, &BytesPerSector, &NumberOfFreeClusters, &TotalNumberOfClusters )) {
                uint64_t tfree = SectorsPerCluster * BytesPerSector * NumberOfFreeClusters;
                printf(", %14I64u free bytes\n", tfree);
            }
        }
        printf("\n");
    }

    return 0;

}

// main() OS entry
int main( int argc, char **argv )
{
    int iret = 0;
    iret = parse_args(argc,argv);
    if (iret)
        return iret;
    iret = enumerate_dir(usr_input,0);

    system("@echo.");
    system("@echo.");
    system("@pause");

    return iret;
}

// eof = test-dir.c
