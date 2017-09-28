sources = ['wkjscoreresult.c']
headers = ['wkjscoreresult.h']

deps = [dependency('gobject-2.0'), dependency('webkit2gtk-4.0')]

api_path = '@0@-@1@'.format(meson.project_name(), api_version)
libwkjscore = library(api_path,
                      sources: sources,
                      dependencies: deps,
                      version: lib_version,
                      soversion: so_version,
                      install: true)

gir_includes = ['GObject-2.0', 'WebKit2-4.0', 'JavaScriptCore-4.0']
gnome = import('gnome')
wkjscore_gir = gnome.generate_gir(libwkjscore,
                                  sources: headers + sources,
                                  namespace: 'WkJsCore',
                                  nsversion: api_version,
                                  dependencies: deps,
                                  includes: gir_includes,
                                  install: true,
                                  extra_args: '--warn-all')
