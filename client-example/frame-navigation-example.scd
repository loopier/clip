// Connect to the server
m = NetAddr("localhost", 12345);
// create a frame clip and pause it
(m.sendMsg("/loopier/clip/clip/new", "exampleclip");
m.sendMsg("/loopier/clip/clip/pause", "exampleclip");)
// advance one frame
m.sendMsg("/loopier/clip/clip/nextframe", "exampleclip");
// go one frame backwards
m.sendMsg("/loopier/clip/clip/previousframe", "exampleclip");
// go back to first frame
m.sendMsg("/loopier/clip/clip/firstframe", "exampleclip");
// go to the last frame
m.sendMsg("/loopier/clip/clip/lastframe", "exampleclip");
// go to a specific frame
m.sendMsg("/loopier/clip/clip/gotoframe", "exampleclip", 9);
// if the number  passed to the app is larger than the number of frames in
// the clip, it will calculate what you meant (modulo of 'frames' % 'framecount')
m.sendMsg("/loopier/clip/clip/gotoframe", "exampleclip", 19);