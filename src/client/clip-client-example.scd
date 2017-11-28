// Connect to the server
m = NetAddr("localhost", 12345);

// --- JUST FOR TESTING --- REMOVE WHEN DONE ---
m.sendMsg("/loopier/clip/clip/aisfjalsdfij");
m.sendMsg("/loopier/clip/clip/new", "mamaclip", "mamma");
m.sendMsg("/loopier/clip/clip/remove", "mamaclip");
m.sendMsg("/loopier/clip/clip/new", "defaultclip");
m.sendMsg("/loopier/clip/clip/new", "walkclip", "manwalk");
// --- END OF TEST ---


//------------------------------------------------------------------
//   CLIP LIST COMMANDS
//------------------------------------------------------------------

// print list of clip  contents to (app's) console
m.sendMsg("/loopier/clip/clips/listresources");
// print list of clips to (app's) console
m.sendMsg("/loopier/clip/clips/listnames");
// clear all clips
m.sendMsg("/loopier/clip/clips/clearall");
// show names
m.sendMsg("/loopier/clip/clips/togglenames");
m.sendMsg("/loopier/clip/clips/shownames");
m.sendMsg("/loopier/clip/clips/hidenames");

//------------------------------------------------------------------
//  SINGLE CLIP COMMANDS
//------------------------------------------------------------------

// create a clip with the 'default.mov' movie (if movie name is not provided it will pick 'default')
m.sendMsg("/loopier/clip/clip/new", "exampleclip", "mamma");
m.sendMsg("/loopier/clip/clip/new", "exampleclip");
// create a clip with the 'default.mov' movie (if movie name is not provided it will pick 'default')
m.sendMsg("/loopier/clip/clip/remove", "exampleclip");

// PLAYING   ------------------------------------------------------

// play, pause or stop movie
m.sendMsg("/loopier/clip/clip/play", "exampleclip");
m.sendMsg("/loopier/clip/clip/stop", "exampleclip");
m.sendMsg("/loopier/clip/clip/pause", "exampleclip");
// there are 3 kinds of loop
m.sendMsg("/loopier/clip/clip/loop", "exampleclip", "none");
m.sendMsg("/loopier/clip/clip/loop", "exampleclip", "normal");
m.sendMsg("/loopier/clip/clip/loop", "exampleclip", "palindrome");
m.sendMsg("/loopier/clip/clip/loop", "exampleclip", "once");
// change movie speed
m.sendMsg("/loopier/clip/clip/speed", "exampleclip", 2);

// LOOK & FEEL  ------------------------------------------------------

// DIMENSIONS

// move, scale, reset...
m.sendMsg("/loopier/clip/clip/reset", "exampleclip");
m.sendMsg("/loopier/clip/clip/scaleup", "exampleclip", 0.1);
m.sendMsg("/loopier/clip/clip/scaledown", "exampleclip", 0.05);
m.sendMsg("/loopier/clip/clip/scale", "exampleclip", 2.0.rand);
m.sendMsg("/loopier/clip/clip/xscale", "exampleclip", 0.5);
m.sendMsg("/loopier/clip/clip/yscale", "exampleclip", 3);
m.sendMsg("/loopier/clip/clip/resetscale", "exampleclip", );
// vertical flip
m.sendMsg("/loopier/clip/clip/vflip", "exampleclip");
// horizontal flip
m.sendMsg("/loopier/clip/clip/hflip", "exampleclip");
// toggle fullscreen
m.sendMsg("/loopier/clip/clip/fullscreen", "exampleclip");
// toggle visibility
m.sendMsg("/loopier/clip/clip/togglevisibility", "exampleclip");
m.sendMsg("/loopier/clip/clip/show", "exampleclip");
m.sendMsg("/loopier/clip/clip/hide", "exampleclip");
// Dimensions of window are normalized.  So moving is always between 0 and 1
m.sendMsg("/loopier/clip/clip/moveto", "exampleclip", 0.5.rand, 0.5.rand);

// COLOR
// grayscale - 0.0 being black, 1.0 being white - It's a STRING argument!!
m.sendMsg("/loopier/clip/clip/color", "exampleclip", 0.5);
// grayscale with alfa - 0.0 being transparent, 1.0 being opaque
m.sendMsg("/loopier/clip/clip/color", "exampleclip", 1, 15);
// RGB
m.sendMsg("/loopier/clip/clip/color", "exampleclip", 1, 0.5, 1);
// RGBA
m.sendMsg("/loopier/clip/clip/color", "exampleclip", 1, 0.5, 1, 0.5);
// change transparency
m.sendMsg("/loopier/clip/clip/alpha", "exampleclip", 0.5);

// MANAGING MOVIES  ------------------------------------------------
/* DEPRECATED

// list the movies in the clip
m.sendMsg("/loopier/clip/clip", "exampleclip", "listmovies");
// add a movie to the clip
m.sendMsg("/loopier/clip/clip", "exampleclip", "addmovie", "mamma");
// play the new movie
m.sendMsg("/loopier/clip/clip", "exampleclip", "setmovie", 1);
// back to the first movie
m.sendMsg("/loopier/clip/clip", "exampleclip", "setmovie", 0);

// SEQUENCE
// add yet another movie
m.sendMsg("/loopier/clip/clip", "exampleclip", "addmovie", "crashtest");
// and set a sequence
m.sendMsg("/loopier/clip/clip", "exampleclip", "sequence", "0,1,2");
*/

//------------------------------------------------------------------
//  ANOTHER CLIP
//------------------------------------------------------------------

// create a new clip named 'anotherclip'
m.sendMsg("/loopier/clip/clip", "anotherclip", "new", "stress");
// move it somewhere
m.sendMsg("/loopier/clip/clip", "anotherclip", "moveto", 1.0.rand, 1.0.rand);
// change it's transparency
m.sendMsg("/loopier/clip/clip", "stress", "alpha",0.5);
// create another clip with the same name.  App will rename it to 'stress1' and
// warn you about this
(
m.sendMsg("/loopier/clip/clip", "stress", "new");
m.sendMsg("/loopier/clip/clip", "stress1", "moveto", 1.0.rand, 1.0.rand);
)
// eval several times to move it around
m.sendMsg("/loopier/clip/clip", "stress1", "moveto", 1.0.rand, 1.0.rand);

// create a new clip named 'mamma' with alpha channel (transparent background)
// give it a random size and position at creation-time
m.sendMsg("/loopier/clip/clip", "mamma", "new");
(
m.sendMsg("/loopier/clip/clip", "mamma", "moveto", 1.0.rand, 1.0.rand);
m.sendMsg("/loopier/clip/clip", "mamma", "scale", 2.0.rand.postln);
m.sendMsg("/loopier/clip/clip", "mamma", "loop", "palindrome");
)
// fool around with it
(
m.sendMsg("/loopier/clip/clip", "mamma", "moveto", 1.0.rand, 1.0.rand);
m.sendMsg("/loopier/clip/clip", "mamma", "scale", 2.0.rand.postln);
)


//------------------------------------------------------------------
//  CONSOLE COMMANDS
//------------------------------------------------------------------

// print something
m.sendMsg("/loopier/clip/console", "print", "hello world");
// change prompt
m.sendMsg("/loopier/clip/console", "prompt", ">> ");
// set the maximum number of lilnes displayed
m.sendMsg("/loopier/clip/console", "lines", 5);
// show or hide
m.sendMsg("/loopier/clip/console", "toggle");
m.sendMsg("/loopier/clip/console", "show");
m.sendMsg("/loopier/clip/console", "hide");
// changing color with normalized values (1 = 255)
// Grayscale
m.sendMsg("/loopier/clip/console", "color", 0.75);
// Grayscale with alpha
m.sendMsg("/loopier/clip/console", "color", 1, 0.5);
// RGB
m.sendMsg("/loopier/clip/console", "color", 1, 0.5, 0);
// set transparency
m.sendMsg("/loopier/clip/console", "alpha", 0.5);
// RGB with alpha -- seems it's not working
// m.sendMsg("/loopier/clip/console", "color", 1, 1, 0, 0.5);
m.sendMsg("/loopier/clip/console", "moveto", 0.5, 0.9)

m.sendMsg("/loopier/clip/console", "font", "OCRAStd.otf")
m.sendMsg("/loopier/clip/console", "font", "Andale Mono.ttf")
m.sendMsg("/loopier/clip/console", "fontsize", 24)

//------------------------------------------------------------------
//  VIDEO INPUT COMMANDS
//------------------------------------------------------------------
// change blob detection threshold
m.sendMsg("/loopier/clip/videoinput", "threshold", 100)
// change detected blob sizes
m.sendMsg("/loopier/clip/videoinput", "minArea", 10)
m.sendMsg("/loopier/clip/videoinput", "maxArea", 250)
// detect holes inside blobs
m.sendMsg("/loopier/clip/videoinput", "holes", true)
// visibility
m.sendMsg("/loopier/clip/videoinput", "togglevisibility")
m.sendMsg("/loopier/clip/videoinput", "show")
m.sendMsg("/loopier/clip/videoinput", "hide")

//------------------------------------------------------------------
//  APPLICATION COMMANDS
//------------------------------------------------------------------
// toggle fullscreen
m.sendMsg("/loopier/clip/app/fullscreen")
// move the application window
m.sendMsg("/loopier/clip/app/move", 1.0, 0)
// quit the application from the client
m.sendMsg("/loopier/clip/app/quit")

// If you want to control it with patterns
s.boot;
p = ProxySpace.push(s);

(
~clip = Pbind(
	\play, {
		m.sendMsg(
			~addr,
			~clip,
			~command,
			~value);
		// ~addr.post;" ".post;~msg.postln
		[~addr, ~clip, ~command, ~value].postln;
	},
	\dur, 0.15,
	\dest, m,
	\addr, "/loopier/clip/clip",
	\clip, "democlip", // clip name
	\command, "scale",
	\value, Pseq([0.5, 1,2],inf)
);
)

~clip.play;
~clip.stop;
