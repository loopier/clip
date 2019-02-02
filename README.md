# README

CLIP is a live-animation application.  

It's a tool that provides some means to perform and improvise with animations and videos on stage.  Some of its features are:
- Create animations on the spot and reproduce them in realtime.
- Launch videos.
- Modify playing speed, animation or movie size, color, position, ...
- Use clips to mask other clips.
- Load and save animations.
- Communicate with the app via OSC.
- Define custom keymaps to control the app from a keyboard.
- Bundle behaviours in script files.

## Developers

See README-DEV.md

## Installation

## Usage

### Creating a clip



### Creating animations

There are different ways to create animations.  Here's one:

Create an empty clip named `palitus`.

`/loopier/clip/clip/new palitus`

Before adding frames to it, we need some kind of source to get new images.
We'll be using a camera.  To see what cameras are available to you:

`/loopier/clip/listcameras`

In the log you may find something like this:

```
[notice ] Number of cameras players loaded: 2
[notice ] 	cam0: Built-in iSight
[notice ] 	cam1: HD Pro Webcam C920
[notice ] Sent OSC:	/loopier/clip/cameranames 	s:cam0	s:cam1
[notice ] OSC:	/loopier/clip/listcameras
```

This is my ouptut, yours will be different depending on what divices are plugged into your system.  For me, there are two cameras.  

`cam0` and `cam1` are the names of the cameras in the application.
`Built-in iSight` and `HD Pro Webcam C920` are the real device names, so you know
which one's which.

Create a new camera clip with the device of your choice.  I'll be using `cam1`.

`/loopier/clip/clip/new cam cam1`

`cam` is the name of the clip, just like we did  with `paliuts` above.
`cam1` is the resource the clip is using.  Since we didn't provide a resource
for `palitus`, the app is creating an empty *Frame* clip.  Frame clips are
clips that play image sequences, animations.  More on this later.

Now you should see the camera.

To make things more interesting, we'll be using computer vision to mask the camera.
For that, we need another clip named `cv` that will be managing all that.

`/loopier/clip/clip/new cv`

`cv` is a *reserved word*.  Any time you create a clip with that name it will create a computer vision clip.  But I don't know why you'd want more than one.

Set the camera clip `cam` as input to the computer vision clip `cv`.

`/loopier/clip/cv/setinput cam`

To see only what we will be adding as frame, mask the camera clip with the cv's blobs:

`/loopier/clip/clip/mask cam cv`

If the CV lines bother you, hide them.

`/loopier/clip/clip/hide cv`

Select all the blobs.

`/loopier/clip/cv/selectall`

Add a new frame to `palitus` using the image from `cam`.

`/loopier/clip/clip/addframe palitus cam`

Repeat this last step as many times as you wish.

When you're done, hide `cam` to admire your work of art.

`/loopier/clip/clip/hide cam`

### Camera input
### Computer vision
### Saving animations to disk
### Loading animations from disk
### Loading movies from disk
### Modifying existing clips

### OSC interface
The application is divided into two apps: a server and a client.  They communicate via OSC messages.  The server is the actual Clip software that manages images and videos.  The client may be a GUI, ClipLang live coding language, or any application or device that can send OSC messages.
#### Setup
#### Sending commands
#### Receiving messages
### GUI
### Scripts
#### Syntax
### Keymaps
#### Syntax
### ClipLang
ClipLang is just a Python module that can be used to live-code interacting with Clip server.
