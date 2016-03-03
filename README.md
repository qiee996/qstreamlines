![Alt text](examples/img/qstreamlines_lines.png?raw=true "Example1")
![Alt text](examples/img/qstreamlines_points.png?raw=true "Example2")
![Alt text](examples/img/qstreamlines_arrows.png?raw=true "Example3")
![Alt text](examples/img/qstreamlines_test_points.png?raw=true "Example4")
![Alt text](examples/img/qstreamlines_test_caps.png?raw=true "Example5")

## Overview
Realtime render, tune and export 2D streamlines animation for a two component vector field.

## Features
* Colormap.
* Lookup table to scale speed.
* Points, lines, caps, arrows.
* Background image with alpha channel.
* Export PNG sequence with alpha channel.

## Example

Export images to /tmp for example dataset animation.

    $ ./qstreamlines --output /tmp/swirl. examples/swirl.json

## Building

	$ cd src && make app

## License
qstreamlines Copyright (C) 2016 Remik Ziemlinski GPLv3

This program comes with ABSOLUTELY NO WARRANTY.
This is free software, and you are welcome to redistribute it under the conditions of the GPLv3 license.
