m = NetAddr("localhost", 12345);
// list all available clips
m.sendMsg("/loopier/clip/clips/listnames")
// list layers
m.sendMsg("/loopier/clip/clip/layers");
// create three clips
m.sendMsg("/loopier/clip/clip/new", "clipone", "exampleclip");
m.sendMsg("/loopier/clip/clip/new", "cliptwo", "exampleclip");
m.sendMsg("/loopier/clip/clip/moveto", "cliptwo", 0.40, 0.5);
m.sendMsg("/loopier/clip/clip/new", "clipthree", "exampleclip");
m.sendMsg("/loopier/clip/clip/moveto", "clipthree", 0.60, 0.5);
// move between public and private outputs
m.sendMsg("/loopier/clip/clip/private", "clipone");
m.sendMsg("/loopier/clip/clip/public", "clipone");
// send clipone all the way to the back
m.sendMsg("/loopier/clip/clip/back", "clipone");
// bring it one layer forward
m.sendMsg("/loopier/clip/clip/forward", "clipone");
// bring it to the front
m.sendMsg("/loopier/clip/clip/front", "clipone");
// send it on layer backward
m.sendMsg("/loopier/clip/clip/backward", "clipone");
// set it as background -- layers sent to the back will still be over this one
m.sendMsg("/loopier/clip/clip/background", "clipone");
// even if you send another layer to the back, it will be over the background
m.sendMsg("/loopier/clip/clip/back", "cliptwo");

// quit app
m.sendMsg("/loopier/clip/app/quit");
