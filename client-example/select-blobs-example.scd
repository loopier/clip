// Connect to the server
m = NetAddr("localhost", 12345);
//

// Create a clip with camera input
(
~clips = {
	m.sendMsg("/loopier/clip/clip/new", "cam", "HD Pro Webcam C920");
	// m.sendMsg("/loopier/clip/clip/new", "cam", "Built-in iSight");
	m.sendMsg("/loopier/clip/clip/new", "aclip", "exampleclip");
m.sendMsg("/loopier/clip/clip/select", "aclip");
	// m.sendMsg("/loopier/clip/clip/speed", "aclip", 0.1);
};
~cv = {
m.sendMsg("/loopier/clip/cv/setinput", "cam");
m.sendMsg("/loopier/clip/clip/background", "cam");
m.sendMsg("/loopier/clip/clip/alpha", "cam", 0.5);
m.sendMsg("/loopier/clip/clip/color", "cv", 1, 0, 0);
m.sendMsg("/loopier/clip/cv/maxblobs", 1);
}
)

~clips.value
~cv.value
m.sendMsg("/loopier/clip/clip/new", "aclip");
m.sendMsg("/loopier/clip/clip/remove", "aclip");