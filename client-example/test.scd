// Connect to the server
m = NetAddr("localhost", 12345);
// ---------------------------------------------------------------------
// LIST
// ---------------------------------------------------------------------
// print list of clip  contents to (app's) console
m.sendMsg("/loopier/clip/clips/listresources");
// print list of clips to (app's) console
m.sendMsg("/loopier/clip/clips/listnames");
// clear all clips
m.sendMsg("/loopier/clip/clips/clearall");

// ---------------------------------------------------------------------
// TEST
// ---------------------------------------------------------------------
// Create a clip with camera input
m.sendMsg("/loopier/clip/app/test", "exampleclip");

// Create a clip with camera input
m.sendMsg("/loopier/clip/clip/new", "exampleclip");
// Set the camera clip as input for Cv
m.sendMsg("/loopier/clip/cv/setinput", "exampleclip");


// Create a clip with camera input
m.sendMsg("/loopier/clip/clip/new", "newemptyclip");

// Create a clip with camera input
m.sendMsg("/loopier/clip/clip/new", "cam1", "Built-in iSight");
m.sendMsg("/loopier/clip/clip/new", "cam1", "HD Webcam C525");
// Set the camera clip as input for Cv
m.sendMsg("/loopier/clip/cv/setinput", "cam1");
// Set it as background to keep it in the back
m.sendMsg("/loopier/clip/clip/background", "cam1");
// Hide camera to see just the blob
m.sendMsg("/loopier/clip/clip/hide", "cam1");
// Create a clip named 'anim' to record a new stop-motion animation
m.sendMsg("/loopier/clip/clip/new", "anim");


m.sendMsg("/loopier/clip/clip/moveto", "exampleclip", 0.1, 0.1);
m.sendMsg("/loopier/clip/clip/scale", "exampleclip", 0.5, 0.1);






// quit the application from the client
m.sendMsg("/loopier/clip/app/quit")
