// Connect to the server
m = NetAddr("localhost", 12345);

( // create a camera and a new animation clip with low framerate
m.sendMsg("/loopier/clip/clip/new", "cam", "HD Pro Webcam C920");
m.sendMsg("/loopier/clip/clip/new", "anim");
m.sendMsg("/loopier/clip/clip/select", "anim");
m.sendMsg("/loopier/clip/clip/speed", "anim", 0.1);
)
( // set CV
m.sendMsg("/loopier/clip/cv/setinput", "cam");
m.sendMsg("/loopier/clip/clip/background", "cam");
m.sendMsg("/loopier/clip/clip/alpha", "cam", 0.5);
m.sendMsg("/loopier/clip/clip/color", "cv", 1, 0, 0);
m.sendMsg("/loopier/clip/cv/maxblobs", 1);
)
// add some frames
m.sendMsg("/loopier/clip/clip/addframe", "anim", "cam");
// save them -- check your resources folder, there should be a new 'anim' folder
m.sendMsg("/loopier/clip/clip/saveframes", "anim");