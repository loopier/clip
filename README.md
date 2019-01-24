# README

CLIP is a live-animation application.  

It's a tool that provides some means to perform and improvise with animations and videos on stage.  Some of its features are:
- Create animations on the spot and reproduce them in realtime.
- Launch videos.
- Modify playing speed, animation or movie size, color, position, ...
- Use clips to mask other clips.
- Load and save animations.
- Communicate with the app via OSC.
- Define custom keymaps for controlling the app from a keyboard.
- Bundle behaviours in script files.

## Developers

See README-DEV.md

## Installation

## Usage

### Creating a clip

All clips use resources, usually movies or images.  When creating a new clip you can choose which resource it will use by specifying the resource name.  If no resource is provided, a new empty clip will be created.  This empty clip can be used to create a new animation (see below).

### Creating animations

There are different ways to create animations.  Following is a description of how we suggest to do it.

Create an empty clip.

Create a new camera clip.  

Set the camera clip as input to the computer visione engine.

Select a blob or group of blobs, or an area in the screen.

Add new frames to the new clip, from the camera input the camera.

Save frames to disk.

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
