// Connect to the server
m = NetAddr("localhost", 12345);
//

// Setup Camera
(
m.sendMsg("/loopier/clip/clip/new", "cam", "HD Pro Webcam C920");
)
( // setup CV
m.sendMsg("/loopier/clip/cv/setinput", "cam");
m.sendMsg("/loopier/clip/clip/background", "cam");
m.sendMsg("/loopier/clip/clip/color", "cv", 1, 0, 0);
m.sendMsg("/loopier/clip/cv/maxblobs", 10);
)
// navigate through blobs
m.sendMsg("/loopier/clip/cv/next");
m.sendMsg("/loopier/clip/cv/previous");
// add the current blob to the selection
m.sendMsg("/loopier/clip/cv/select");
// add some more blobs to the seleciton
// ... then go back to a selected blob and deselect it
m.sendMsg("/loopier/clip/cv/deselect");
// go directly to largest blob
m.sendMsg("/loopier/clip/cv/first");
// go directly to smallest blob
m.sendMsg("/loopier/clip/cv/last");