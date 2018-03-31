// Connect to the server
m = NetAddr("localhost", 12345);
//

// Create a clip with camera input
m.sendMsg("/loopier/clip/clip/new", "cam1", "HD Webcam C525 #2");
(
f = {
	m.sendMsg("/loopier/clip/clip/new", "cam1", "HD Pro Webcam C920");
	m.sendMsg("/loopier/clip/clip/new", "anim");
};
g = {
	m.sendMsg("/loopier/clip/cv/setinput", "cam1");
	m.sendMsg("/loopier/clip/clip/background", "cam1");
	// m.sendMsg("/loopier/clip/clip/mask", "cam1", "cv");
	m.sendMsg("/loopier/clip/clip/alpha", "cam1", 0.5);
	m.sendMsg("/loopier/clip/clip/color", "cv", 1, 0, 0);
	m.sendMsg("/loopier/clip/cv/maxblobs", 1);
}
)

f.value;
g.value;
m.sendMsg("/loopier/clip/clip/addframe", "anim", "cam1")
m.sendMsg("/loopier/clip/clip/scale", "anim", 0.5)
m.sendMsg("/loopier/clip/clip/save", "anim")
m.sendMsg("/loopier/clip/clip/moveto", "anim", 0.25, 0.5)
m.sendMsg("/loopier/clip/clip/scale", "anim", 0.5)


m.sendMsg("/loopier/clip/clip/new", "cam2", "HD Pro Webcam C920");

m.sendMsg("/loopier/clip/clip/new", "anim", "exampleclip")
m.sendMsg("/loopier/clip/clip/new", "anim", "mammaframes")
m.sendMsg("/loopier/clip/clip/new", "oneclip")
m.sendMsg("/loopier/clip/clip/moveto", "oneclip", 0.1)
m.sendMsg("/loopier/clip/clip/parent", "anim", "oneclip")
m.sendMsg("/loopier/clip/clip/new", "exampleclip")
m.sendMsg("/loopier/clip/clip/scale", "anim", 0.5)
m.sendMsg("/loopier/clip/clip/scale", "cam2", 0.5)
m.sendMsg("/loopier/clip/clip/save", "exampleclip")
m.sendMsg("/loopier/clip/clip/hide", "cv")
