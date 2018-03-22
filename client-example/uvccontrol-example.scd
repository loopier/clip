// Connect to the server
m = NetAddr("localhost", 12345);
// ---------------------------------------------------------------------
// UVC
// ---------------------------------------------------------------------
m.sendMsg("/loopier/clip/clip/new", "cam1", "HD Pro Webcam C920");
m.sendMsg("/loopier/uvc/autoexposure", 0);

m.sendMsg("/loopier/clip/app/quit");