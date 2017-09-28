project('wkjscore', 'c')
api_version = '0.1'

# Need better versioning maybe
lib_version = '0.1.0'
so_version = '0'

sources = ['wkjscoreresult.c']
headers = ['wkjscoreresult.h']

deps = [dependency('gobject-2.0'), dependency('webkit2gtk-4.0')]

api_path = '@0@-@1@'.format(meson.project_name(), api_version)
libwkjscore = library(api_path,
                      sources: ['wkjscoreresult.c'],
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

test_deps = [dependency('gtk+-3.0'), dependency('webkit2gtk-4.0')]
test_string = executable('test-string-result-' + api_path,
                         ['testbase.h', 'testbase.c','teststring.c'],
                         dependencies: test_deps,
                         link_with: libwkjscore)
test_int = executable('test-int-result-' + api_path,
                      ['testbase.h', 'testbase.c', 'testinteger.c'],
                      dependencies: test_deps,
                      link_with: libwkjscore)
test('Test string retrieval', test_string, is_parallel: false)
test('Test integer retrieval', test_int, is_parallel: false)
