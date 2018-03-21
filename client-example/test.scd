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
m.sendMsg("/loopier/clip/clip/new", "manwalk", "exampleclip");
m.sendMsg("/loopier/clip/clip/color", "manwalk", 1,0,0);
m.sendMsg("/loopier/clip/clip/parent", "manwalk", "exampleclip");
m.sendMsg("/loopier/clip/clip/scale", "manwalk", 0.5);
m.sendMsg("/loopier/clip/clip/moveto", "manwalk", 0.75,0.5);
m.sendMsg("/loopier/clip/clip/parent", "manwalk", "exampleclip");
m.sendMsg("/loopier/clip/clip/moveto", "exampleclip", 0.5,0.2);
m.sendMsg("/loopier/clip/clip/removeparent", "manwalk");
m.sendMsg("/loopier/clip/cv/setinput", "exampleclip");


m.sendMsg("/loopier/clip/clip/new", "cam1", "HD Webcam C525");
m.sendMsg("/loopier/clip/clip/scale", "cam1", 0.5);
m.sendMsg("/loopier/clip/clip/moveto", "cam1", 0.8, 0.2);
m.sendMsg("/loopier/clip/clip/new", "cam2", "HD Webcam C525 #2");
m.sendMsg("/loopier/clip/clip/scale", "cam2", 0.5);
m.sendMsg("/loopier/clip/clip/moveto", "cam2", 0.2, 0.2);
m.sendMsg("/loopier/clip/clip/new", "cam3", "Built-in iSight");
m.sendMsg("/loopier/clip/clip/background", "cam1");

m.sendMsg("/loopier/clip/cv/setinput", "cam2");
m.sendMsg("/loopier/clip/clip/mask", "cam1", "cv");
m.sendMsg("/loopier/clip/clip/maskoff", "cam1", "cv");
m.sendMsg("/loopier/clip/clip/hide", "cam1");
m.sendMsg("/loopier/clip/clip/show", "cam1");
m.sendMsg("/loopier/clip/cv/maxblobs", 1);
m.sendMsg("/loopier/clip/cv/maxblobs", 5);

m.sendMsg("/loopier/clip/clip/scale", "cv", 0.5);
m.sendMsg("/loopier/clip/clip/moveto", "cv", 0.28, 0.14);


// Create a clip with camera input
m.sendMsg("/loopier/clip/clip/new", "newemptyclip");

// Create a clip with camera input
m.sendMsg("/loopier/clip/clip/new", "cam1", "Built-in iSight");
m.sendMsg("/loopier/clip/clip/new", "cam1", "HD Webcam C525");
m.sendMsg("/loopier/clip/clip/new", "cam1", "Logitech Camera #3");
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
