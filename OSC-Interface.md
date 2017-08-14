Clip OSC Interface
=======================
<!--
Notes:
------

- `<argName:TYPE>` is a required argument.
- `[argName:TYPE]` is an optional argument.
- `...` means the previous argument (or group of arguments) is optionally
  repeated; used when sending lists.
- For BOOLEAN types, you can send arguments as strings (`"false"`, `"true"` or
  `"0"`, `"1"`) or numbers (`0`, `1`).
- For NUMBER types, you can send arguments as strings (`"37.2"`, `"-5"`) or
  numbers (`3.14159`, `-2`).
-->

Clip list commands
------------------


#### Create a clip
  > `/loopier/clip/clip "clipname" "new" "moviename"` - If no movie name is provided, it will get the default.


#### Print list of clips to (app's) console

  > `/loopier/clip/clip "listnames"`


#### Clear all clips
  > `/loopier/clip/clip "clearall"`


#### Show names
  > `/loopier/clip/clip "togglenames"`

  > `/loopier/clip/clip "shownames"`

  > `/loopier/clip/clip "hidenames"`


Single clip commands
--------------------
---
### Playback

#### Play, pause or stop movie
  > `/loopier/clip/clip "exampleclip" "play"`

  > `/loopier/clip/clip "exampleclip" "stop"`

  > `/loopier/clip/clip "exampleclip" "pause"`


#### Loop (3 modes)
  > `/loopier/clip/clip "exampleclip" "loop" "none"` - stops at the end of the movie.

  > `/loopier/clip/clip "exampleclip" "loop" "normal"` - starts over and over again.

  > `/loopier/clip/clip "exampleclip" "loop" "palindrome"` - bounces back and forth from beginning to end and back to the beginning.


#### Speed
  > `/loopier/clip/clip "exampleclip" "speed" 2.0` - with `1.0` being normal speed.  Any negative value will play the movie backwards.

---
### Reset

#### Reset
  > `/loopier/clip/clip "exampleclip", "reset"`

---
### Size

#### Scale to any size
  > `/loopier/clip/clip "exampleclip", "scale", 2.0.rand` - with `1.0` being default size.  You can try negative values for fun.


#### Increase size by a given amount
  > `/loopier/clip/clip "exampleclip", "scaleup", 0.1`


#### Decrease size by a given amount
  > `/loopier/clip/clip "exampleclip", "scaledown", 0.05`


#### Stretch and squash
  > `/loopier/clip/clip "exampleclip", "xscale", 0.5`

  > `/loopier/clip/clip "exampleclip", "yscale", 3`


#### Back to normal dimensions
  > `/loopier/clip/clip "exampleclip", "resetscale"`

---
### Visibility

#### Vertical flip
  > `/loopier/clip/clip "exampleclip", "vflip"`


#### Horizontal flip
  > `/loopier/clip/clip "exampleclip", "hflip"`


#### Fullscreen (toggle)
  > `/loopier/clip/clip "exampleclip", "fullscreen"`


#### Visibility
  > `/loopier/clip/clip "exampleclip", "togglevisibility"`

  > `/loopier/clip/clip "exampleclip", "show"`

  > `/loopier/clip/clip "exampleclip", "hide"`


#### Move to a position (normalized)

  > `/loopier/clip/clip "exampleclip", "moveto", 1.0.rand, 1.0.rand` - Window max size is `1.0`


#### Change transparency

  > `/loopier/clip/clip "exampleclip", "alpha", 0.5` with `1.0` being opaque, and `0.0` invisible.


Managing the movies one single clip can play
--------------------------------------------

A ***clip*** stores a list of movies it can play.  Use these commands to manage the movies.

---

#### Add a movie to the clip
You need to provide the name of an existing movie.  There's a command to get a list of all available movies.
  > `/loopier/clip/clip "exampleclip", "addmovie", "mamma"`


#### List the movies in the clip
  > `/loopier/clip/clip "exampleclip", "listmovies"`


#### Play a movie
  > `/loopier/clip/clip "exampleclip", "setmovie", 1`

  The index of the movie in the clip's movie list.  First movie is index `0`.


#### Sequence
  > `/loopier/clip/clip "exampleclip", "sequence", "0,1,2"`

  Play all the movies in the clip in a given order.

  Pass a list of numbers (indexes of movies in the clip) indicating the order in which you want to play the movies. They can be repeated any number of times and can be in any order.
  For example:

  - `"0,1,2"` will play 3 clips in order.

  - `"1, 0, 0, 3"` will play the second movie, then two times the first one, and then the fourth one, in sequence



Console commands
----------------



#### Print a Messages
  > `/loopier/clip/console "print", "hello world"`


#### Change prompt
The prompt is the text and/or symbols displayed before the message itself.
  > `/loopier/clip/console "prompt", ">> "`


#### Number of lines
Sets the maximum number of lines dislpayed.
  > `/loopier/clip/console "lines", 20`


#### Show or hide console
  > `/loopier/clip/console "toggle"`

  > `/loopier/clip/console "show"`

  > `/loopier/clip/console "hide"`


#### Grayscale
  > `/loopier/clip/console "color", 0.75`

  Normalized values ( `0.0` - `1.0` )


#### Grayscale with alpha
  > `/loopier/clip/console "color", 1, 0.5`

  Normalized values ( `0.0` - `1.0` )


#### RGB
  > `/loopier/clip/console "color" 1 0.5 0`

  Normalized values ( `0.0` - `1.0` )


Application commands
--------------------


#### Toggle fullscreen
  > `/loopier/clip "fullscreen"`


#### Move the application window`
  > `/loopier/clip "move" 1.0`


#### Quit
  > `/loopier/clip "quit"`
