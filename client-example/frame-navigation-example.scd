// Connect to the server
m = NetAddr("localhost", 12345);

m.sendMsg("/loopier/clip/clip/new", "exampleclip");
m.sendMsg("/loopier/clip/clip/pause", "exampleclip");
m.sendMsg("/loopier/clip/clip/firstframe", "exampleclip");
m.sendMsg("/loopier/clip/clip/nextframe", "exampleclip");
m.sendMsg("/loopier/clip/clip/previousframe", "exampleclip");
m.sendMsg("/loopier/clip/clip/lastframe", "exampleclip");