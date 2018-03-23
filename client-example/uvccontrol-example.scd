// Connect to the server
m = NetAddr("localhost", 12345);
// ---------------------------------------------------------------------
// UVC
// ---------------------------------------------------------------------
m.sendMsg("/loopier/clip/clip/new", "cam1", "HD Pro Webcam C920");
m.sendMsg("/loopier/clip/clip/new", "cam1", "HD Webcam C525 #2");
m.sendMsg("/loopier/uvc/autoexposure", 1);
m.sendMsg("/loopier/uvc/autoexposure", 0);
m.sendMsg("/loopier/uvc/exposure", 0.1);
m.sendMsg("/loopier/uvc/autofocus", 0);
m.sendMsg("/loopier/uvc/autofocus", 1);
m.sendMsg("/loopier/uvc/focus", 0.1);
m.sendMsg("/loopier/uvc/autowhitebalance", 0);
m.sendMsg("/loopier/uvc/autowhitebalance", 1);
m.sendMsg("/loopier/uvc/whitebalance", 0.19);
m.sendMsg("/loopier/uvc/brightness", 0.9);
m.sendMsg("/loopier/uvc/contrast", 0.9);
m.sendMsg("/loopier/uvc/saturation", 0.9);
m.sendMsg("/loopier/uvc/sharpness", 0.9);

m.sendMsg("/loopier/clip/app/quit");