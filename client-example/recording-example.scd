// Connect to the server
m = NetAddr("localhost", 12345);
// create something
m.sendMsg("/loopier/clip/clip/new", "mama", "mammaframes");
// choose where to save your movies
m.sendMsg("/loopier/clip/rec/path", "/Users/roger/Desktop/");
// choose the format -- default is .mov mpeg4
// change format to GIF
(m.sendMsg("/loopier/clip/rec/codec", "gif");
m.sendMsg("/loopier/clip/rec/ext", ".gif");)
// start /pause/resume recording
m.sendMsg("/loopier/clip/rec/record", "me");
// to finish you need to stop recording
m.sendMsg("/loopier/clip/rec/stop");

// quit app
m.sendMsg("/loopier/clip/app/quit");