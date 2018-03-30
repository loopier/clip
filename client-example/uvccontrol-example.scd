// Connect to the server
m = NetAddr("localhost", 12345);
// ---------------------------------------------------------------------
// UVC
// ---------------------------------------------------------------------
( // create 2 camera clips
m.sendMsg("/loopier/clip/clip/new", "cam1", "HD Pro Webcam C920");
m.sendMsg("/loopier/clip/clip/new", "cam2", "HD Webcam C525 #4");
// m.sendMsg("/loopier/clip/clip/new", "cam3", "HD Webcam C525");
// arrange them on the screen
m.sendMsg("/loopier/clip/clip/scale", "cam1", 0.5);
m.sendMsg("/loopier/clip/clip/moveto", "cam1", 0.25, 0.25);
m.sendMsg("/loopier/clip/clip/scale", "cam2", 0.5);
m.sendMsg("/loopier/clip/clip/moveto", "cam2", 0.75, 0.25);
)
// choose which one you want to control
m.sendMsg("/loopier/uvc/use", "HD Webcam C525 #4");
m.sendMsg("/loopier/uvc/use", "HD Pro Webcam C920");
// change camera settings
m.sendMsg("/loopier/uvc/autoexposure", 0);
m.sendMsg("/loopier/uvc/exposure", 0.1);
m.sendMsg("/loopier/uvc/exposure", 0.9);
m.sendMsg("/loopier/uvc/autoexposure", 1);
m.sendMsg("/loopier/uvc/autofocus", 0);
m.sendMsg("/loopier/uvc/focus", 0.9);
m.sendMsg("/loopier/uvc/focus", 0.1);
m.sendMsg("/loopier/uvc/autofocus", 1);
m.sendMsg("/loopier/uvc/autowhitebalance", 0);
m.sendMsg("/loopier/uvc/whitebalance", 0.19);
m.sendMsg("/loopier/uvc/autowhitebalance", 1);
m.sendMsg("/loopier/uvc/gain", 0.15);
m.sendMsg("/loopier/uvc/brightness", 0.5);
m.sendMsg("/loopier/uvc/contrast", 0.15);
m.sendMsg("/loopier/uvc/saturation", 0.25);
m.sendMsg("/loopier/uvc/sharpness", 0.1);
// quit app
m.sendMsg("/loopier/clip/app/quit");