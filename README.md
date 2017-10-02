# WkJsCoreResult for WebKitGTK+

This is a small library attempting to wrap the extraction of meaningful
value from a `WebKitJavascriptResult` object into a facade. Primarily, this
is meant to be used by language bindings and that is why the build script also
generates `GIR` and `typelib` files (along with the library) and installs them
in relavant directories.


## Installation

To build the library and introspectable API you will need
[meson build system](http://mesonbuild.com/Getting-meson.html) which itself
depends on [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).
Other obvious requirements would be __WebKitGTK+-4.0__ and __GObject-2.0__.
Having all that, we can clone, build and install the library with:

```
git clone https://github.com/saifulbkhan/wkjscore-result.git
cd wkjscore-result
meson build
ninja -C build install
```

You can add a `--prefix=cutom/path` option next to `meson build` to change the
installation prefix (perhaps something like: `meson build --prefix=$HOME/.local`
to avoid root installation, if you are just trying out the library). But you
will need to export library and typelib paths so that `libgirepository` can find
the installed files. Essentially you might need to do something like:

```
export LD_LIBRARY_PATH=LD_LIBRARY_PATH:$HOME/.local/lib64
export GI_TYPELIB_PATH=GI_TYPELIB_PATH:$HOME/.local/lib64/girepository-1.0
```

Replace the paths with your own custom installation paths. This is supposed to
be temporary and if you want to preserve this over every user session put the
above exports in your .bashrc or .zshrc. Bear in mind that some people consider
setting `LD_LIBRARY_PATH` to be harmful, so navigate around this accordingly.

To uninstall the library simply perform:

```
ninja -C build uninstall
```

This is assuming you still have the `/build` dir in your cloned repo, which you
may not have and that is why I need to write an uninstallation script or
distribute this as a package (cannot guarantee this happening anytime soon).


## Usage

Using the library is easy enough once you have a webkit webview setup in your
code. Here's a demonstration in python:

```python
import gi
gi.require_version('WkJsCore', '0.1')
from gi.repository import WkJsCore

def js_finished_callback(webview, result, user_data):
    js_result = webview.run_javascript_finish(result)
    result_proxy = WkJsCore.Result.new(js_result)
    # result_proxy can process the result as either boolean,
    # number or string. It can also create a JSON string for
    # 'stringifiable' JS objects.
    print(result_proxy.process_result_as_number())

# Assuming webview is already setup
webview.run_javascript('5 / 2', None, js_finished_callback, None)
# 2.5 is printed to stdout
```

This project needs some documentation but reading the source or even just
the doc comments in [wkjscoreresult.h](https://github.com/saifulbkhan/wkjscore-result/blob/master/src/wkjscoreresult.h)
should give you a fair idea what its capable of.


## Testing

To run unit tests build and test with:

```
meson build
ninja -C build test
```

If you make any modifications to the code, please run the tests and see to it
that they pass. Note: Close the gtk windows that spawn during the tests to
move on to the next test. I intend to find a way to close them automatically
after a certain time lapse.


## Contributing
Issue reports and pull requests are welcome. This library is far from ideal,
even when you don't count the hideous name. Any form of help is welcome! :)
