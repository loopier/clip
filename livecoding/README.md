# ClipLang

An python environment to live code video with Clip server.

ClipLang is just Python with some extra functions.  It's optimal when used with Hydrogen on Atom.  But I guess you could also use it just with *IPython*.

## Installation

Install Atom.

Install Hydrogen and Hydrodgen-Python packages.

Create a new file.

Add `from cliplang.cliplang import *` to the top and execute with `Cmd-Enter`

Type `boot()` and execute.

You should be all set.

## Usage


**`commands()`** To view all available commands.

**`commands("clip")`** To view a list of clip commads.

**`foo = Clip("foo")`** To create a new clip instance named ***foo***.

**`foo.new()`** To add the clip to the stage.  If there's a resource named *foo* in the resource folder, it will use that.  If there isn't it will create a new empty animation clip.

**`foo.[command]([parameters])`** Tell **foo** to do something.  *[command]* should be substituted by any of the commands in the *clip* commands list.  For a list of possible commands see *commands("clip")*.  For closer details of each command see Clip server's documentation.
