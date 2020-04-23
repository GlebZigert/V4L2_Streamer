#include "sdl_class.h"

SDL_class::SDL_class()
{

}

int SDL_class::init_view(struct v4l2_format fmt)
{

        if (SDL_Init(SDL_INIT_VIDEO)) {
            printf("Unable to initialize SDL\n");
            return -1;
        }

        if (SDL_CreateWindowAndRenderer(fmt.fmt.pix.width
                        , fmt.fmt.pix.height
                        , SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
                        , &window
                        , &renderer)) {
            printf("SDL_CreateWindowAndRenderer failed: %s\n", SDL_GetError());
            return -1;
        }

        if (fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_YUYV) {
            texture = SDL_CreateTexture(renderer
                            // YUY2 is also know as YUYV in SDL
                            , SDL_PIXELFORMAT_YUY2
                            , SDL_TEXTUREACCESS_STREAMING
                            , fmt.fmt.pix.width
                            , fmt.fmt.pix.height);
            if (!texture) {
                printf("SDL_CreateTexture failed: %s\n", SDL_GetError());
                return -1;
            }
        } else if (fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_MJPEG) {
            if (!IMG_Init(IMG_INIT_JPG)) {
                printf("Unable to initialize IMG\n");
                return -1;
            }
        }

        printf("Device: %s\nWidth: %d\nHeight: %d\n"
            , "/dev/video0", fmt.fmt.pix.width, fmt.fmt.pix.height);

        return 0;


}

static int sdl_filter(void *userdata, SDL_Event *event)
{
    (void)userdata;
    return event->type == SDL_QUIT;
}

void SDL_class::run_SDL_SetEventFilter()
{
 SDL_SetEventFilter(sdl_filter, NULL);
}

void SDL_class::draw_YUV(void *buffer_start,size_t length,struct v4l2_format fmt)
{
    // YUYV is two bytes per pixel, so multiple line width by 2
    SDL_UpdateTexture(texture, NULL, buffer_start, fmt.fmt.pix.width * 2);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void SDL_class::draw_MJPEG(void *buffer_start,size_t length,struct v4l2_format fmt)
{
    SDL_RWops *buf_stream = SDL_RWFromMem(buffer_start, (int)length);
    SDL_Surface *frame = IMG_Load_RW(buf_stream, 0);
    SDL_Texture *tx = SDL_CreateTextureFromSurface(renderer, frame);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, tx, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(tx);
    SDL_FreeSurface(frame);
    SDL_RWclose(buf_stream);
}
