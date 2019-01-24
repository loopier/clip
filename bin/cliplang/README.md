# ClipLang

A live coding language for ClipServer.

## Installation

//

## Usage

### Starting a new session

Type the following command:

`python cliplang.py`

Or, if you'd like to lower the log level to DEBUG, type:

`python cliplang.py -d`

If you don't want to boot the server automatically, you may type:

`python cliplang.py -b`

You can combine both like this:

`python cliplang.py -d -b`

<!-- ### Creating a new language -->

### Commands

There are two types of commands:

- ClipLang commands
- ClipServer commands

##### ClipLang Commands

To see a list of available commands type `help`.

If you want further information on a specific command, type `help <command>`.

##### ClipServer Commands

These commands ar to communicate with the server.  Their basic syntax must follow this format:

`<action> [<target>] [parameters]`

Where `action` is imperative, `target` may or may not be used depending on the command, and `parameters` are optional.

To see a list of available commands just type `commands`.  
