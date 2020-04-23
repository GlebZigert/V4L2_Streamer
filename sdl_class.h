#ifndef SDL_CLASS_H
#define SDL_CLASS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <QDebug>

class SDL_class
{
public:
    SDL_class();

     int init_view(struct v4l2_format fmt);
     void run_SDL_SetEventFilter();

    void draw_YUV(void *buffer_start,size_t length,struct v4l2_format fmt);
    void draw_MJPEG(void *buffer_start,size_t length,struct v4l2_format fmt);

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
};

#endif // SDL_CLASS_H
