# WkJsCoreResult for WebKitGTK+

This is a small library attempting to wrap the extraction of meaningful
value from a `WebKitJavascriptResult` object into a facade API. Primarily, this
is meant to be used by language bindings and that is why the build script also
generates `GIR` and `typelib` files (along with the library) and installs them
in relavant directories.
