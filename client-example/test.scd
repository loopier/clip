// Connect to the server
m = NetAddr("localhost", 12345);
//

// Create a clip with camera input
m.sendMsg("/loopier/clip/clip/new", "cam1", "HD Pro Webcam C920");
m.sendMsg("/loopier/clip/clip/new", "cam1", "HD Webcam C525 #2");
(m.sendMsg("/loopier/clip/cv/setinput", "cam1");
m.sendMsg("/loopier/clip/clip/background", "cam1");
m.sendMsg("/loopier/clip/clip/mask", "cam1", "cv");)
m.sendMsg("/loopier/clip/cv/maxArea", 50);
m.sendMsg("/loopier/clip/cv/maxblobs", 1);
m.sendMsg("/loopier/clip/cv/threshold", 220);
m.sendMsg("/loopier/clip/clip/new", "anim");)


m.sendMsg("/loopier/clip/clip/new", "anim")
m.sendMsg("/loopier/clip/clip/addframe", "anim", "cam1")
m.sendMsg("/loopier/clip/clip/replaceblob", "anim")
m.sendMsg("/loopier/clip/clip/clearframes", "anim")
m.sendMsg("/loopier/clip/cv/maxArea", 100);
m.sendMsg("/loopier/clip/clip/show", "cam1");

// quit the application from the client
m.sendMsg("/loopier/clip/app/quit")