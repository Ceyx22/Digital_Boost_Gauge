/*
 * Author: Fernando Matias 
 * Proptery of Trelik Motor sports
 */
#include <Arduino_GFX_Library.h>

/* More dev device declaration: https://github.com/moononournation/Arduino_GFX/wiki/Dev-Device-Declaration */
#if defined(DISPLAY_DEV_KIT)
Arduino_GFX *gfx = create_default_Arduino_GFX();
#else /* !defined(DISPLAY_DEV_KIT) */

/* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, 18 /* SCK */, 23/*MOSI*/, -1/*MISO*/, VSPI /*SPI_NUM*/);

/* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
Arduino_GC9A01 *gfx = new Arduino_GC9A01(bus, TFT_RST, 0/*rotation*/, true /*IPS*/);

#endif /* !defined(DISPLAY_DEV_KIT) */

#define BACKGROUND BLACK
#define MARK_COLOR WHITE
#define SUBMARK_COLOR WHITE // was DARKGREY     //LIGHTGREY
#define HOUR_COLOR WHITE
#define MINUTE_COLOR BLUE // LIGHTGREY
#define SECOND_COLOR RED

#define SIXTIETH 0.016666667
#define TWELFTH 0.08333333
#define SIXTIETH_RADIAN 0.10471976
#define TWELFTH_RADIAN 0.52359878
#define RIGHT_ANGLE_RADIAN 1.5707963

#define DEGREE_OF_ROTATION 19.65
#define ARTIFICAIL_THICKNESS 1

static uint8_t conv2d(const char *p)
{
    uint8_t v = 0;
    return (10 * (*p - '0')) + (*++p - '0');
}

static int16_t w, h, center;
static int16_t hHandLen, mHandLen, sHandLen, markLen;
static float sdeg, mdeg, hdeg;
static int16_t osx = 0, osy = 0, omx = 0, omy = 0, ohx = 0, ohy = 0; // Saved H, M, S x & y coords
static int16_t nsx, nsy, nmx, nmy, nhx, nhy;                         // H, M, S x & y coords
static int16_t xMin, yMin, xMax, yMax;                               // redraw range
static int16_t hh, mm, ss;
static unsigned long targetTime; // next action time

static int16_t *cached_points;
static uint16_t cached_points_idx = 0;
static int16_t *last_cached_point;

void setup() {
  // put your setup code here, to run once:
 gfx->begin();
    gfx->fillScreen(BACKGROUND);

#ifdef TFT_BL
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
#endif

    // init LCD constant
    w = gfx->width();
    h = gfx->height();
    if (w < h)
    {
        center = w/2;
    }
    else
    {
        center = h / 2;
    }

    //controlls length of lines
//    hHandLen = center * 3 / 8;
//    mHandLen = center * 2 / 3;
    sHandLen = center * 5 / 6;
    markLen = sHandLen / 3;
    cached_points = (int16_t *)malloc((hHandLen + 1 + mHandLen + 1 + sHandLen + 1) * 2 * 2);

        // Draw 60 clock marks
    draw_round_clock_mark(
    // draw_square_clock_mark(
        center - markLen, center,
        center - (markLen * 2 / 3), center,
        center - (markLen / 2), center);

    hh = conv2d(__TIME__);
    mm = conv2d(__TIME__ + 3);
    ss = conv2d(__TIME__ + 6);

    targetTime = ((millis() / 1000) + 1) * 1000;
}

void loop() {
  // put your main code here, to run repeatedly:

}

void draw_round_clock_mark(int16_t innerR1, int16_t outerR1, int16_t innerR2, int16_t outerR2, int16_t innerR3, int16_t outerR3)
{
  float x, y;
  int16_t x0, x1, y0, y1, innerR, outerR;
  int16_t x0p2, x1p2, y0p2, y1p2;
  uint16_t c;

  for (uint8_t i = 0; i < 46; i++)
  {
    //This if statement controlls the longer white lines
    if ((i % 5) == 0)
    {
      innerR = innerR1;
      outerR = outerR1;
      c = MARK_COLOR;
    }
//    else if ((i % 20) == 0)
//    {
//      innerR = innerR2;
//      outerR = outerR2;
//      c = MARK_COLOR;
//    }
    //Controlls the smaller lines on gauge
    else
    {
      innerR = innerR3;
      outerR = outerR3;
      c = SUBMARK_COLOR;
    }

    //controllers the degree of rotyations if the gauge
   
    mdeg = (SIXTIETH_RADIAN * i) - RIGHT_ANGLE_RADIAN + DEGREE_OF_ROTATION; // 19.65 looks good // 15 is offset so that it is side ways
    x = cos(mdeg);
    y = sin(mdeg);
    //controllers how centered this is on the screen
    x0 = x * outerR + center;
    y0 = y * outerR + center;
    x1 = x * innerR + center;
    y1 = y * innerR + center;

    x0p2 = x0 + ARTIFICAIL_THICKNESS;
    y0p2 = y0 + ARTIFICAIL_THICKNESS;
    x1p2 = x1 ;
    y1p2 = y1 ;

    gfx->drawLine(x0, y0, x1, y1, c);
    //gfx->drawLine(x0p2, y0p2, x1p2, y1p2, c);
    
  }
}
