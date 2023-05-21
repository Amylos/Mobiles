/*
 * app.h
 *
 *  Created on: 20 d�c. 2021
 *      Author: Garnier
 */

#define APP_WINDOW_TITLE			("Mobiles")
#define APP_WINDOW_TITLE_PAUSED		("Mobiles PAUSED")
#define	APP_WINDOW_HEIGHT			(1000)
#define	APP_WINDOW_WIDTH			(900)
#define	APP_WINDOW_COLOR_BKGND		(SDL_Color){20,20,20,255}
#define APP_WINDOW_COLOR_DELIMITING	(SDL_Color){0,250,30,255}
#define	APP_WINDOW_PADDING_TOP		(50)
#define	APP_WINDOW_PADDING_BOT		(20)
#define	APP_WINDOW_PADDING_HRZ		(20)

#define	APP_MOBILE_NB_MAX			(3)
#define	APP_MOBILE_SIZE				(20)

#define	APP_MOBILE_ANIMATE_RATE		(20)
#define APP_MOBILE_SPEED_MAX		(10)

#define APP_MOBILE_LIVE_MIN			(200)
#define APP_MOBILE_LIVE_MAX			(400)

typedef struct s_app t_app;

t_app*AppCreate(void);
t_app*AppDestroy(t_app*pApp);
int AppRun(t_app*pApp);

