// Connect to the server
m = NetAddr("localhost", 12345);


// CLIP LIST COMMANDS

// print list of clips to (app's) console
m.sendMsg("/loopier/clip/clips", "listnames");
// clear all clips
m.sendMsg("/loopier/clip/clips", "clearall");
// show names
m.sendMsg("/loopier/clip/clips", "togglenames");
m.sendMsg("/loopier/clip/clips", "shownames");
m.sendMsg("/loopier/clip/clips", "hidenames");

// SINGLE CLIP COMMANDS
// move, scale, reset...
m.sendMsg("/loopier/clip/clip", "default", "reset");
m.sendMsg("/loopier/clip/clip", "default", "scaleup", 0.1);
m.sendMsg("/loopier/clip/clip", "default", "scaledown", 0.05);
m.sendMsg("/loopier/clip/clip", "default", "scale", 2.0.rand);
m.sendMsg("/loopier/clip/clip", "default", "resetscale");
m.sendMsg("/loopier/clip/clip", "default", "togglefullscreen");
// Dimensions of window are normalized.  So moving is always between 0 and 1
m.sendMsg("/loopier/clip/clip", "default", "moveto", 1.0.rand, 1.0.rand);
// play, pause or stop movie
m.sendMsg("/loopier/clip/clip", "default", "play");
m.sendMsg("/loopier/clip/clip", "default", "stop");
m.sendMsg("/loopier/clip/clip", "default", "pause");
// there are 3 kinds of loop
m.sendMsg("/loopier/clip/clip", "default", "loop", "none");
m.sendMsg("/loopier/clip/clip", "default", "loop", "normal");
m.sendMsg("/loopier/clip/clip", "default", "loop", "palindrome");
// change transparency
m.sendMsg("/loopier/clip/clip", "default", "alpha",0.5);

// create a new clip named 'stress'
(
m.sendMsg("/loopier/clip/clip", "stress", "new");
m.sendMsg("/loopier/clip/clip", "stress", "moveto", 1.0.rand, 1.0.rand);
)
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
(
m.sendMsg("/loopier/clip/clip", "mamma", "new");
m.sendMsg("/loopier/clip/clip", "mamma", "moveto", 1.0.rand, 1.0.rand);
m.sendMsg("/loopier/clip/clip", "mamma", "scale", 2.0.rand.postln);
m.sendMsg("/loopier/clip/clip", "mamma", "loop", "palindrome");
)
// fool around with it
(
m.sendMsg("/loopier/clip/clip", "mamma", "moveto", 1.0.rand, 1.0.rand);
m.sendMsg("/loopier/clip/clip", "mamma", "scale", 2.0.rand.postln);
)

// CONSOLE COMMANDS
// print something
m.sendMsg("/loopier/clip/console", "print", "hello world");
// change prompt
m.sendMsg("/loopier/clip/console", "prompt", ">> ");
// set the maximum number of lilnes displayed
m.sendMsg("/loopier/clip/console", "lines", 20);
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
// RGB with alpha -- seems it's not working
// m.sendMsg("/loopier/clip/console", "color", 1, 1, 0, 0.5);

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