// Connect to the server
m = NetAddr("localhost", 12345);
//

(
// create two clips
m.sendMsg("/loopier/clip/clip/new", "mamma", "mammaframes");
m.sendMsg("/loopier/clip/clip/new", "exampleclip");
)
// select and modify them
m.sendMsg("/loopier/clip/clip/select", "exampleclip");
m.sendMsg("/loopier/clip/clip/select", "mamma");
m.sendMsg("/loopier/clip/clip/moveto", "mamma", 0.3, 0.5);
m.sendMsg("/loopier/clip/clip/scale", "mamma", 0.5);