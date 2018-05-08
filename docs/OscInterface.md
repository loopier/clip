## Application commands

### Quit

Quit the server application.

```
/loopier/clip/app/quit
```

### Toggle fullscreen

Toggle between FULLSCREEN and WINDOW modes.

```
/loopier/clip/app/fullscreen
```

### Move window

Move window to a new position

```
/loopier/clip/app/move <x:FLOAT> <y:FLOAT>
```

- **x** X coordinate in pixels
- **y** Y coordinate in pixels


### Load command library

Load a clip command file.

```
/loopier/clip/command/loadlibrary <libraryname|path:STRING>
```

- **name | path**   Name of the library.  You can also load a custom file, providing the full **path** to a library file.

The file must be a collection of osc messages in the following format:
  `/address/with/leading/slash[, arg1, arg2, ...]`

Make sure the address has a leading forward slash `/` and that is followed by a comma `,`.
Arguments must be separated by commas `,`.

See any library file as an example.

### List command libraries

Get a list of the command library filenames in the `commands/` folder.

```
/loopier/clip/command/listlibraries
```

**Response** `/loopier/clip/command/librarynames <library1:STRING> <library2:STRING> ...`


## Clip commands

### New clip

Create a new clip

```
/loopier/clip/clip/new <clipname:STRING> [resourcename:STRING]
```

- **clipname** Name of the new clip
- **resourcename** Name of the resource the clip will be using.  If nothing a new emtpy frame clip will be created.

### Replace

*WARNING: Better not use yet.  It will change soon.*

Replace on clip with another clip.  

```
/loopier/clip/clip/replace <clipname:STRING> <resourcename:STRING>
```

- **clipname** Name of the clip.
- **resourcename** Name of the resource the clip will be using


### Replace blob

Places a clip wherever there's a selected blob, resizing the clip to the blobs dimensions.

```
/loopier/clip/clip/replaceblob <clipname:STRING> <resourcename:STRING>
```

- **clipname** Name of the clip.
- **resourcename** Name of the resource the clip will be using.


### Remove clip

Deletes a clip.

```
/loopier/clip/clip/remove <clipname:STRING>
```


### Reset clip

Restores clip's default parameters.

```
/loopier/clip/clip/reset <clipname:STRING>
```


### Select clip

Select a clip by name.

```
/loopier/clip/clip/select <clipname:STRING>
```


### Deselect clip

Deselects the clip.

```
/loopier/clip/clip/deselect <clipname:STRING>
```


### List clip info

Logs and returns the clip parameters.

```
/loopier/clip/clip/listinfo <clipname:STRING>
```

- **Response** `/loopier/clip/clip/info <clipname:STRING> <resourcename:STRING> <isPlaying:BOOL> <speed:FLOAT> <loopType:STRING> <xCoordinate:FLOAT> <yCoordinate:FLOAT> <width:FLOAT> <height:FLOAT> <scale:FLOAT> <red:FLOAT> <green:FLOAT> <blue:FLOAT> <alpha:FLOAT> <depth:FLOAT> <visibility:BOOL> <fullscreen:BOOL> <flipV:BOOL> <flipH:BOOL> <parentName:STRING> <xOffset:FLOAT> <yOffset:FLOAT>`


## Clip's parent commands

### Parent clip

Sets the parent clip.  It will copy parent's position.

```
/loopier/clip/clip/parent <childname:STRING> <parentname:STRING>
```


### Remove parent clip

```
/loopier/clip/clip/removeparent <clipname:STRING>
```


### Offset

Set's an offset relative to parent's position.  Used normalized floats `[0.0-1.0]`.

```
/loopier/clip/clip/offset <x:FLOAT> <y:FLOAT>
```

## Arrange clips

### Depth

Sets the drawing order of the clip.  `0` will be drawn at the top.  Set larger numbers for clips you want to be drawn below other clips.

```
/loopier/clip/clip/depth <clipname:STRING> <depth:INT>
```

### Bring clip to front

Brings clip to frontmost position.  It will be drawn on top of everything else.

```
/loopier/clip/clip/front <clipname:STRING>
```

### Bring clip forward

Rises clip one level in the drawing order.

```
/loopier/clip/clip/forward <clipname:STRING>
```

### Send clip backward

Lowers clip one level in the drawing order.

```
/loopier/clip/clip/backward <clipname:STRING>
```

### Send clip to back

Sends clip to the lowest position in the drawing order.  Will be drawn below everything else -- except the background clip.

```
/loopier/clip/clip/back <clipname:STRING>
```

### Background clip

Set clip as the backround image.  It will be drawn below all other clips.  There can be only one backround clip.

```
/loopier/clip/clip/background <clipname:STRING>
```

### Draw in public screen

Show this clip on the public output.  *NOTE: Clips on the public screen will be also seen on the private screen.  Everything that is on public screen will also be on private screen.*

```
/loopier/clip/clip/public <clipname:STRING>
```

### Draw in private screen

Draw this clip in the private screen ONLY.

```
/loopier/clip/clip/private <clipname:STRING>
```

### TODO: Move to ../app/.. or ../clips/..

```
/loopier/clip/clip/layers
```

## Clip Transformations

### Scale clip up

Make clip larger by a certain amount.  `1.0` will not change anything.  `0.5` is 50%.  `2.0` is 200%.

```
/loopier/clip/clip/scaleup <clipname:STRING> <amount:FLOAT>
```


### Scale clip down

Make clip smaller by a certain amount.  `1.0` will not change anything.  `0.5` is 50%.  `2.0` is 200%.

```
/loopier/clip/clip/scaledown <clipname:STRING> <amount:FLOAT>
```


### Scale clip (Resize)

Change clip's size.  `1.0` will not change anything.  `0.5` will make it 50% smaller.  `2.0` will make it 200% larger.

```
/loopier/clip/clip/scale <clipname:STRING> <amoutn:FLOAT>
```


### Scale X

Scale only the X axis.

```
/loopier/clip/clip/xscale <clipname:STRING> <amount:FLOAT>
```


### Scale y

Scale only the Y axis.

```
/loopier/clip/clip/yscale <clipname:STRING> <amount:FLOAT>
```


### Reset clip's scale
```
/loopier/clip/clip/resetscale <clipname:STRING>
```


### Fullscreen

Resizes clip to occupy the whole screen.

```
/loopier/clip/clip/fullscreen <clipname:STRING>
```

### Flip clip vertically

```
/loopier/clip/clip/flipv  <clipname:STRING>
```

### Flip clip horizontally

```
/loopier/clip/clip/fliph  <clipname:STRING>
```

### Toggle visibility

```
/loopier/clip/clip/togglevisibility  <clipname:STRING>
```

### Show clip
```
/loopier/clip/clip/show  <clipname:STRING>
```

### Hide clip
```
/loopier/clip/clip/hide  <clipname:STRING>
```

## FX

### Mask

Set one clip as the mask of another clip.

```
/loopier/clip/clip/mask  <clipname:STRING> <maskname:STRING>
```

### Mask on

Truns mask on.

```
/loopier/clip/clip/maskon  <clipname:STRING>
```

### Mask off

Turns mask off, but keeps it.

```
/loopier/clip/clip/maskoff  <clipname:STRING>
```

### Play clip

Tells a clip to do it's thing.

```
/loopier/clip/clip/play  <clipname:STRING>
```

## Stop clip

Stops clip and goes back to the first frame.

```
/loopier/clip/clip/stop  <clipname:STRING>
```

## Pause clip

Pauses clip at the current frame.

```
/loopier/clip/clip/pause  <clipname:STRING>
```

## Loop type

Set clip's loop type.

```
/loopier/clip/clip/loop  <clipname:STRING> <looptype:STRING>
```

- **normal:** When it reaches the last frame, play again from first frame.
- **palindrome:** When it reaches the last frame, play backwards.  Play forward again when reaching first frame.
- **once:** Stop when reaching last frame.

## Play direction

Play forwards or backwards.

```
/loopier/clip/clip/playdirection  <clipname:STRING> <direction:STRING>
```

- **normal:** Play clip forwards.
- **reverse:** Play clip backwards.

## Speed

Set the playing speed of the clip.  `1.0` is normal speed.  `2.0` for double speed. `0.5` for half speed.

```
/loopier/clip/clip/speed  <clipname:STRING> <speed:FLOAT>
```

## Edit clip frames

This might only work with `frame` clips.

### Add frame

Add frame to the end.

```
/loopier/clip/clip/addframe  <clipname:STRING> <sourceclipname:STRING>
```

- **clipname:** Name of the clip.
- **sourceclipname:** Name of the clip that provides the frames (usually a camera clip).

### Insert frame

Add a frame at the current position.

```
/loopier/clip/clip/insertframe  <clipname:STRING> <sourceclipname:STRING>
```
See `Add frame` for parameters.

### Remove frame

Remove current frame.

```
/loopier/clip/clip/removeframe  <clipname:STRING>
```

### Clear frames

Delete all frames.  Empty clip.

```
/loopier/clip/clip/clearframes  <clipname:STRING>
```

### Save frames

Save clip frames to disk.  Should create a new folder with the clip's name under `resources/frames/`.

```
/loopier/clip/clip/saveframes  <clipname:STRING>
```

### Load frames

Load frames to clip.

```
/loopier/clip/clip/loadframes  <clipname:STRING> <resourcename:STRING>
```

### First frame

Go to first frame of the clip.

```
/loopier/clip/clip/firstframe  <clipname:STRING>
```

### Next frame

Advance one frame only.

```
/loopier/clip/clip/nextframe  <clipname:STRING>
```

### Previous frame

Move one frame backwards.

```
/loopier/clip/clip/previousframe  <clipname:STRING>
```

### Last frame

Go to last frame of the clip.

```
/loopier/clip/clip/lastframe  <clipname:STRING>
```

### Go to frame #

Go to a specific frame of the clip.

```
/loopier/clip/clip/gotoframe  <clipname:STRING> <frameNumber:INT>
```

### Save

Save clip to disk.

```
/loopier/clip/clip/save  <clipname:STRING>
```

## Move clip

Move clip to a position.  Use normalized `[0.0-1.0]` coordinates, where `x:0.0 y:0.0` is top left corner of the screen and `x:1.0 y:1.0` is the bottom right.

```
/loopier/clip/clip/moveto  <clipname:STRING> <x:FLOAT> <y:FLOAT>
```

### Center clip

Put clip in the center of the screen.

```
/loopier/clip/clip/center  <clipname:STRING>
```

### Clip color

Set the color of the clip.  Tint it.

```
/loopier/clip/clip/color  <clipname:STRING> <grayscale:FLOAT>
```

```
/loopier/clip/clip/color  <clipname:STRING> <grayscale:FLOAT> <alpha:FLOAT>
```

```
/loopier/clip/clip/color  <clipname:STRING> <red:FLOAT> <green:FLOAT> <blue:FLOAT>
```

```
/loopier/clip/clip/color  <clipname:STRING> <red:FLOAT> <green:FLOAT> <blue:FLOAT> <alpha:FLOAT>
```

### Alpha

Set the transparency of the clip.  Use normalized values `[0.0-1.0]` where `0.0` is absolute transparency and `1.0`
is absolute opacity.

```
/loopier/clip/clip/alpha  <clipname:STRING>  <alpha:FLOAT>
```


## Clip collection commands


### Load library

Load many clips all at once.

```
/loopier/clip/clips/loadlibrary  <libraryname:STRING>
```

### Clear all

Delete all clips at once.

```
/loopier/clip/clips/clearall
```

### List clip names

Get (and log) the list of available clip.

```
/loopier/clip/clips/listnames
```

**Response** `/loopier/clip/clips/clipnames <clipname1:STRING> <clipname2:STRING> ...`

### listresources

Get (and log) the list of available resources.

```
/loopier/clip/clips/listresources
```

**Response** `/loopier/clip/clips/resourcenames <resourcename1:STRING> <resourcename2:STRING> ...`


### listlibraries



```
/loopier/clip/clips/listlibraries
```

### listcameras



```
/loopier/clip/clips/listcameras
```

### togglenames



```
/loopier/clip/clips/togglenames
```

### shownames



```
/loopier/clip/clips/shownames
```

### hidenames



```
/loopier/clip/clips/hidenames
```


## Syphon

```
/loopier/clip/syphon/servername
```


## CV commands

```
/loopier/clip/cv/setinput
```


```
/loopier/clip/cv/color
```


```
/loopier/clip/cv/threshold
```


```
/loopier/clip/cv/minArea
```


```
/loopier/clip/cv/maxArea
```


```
/loopier/clip/cv/holes
```


```
/loopier/clip/cv/toggle
```


```
/loopier/clip/cv/show
```


```
/loopier/clip/cv/hide
```


```
/loopier/clip/cv/detectionarea
```


```
/loopier/clip/cv/maxblobs
```


```
/loopier/clip/cv/select
```


```
/loopier/clip/cv/deselect
```


```
/loopier/clip/cv/selectall
```


```
/loopier/clip/cv/deselectall
```


```
/loopier/clip/cv/first
```


```
/loopier/clip/cv/next
```


```
/loopier/clip/cv/previous
```


```
/loopier/clip/cv/last
```


## Console commands

```
/loopier/clip/console/color
```


```
/loopier/clip/console/alpha
```


```
/loopier/clip/console/prompt
```


```
/loopier/clip/console/print
```


```
/loopier/clip/console/lines
```


```
/loopier/clip/console/toggle
```


```
/loopier/clip/console/show
```


```
/loopier/clip/console/hide
```


```
/loopier/clip/console/moveto
```


```
/loopier/clip/console/font
```


```
/loopier/clip/console/fontsize
```



```
/loopier/uvc/add
```


```
/loopier/uvc/use
```


```
/loopier/uvc/autoexposure
```


```
/loopier/uvc/exposure
```


```
/loopier/uvc/autofocus
```


```
/loopier/uvc/focus
```


```
/loopier/uvc/autowhitebalance
```


```
/loopier/uvc/whitebalance
```


```
/loopier/uvc/gain
```


```
/loopier/uvc/brightness
```


```
/loopier/uvc/contrast
```


```
/loopier/uvc/saturation
```


```
/loopier/uvc/sharpness
```
