#include "dirent.h"


#ifdef _MSC_VER
#define M_IS_DIR _S_IFDIR
#define PATH_SEP "\\"
#else // !_MSC_VER
#define M_IS_DIR S_IFDIR
#define PATH_SEP "/"
#endif

#define DT_NONE 0
#define DT_FILE 1
#define DT_DIR  2

#ifdef __cplusplus
extern "C" {
#endif

static const char *module = "test-dir";
static const char *usr_input = NULL ;
static bool recursive = false;
static bool utc_option = false;

static uint64_t total_files = 0;
static uint64_t total_dirs  = 0;
static uint64_t total_bytes = 0;

static char szFullPath[MAX_PATH];

static struct stat buf;
inline int is_file_or_directory32 ( const char * path )
{
    if (!path)
        return DT_NONE;
    int res = stat(path,&buf);
	if (res == 0) {
		if (buf.st_mode & M_IS_DIR)
			return DT_DIR;
		else
			return DT_FILE;
	} else {
      switch (errno) {
         case ENOENT:
           printf("Path %s not found.\n", path);
           break;
         case EINVAL:
           printf("Invalid parameter to _stat.\n");
           break;
         default:
           /* Should never be reached. */
           printf("Unexpected error in _stat.\n");
      }

    }
	return DT_NONE;
}

inline uint64_t get_last_file_size() { return buf.st_size; }

// 19/10/2014  19:25    <DIR>          Win32
// 19/10/2014  19:34            22,579 ZERO_CHECK.vcxproj
inline void output_stat()
{
   struct tm * ptm;
   ptm = utc_option ? gmtime(&buf.st_mtime) : localtime(&buf.st_mtime);
   printf("%04ld/%02d/%02d %02d:%02d ",
       ptm->tm_year + 1900L, ptm->tm_mon + 1, ptm->tm_mday,
	   ptm->tm_hour, ptm->tm_min );
    if (buf.st_mode & M_IS_DIR) {
        printf("       <DIR> ");
    } else {
        printf( "% 12ld ", buf.st_size );
    }
}

inline void output_stat2()
{
    char timebuf[26];
    errno_t err = ctime_s(timebuf, 26, &buf.st_mtime);
    if (err) {
        printf("Invalid arguments to ctime_s!\n");
        exit(1);
    }
    size_t len = strlen(timebuf);
    while (len) {
        len--;
        if (timebuf[len] > ' ')
            break;
        timebuf[len] = 0;
    }
    printf("%s ",timebuf);
    if (buf.st_mode & M_IS_DIR) {
        printf("       <DIR> ");
    } else {
        printf( "% 12ld ", buf.st_size );
    }
}

__attribute__((noreturn))
inline void give_help( const char *name )
{
    (void)name ;
    printf("%s: usage: [options] usr_input\n", module);
    printf("Options:\n");
    printf(" --help  (-h or -?) = This help and exit(2)\n");
    printf(" --recursive   (-r) = Recursively enumerate the given directory.\n");
    printf(" Given a valid directory input, will enumerate the items found.\n");
    system("@echo.");
    system("@echo.");
    system("@pause");
    // yes, very naughty
    exit(EXIT_SUCCESS);
}

inline int parse_args( int argc, char **argv )
{
    int i,i2,c;
    char *arg, *sarg;
    for (i = 1; i < argc; i++) {
        arg = argv[i];
        i2 = i + 1;
        if (*arg == '-') {
            sarg = &arg[1];
            while (*sarg == '-')
                sarg++;
            c = *sarg;
            switch (c) {
            case 'h':
            case '?':
                give_help(argv[0]);
                return 2;
            case 'r':
                recursive = true;
                break;
            default:
                printf("%s: Unknown argument '%s'. Tyr -? for help...\n", module, arg);
                return 1;
            }
        } else {
            // bear argument
            if (usr_input) {
                printf("%s: Already have input '%s'! What is this '%s'\n", module, usr_input, arg );
                return 1;
            }
            _fullpath (szFullPath, arg, MAX_PATH);
            usr_input = _strdup(szFullPath);

            if (is_file_or_directory32(usr_input) != DT_DIR) {
                printf("%s: Error: Unable to 'stat' '%s'! Aborting...\n", module, usr_input);
                return 1;
            }
        }
    }
    if (!usr_input) {
        printf("%s: No valid arguments found...\n", module);
        give_help(module);
        return 1;
    }
    return 0;
}

#ifdef __cplusplus
} // extern "C" 
#endif
