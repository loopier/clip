// Connect to the server -- clip application
m = NetAddr("localhost", 12345);

// Create a clip with camera input
m.sendMsg("/loopier/clip/clip/new", "cam1", "C525");
// Set it as background to keep it in the back
m.sendMsg("/loopier/clip/clip/background", "cam1");
// Set the camera clip as input for Cv
m.sendMsg("/loopier/clip/cv/setinput", "cam1");
// Hide camera to see just the blob
m.sendMsg("/loopier/clip/clip/hide", "cam1");
// Create a clip named 'anim' to record a new stop-motion animation
m.sendMsg("/loopier/clip/clip/new", "anim");
// Start adding frames by repeatedly sending this command
//    It's the camera image masked with Cv blobs
//    You need to specify the input -- 'cam1' in this case
m.sendMsg("/loopier/clip/clip/addframe", "anim", "cam1")

// ---- Other commands for editing the animation ----
// Insert a frame at the current frame position
m.sendMsg("/loopier/clip/clip/insertframe", "anim", "cam1");
// Remove the current frame
m.sendMsg("/loopier/clip/clip/removeframe", "anim");
// Remove all frames -- start over
m.sendMsg("/loopier/clip/clip/clearframes");
// Save frames to disk
//    Will save them in a directory named after the
//    clip.  In this case it will be saved in app/path/frames/anim
m.sendMsg("/loopier/clip/clip/saveframes", );
