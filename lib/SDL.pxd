# Based on http://mdqinc.com/blog/2011/10/python-cython-wrapper-for-sdl-1-3/
# Not copyrightable, I think.
cdef extern from "SDL.h":
    ctypedef unsigned char Uint8
    ctypedef unsigned long Uint32
    ctypedef unsigned long long Uint64
    ctypedef signed long long Sint64
    ctypedef signed short Sint16
    ctypedef unsigned short Uint16

    ctypedef enum:
        SDL_PIXELFORMAT_ARGB8888
        SDL_INIT_VIDEO

    ctypedef enum SDLMod:
        pass

    ctypedef enum SDLKey:
        SDLK_DOWN
        SDLK_UP
        SDLK_LEFT
        SDLK_RIGHT
        SDLK_SPACE
        SDLK_ESCAPE
        SDLK_BACKSPACE
        SDLK_AC_BACK
        SDLK_F1
        SDLK_a
        SDLK_b
        SDLK_c
        SDLK_d
        SDLK_e
        SDLK_f
        SDLK_g
        SDLK_h
        SDLK_i
        SDLK_j
        SDLK_k
        SDLK_l
        SDLK_m
        SDLK_o
        SDLK_p
        SDLK_q
        SDLK_r
        SDLK_s
        SDLK_t
        SDLK_u
        SDLK_v
        SDLK_w
        SDLK_x
        SDLK_y
        SDLK_z

    ctypedef enum SDL_BlendMode:
        SDL_BLENDMODE_NONE = 0x00000000
        SDL_BLENDMODE_BLEND = 0x00000001
        SDL_BLENDMODE_ADD = 0x00000002
        SDL_BLENDMODE_MOD = 0x00000004

    ctypedef enum SDL_TextureAccess:
        SDL_TEXTUREACCESS_STATIC
        SDL_TEXTUREACCESS_STREAMING
        SDL_TEXTUREACCESS_TARGET

    ctypedef enum SDL_RendererFlags:
        SDL_RENDERER_SOFTWARE = 0x00000001
        SDL_RENDERER_ACCELERATED = 0x00000002
        SDL_RENDERER_PRESENTVSYNC = 0x00000004

    ctypedef enum SDL_bool:
        SDL_FALSE = 0
        SDL_TRUE = 1

    cdef struct SDL_Rect:
        int x, y
        int w, h

    ctypedef struct SDL_Point:
        int x, y

    cdef struct SDL_Color:
        Uint8 r
        Uint8 g
        Uint8 b
        Uint8 unused

    cdef struct SDL_Palette:
        int ncolors
        SDL_Color *colors
        Uint32 version
        int refcount

    cdef struct SDL_PixelFormat:
        Uint32 format
        SDL_Palette *palette
        Uint8 BitsPerPixel
        Uint8 BytesPerPixel
        Uint8 padding[2]
        Uint32 Rmask
        Uint32 Gmask
        Uint32 Bmask
        Uint32 Amask
        Uint8 Rloss
        Uint8 Gloss
        Uint8 Bloss
        Uint8 Aloss
        Uint8 Rshift
        Uint8 Gshift
        Uint8 Bshift
        Uint8 Ashift
        int refcount
        SDL_PixelFormat *next

    cdef struct SDL_BlitMap

    cdef struct SDL_Surface:
        Uint32 flags
        SDL_PixelFormat *format
        int w, h
        int pitch
        void *pixels
        void *userdata
        int locked
        void *lock_data
        SDL_Rect clip_rect
        SDL_BlitMap *map
        int refcount

    ctypedef enum SDL_EventType:
        SDL_FIRSTEVENT     = 0,
        SDL_QUIT           = 0x100
        SDL_WINDOWEVENT    = 0x200
        SDL_SYSWMEVENT
        SDL_KEYDOWN        = 0x300
        SDL_KEYUP
        SDL_TEXTEDITING
        SDL_TEXTINPUT
        SDL_MOUSEMOTION    = 0x400
        SDL_MOUSEBUTTONDOWN
        SDL_MOUSEBUTTONUP
        SDL_MOUSEWHEEL
        SDL_INPUTMOTION    = 0x500
        SDL_INPUTBUTTONDOWN
        SDL_INPUTBUTTONUP
        SDL_INPUTWHEEL
        SDL_INPUTPROXIMITYIN
        SDL_INPUTPROXIMITYOUT
        SDL_JOYAXISMOTION  = 0x600
        SDL_JOYBALLMOTION
        SDL_JOYHATMOTION
        SDL_JOYBUTTONDOWN
        SDL_JOYBUTTONUP
        SDL_FINGERDOWN      = 0x700
        SDL_FINGERUP
        SDL_FINGERMOTION
        SDL_TOUCHBUTTONDOWN
        SDL_TOUCHBUTTONUP
        SDL_DOLLARGESTURE   = 0x800
        SDL_DOLLARRECORD
        SDL_MULTIGESTURE
        SDL_CLIPBOARDUPDATE = 0x900
        SDL_EVENT_COMPAT1 = 0x7000
        SDL_EVENT_COMPAT2
        SDL_EVENT_COMPAT3
        SDL_USEREVENT    = 0x8000
        SDL_LASTEVENT    = 0xFFFF

    ctypedef enum SDL_WindowEventID:
        SDL_WINDOWEVENT_NONE           #< Never used */
        SDL_WINDOWEVENT_SHOWN          #< Window has been shown */
        SDL_WINDOWEVENT_HIDDEN         #< Window has been hidden */
        SDL_WINDOWEVENT_EXPOSED        #< Window has been exposed and should be
                                        #     redrawn */
        SDL_WINDOWEVENT_MOVED          #< Window has been moved to data1, data2
                                        # */
        SDL_WINDOWEVENT_RESIZED        #< Window has been resized to data1xdata2 */
        SDL_WINDOWEVENT_SIZE_CHANGED   #< The window size has changed, either as a result of an API call or through the system or user changing the window size. */
        SDL_WINDOWEVENT_MINIMIZED      #< Window has been minimized */
        SDL_WINDOWEVENT_MAXIMIZED      #< Window has been maximized */
        SDL_WINDOWEVENT_RESTORED       #< Window has been restored to normal size
                                        # and position */
        SDL_WINDOWEVENT_ENTER          #< Window has gained mouse focus */
        SDL_WINDOWEVENT_LEAVE          #< Window has lost mouse focus */
        SDL_WINDOWEVENT_FOCUS_GAINED   #< Window has gained keyboard focus */
        SDL_WINDOWEVENT_FOCUS_LOST     #< Window has lost keyboard focus */
        SDL_WINDOWEVENT_CLOSE           #< The window manager requests that the
                                        # window be closed */

    ctypedef enum SDL_WindowFlags:
        SDL_WINDOW_FULLSCREEN = 0x00000001
        SDL_WINDOW_OPENGL = 0x00000002
        SDL_WINDOW_SHOWN = 0x00000004
        SDL_WINDOW_HIDDEN = 0x00000008
        SDL_WINDOW_BORDERLESS = 0x00000010
        SDL_WINDOW_RESIZABLE = 0x00000020
        SDL_WINDOW_MINIMIZED = 0x00000040
        SDL_WINDOW_MAXIMIZED = 0x00000080
        SDL_WINDOW_INPUT_GRABBED = 0x00000100
        SDL_WINDOW_INPUT_FOCUS = 0x00000200
        SDL_WINDOW_MOUSE_FOCUS = 0x00000400
        SDL_WINDOW_FOREIGN = 0x00000800

    ctypedef enum SDL_RendererFlip:
        SDL_FLIP_NONE = 0x00000000
        SDL_FLIP_HORIZONTAL = 0x00000001
        SDL_FLIP_VERTICAL = 0x00000002

    cdef struct SDL_MouseMotionEvent:
        Uint32 type
        Uint32 windowID
        Uint8 state
        Uint8 padding1
        Uint8 padding2
        Uint8 padding3
        int x
        int y
        int xrel
        int yrel

    cdef struct SDL_MouseButtonEvent:
        Uint32 type
        Uint32 windowID
        Uint8 button
        Uint8 state
        Uint8 padding1
        Uint8 padding2
        int x
        int y

    cdef struct SDL_WindowEvent:
        Uint32 type
        Uint32 windowID
        Uint8 event
        Uint8 padding1
        Uint8 padding2
        Uint8 padding3
        int data1
        int data2

    ctypedef Sint64 SDL_TouchID
    ctypedef Sint64 SDL_FingerID

    cdef struct SDL_TouchFingerEvent:
        Uint32 type
        Uint32 windowID
        SDL_TouchID touchId
        SDL_FingerID fingerId
        Uint8 state
        Uint8 padding1
        Uint8 padding2
        Uint8 padding3
        Uint16 x
        Uint16 y
        Sint16 dx
        Sint16 dy
        Uint16 pressure

    cdef struct SDL_keysym:
        Uint8 scancode
        SDLKey sym
        SDLMod mod
        Uint16 unicode

    cdef struct SDL_KeyboardEvent:
        Uint8 type
        Uint8 state
        SDL_keysym keysym

    ctypedef enum:
        SDL_TEXTINPUTEVENT_TEXT_SIZE
        SDL_TEXTEDITINGEVENT_TEXT_SIZE

    cdef struct SDL_TextEditingEvent:
        Uint32 type
        Uint32 windowID
        char text[SDL_TEXTEDITINGEVENT_TEXT_SIZE]
        int start
        int length

    cdef struct SDL_TextInputEvent:
        Uint32 type
        Uint32 windowID
        char text[SDL_TEXTINPUTEVENT_TEXT_SIZE]
    cdef struct SDL_MouseWheelEvent:
        Uint32 type
        Uint32 windowID
        int x
        int y

    cdef struct SDL_JoyAxisEvent:
        pass
    cdef struct SDL_JoyBallEvent:
        pass
    cdef struct SDL_JoyHatEvent:
        pass
    cdef struct SDL_JoyButtonEvent:
        pass
    cdef struct SDL_QuitEvent:
        pass
    cdef struct SDL_UserEvent:
        pass
    cdef struct SDL_SysWMEvent:
        pass
    cdef struct SDL_TouchFingerEvent:
        pass
    cdef struct SDL_TouchButtonEvent:
        pass
    cdef struct SDL_MultiGestureEvent:
        pass
    cdef struct SDL_DollarGestureEvent:
        pass

    cdef union SDL_Event:
        Uint32 type
        SDL_WindowEvent window
        SDL_KeyboardEvent key
        SDL_TextEditingEvent edit
        SDL_TextInputEvent text
        SDL_MouseMotionEvent motion
        SDL_MouseButtonEvent button
        SDL_MouseWheelEvent wheel
        SDL_JoyAxisEvent jaxis
        SDL_JoyBallEvent jball
        SDL_JoyHatEvent jhat
        SDL_JoyButtonEvent jbutton
        SDL_QuitEvent quit
        SDL_UserEvent user
        SDL_SysWMEvent syswm
        SDL_TouchFingerEvent tfinger
        SDL_TouchButtonEvent tbutton
        SDL_MultiGestureEvent mgesture
        SDL_DollarGestureEvent dgesture

    cdef struct SDL_RendererInfo:
        char *name
        Uint32 flags
        Uint32 num_texture_formats
        Uint32 texture_formats[16]
        int max_texture_width
        int max_texture_height

    ctypedef struct SDL_Texture
    ctypedef struct SDL_Renderer
    ctypedef struct SDL_Window
    ctypedef struct SDL_DisplayMode:
        Uint32 format
        int w
        int h
        int refresh_rate
        void *driverdata

    cdef struct SDL_RWops:
        long (* seek) (SDL_RWops * context, long offset,int whence)
        size_t(* read) ( SDL_RWops * context, void *ptr, size_t size, size_t maxnum)
        size_t(* write) (SDL_RWops * context, void *ptr,size_t size, size_t num)
        int (* close) (SDL_RWops * context)

    cdef int SDL_SetHint(char* name, char* value)
    cdef SDL_Renderer * SDL_CreateRenderer(SDL_Window * window, int index, Uint32 flags)
    cdef int SDL_SetRenderTarget(SDL_Renderer * renderer, SDL_Texture * texture)
    cdef SDL_Renderer * SDL_CreateSoftwareRenderer(SDL_Surface * surface)
    cdef SDL_Texture * SDL_CreateTexture(SDL_Renderer * renderer, Uint32 format, int access, int w, int h)
    cdef SDL_Texture * SDL_CreateTextureFromSurface(SDL_Renderer * renderer, SDL_Surface * surface)
    cdef SDL_Surface * SDL_CreateRGBSurface(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask)
    cdef int SDL_RenderCopy(SDL_Renderer * renderer, SDL_Texture * texture, SDL_Rect * srcrect, SDL_Rect * dstrect)
    cdef int SDL_RenderCopyEx(SDL_Renderer * renderer, SDL_Texture * texture, SDL_Rect * srcrect, SDL_Rect * dstrect, double angle, SDL_Point *center, SDL_RendererFlip flip)
    cdef void SDL_RenderPresent(SDL_Renderer * renderer)
    cdef int SDL_RenderDrawRect(SDL_Renderer * renderer, SDL_Rect * rect)
    cdef int SDL_RenderFillRect(SDL_Renderer * renderer, SDL_Rect * rect)
    cdef int SDL_FillRect(SDL_Surface * dst,  SDL_Rect* rect, Uint32 color)
    cdef Uint32 SDL_MapRGBA(SDL_PixelFormat* format, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    cdef int SDL_UpdateTexture(SDL_Texture * texture, SDL_Rect* rect, void* pixels, int pitch)
    cdef SDL_bool SDL_RenderTargetSupported(SDL_Renderer *renderer)
    cdef int SDL_SetTargetTexture(SDL_Texture *texture)
    cdef SDL_bool SDL_ResetTargetTexture(SDL_Renderer *renderer)
    cdef void SDL_DestroyTexture(SDL_Texture * texture)
    cdef void SDL_FreeSurface(SDL_Surface * surface)
    cdef int SDL_UpperBlit (SDL_Surface * src, SDL_Rect * srcrect, SDL_Surface * dst, SDL_Rect * dstrect)
    cdef int SDL_LockTexture(SDL_Texture * texture, SDL_Rect * rect, void **pixels, int *pitch)
    cdef void SDL_UnlockTexture(SDL_Texture * texture)
    cdef void SDL_GetWindowSize(SDL_Window * window, int *w, int *h)
    cdef SDL_Window * SDL_CreateWindow(char *title, int x, int y, int w, int h, Uint32 flags)
    cdef int SDL_SetRenderDrawColor(SDL_Renderer * renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    cdef int SDL_SetRenderDrawBlendMode(SDL_Renderer* renderer, SDL_BlendMode blendMode)
    cdef int SDL_RenderClear(SDL_Renderer * renderer)
    cdef int SDL_SetTextureBlendMode(SDL_Texture * texture, SDL_BlendMode blendMode)
    cdef int SDL_GetTextureBlendMode(SDL_Texture * texture, SDL_BlendMode *blendMode)
    cdef SDL_Surface * SDL_CreateRGBSurfaceFrom(void *pixels, int width, int height, int depth, int pitch, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask)
    cdef int SDL_Init(Uint32 flags)
    cdef void SDL_Quit()
    cdef void SDL_StartTextInput()
    cdef void SDL_StopTextInput()
    cdef Uint32 SDL_GetTicks()
    cdef void SDL_Delay(Uint32 ms)
    cdef int SDL_PollEvent(SDL_Event * event)
    cdef SDL_RWops * SDL_RWFromFile(char *file, char *mode)
    cdef int SDL_RWclose(SDL_RWops* context)
    cdef size_t SDL_RWread(SDL_RWops* context, void* ptr, size_t size, size_t maxnum)
    cdef void SDL_FreeRW(SDL_RWops *area)
    cdef int SDL_GetRendererInfo(SDL_Renderer *renderer, SDL_RendererInfo *info)
    cdef int SDL_RenderSetViewport(SDL_Renderer * renderer, SDL_Rect * rect)
    cdef int SDL_GetCurrentDisplayMode(int displayIndex, SDL_DisplayMode * mode)
    cdef int SDL_GetDesktopDisplayMode(int displayIndex, SDL_DisplayMode * mode)
    cdef int SDL_SetTextureColorMod(SDL_Texture * texture, Uint8 r, Uint8 g, Uint8 b)
    cdef int SDL_SetTextureAlphaMod(SDL_Texture * texture, Uint8 alpha)
    cdef char * SDL_GetError()

cdef extern from "SDL_image.h":
    cdef SDL_Surface *IMG_Load(char *file)
    cdef SDL_Surface *IMG_Load_RW(SDL_RWops* src, int freesrc)

cdef extern from "SDL_ttf.h":
    ctypedef struct TTF_Font
    cdef int TTF_Init()
    cdef char *TTF_GetError()
    cdef TTF_Font *  TTF_OpenFont( char *file, int ptsize)
    cdef TTF_Font *  TTF_OpenFontIndex( char *file, int ptsize, long index)
    cdef TTF_Font *  TTF_OpenFontRW(SDL_RWops *src, int freesrc, int ptsize)
    cdef TTF_Font *  TTF_OpenFontIndexRW(SDL_RWops *src, int freesrc, int ptsize, long index)
    #Set and retrieve the font style
    #define TTF_STYLE_NORMAL    0x00
    #define TTF_STYLE_BOLD      0x01
    #define TTF_STYLE_ITALIC    0x02
    #define TTF_STYLE_UNDERLINE 0x04
    #define TTF_STYLE_STRIKETHROUGH 0x08
    cdef int  TTF_GetFontStyle( TTF_Font *font)
    cdef void  TTF_SetFontStyle(TTF_Font *font, int style)
    cdef int  TTF_GetFontOutline( TTF_Font *font)
    cdef void  TTF_SetFontOutline(TTF_Font *font, int outline)

    #Set and retrieve FreeType hinter settings */
    #define TTF_HINTING_NORMAL    0
    #define TTF_HINTING_LIGHT     1
    #define TTF_HINTING_MONO      2
    #define TTF_HINTING_NONE      3
    cdef int  TTF_GetFontHinting( TTF_Font *font)
    cdef void  TTF_SetFontHinting(TTF_Font *font, int hinting)

    #Get the total height of the font - usually equal to point size
    cdef int  TTF_FontHeight( TTF_Font *font)

    ## Get the offset from the baseline to the top of the font
    #This is a positive value, relative to the baseline.
    #*/
    cdef int  TTF_FontAscent( TTF_Font *font)

    ## Get the offset from the baseline to the bottom of the font
    #   This is a negative value, relative to the baseline.
    # */
    cdef int  TTF_FontDescent( TTF_Font *font)

    ## Get the recommended spacing between lines of text for this font */
    cdef int  TTF_FontLineSkip( TTF_Font *font)

    ## Get/Set whether or not kerning is allowed for this font */
    cdef int  TTF_GetFontKerning( TTF_Font *font)
    cdef void  TTF_SetFontKerning(TTF_Font *font, int allowed)

    ## Get the number of faces of the font */
    cdef long  TTF_FontFaces( TTF_Font *font)

    ## Get the font face attributes, if any */
    cdef int  TTF_FontFaceIsFixedWidth( TTF_Font *font)
    cdef char *  TTF_FontFaceFamilyName( TTF_Font *font)
    cdef char *  TTF_FontFaceStyleName( TTF_Font *font)

    ## Check wether a glyph is provided by the font or not */
    cdef int  TTF_GlyphIsProvided( TTF_Font *font, Uint16 ch)

    ## Get the metrics (dimensions) of a glyph
    #   To understand what these metrics mean, here is a useful link:
    #    http://freetype.sourceforge.net/freetype2/docs/tutorial/step2.html
    # */
    cdef int  TTF_GlyphMetrics(TTF_Font *font, Uint16 ch,int *minx, int *maxx, int *miny, int *maxy, int *advance)

    ## Get the dimensions of a rendered string of text */
    cdef int  TTF_SizeText(TTF_Font *font,  char *text, int *w, int *h)
    cdef int  TTF_SizeUTF8(TTF_Font *font,  char *text, int *w, int *h)
    cdef int  TTF_SizeUNICODE(TTF_Font *font,  Uint16 *text, int *w, int *h)

    # Create an 8-bit palettized surface and render the given text at
    #   fast quality with the given font and color.  The 0 pixel is the
    #   colorkey, giving a transparent background, and the 1 pixel is set
    #   to the text color.
    #   This function returns the new surface, or NULL if there was an error.
    #*/
    cdef SDL_Surface *  TTF_RenderText_Solid(TTF_Font *font, char *text, SDL_Color fg)
    cdef SDL_Surface *  TTF_RenderUTF8_Solid(TTF_Font *font, char *text, SDL_Color fg)
    cdef SDL_Surface *  TTF_RenderUNICODE_Solid(TTF_Font *font, Uint16 *text, SDL_Color fg)

    # Create an 8-bit palettized surface and render the given glyph at
    #   fast quality with the given font and color.  The 0 pixel is the
    #   colorkey, giving a transparent background, and the 1 pixel is set
    #   to the text color.  The glyph is rendered without any padding or
    #   centering in the X direction, and aligned normally in the Y direction.
    #   This function returns the new surface, or NULL if there was an error.
    #*/
    cdef SDL_Surface *  TTF_RenderGlyph_Solid(TTF_Font *font, Uint16 ch, SDL_Color fg)

    # Create an 8-bit palettized surface and render the given text at
    #   high quality with the given font and colors.  The 0 pixel is background,
    #   while other pixels have varying degrees of the foreground color.
    #  This function returns the new surface, or NULL if there was an error.
    #*/
    cdef SDL_Surface *  TTF_RenderText_Shaded(TTF_Font *font, char *text, SDL_Color fg, SDL_Color bg)
    cdef SDL_Surface *  TTF_RenderUTF8_Shaded(TTF_Font *font, char *text, SDL_Color fg, SDL_Color bg)
    cdef SDL_Surface *  TTF_RenderUNICODE_Shaded(TTF_Font *font, Uint16 *text, SDL_Color fg, SDL_Color bg)

    # Create an 8-bit palettized surface and render the given glyph at
    #   high quality with the given font and colors.  The 0 pixel is background,
    #   while other pixels have varying degrees of the foreground color.
    #   The glyph is rendered without any padding or centering in the X
    #   direction, and aligned normally in the Y direction.
    #   This function returns the new surface, or NULL if there was an error.
    #
    cdef SDL_Surface *  TTF_RenderGlyph_Shaded(TTF_Font *font,
                    Uint16 ch, SDL_Color fg, SDL_Color bg)

    # Create a 32-bit ARGB surface and render the given text at high quality,
    #   using alpha blending to dither the font with the given color.
    #   This function returns the new surface, or NULL if there was an error.
    #*/
    cdef SDL_Surface *  TTF_RenderText_Blended(TTF_Font *font,
                     char *text, SDL_Color fg)
    cdef SDL_Surface *  TTF_RenderUTF8_Blended(TTF_Font *font,
                     char *text, SDL_Color fg)
    cdef SDL_Surface *  TTF_RenderUNICODE_Blended(TTF_Font *font,
                     Uint16 *text, SDL_Color fg)

    # Create a 32-bit ARGB surface and render the given glyph at high quality,
    #   using alpha blending to dither the font with the given color.
    #   The glyph is rendered without any padding or centering in the X
    #   direction, and aligned normally in the Y direction.
    #   This function returns the new surface, or NULL if there was an error.
    #*/
    cdef SDL_Surface *  TTF_RenderGlyph_Blended(TTF_Font *font,
                            Uint16 ch, SDL_Color fg)

    # For compatibility with previous versions, here are the old functions */
    #define TTF_RenderText(font, text, fg, bg)  \
    #    TTF_RenderText_Shaded(font, text, fg, bg)
    #define TTF_RenderUTF8(font, text, fg, bg)  \
    #    TTF_RenderUTF8_Shaded(font, text, fg, bg)
    #define TTF_RenderUNICODE(font, text, fg, bg)   \
    #    TTF_RenderUNICODE_Shaded(font, text, fg, bg)

    # Close an opened font file */
    cdef void  TTF_CloseFont(TTF_Font *font)

    # De-initialize the TTF engine */
    cdef void  TTF_Quit()

    # Check if the TTF engine is initialized */
    cdef int  TTF_WasInit()

    # Get the kerning size of two glyphs */
    cdef int TTF_GetFontKerningSize(TTF_Font *font, int prev_index, int index)
