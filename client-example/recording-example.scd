// Connect to the server
m = NetAddr("localhost", 12345);
// create something
m.sendMsg("/loopier/clip/clip/new", "clip", "exampleclip");
// choose where to save your movies
m.sendMsg("/loopier/clip/rec/path",Platform.userHomeDir++"/Desktop/" );
// choose the format -- default is .mov mpeg4
// change format to GIF
(m.sendMsg("/loopier/clip/rec/codec", "gif");
m.sendMsg("/loopier/clip/rec/ext", ".gif");)
// in case you want the origiinal format
(m.sendMsg("/loopier/clip/rec/codec", "mpeg4");
m.sendMsg("/loopier/clip/rec/ext", ".mov");)
// reduce bitrate -- default is 800k
m.sendMsg("/loopier/clip/rec/bitrate", "400k");
// try with a hight bitrate
m.sendMsg("/loopier/clip/rec/bitrate", "8000k");
// start /pause/resume recording
m.sendMsg("/loopier/clip/rec/record", "me");
// to finish you need to stop recording
m.sendMsg("/loopier/clip/rec/stop");

// quit app
m.sendMsg("/loopier/clip/app/quit");

Platform.userHomeDir++"/Desktop/"