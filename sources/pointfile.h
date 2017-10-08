#ifndef POINTFILE
#define POINTFILE

#define NAME_SIZE (100)

typedef struct pointfile_t
{
    char name[NAME_SIZE];
    float x;
    float y;
}PointFile;

#endif // POINTFILE

