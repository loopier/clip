// Connect to the server
m = NetAddr("localhost", 12345);
//

// Create a clip with camera input
(
m.sendMsg("/loopier/clip/clip/new", "cam", "HD Pro Webcam C920");
m.sendMsg("/loopier/clip/clip/new", "anim");
m.sendMsg("/loopier/clip/clip/select", "anim");
m.sendMsg("/loopier/clip/clip/speed", "anim", 0.1);
)
(
m.sendMsg("/loopier/clip/cv/setinput", "cam");
m.sendMsg("/loopier/clip/clip/background", "cam");
m.sendMsg("/loopier/clip/clip/alpha", "cam", 0.5);
m.sendMsg("/loopier/clip/clip/color", "cv", 1, 0, 0);
m.sendMsg("/loopier/clip/cv/maxblobs", 1);
)

m.sendMsg("/loopier/clip/clip/addframe", "anim", "cam");
m.sendMsg("/loopier/clip/clip/replaceblob", "anim");