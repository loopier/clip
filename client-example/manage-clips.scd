// Connect to the server
m = NetAddr("localhost", 12345);
// Create a clip.  Should appear in public screen
m.sendMsg("/loopier/clip/clip/new", "mama", "mammaframes");
// Move it to private screen
m.sendMsg("/loopier/clip/clip/private", "mama");
// Move it back to public screen
m.sendMsg("/loopier/clip/clip/public", "mama");
// Get rid of the clip
m.sendMsg("/loopier/clip/clip/remove", "mama");